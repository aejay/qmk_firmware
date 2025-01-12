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
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _ARROWS,
  _LOWER,
  _RAISE,
  _ADJUST,
  _DEUTSCH,
};

enum planck_keycodes {
  EXT_PLV = SAFE_RANGE,
};

enum {
    TD_ARROW_EQUALS,
    TD_ARROW_MINUS,
    TD_ARROW_PIPE,
    TD_GOOGLE_MUTE,
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
    [TD_GOOGLE_MUTE] = ACTION_TAP_DANCE_DOUBLE(C(KC_CAPS), C(A(KC_CAPS))),
};

#define ARR_EQL TD(TD_ARROW_EQUALS)
#define ARR_MIN TD(TD_ARROW_MINUS)
#define ARR_PIP TD(TD_ARROW_PIPE)
#define GOG_MUT TD(TD_GOOGLE_MUTE)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define DEUTC MO(_DEUTSCH)

#define CLM_COL LSFT(KC_P)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,     KC_P, GOG_MUT,
    KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,  KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, DEUTC, KC_LGUI, KC_LALT,   LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT,   KC_UP,  KC_DOWN, KC_RGHT
),

[_ARROWS] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,  KC_F10, KC_F11,
    KC_BSPC,    KC_0,    KC_1,    KC_2,    KC_3, KC_HASH,  KC_DLR,    KC_4,     KC_5,    KC_6,    KC_7, KC_F12,
    _______,    KC_8,    KC_9,    KC_A,    KC_B, KC_COMM,  KC_DOT,    KC_C,     KC_G,    KC_K,    KC_E, KC_ENT,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
     KC_GRV, KC_HASH, KC_AMPR, KC_UNDS, KC_PLUS,  KC_DLR, XXXXXXX, ARR_PIP,   KC_UP,   KC_AT, CLM_COL,  KC_CIRC,
     KC_DEL, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, ARR_MIN, KC_EXLM, KC_LEFT, KC_DOWN, KC_RGHT, ARR_EQL,  KC_DQUO,
    _______, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK, XXXXXXX, XXXXXXX, KC_BSLS, KC_ASTR, KC_PERC, KC_QUES, KC_TILDE,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TT(_ARROWS),
    _______, _______,   AU_ON,  AU_OFF,  AU_TOG, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,   MU_ON,  MU_OFF,  MU_TOG, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
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
