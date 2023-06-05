// Copyright 2022 rsheldiii (@rsheldiii)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {
    NAVY_SEAL = SAFE_RANGE,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * -------------
     * | 1 | 2 | 3 |
     * -------------
     * | 4 | 5 | 6 |
     * -----------------
     * | 7 | 8 | 9 | 0 |
     * -----------------

     */
    [0] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_ESC, KC_1, KC_NO, KC_Q, KC_X, KC_U, KC_SPC, KC_TAB, KC_9, KC_SCLN,
        KC_BSPC, KC_LCTL, KC_D, KC_S, KC_NO, KC_G, KC_B, KC_C, KC_V, KC_F,
        KC_CAPS, KC_LSFT, KC_Z, KC_QUOT, KC_A, KC_8, KC_RSFT, KC_R, KC_5, KC_3,
        KC_E, KC_NO, KC_W, KC_O, KC_T, KC_4, KC_LEFT, KC_7, KC_NO, KC_M,
        KC_J, KC_6, KC_I, KC_K, KC_UP, KC_SLSH, KC_P, KC_RGHT, KC_NO, KC_H,
        KC_BSLS, KC_0, KC_LALT, KC_N, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case NAVY_SEAL:
        if (record->event.pressed) {
            // when keycode NAVY_SEAL is pressed
            send_string_with_delay("What the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little \"clever\" comment was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn't, you didn't, and now you're paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You're fucking dead, kiddo.", 10);
        } else {
            // when keycode NAVY_SEAL is released
        }
        break;
    }
    return true;
};
