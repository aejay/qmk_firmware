/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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

#include "../../moonlander.h"
#include "../../config.h"
#include "./config.h"
// #include "version.h"
#include "keymap_us_international.h"
// #include "rgblight_list.h"

enum layers {
    BAS,  // default layer
    ARR,  // arrows at bottom right
    NMP,  // numpad/mouse mode
    SYM,  // dev/symbols
    NUM,  // numrow on the home row, dawg
    DEU,  // german keys
};

enum custom_keycodes {
    KC_VRSN = ML_SAFE_RANGE,
};

// Tap Dance declarations
enum {
    TD_ARROW_EQUALS,
    TD_ARROW_MINUS,
    TD_ARROW_PIPE,
    TD_GOOGLE_MUTE,
    TD_RDP_MINIMIZE,
};

void arrow_dance_tap(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t idx = state->keycode - QK_TAP_DANCE;
    switch (idx) {
        // For each down, regardless of hold, put the main character.
        case TD_ARROW_EQUALS:
            tap_code(KC_EQUAL);
            break;
        case TD_ARROW_MINUS:
            tap_code(KC_MINUS);
            break;
        case TD_ARROW_PIPE:
            tap_code16(KC_PIPE);
            break;
    }
}

void arrow_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->interrupted && state->pressed) {
        // If the dance is finished with a hold, finish it off with a >
        tap_code16(KC_RIGHT_ANGLE_BRACKET);
        tap_code(KC_SPACE);
        // tap_code16(KC_LEFT_CURLY_BRACE);
        // tap_code(KC_SPACE);
    }
}

#define ARROWDANCE ACTION_TAP_DANCE_FN_ADVANCED(arrow_dance_tap, arrow_dance_finished, NULL)

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for = twice for =>
    [TD_ARROW_EQUALS] = ARROWDANCE,
    // Tap once for - twice for ->
    [TD_ARROW_MINUS] = ARROWDANCE,
    // Tap once for | twice for |>
    [TD_ARROW_PIPE]   = ARROWDANCE,
    [TD_RDP_MINIMIZE] = ACTION_TAP_DANCE_DOUBLE(S(KC_CAPS), S(A(KC_CAPS))),
    [TD_GOOGLE_MUTE] = ACTION_TAP_DANCE_DOUBLE(C(KC_CAPS), C(A(KC_CAPS))),
};

#define ARR_EQL TD(TD_ARROW_EQUALS)
#define ARR_MIN TD(TD_ARROW_MINUS)
#define ARR_PIP TD(TD_ARROW_PIPE)
#define GOG_MUT TD(TD_GOOGLE_MUTE)
#define RDP_MIN TD(TD_RDP_MINIMIZE)
#define LYR_CLR TOGGLE_LAYER_COLOR
#define CLM_COL LSFT(KC_P)
// #define RDP_MIN C(S(KC_CAPS))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BAS] = LAYOUT_moonlander(
         KC_ESC, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, _______,           _______,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, GOG_MUT,
        KC_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, _______,           _______,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, MO(DEU), RGB_TOG, KC_LGUI, KC_LALT,          TT(ARR),           TT(NMP),          KC_RALT,  KC_APP, RGB_MOD, XXXXXXX, KC_RCTRL,
                                                KC_SPC,  MO(NUM), RDP_MIN,           GOG_MUT,  MO(SYM), KC_ENT
    ),

    [ARR] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______,   KC_UP, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [NMP] =  LAYOUT_moonlander(
        XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX, _______,           _______, KC_CALC, KC_PSLS, KC_PAST, KC_LPRN, KC_RPRN, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_PGUP, KC_MS_U, KC_HOME, XXXXXXX, _______,           _______, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, XXXXXXX,
        XXXXXXX, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, _______,           _______, KC_BSPC, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, XXXXXXX,
        _______, _______, KC_PGDN, KC_WH_D,  KC_END, XXXXXXX,                             XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          KC_KP_0, KC_KP_0, KC_PDOT, KC_PENT, _______,
                                            KC_BTN1, KC_BTN2, KC_BTN3,           _______, _______, KC_PENT
    ),

    [SYM] = LAYOUT_moonlander(
         KC_GRV, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
         KC_GRV, KC_HASH, KC_AMPR, KC_UNDS, KC_PLUS,  KC_DLR, XXXXXXX,           XXXXXXX, XXXXXXX, ARR_PIP,   KC_UP,   KC_AT, CLM_COL,  KC_CIRC,
         KC_DEL, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, ARR_MIN, XXXXXXX,           XXXXXXX, KC_EXLM, KC_LEFT, KC_DOWN, KC_RGHT, ARR_EQL,  KC_DQUO,
        _______, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK, XXXXXXX,                             XXXXXXX, KC_BSLS, KC_ASTR, KC_PERC, KC_QUES, KC_TILDE,
        _______, _______, LYR_CLR, XXXXXXX, _______,          _______,           _______,          _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [NUM] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
         KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______,           _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
        _______,    KC_0,    KC_1,    KC_2,    KC_3, KC_HASH, _______,           _______,  KC_DLR,    KC_4,    KC_5,    KC_6,    KC_7,  KC_F12,
        // This next line is messy because of colemak... need to think of something cleverer
        _______,    KC_8,    KC_9,    KC_A,    KC_B, KC_COMM,                              KC_DOT,    KC_C,    KC_G,    KC_K,    KC_E, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [DEU] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______,           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, XXXXXXX, US_ADIA, US_ODIA, US_UDIA,   US_SS, XXXXXXX,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
    // [] = LAYOUT_moonlander(
    //     _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______, _______, _______,
    //                                         _______, _______, _______,           _______, _______, _______
    // ),
};


