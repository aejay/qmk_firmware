#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_us_international.h"

enum {
    TD_ARROW_EQUALS,
    TD_ARROW_MINUS,
    TD_ARROW_PIPE,
    TD_GOOGLE_MUTE,
    TD_RDP_MINIMIZE,
};

enum layers {
    BAS,  // default layer
    ARR,  // arrows at bottom right
    NMP,  // numpad/mouse mode
    SYM,  // dev/symbols
    NUM,  // numrow on the home row, dawg
    DEU,  // german keys
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
    if (!state->interrupted && state->pressed)
    {
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
    [TD_ARROW_PIPE] = ARROWDANCE,
};

#define ARR_EQL TD(TD_ARROW_EQUALS)
#define ARR_MIN TD(TD_ARROW_MINUS)
#define ARR_PIP TD(TD_ARROW_PIPE)
#define CLM_COL LSFT(KC_P)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BAS] = LAYOUT_ergodox_pretty(
      KC_ESC, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, _______,           _______,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, _______,
      KC_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, _______,           _______,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
      KC_LCTL, MO(DEU), RGB_TOG, KC_LGUI, KC_LALT,                                               KC_RALT,  KC_APP, RGB_MOD, XXXXXXX, KC_RCTRL,
                                                   TT(ARR), TT(ARR),           TT(NMP),  TT(NMP),
                                                            _______,           _______,
                                          KC_SPC,  MO(NUM), _______,           _______,  MO(SYM),  KC_ENT
  ),

  [ARR] = LAYOUT_ergodox_pretty(
      _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______,   KC_UP, _______,
      _______, _______, _______, _______, _______,                                               _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,
                                                   _______, _______,           _______, _______,
                                                            _______,           _______,
                                          _______, _______, _______,           _______, _______, _______
  ),

  [NMP] =  LAYOUT_ergodox_pretty(
      XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX, _______,           _______, KC_CALC, KC_PSLS, KC_PAST, KC_LPRN, KC_RPRN, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_PGUP, KC_MS_U, KC_HOME, XXXXXXX, _______,           _______, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, XXXXXXX,
      XXXXXXX, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,                             KC_BSPC, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, XXXXXXX,
      _______, _______, KC_PGDN, KC_WH_D,  KC_END, XXXXXXX, _______,           _______, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
      _______, _______, _______, _______, _______,                                               KC_KP_0, KC_KP_0, KC_PDOT, KC_PENT, _______,
                                                   _______, _______,           _______, _______,
                                                            KC_BTN3,           _______,
                                          KC_BTN1, KC_BTN2, KC_BTN3,           _______, _______, KC_PENT
  ),

  [SYM] = LAYOUT_ergodox_pretty(
       KC_GRV, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
       KC_GRV, KC_HASH, KC_AMPR, KC_UNDS, KC_PLUS,  KC_DLR, XXXXXXX,           XXXXXXX, XXXXXXX, ARR_PIP,   KC_UP,   KC_AT, CLM_COL,  KC_CIRC,
       KC_DEL, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, ARR_MIN,                             KC_EXLM, KC_LEFT, KC_DOWN, KC_RGHT, ARR_EQL,  KC_DQUO,
       KC_DLR, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, KC_BSLS, KC_ASTR, KC_PERC, KC_QUES, KC_TILDE,
      _______, _______, _______, XXXXXXX, _______,                                               _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,
                                                   _______, _______,           _______, _______,
                                                            _______,           _______,
                                          _______, _______, _______,           _______, _______, _______
  ),

  [NUM] = LAYOUT_ergodox_pretty(
      _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
      KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______,           _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
      _______,    KC_0,    KC_1,    KC_2,    KC_3, KC_HASH,                              KC_DLR,    KC_4,    KC_5,    KC_6,    KC_7,  KC_F12,
      // This next line is messy because of colemak... need to think of something cleverer
      _______,    KC_8,    KC_9,    KC_A,    KC_B, KC_COMM, _______,           _______,  KC_DOT,    KC_C,    KC_G,    KC_K,    KC_E, _______,
      _______, _______, _______, _______, _______,                                               _______, _______, _______, _______, _______,
                                                   _______, _______,           _______, _______,
                                                            _______,           _______,
                                          _______, _______, _______,           _______, _______, _______
  ),

  [DEU] = LAYOUT_ergodox_pretty(
      _______, _______, _______, _______, _______, _______, _______,           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, _______, _______, _______, _______, _______, _______,           _______, XXXXXXX, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                             XXXXXXX, US_ADIA, US_ODIA, US_UDIA,   US_SS, XXXXXXX,
      _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,                                               _______, _______, _______, _______, _______,
                                                   _______, _______,           _______, _______,
                                                            _______,           _______,
                                          _______, _______, _______,           _______, _______, _______
  ),
  /*
  [___] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                                               _______, _______, _______, _______, _______,
                                                 _______, _______,           _______, _______,
                                                          _______,           _______,
                                        _______, _______, _______,           _______, _______, _______
  ),
  */
};

