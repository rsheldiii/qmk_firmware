#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )


#include "matrix.h"
#include "gpio.h"
#include "print.h"
#include "i2c_master.h"
#include "debug.h"
#include "timer.h"

#define I2C_MAX_ADDRESSES 127
#define I2C_STARTUP_DELAY_MS 0
#define I2C_STATUS_INTERVAL_MS 5000

static bool addresses[I2C_MAX_ADDRESSES] = {false};
static bool i2c_ready = false;
static uint32_t i2c_init_time = 0;
static bool key_state[I2C_MAX_ADDRESSES] = {false};
static uint32_t last_status_print = 0;

// Prints every known i2c address and its current pressed/released state,
// pulled from the state the scan loop already tracks. Read-only, so it
// doesn't touch scan timing.
void print_i2c_status(void) {
    dprintf("-- i2c status --\n");
    for (uint16_t address = 1; address < I2C_MAX_ADDRESSES; address++) {
        if (addresses[address]) {
            dprintf("  %u: %s\n", address, key_state[address] ? "DOWN" : "UP");
        }
    }
}

void do_scan(void) {
    uint8_t nDevices = 0;

    dprintf("Scanning...\n");

    for (uint16_t address = 1; address < I2C_MAX_ADDRESSES; address++) {
        // The i2c_scanner uses the return value of
        // i2c_ping_address to see if a device did acknowledge to the address.
        i2c_status_t error = i2c_ping_address(address << 1, 250);
        if (error == I2C_STATUS_SUCCESS) {
            addresses[address] = true;
            dprintf("  I2C device found at address 0x%02X\n", address);
            nDevices++;
        } else if (error == I2C_STATUS_ERROR) {
            dprintf("  Unknown error (%u) at address 0x%02X\n", error, address);
        } else {
            dprintf("  Unknown error (%u) at address 0x%02X\n", error, address);
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
    i2c_init_time = timer_read32();
    print("inited lol");
    // TODO: initialize hardware here
}

static uint16_t scan_now = 0;

// bool matrix_scan_custom(matrix_row_t current_matrix[]) {
//     // dprintf("%lx\n", current_matrix[0]);
//     matrix_row_t current_row_value = 0;

//     bool matrix_has_changed = false;

//     if (scan_now == 0) {
//         do_scan();
//     }
//     scan_now++;

//     for (uint8_t address = 0; address < I2C_MAX_ADDRESSES; address++) {
//         if (addresses[address]) {
//             // i2c_start(address << 1, 50);
//             uint8_t data;
//             i2c_status_t receive_status = i2c_receive(address << 1, &data, 1, 50);

//             if (receive_status == I2C_STATUS_SUCCESS && data > 0) {
//                 current_row_value |= MATRIX_ROW_SHIFTER << address;
//                 matrix_has_changed = true;
//                 // print("you pressin a button, bitch?");
//             }
//         }
//     }

//     current_matrix[1] = current_row_value;

//     // print("scan,");

//     // TODO: add matrix scanning routine here

//     return matrix_has_changed;
// }


static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    uint8_t address_offset = current_row * MATRIX_COLS;

    for (uint8_t column = 0; column < MATRIX_COLS; column++) {
        uint8_t address = address_offset + column;

        if (addresses[address]) {
            // i2c_start(address << 1, 50);
            uint8_t data = 0;
            i2c_status_t receive_status = i2c_receive(address << 1, &data, 1, 50);

            bool pressed = (receive_status == I2C_STATUS_SUCCESS && data > 0);
            if (pressed != key_state[address]) {
                dprintf("  %u: %s\n", address, pressed ? "DOWN" : "UP");
            }
            key_state[address] = pressed;
            if (pressed) {
                current_matrix[current_row] |= MATRIX_ROW_SHIFTER << column;
            }
        }
    }

    // current_matrix[1] = current_row_value;

    // print("scan,");

    // TODO: add matrix scanning routine here

    // return matrix_has_changed;

    return (last_row_value != current_matrix[current_row]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // Wait after initialization before attempting I2C communications to avoid brown start
    if (!i2c_ready) {
        if (timer_elapsed32(i2c_init_time) >= I2C_STARTUP_DELAY_MS) {
            i2c_ready = true;
            dprintf("I2C ready after %ums\n", I2C_STARTUP_DELAY_MS);
        } else {
            return false;
        }
    }

    // print("matrix scan...\n");
    // scan for new devices
    if (scan_now == 0) {
        do_scan();
    }
    scan_now++;

    bool matrix_has_changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_has_changed |= read_cols_on_row(current_matrix, current_row);
    }

    // Periodic status pulse - does not affect scan frequency, just reports
    // the state the scan above already gathered.
    if (timer_elapsed32(last_status_print) >= I2C_STATUS_INTERVAL_MS) {
        print_i2c_status();
        last_status_print = timer_read32();
    }

    return matrix_has_changed;
}