extern bool g_suspend_state;

const uint8_t PROGMEM ledkeymap[] = {
    [0] =  0, [5] =  1, [10] =  2, [15] =  3, [20] =  4, [25] =  5, [29] =  6,           [65] =  7, [61] =  8, [56] =  9, [51] = 10, [46] = 11, [41] = 12, [36] = 13,
    [1] = 14, [6] = 15, [11] = 16, [16] = 17, [21] = 18, [26] = 19, [30] = 20,           [66] = 21, [62] = 22, [57] = 23, [52] = 24, [47] = 25, [42] = 26, [37] = 28,
    [2] = 28, [7] = 29, [12] = 30, [17] = 31, [22] = 32, [27] = 33, [31] = 34,           [67] = 35, [63] = 36, [58] = 37, [53] = 38, [48] = 39, [43] = 40, [38] = 41,
    [3] = 42, [8] = 43, [13] = 44, [18] = 45, [23] = 46, [28] = 47,                                 [64] = 48, [59] = 49, [54] = 50, [49] = 51, [44] = 52, [39] = 53,
    [4] = 54, [9] = 55, [14] = 56, [19] = 57, [24] = 58,            [35] = 59,           [71] = 60,            [60] = 61, [55] = 62, [50] = 63, [45] = 64, [40] = 65,
                                              [32] = 66, [33] = 67, [34] = 68,           [70] = 69, [69] = 70, [68] = 71
};

#define COL_RED (uint8_t[3]){255,0,0}
#define COL_PNK (uint8_t[3]){255,0,255}
#define COL_GRN (uint8_t[3]){0,255,0}
#define COL_BLU (uint8_t[3]){0,0,255}
#define COL_YEL (uint8_t[3]){255,255,0}
#define COL_WIT (uint8_t[3]){255,255,255}
#define __off__ (uint8_t[3]){0,0,0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [ARR] = {
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__, COL_PNK, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,           __off__,          __off__, __off__, COL_PNK, COL_PNK, COL_PNK,
                                            __off__, __off__, __off__,           __off__, __off__, __off__
    },
    [NMP] = {
        __off__, __off__, __off__, COL_BLU, __off__, __off__, __off__,           __off__, COL_BLU, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, COL_WIT, COL_BLU, COL_WIT, __off__, __off__,           __off__, __off__, COL_BLU, COL_BLU, COL_BLU, __off__, __off__,
        __off__, COL_BLU, COL_BLU, COL_BLU, COL_BLU, COL_BLU, __off__,           __off__, COL_RED, COL_BLU, COL_BLU, COL_BLU, __off__, __off__,
        __off__, __off__, COL_WIT, COL_BLU, COL_WIT, __off__,                             __off__, COL_BLU, COL_BLU, COL_BLU, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,           __off__,          COL_BLU, COL_BLU, __off__, __off__, __off__,
                                            __off__, __off__, __off__,           __off__, __off__, __off__
    },
    [SYM] = {
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN, __off__, __off__,           __off__, __off__, COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN,
        COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN, __off__,           __off__, COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN,
        __off__, COL_GRN, COL_GRN, COL_GRN, COL_GRN, __off__,                             __off__, COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN,
        __off__, __off__, __off__, __off__, __off__,          __off__,           __off__,          __off__, __off__, __off__, __off__, __off__,
                                            __off__, __off__, __off__,           __off__, __off__, __off__
    },
    [NUM] = {
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, COL_RED, COL_RED, COL_RED, COL_RED, COL_RED, __off__,           __off__, COL_RED, COL_RED, COL_RED, COL_RED, COL_RED, COL_RED,
        __off__, COL_BLU, COL_BLU, COL_BLU, COL_BLU, COL_WIT, __off__,           __off__, COL_WIT, COL_BLU, COL_BLU, COL_BLU, COL_BLU, COL_RED,
        __off__, COL_BLU, COL_BLU, COL_BLU, COL_BLU, __off__,                             __off__, COL_BLU, COL_BLU, COL_BLU, COL_BLU, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,           __off__,          __off__, __off__, __off__, __off__, __off__,
                                            __off__, __off__, __off__,           __off__, __off__, __off__
    },
    [DEU] = {
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, COL_YEL, COL_YEL, COL_YEL, COL_YEL, __off__,
        __off__, __off__, __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,          __off__,           __off__,          __off__, __off__, __off__, __off__, __off__,
                                            __off__, __off__, __off__,           __off__, __off__, __off__
    },
    // [___] = {
    //     __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__,          __off__,           __off__,          __off__, __off__, __off__, __off__, __off__,
    //                                         __off__, __off__, __off__,           __off__, __off__, __off__
    // },
};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    int j = pgm_read_byte(&ledkeymap[i]);
    RGB rgb = {
      .r = pgm_read_byte(&ledmap[layer][j][0]),
      .g = pgm_read_byte(&ledmap[layer][j][1]),
      .b = pgm_read_byte(&ledmap[layer][j][2]),
    };
    if (!rgb.r && !rgb.g && !rgb.b) {
        // rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  rgb_matrix_set_color_all(0, 0, 0);
  if (layer_state & (1 << ARR))
  {
      set_layer_color(ARR);
  }
  if (layer_state & (1 << NMP))
  {
      set_layer_color(NMP);
  }
  if (layer_state & (1 << SYM))
  {
      set_layer_color(SYM);
  }
  if (layer_state & (1 << NUM))
  {
      set_layer_color(NUM);
  }
  if (layer_state & (1 << DEU))
  {
      set_layer_color(DEU);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
    //     case KC_VRSN:
    //         if (record->event.pressed) {
    //             // SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    //             return false;
    //         }
    // }
    return true;
}
