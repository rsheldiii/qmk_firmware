#include QMK_KEYBOARD_H
#include "quantum.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _FN,
    _ADJ
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_MS_BTN1,                                                                                                 RALT(KC_F4),
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_BSPC,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        MO(_FN),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_ENT,
        MO(_ADJ),  RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,KC_SPC, KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT,RGB_MOD
    ),

    [_FN] = LAYOUT(
        _______,                                                                                                    _______,
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______,_______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_EQL,  KC_MINS, _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,
        _______, _______, _______, KC_EQL,  KC_MINS, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______
    ),

    [_ADJ] = LAYOUT(
        _______,                                                                                                   _______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_PSCR,
        _______, RGB_SAD, RGB_VAI, RGB_SAI, RESET,   _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
        _______, RGB_HUD, RGB_VAD, RGB_HUI, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,
        _______, RGB_SPD, _______, RGB_SPI, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______,
        _______, _______, _______, RGB_MOD, _______, _______, _______, KC_P0,   KC_PDOT, KC_NLCK, _______, _______
    )
};

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("RGBKB Pan\n"), false);
    oled_write_P(PSTR("Layer: "), false);
    uint8_t layer = layer_state ? biton(layer_state) : biton32(default_layer_state);
    switch (layer) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            //oled_write_ln_P(PSTR("Undefined"), false);
    }
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("Numlock On\n") : PSTR("           \n"), false);
    oled_write_P(led_state.caps_lock ? PSTR("Capslock On \n") : PSTR("           \n"), false);
}
#endif

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {         // First encoder - right
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) {  // Second encoder - left
    if (clockwise) {
      tap_code(KC_MS_WH_DOWN);
      // unregister_code(KC_MS_WH_DOWN);
    } else {
      tap_code(KC_MS_WH_UP);
      // unregister_code(KC_MS_WH_UP);
    }
  }
}
