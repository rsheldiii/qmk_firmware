/* Copyright 2017 Brian Fong
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "gherkin.h"

enum {
  TD_QUOT_SCLN = 0,
  TD_KC_LSFT_CAPS,
  TD_KC_RSFT_CAPS
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
};

const uint16_t PROGMEM bspc_combo[] = {KC_O,      KC_P, COMBO_END};
const uint16_t PROGMEM ent_combo[]  = {KC_L,   KC_SCLN, COMBO_END};
const uint16_t PROGMEM tab_combo[]  = {KC_A,      KC_S, COMBO_END};
const uint16_t PROGMEM esc_combo[]  = {KC_Q,      KC_W, COMBO_END};
const uint16_t PROGMEM rsft_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM lsft_combo[] = {KC_Z,      KC_X, COMBO_END};

combo_t key_combos[] = {
  COMBO(bspc_combo, KC_BSPC),
  COMBO(ent_combo,  KC_ENT),
  COMBO(tab_combo,  KC_TAB),
  COMBO(esc_combo,  KC_ESC),
};

#define LX LT(_LOWER, KC_X)
#define SZ LSFT_T(KC_Z)
#define CC RCTL_T(KC_C)
#define SS RSFT_T(KC_SLSH)
#define TQS TD(TD_QUOT_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* Qwerty
 * .-----------------------------------------------------------------------------------------.
 * | Q//ESC | W      | E      | R      | T      | Y      | U      | I      | O      | P      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | A      | S      | D      | F      | G      | H      | J      | K      | L      | ENTER  |
* |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Z      | X      | C      | V/NUM  | B/ETC  | N      | M/DIR  | ,/GUI  | ./ALT  | BKSC   |
 * |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------'
 */

 [_QWERTY] = KEYMAP( /* Qwerty*/
 KC_Q,  KC_W,  KC_E, KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
 KC_A,  KC_S,  KC_D, KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
   SZ,    LX,    CC, KC_V,    KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,      SS, //MO(_LOWER)
                                  KC_SPC
  ),

  [_LOWER] = KEYMAP( /* Qwerty*/
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,       KC_7,    KC_8,    KC_9,    KC_0,
    KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_TRNS,         KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS,     TQS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT,
                                                  KC_TRNS
   ),

   [_RAISE] = KEYMAP( /* Qwerty*/
     KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,   KC_RPRN,
     KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS,  KC_TRNS,         KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS, RSFT(TQS),
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                                                   KC_TRNS
    ),
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {

  //Tap once for space, tap twice for enter
  [TD_QUOT_SCLN]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_SCLN),
  //Tap once for Left Shift, twice for Caps Lock
  [TD_KC_LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  //Tap once for Right Shift, twice for Caps Lock
  [TD_KC_RSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS)

// Other declarations would go here, separated by commas, if you have them

};