extern bool g_suspend_state;

const uint8_t PROGMEM ledkeymap[] = {
    [28] =  0,  [27] =  1,  [26] =  2, [25] =  3, [24] =  4,            [ 0] =  5, [ 1] =  6, [ 2] =  7, [ 3] =  8, [ 4] =  9,
    [33] = 10,  [32] = 11,  [31] = 12, [30] = 13, [29] = 14,            [ 5] = 15, [ 6] = 16, [ 7] = 17, [ 8] = 18, [ 9] = 19,
    [38] = 20,  [37] = 21,  [36] = 22, [35] = 23, [34] = 24,            [10] = 25, [11] = 26, [12] = 27, [13] = 28, [14] = 29,
    [43] = 30,  [42] = 31,  [41] = 32, [40] = 33, [39] = 34,            [15] = 35, [16] = 36, [17] = 37, [18] = 38, [19] = 39,
    [47] = 40,  [46] = 41,  [45] = 42, [44] = 43,                                  [20] = 44, [21] = 45, [22] = 46, [23] = 47,
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
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, COL_PNK,
        __off__, __off__, __off__, __off__,                             __off__, __off__, COL_PNK, COL_PNK,
    },
    [NMP] = {
        __off__, __off__, COL_BLU, __off__, __off__,           COL_BLU, __off__, __off__, __off__, __off__,
        __off__, COL_WIT, COL_BLU, COL_WIT, __off__,           __off__, COL_BLU, COL_BLU, COL_BLU, __off__,
        COL_BLU, COL_BLU, COL_BLU, COL_BLU, COL_BLU,           COL_RED, COL_BLU, COL_BLU, COL_BLU, __off__,
        __off__, COL_WIT, COL_BLU, COL_WIT, __off__,           __off__, COL_BLU, COL_BLU, COL_BLU, __off__,
        __off__, __off__, __off__, __off__,                             COL_BLU, COL_BLU, __off__, __off__,
    },
    [SYM] = {
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        COL_GRN, COL_GRN, COL_GRN, COL_GRN, __off__,           __off__, COL_GRN, COL_GRN, COL_GRN, COL_GRN,
        COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN,           COL_GRN, COL_GRN, COL_GRN, COL_GRN, COL_GRN,
        COL_GRN, COL_GRN, COL_GRN, COL_GRN, __off__,           __off__, COL_GRN, COL_GRN, COL_GRN, COL_GRN,
        __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__,
    },
    [NUM] = {
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        COL_RED, COL_RED, COL_RED, COL_RED, COL_RED,           COL_RED, COL_RED, COL_RED, COL_RED, COL_RED,
        COL_BLU, COL_BLU, COL_BLU, COL_BLU, COL_WIT,           COL_WIT, COL_BLU, COL_BLU, COL_BLU, COL_BLU,
        COL_BLU, COL_BLU, COL_BLU, COL_BLU, __off__,           __off__, COL_BLU, COL_BLU, COL_BLU, COL_BLU,
        __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__,
    },
    // [NUM] = {
    //     __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
    //     COL_BLU, COL_BLU, COL_BLU, COL_BLU, COL_BLU,           COL_BLU, COL_BLU, COL_BLU, COL_BLU, COL_BLU,
    //     __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__,
    // },
    [DEU] = {
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__, __off__,           __off__, COL_YEL, COL_YEL, COL_YEL, COL_YEL,
        __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__,
        __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__,
    },
    // [___] = {
    //     __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__, __off__, __off__,           __off__, __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__, __off__,                             __off__, __off__, __off__, __off__, __off__, __off__,
    //     __off__, __off__, __off__, __off__, __off__,          __off__,           __off__,          __off__, __off__, __off__, __off__, __off__,
    //                                         __off__, __off__, __off__,           __off__, __off__, __off__
    // },


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

layer_state_t layer_state_set_user(layer_state_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
          case 1:
            ergodox_right_led_1_on();
            break;
          case 2:
            ergodox_right_led_2_on();
            break;
          case 3:
            ergodox_right_led_3_on();
            break;
          case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
          case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
          case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
          case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
          default:
            break;
        }
    return state;

};
