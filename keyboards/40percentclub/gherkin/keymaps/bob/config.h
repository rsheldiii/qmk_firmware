// Bob-specific

#define COMBO_COUNT 4
#define COMBO_TERM 20

#ifndef CONFIG_H
#define CONFIG_H

  #include "config_common.h"


  /* USB Device descriptor parameter */
  #define VENDOR_ID       0xFEED
  #define PRODUCT_ID      0x6060
  #define DEVICE_VER      0x0001
  #define MANUFACTURER    40 Percent Club
  #define PRODUCT         Gherkin
  #define DESCRIPTION     A 30 key ortholinear keyboard

  /* key matrix size */
  #undef MATRIX_ROWS
  #define MATRIX_ROWS 6
  #undef MATRIX_COLS
  #define MATRIX_COLS 7

  /* key matrix pins */
  #undef MATRIX_ROW_PINS
  #define MATRIX_ROW_PINS { F7, B1, B3, B2, B6, F5 }
  #undef MATRIX_COL_PINS
  #define MATRIX_COL_PINS { B4, E6, D7, C6, D4, D0, F6 }
  #define UNUSED_PINS

  /* COL2ROW or ROW2COL */
  #define DIODE_DIRECTION COL2ROW

  /* number of backlight levels */
  #define BACKLIGHT_PIN B5

  #ifdef BACKLIGHT_PIN
    #define BACKLIGHT_LEVELS 3
  #endif

  /* Set 0 if debouncing isn't needed */
  #define DEBOUNCING_DELAY 5

  /* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
  #define LOCKING_SUPPORT_ENABLE

  /* Locking resynchronize hack */
  #define LOCKING_RESYNC_ENABLE

  /* key combination for command */
  #define IS_COMMAND() ( \
      keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
  )

  /* prevent stuck modifiers */
  #define PREVENT_STUCK_MODIFIERS

  /*tap dance definition */
  #define TAPPING_TERM 200

  //Mousekeys Settings
  #define MOUSEKEY_INTERVAL 1
  #define MOUSEKEY_DELAY 0
  #define MOUSEKEY_TIME_TO_MAX 1
  #define MOUSEKEY_MAX_SPEED 15
  #define MOUSEKEY_WHEEL_DELAY 0


  #ifdef RGB_DI_PIN
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 0
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
  #endif

  #define KEYMAP( \
  	 K00,   K01,   K02,   K03,   K04,   K05,   K10,   K11,   K12,   K13 , \
  	 K14,   K15,   K20,   K21,   K22,   K23,   K24,   K25,   K30,   K31 , \
  	 K32,   K33,   K34,   K35,   K40,   K41,   K42,   K43,   K44,   K45 ,  \
  	 K56 \
  ) { \
  	{   K00,     K01,     K02,     K03,     K04,     K05, KC_NO }, \
  	{   K10,     K11,     K12,     K13,     K14,     K15, KC_NO }, \
  	{   K20,     K21,     K22,     K23,     K24,     K25, KC_NO }, \
  	{   K30,     K31,     K32,     K33,     K34,     K35, KC_NO }, \
  	{   K40,     K41,     K42,     K43,     K44,     K45, KC_NO },  \
  	{ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, K56   }  \
  }
#endif
