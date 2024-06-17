/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

enum charybdis_keymap_layers {
    BASE = 0,
    MEDIA,
    NAV,
    NUM,
    SYM,
    FUN,
    GAME,
    MOUSE
};

enum tap_dance_declations {
  DOUBLE_TAP_BOOT,
  DOUBLE_TAP_GAME
};

void double_tap_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

void double_tap_game(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    default_layer_set(0x01 << GAME);
    reset_tap_dance(state);
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [DOUBLE_TAP_BOOT] = ACTION_TAP_DANCE_FN(double_tap_boot),
  [DOUBLE_TAP_GAME] = ACTION_TAP_DANCE_FN(double_tap_game),
};

enum custom_keycodes {
  DRAG_SCRL
};

void pointing_device_init_user(void) {
  set_auto_mouse_layer(MOUSE);
  set_auto_mouse_enable(true);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DRAG_SCRL:
      charybdis_set_pointer_dragscroll_enabled(record->event.pressed);
      return false;
    default:
      return true;
  }
}

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
#define FUN_TAB LT(FUN,   KC_TAB)
#define SYM_ENT LT(SYM,   KC_ENT)
#define NUM_BSP LT(NUM,   KC_BSPC)

#define TD_BOOT TD(DOUBLE_TAP_BOOT)
#define TD_GAME TD(DOUBLE_TAP_GAME)

#define DF_BASE DF(BASE)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
      KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,        KC_J,     KC_L,     KC_U,     KC_Y,  KC_QUOT,
    UGUI_A,   UALT_R,   UCTL_S,   USFT_T,     KC_G,        KC_M,   USFT_N,   UCTL_E,   UALT_I,   UGUI_O,
      KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,        KC_K,     KC_H,  KC_COMM,   KC_DOT,  KC_SLSH,
                       MED_ESC,  NAV_SPC,  FUN_TAB,     SYM_ENT,  NUM_BSP
  ),
  // Left-hand
  [MEDIA] = LAYOUT(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
   KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,    KC_NO,       KC_NO,  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                         KC_NO,    KC_NO,    KC_NO,     KC_MSEL,  KC_MPLY
  ),
  [NAV] = LAYOUT(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
   KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,    KC_NO,     CW_TOGG,  KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_INS,  KC_HOME,  KC_PGDN,  KC_PGUP,   KC_END,
                         KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_NO
  ),
  [FUN] = LAYOUT(
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_F7,    KC_F8,    KC_F9,   KC_F12,
   KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,    KC_NO,       KC_NO,    KC_F4,    KC_F5,    KC_F6,   KC_F11,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,    KC_F1,    KC_F2,    KC_F3,   KC_F10,
                         KC_NO,    KC_NO,    KC_NO,      KC_DEL,  KC_PSCR
  ),
  // Right-hand
  [SYM] = LAYOUT(
   KC_LCBR,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RCBR,       KC_NO,    KC_NO,    KC_NO,  TD_GAME,  TD_BOOT,
   KC_COLN,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_PLUS,       KC_NO,  KC_RSFT,  KC_RCTL,  KC_RALT,  KC_RGUI,
   KC_TILD,  KC_EXLM,    KC_AT,  KC_HASH,  KC_PIPE,       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                       KC_LPRN,  KC_RPRN,  KC_UNDS,       KC_NO,    KC_NO
  ),
  [NUM] = LAYOUT(
   KC_LBRC,     KC_7,     KC_8,     KC_9,  KC_RBRC,       KC_NO,    KC_NO,    KC_NO,  TD_GAME,  TD_BOOT,
   KC_SCLN,     KC_4,     KC_5,     KC_6,   KC_EQL,       KC_NO,  KC_RSFT,  KC_RCTL,  KC_RALT,  KC_RGUI,
    KC_GRV,     KC_1,     KC_2,     KC_3,  KC_BSLS,       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                        KC_DOT,     KC_0,  KC_MINS,       KC_NO,    KC_NO
  ),
  // Special
  [GAME] = LAYOUT(
    KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,        KC_U,      KC_I,   KC_UP,     KC_P,  KC_BSPC,
   KC_LSFT,     KC_A,     KC_S,     KC_D,     KC_F,        KC_J,   KC_LEFT, KC_DOWN,  KC_RGHT,   KC_ENT,
      KC_G,     KC_Z,     KC_X,     KC_C,     KC_V,        KC_M,   KC_COMM,  KC_DOT,  KC_SLSH,  DF_BASE,
                       KC_LCTL,   KC_SPC,   KC_ESC,     KC_RGUI,   KC_RALT
  ),
  [MOUSE] = LAYOUT(
   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
                     DRAG_SCRL,  KC_BTN1,  KC_BTN2,     KC_TRNS,   KC_TRNS
  ),
};
// clang-format on

