/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "keymap_steno.h"
#include "eeprom.h"
/* #include "rgblight.h" */
/* void sethsv(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1); */

typedef union {
  uint32_t raw;
  struct {
    uint8_t      led_level :3;
    bool         disable_layer_led   :1;
    bool         rgb_matrix_enable   :1;
  };
} keyboard_config_t;

keyboard_config_t keyboard_config;

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  /* RGB_SLD, // = SAFE_RANGE, */
  /* HSV_0_128_145, */
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Sft/A |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | Sft/;|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Lo/Esc| Tab  |      |  GUI | Bkspc| Ctrl | Alt  | Spc  | LAlt |  -   |  '   |Hi/Ent|
 * `-----------------------------------------------------------------------------------'
 * NOTE:
 * - tab on linux: ctrl+i
 */
[_QWERTY] = LAYOUT_planck_grid(
    _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
    _______,  SFT_T(KC_A),    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SFT_T(KC_SCLN), _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
    LT(_LOWER, KC_ESC), KC_TAB, _______, KC_LGUI,   KC_BSPC, KC_LCTL, KC_RALT, KC_SPC,  KC_LALT,   KC_MINS, KC_QUOT, LT(_RAISE, KC_ENT)
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    /* BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT */
    LT(_LOWER, KC_ESC), KC_TAB, _______, KC_LGUI,   KC_BSPC, KC_LCTL, KC_RALT, KC_SPC,  KC_LALT,   KC_MINS, KC_QUOT, LT(_RAISE, KC_ENT)
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
    /* BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT */
    LT(_LOWER, KC_ESC), KC_TAB, _______, KC_LGUI,   KC_BSPC, KC_LCTL, KC_RALT, KC_SPC,  KC_LALT,   KC_MINS, KC_QUOT, LT(_RAISE, KC_ENT)
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
_______, KC_INS,          KC_HOME,   KC_UP,    KC_END,    KC_PGUP,  KC_PGUP,  KC_7,      KC_8,      KC_9,       KC_0,            _______,
_______, SFT_T(KC_DEL),   KC_LEFT,   KC_DOWN,  KC_RIGHT,  KC_PGDN,  KC_PGDN,  KC_4,      KC_5,      KC_6,       SFT_T(KC_EQUAL), _______,
_______, _______,         _______,   KC_LBRC,  KC_RBRC,   KC_GRAVE, _______,  KC_1,      KC_2,      KC_3,       KC_BSLS,         _______,
_______, _______,         _______,   _______,  _______,   _______,  _______,  _______,  _______, _______,       KC_DOT,          _______
                              ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
_______, XXXXXXX  , XXXXXXX , KC_MS_U, XXXXXXX ,  KC_F4  , KC_SLCK , KC_PAUSE, KC_F11  , KC_F10  , KC_F9   , _______,
_______, XXXXXXX , KC_MS_L  , KC_MS_D, KC_MS_R ,  KC_F3  , KC_VOLD , KC_ACL0 , KC_ACL1 , KC_ACL2 , KC_VOLU , _______,
_______, KC_F1   , KC_F2    , KC_F3  , KC_F4   ,  KC_F5  , KC_MUTE , KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE , _______,
LT(_LOWER, KC_BTN1), _______ ,   RESET  , _______, _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = {
  {STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR },
  {XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR },
  {STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC },
  {EXT_PLV, XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2}
},

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|      |      |Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, _______, QWERTY,   PLOVER,  COLEMAK,  _______,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, KC_BRIU, KC_BRID, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}
#define RGB_BLK 0x01, 0x01, 0x01
// Base layer colors
const uint8_t BASECOL[][3] = {
[_QWERTY] = {RGB_CYAN},
[_COLEMAK] = {RGB_ORANGE},
[_RAISE] = {RGB_TURQUOISE},
[_LOWER] = {RGB_ORANGE},
[_PLOVER] = {RGB_MAGENTA},
[_ADJUST] = {RGB_GREEN},
};

// Per layer - per key colors
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
[_QWERTY] = {
{ RGB_RED   },{          },{          },{          },{          },{          },   {          },{          },{          },{          },{          },{  RGB_RED },
{ RGB_RED   },{          },{          },{          },{          },{          },   {          },{          },{          },{          },{          },{  RGB_RED },
{ RGB_RED   },{          },{          },{          },{          },{          },   {          },{          },{          },{          },{          },{  RGB_RED },
{ RGB_RED   },{  RGB_RED },{  RGB_RED },{  RGB_RED },{  RGB_RED },{     },{RGB_BLK},{        },{  RGB_RED },{  RGB_RED },{  RGB_RED },{  RGB_RED },{  RGB_RED },
},
/* [_RAISE] = LAYOUT_planck_grid( */
/* _______, XXXXXXX  , XXXXXXX , KC_MS_U, XXXXXXX ,  KC_F4  , KC_SLCK , KC_PAUSE, KC_F11  , KC_F10  , KC_F9   , _______, */
/* _______, XXXXXXX , KC_MS_L  , KC_MS_D, KC_MS_R ,  KC_F3  , KC_VOLD , KC_ACL0 , KC_ACL1 , KC_ACL2 , KC_VOLU , _______, */
/* _______, KC_F1   , KC_F2    , KC_F3  , KC_F4   ,  KC_F5  , KC_MUTE , KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE , _______, */
/* LT(_LOWER, KC_BTN1), _______ ,   RESET  , _______, _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ */
/* ), */
[_RAISE] = {
{ RGB_RED },{ RGB_BLK  },{ RGB_BLK  },{          },{  RGB_BLK},{ RGB_TEAL  },    {          },{          },{          },{          },{          },{ RGB_RED  },
{ RGB_RED  },{ RGB_BLK },{          },{          },{         },{ RGB_TEAL  },    {          },{          },{          },{          },{          },{ RGB_RED  },
{ RGB_RED },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL  },    {          },{          },{          },{          },{ RGB_RED },{ RGB_RED  },
{ RGB_RED },{ RGB_RED  },{ RGB_PURPLE },{ RGB_RED },{ RGB_RED },{ RGB_RED },{RGB_BLK},{RGB_RED },{RGB_RED },{  RGB_RED },{ RGB_RED },{ RGB_RED },{  RGB_RED  },
},
/* [_LOWER] = LAYOUT_planck_grid( */
/* _______, KC_INS,          KC_HOME,   KC_UP,    KC_END,    KC_PGUP,  KC_PGUP,  KC_7,      KC_8,      KC_9,       KC_0,            _______, */
/* _______, SFT_T(KC_DEL),   KC_LEFT,   KC_DOWN,  KC_RIGHT,  KC_PGDN,  KC_PGDN,  KC_4,      KC_5,      KC_6,       SFT_T(KC_EQUAL), _______, */
/* _______, _______,         _______,   KC_LBRC,  KC_RBRC,   KC_GRAVE, _______,  KC_1,      KC_2,      KC_3,       KC_BSLS,         _______, */
/* _______, _______,         _______,   _______,  _______,   _______,  _______,  _______,  _______, _______,       KC_DOT,          _______ */
/*                               ), */
[_LOWER] = {
{ RGB_RED },{ RGB_CORAL},{ RGB_BLK  },{          },{  RGB_BLK},{ RGB_BLK  },    { RGB_BLK  },{          },{          },{          },{          },{ RGB_RED  },
{ RGB_RED },{ RGB_CORAL},{          },{          },{         },{ RGB_BLK  },    { RGB_BLK  },{          },{          },{          },{ RGB_PINK },{ RGB_RED  },
{ RGB_RED },{ RGB_TEAL },{ RGB_TEAL },{ RGB_PINK },{ RGB_PINK},{RGB_PINK },    { RGB_TEAL },{          },{          },{          },{ RGB_PINK  },{ RGB_RED  },
{ RGB_RED },{ RGB_RED  },{ RGB_PURPLE },{ RGB_RED },{ RGB_RED },{ RGB_RED },{RGB_BLK},{RGB_RED },{RGB_RED },{  RGB_RED },{ RGB_RED },{ RGB_PINK},{  RGB_RED  },
},
[_COLEMAK] = {
{ RGB_BLUE  },{          },{          },{          },{          },{          },   {          },{          },{          },{          },{          },{  RGB_BLUE },
{ RGB_BLUE  },{          },{          },{          },{          },{          },   {          },{          },{          },{          },{          },{  RGB_BLUE },
{ RGB_BLUE  },{          },{          },{          },{          },{          },   {          },{          },{          },{          },{          },{  RGB_BLUE },
{ RGB_BLUE  },{ RGB_BLUE },{ RGB_BLUE },{ RGB_BLUE },{ RGB_BLUE },{     },{RGB_BLK},{        },{ RGB_BLUE },{ RGB_BLUE },{ RGB_BLUE },{ RGB_BLUE },{  RGB_BLUE },
},
[_PLOVER] = {
{ RGB_TEAL },{          },{          },{          },{          },{ RGB_TEAL  },    { RGB_TEAL },{          },{          },{          },{          },{  RGB_TEAL},
{ RGB_BLK  },{          },{          },{          },{          },{ RGB_TEAL  },    { RGB_TEAL },{          },{          },{          },{          },{  RGB_TEAL},
{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL  },    { RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{ RGB_TEAL },{  RGB_TEAL},
{ RGB_TEAL },{ RGB_BLK  },{ RGB_BLK  },{          },{          },{ RGB_BLK},{RGB_BLK},{RGB_BLK},{          },{          },{ RGB_TEAL },{ RGB_TEAL },{  RGB_TEAL},
},
/* [_ADJUST] = LAYOUT_planck_grid( */
/*     _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL , */
/*     _______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, _______, QWERTY,   PLOVER,  COLEMAK,  _______,  _______, */
/*     _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, KC_BRIU, KC_BRID, _______, */
/*     _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ */
/* ) */
[_ADJUST] = {
{ RGB_BLUE  },{ RGB_RED  },{          },{          },{          },{          },   {          },{          },{            },{          },{          },{  RGB_BLUE },
{ RGB_BLUE  },{ RGB_BLUE },{          },{          },{ RGB_BLUE },{ RGB_BLUE },   {          },{ RGB_TEAL },{ RGB_MAGENTA},{RGB_ORANGE},{ RGB_BLUE },{  RGB_BLUE },
{ RGB_BLUE  },{          },{          },{          },{          },{          },   {          },{          },{            },{ 0, 50, 10},{ 0, 50, 10},{  RGB_BLUE },
{ RGB_BLUE  },{ RGB_BLUE },{ RGB_BLUE },{ RGB_BLUE },{ RGB_BLUE },{     },{RGB_BLK},{        },{ RGB_BLUE },{ RGB_BLUE   },{ RGB_BLUE },{ RGB_BLUE },{  RGB_BLUE },
},
    /* [0] = { */
    /*   {85,203,158}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189},           {85,203,158}, */
    /*   {85,203,158}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {85,203,158}, {85,203,158}, {85,203,158}, {0,203,189}, {0,203,189}, {0,203,189},        {85,203,158}, */
    /*   {85,203,158}, {0,203,189}, {0,203,189}, {32,176,255}, {32,176,255}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189}, {0,203,189},         {85,203,158}, */
    /*   {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {0,203,189}, {0,203,189}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, (85,203,158) }, */

};

void set_layer_color(int layer) {
  int r, g, b;
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  f = 0.10;
  r = BASECOL[layer][0];
  g = BASECOL[layer][1];
  b = BASECOL[layer][2];
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    RGB rgb = {
      .r = pgm_read_byte(&ledmap[layer][i][0]),
      .g = pgm_read_byte(&ledmap[layer][i][1]),
      .b = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!rgb.r && !rgb.g && !rgb.b) {
        rgb_matrix_set_color( i, f * r, f * g, f * b );
    } else {
    /* if (rgb.r && rgb.g && rgb.b) { */
    /* if (hsv.h && hsv.s && hsv.v) { */
        /* RGB rgb = hsv_to_rgb( hsv ); */
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  set_layer_color(biton32(layer_state)) ;
  /*  switch (biton32(layer_state)) {
    case _QWERTY:
      set_layer_color(_QWERTY);
      break;
    case _COLEMAK:
      set_layer_color(_COLEMAK);
      break;
    case _PLOVER:
      set_layer_color(_PLOVER);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }*/
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
    /* case RGB_SLD: */
    /*   if (record->event.pressed) { */
    /*     rgblight_mode(1); */
    /*   } */
    /*   return false; */
    /*   break; */
    /* case HSV_0_128_145: */
    /*   if (record->event.pressed) { */
    /*     rgblight_mode(1); */
    /*     rgblight_sethsv(0,128,145); */
    /*   } */
    /*   return false; */
    /*   break; */
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

/* void matrix_init_user() { */
/*   /\* steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT *\/ */
/*   steno_set_mode(STENO_MODE_BOLT); // or STENO_MODE_BOLT */
/* } */
