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

enum combo_names {
  SPC_COMBO = 0,
  BSPC_COMBO,
  ENT_COMBO,
  TAB_COMBO,
  ESC_COMBO,
  SFT_COMBO,
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

const uint16_t PROGMEM combos[COMBO_COUNT][3] = {
  [SPC_COMBO]  = {KC_B, KC_N,    COMBO_END},
  [BSPC_COMBO] = {KC_O,         KC_P,    COMBO_END},
  [ENT_COMBO]  = {KC_L,         KC_SCLN, COMBO_END},
  [TAB_COMBO]  = {KC_A,         KC_S,    COMBO_END},
  [ESC_COMBO]  = {KC_Q,         KC_W,    COMBO_END},
  [SFT_COMBO]  = {KC_DOT,       KC_SLSH, COMBO_END},
};

combo_t key_combos[] = {
  COMBO(combos[SPC_COMBO], MO(_LOWER)),
  COMBO(combos[BSPC_COMBO],KC_BSPC),
  COMBO(combos[ENT_COMBO], KC_ENT),
  COMBO(combos[TAB_COMBO], KC_TAB),
  COMBO(combos[ESC_COMBO], KC_ESC),
  COMBO(combos[SFT_COMBO], KC_LSFT),
};


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
   KC_Q,            KC_W,    KC_E,    KC_R,    KC_T, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
   KC_A,            KC_S,    KC_D,    KC_F,    KC_G, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
   RCTL_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B, KC_N,    KC_M,    KC_COMM, KC_DOT,  MO(_LOWER)//KC_SLSH
  ),

  [_LOWER] = KEYMAP( /* Qwerty*/
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_TRNS,         KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
   ),
};
