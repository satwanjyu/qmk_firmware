/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

enum layers {
    BASE = 0,
    MEDIA,
    NAV,
    LIGHT,
    NUM,
    SYM,
    FUN,
    GAME,
    GFUN
};

bool dip_switch_update_user(uint8_t index, bool active) {
  default_layer_set(0x01 << (active ? GAME : BASE));
  return false;
}

enum tap_dance_actions {
  DOUBLE_TAP_BOOT,
  DOUBLE_TAP_SLEEP,
  DOUBLE_TAP_POWER,
  MEDIA_CONTROL
};

void double_tap_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

void media_control(tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16(KC_MEDIA_PLAY_PAUSE);
      break;
    case 2:
      tap_code16(KC_MEDIA_NEXT_TRACK);
      break;
    case 3:
      tap_code16(KC_MEDIA_PREV_TRACK);
      break;
  }
  reset_tap_dance(state);
}

tap_dance_action_t tap_dance_actions[] = {
  [DOUBLE_TAP_BOOT]  = ACTION_TAP_DANCE_FN(double_tap_boot),
  [DOUBLE_TAP_SLEEP] = ACTION_TAP_DANCE_DOUBLE(KC_NO, KC_SYSTEM_SLEEP),
  [DOUBLE_TAP_POWER] = ACTION_TAP_DANCE_DOUBLE(KC_NO, KC_SYSTEM_POWER),
  [MEDIA_CONTROL]    = ACTION_TAP_DANCE_FN(media_control)
};

#define UGUI_A LGUI_T(KC_A)
#define UALT_R LALT_T(KC_R)
#define UCTL_S LCTL_T(KC_S)
#define USFT_T LSFT_T(KC_T)
#define USFT_N RSFT_T(KC_N)
#define UCTL_E RCTL_T(KC_E)
#define UALT_I RALT_T(KC_I)
#define UGUI_O RGUI_T(KC_O)

#define MED_ESC LT(MEDIA, KC_ESC)
#define NAV_SPC LT(NAV,   KC_SPC)
#define LIG_TAB LT(LIGHT,   KC_TAB)
#define SYM_ENT LT(SYM,   KC_ENT)
#define NUM_BSP LT(NUM,   KC_BSPC)
#define FUN_DEL LT(FUN,   KC_DEL)

#define TD_BOOT TD(DOUBLE_TAP_BOOT)
#define TD_SLEP TD(DOUBLE_TAP_SLEEP)
#define TD_PWR  TD(DOUBLE_TAP_POWER)
#define TD_MED  TD(MEDIA_CONTROL)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TD_MED:
      return TAPPING_TERM * 2;
    default:
      return TAPPING_TERM;
  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ansi_69(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                       TD_MED,
     KC_NO,     KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                         KC_J,     KC_L,     KC_U,     KC_Y,  KC_QUOT,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,   UGUI_A,   UALT_R,   UCTL_S,   USFT_T,     KC_G,                         KC_M,   USFT_N,   UCTL_E,   UALT_I,   UGUI_O,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,     KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,              KC_NO,     KC_K,     KC_H,  KC_COMM,   KC_DOT,  KC_SLSH,    KC_NO,              KC_NO,  
     KC_NO,    KC_NO,            MED_ESC,  NAV_SPC,  LIG_TAB,            SYM_ENT,  NUM_BSP,  FUN_DEL,                                            KC_NO,    KC_NO,    KC_NO
    ),
  [MEDIA] = LAYOUT_ansi_69(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                       TD_MED,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,    KC_NO,                        KC_NO,  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,              KC_NO,  KC_MPLY,  KC_MUTE,                                            KC_NO,    KC_NO,    KC_NO
    ),
  [NAV] = LAYOUT_ansi_69(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                       TD_MED,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,    KC_NO,                      CW_TOGG,  KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,  KC_HOME,  KC_PGDN,  KC_PGUP,   KC_END,    KC_NO,              KC_NO,     
     KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,                                            KC_NO,    KC_NO,    KC_NO
    ),
  [LIGHT] = LAYOUT_ansi_69(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                       TD_MED,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                        KC_NO,  RGB_M_P,  RGB_M_B,  RGB_M_R, RGB_M_SW,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,    KC_NO,                      RGB_TOG,  RGB_MOD,  RGB_VAD,  RGB_VAI, RGB_RMOD,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,  RGB_SAD,  RGB_HUD,  RGB_HUI,  RGB_SAI,    KC_NO,              KC_NO,
     KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,            RGB_SPI,  RGB_SPD,    KC_NO,                                            KC_NO,    KC_NO,    KC_NO
    ),
  [SYM] = LAYOUT_ansi_69(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                       TD_MED,
     KC_NO,  KC_LCBR,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RCBR,                        KC_NO,   TD_PWR,  TD_SLEP,    KC_NO,  TD_BOOT,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,  KC_COLN,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_PLUS,                        KC_NO,  KC_RSFT,  KC_RCTL,  KC_RALT,  KC_RGUI,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,  KC_TILD,  KC_EXLM,    KC_AT,  KC_HASH,  KC_PIPE,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,    KC_NO,            KC_LPRN,  KC_RPRN,  KC_UNDS,              KC_NO,    KC_NO,    KC_NO,                                            KC_NO,    KC_NO,    KC_NO
    ),
  [NUM] = LAYOUT_ansi_69(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                       TD_MED,
     KC_NO,  KC_LBRC,     KC_7,     KC_8,     KC_9,  KC_RBRC,                        KC_NO,   TD_PWR,  TD_SLEP,    KC_NO,  TD_BOOT,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,  KC_SCLN,     KC_4,     KC_5,     KC_6,   KC_EQL,                        KC_NO,  KC_RSFT,  KC_RCTL,  KC_RALT,  KC_RGUI,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,   KC_GRV,     KC_1,     KC_2,     KC_3,  KC_BSLS,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,   
     KC_NO,    KC_NO,             KC_DOT,     KC_0,  KC_MINS,              KC_NO,    KC_NO,    KC_NO,                                            KC_NO,    KC_NO,    KC_NO
    ),
  [FUN] = LAYOUT_ansi_69(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                       TD_MED,
     KC_NO,   KC_F12,    KC_F7,    KC_F8,    KC_F9,  KC_PSCR,                        KC_NO,   TD_PWR,  TD_SLEP,    KC_NO,  TD_BOOT,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,   KC_F11,    KC_F4,    KC_F5,    KC_F6,    KC_NO,                        KC_NO,  KC_RSFT,  KC_RCTL,  KC_RALT,  KC_RGUI,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,   KC_F10,    KC_F1,    KC_F2,    KC_F3,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,                                            KC_NO,    KC_NO,    KC_NO
    ),
  [GAME] = LAYOUT_ansi_69(
    KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,               KC_7,     KC_8,     KC_9,     KC_0,  KC_MINS,   KC_EQL,  KC_BSPC,                       TD_MED,
    KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_LBRC,  KC_RBRC,  KC_BSLS,             KC_DEL,
   KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,   KC_ENT,                      KC_HOME,
   KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_B,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT,              KC_UP,  
   KC_LCTL,  KC_LGUI,            KC_LALT,   KC_SPC,    KC_NO,           MO(GFUN),   KC_SPC,  KC_RALT,                                          KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
  [GFUN] = LAYOUT_ansi_69(
     KC_NO,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,              KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,    KC_NO,                       TD_MED,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                        KC_NO,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,     
     KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,                                            KC_NO,    KC_NO,    KC_NO
    ),
};
