#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  ATOM,
};

//Tap Dance Declarations
enum tap_dance_keycodes {
  TD_SHIFT_SPACE = 0,
  TD_GRV_ESC,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define TD_SPC TD(TD_SHIFT_SPACE)
#define TD_GRV TD(TD_GRV_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  `   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctrl  | Alt  | GUI  |Lower |Lower |Space |Space | Left | Up   | Down |Right |Adjust|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  TD_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_RSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
  KC_LCTL, KC_LGUI, KC_LALT, ATOM,    LOWER,   TD_SPC,  KC_SPC,  KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, ADJUST \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |   -  |   =  |      |      |   [  |   ]  |      |      |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, XXXXXXX, XXXXXXX, KC_EQL,  KC_MINS, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, _______, KC_BSLS, \
  _______, XXXXXXX, XXXXXXX, KC_PLUS, KC_UNDS, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |  F1  | F2   | F3   |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |  _   |   +  |      |      |      |  {   |    } |      |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  | Prev |Volu  | Vold |Next  |             |Home  |PgUp  | PgDn |End   |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, _______, _______, KC_UNDS, KC_PLUS, _______, _______, KC_LCBR, KC_RCBR, _______, _______, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_DEL,  KC_MPRV, KC_VOLU, KC_VOLD, KC_MNXT, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______  \
)

};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_SHIFT_SPACE]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_SPC),
  [TD_GRV_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
// Other declarations would go here, separated by commas, if you have them
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case ATOM:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("P"));
      }
      return false;
      break;
  }
  return true;
}
