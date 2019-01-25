#ifndef GHERKIN_H
#define GHERKIN_H

#include "quantum.h"

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
