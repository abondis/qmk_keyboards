// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "quantum.h"
#include "stm32_f103_atreus.h"

//#define KC_TRNS KC_TRNS
#define XXXXXXX KC_NO
#define BASE 0
#define NUM 1
#define MOU 2

/* Orignal abondis atreus
KEYMAP(KC_Q,             KC_W,     KC_E,     KC_R,     KC_T,                    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
       KC_A,             KC_S,     KC_D,     KC_F,     KC_G,                    KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,
       SFT_T(KC_Z),      KC_X,     KC_C,     KC_V,     KC_B,                    KC_N,     KC_M,     KC_COMM,  KC_DOT,   SFT_T(KC_SLSH),
       LT(NUM,KC_ESC),   KC_TAB,   KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_RALT, KC_SPC,  KC_FN0,    KC_MINS,  KC_QUOT,  KC_ENT
       ),
*/
/*
 * NOTE: SCLN: ;, needed in colemak as it is o
 * FIXME: Move LT one row up ?
 * TODO: move MINS somewhere else ?
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = KEYMAP(
KC_Q,           KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,      KC_I,     KC_O,     KC_P,
SFT_T(KC_A),    KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,      KC_K,     KC_L,     SFT_T(KC_SCLN),
KC_Z,           KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,      KC_COMM,  KC_DOT,   KC_SLSH,
LT(NUM,KC_ESC), KC_TAB,   KC_LGUI,  KC_BSPC,  XXXXXXX, KC_LCTL,   KC_RALT,  KC_SPC,   XXXXXXX,   KC_MINS,  KC_QUOT,  LT(MOU, KC_ENT)
       ),
/*
 * FIXME: KC_SHIFT
 * NOTE: Press ESC+TAB or ENT+DOT to get to mouse layer
 * DONE: KC_GRAVE
 */
[NUM] = KEYMAP(
KC_INS,          KC_HOME,   KC_UP,    KC_END,    KC_PGUP,                    KC_PGUP,  KC_7,      KC_8,      KC_9,       KC_0,
KC_DEL,          KC_LEFT,   KC_DOWN,  KC_RIGHT,  KC_PGDN,                    KC_PGDN,  KC_4,      KC_5,      KC_6,       KC_EQUAL,
XXXXXXX,         XXXXXXX,   KC_LBRC,  KC_RBRC,   KC_GRAVE,                    XXXXXXX,  KC_1,      KC_2,      KC_3,       KC_BSLS,
KC_TRNS,  LT(MOU,KC_TAB),   KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, LT(MOU, KC_DOT), KC_TRNS
               ),
/*
 */
[MOU] = KEYMAP( /* Mouse and Media Keys */
KC_SLCK, KC_PAUSE, KC_F11 , KC_F10 , KC_F9  ,                   KC_F8  , KC_F7  , KC_F6  , KC_F5  , KC_F4,
KC_VOLD, KC_ACL0 , KC_ACL1, KC_ACL2, KC_VOLU,                   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_F3,
KC_MUTE, KC_MPRV , KC_MPLY, KC_MNXT, KC_MUTE,                   KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_F2,
KC_TRNS, KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, F(BASE), RESET  , KC_TRNS, KC_TRNS)
};

const uint16_t PROGMEM fn_actions[] = {
};
