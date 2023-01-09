#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )


#include "matrix.h"
#include "gpio.h"
#include "print.h"
#include "i2c_master.h"
#include "debug.h"

#define I2C_MAX_ADDRESSES 127

static bool addresses[I2C_MAX_ADDRESSES] = {false};
// static bool keystate[I2C_MAX_ADDRESSES] = {false};

// TODO: remove patch
#ifdef PROTOCOL_CHIBIOS
#    pragma message("ChibiOS is currently 'best effort' and might not report accurate results")

i2c_status_t i2c_start_bodge(uint8_t address, uint16_t timeout) {
    i2c_start(address);

    // except on ChibiOS where the only way is do do "something"
    uint8_t data = 0;
    return i2c_readReg(address, 0, &data, sizeof(data), timeout);
}

#    define i2c_start i2c_start_bodge
#endif

void do_scan(void) {
    uint8_t nDevices = 0;

    dprintf("Scanning...\n");

    for (uint8_t address = 1; address < I2C_MAX_ADDRESSES; address++) {
        // The i2c_scanner uses the return value of
        // i2c_start to see if a device did acknowledge to the address.
        i2c_status_t error = i2c_start(address << 1, 50);
        if (error == I2C_STATUS_SUCCESS) {
            addresses[address] = true;
            i2c_stop();
            dprintf("  I2C device found at address 0x%02X\n", address);
            nDevices++;
        } else if (error == I2C_STATUS_ERROR) {
            // dprintf("  Unknown error (%u) at address 0x%02X\n", error, address);
        } else {
            // dprintf("  Unknown error (%u) at address 0x%02X\n", error, address);
        }
    }

    if (nDevices == 0) {
        dprintf("No I2C devices found\n");
    } else {
        dprintf("done\n");
    }
}

void matrix_init_custom(void) {
    
    print("init matrix");
    i2c_init();
    print("inited lol");
    // TODO: initialize hardware here
}

static uint16_t scan_now = 0;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // dprintf("%lx\n", current_matrix[0]);
    matrix_row_t current_row_value = 0;

    bool matrix_has_changed = false;

    if (scan_now == 0) {
        do_scan();
    }
    scan_now++;

    for (uint8_t address = 0; address < I2C_MAX_ADDRESSES; address++) {
        if (addresses[address]) {
            // i2c_start(address << 1, 50);
            uint8_t data;
            i2c_status_t receive_status = i2c_receive(address << 1, &data, 1, 50);

            if (receive_status == I2C_STATUS_SUCCESS && data > 0) {
                current_row_value |= MATRIX_ROW_SHIFTER << address;
                matrix_has_changed = true;
                // print("you pressin a button, bitch?");
            }
        }
    }

    current_matrix[1] = current_row_value;

    // print("scan,");

    // TODO: add matrix scanning routine here

    return matrix_has_changed;
}