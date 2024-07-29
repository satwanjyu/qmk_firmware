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
#include "superkeys.h"
#include "state_machine.h"
#include "rgb_engine.h"








keyboard_state_t keyboard_state = {0};








enum rgb_animation_names {
     ANIM_OFF,
     ANIM_TEST
};

rgb_animation_t rgb_animations[] = {
     [ANIM_OFF] = {100, {1000}, {{0, 0, 0}}, 0, 1},
     [ANIM_TEST] = {100, {1000, 1000, 1000}, {{85, 255, RGB_MAX_BRIGHTNESS}, {170, 255, RGB_MAX_BRIGHTNESS}, {0, 255, RGB_MAX_BRIGHTNESS}}, 0, 3}
};



void test_down_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
}

void test_up_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
}

bool test_interrupt_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
     return true;
}

void test_timeout_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
}

enum charybdis_keymap_layers {
    LAYER_TEST = 0,
};

enum custom_keycodes {
     SK_TEST = SAFE_RANGE,
};

// Define superkey
superkey_t superkeys[] = {
     [SK_INDEX(SK_TEST)] = SK_DEFINE(SK_TEST, 200, 500, &test_down_fn, &test_up_fn, &test_interrupt_fn, &test_timeout_fn)
};
const size_t n_superkeys = sizeof(superkeys) / sizeof(superkeys[0]);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_TEST] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_ENT,    KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,       KC_J,    KC_F,    KC_U,    KC_P, KC_SCLN,  KC_TAB,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_BSPC,    KC_A,    KC_S,    KC_H,    KC_T,    KC_G,       KC_Y,    KC_N,    KC_E,    KC_O,    KC_I, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,       KC_K,    KC_L, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______,  KC_SPC, SK_TEST,    _______, _______,
                                           _______, _______,    QK_BOOT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on






uint32_t counter = 0;
uint32_t start_time = 0;











void keyboard_post_init_user(void) {
     rgb_setup(&(keyboard_state.rgb));
     start_time = timer_read32();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     if (keycode == QK_BOOT) {
          return true;
     }
     superkey_handle_event(&keyboard_state, keycode, record->event.pressed);

     if (!record->event.pressed) {
          return false;
     }
     if (keycode == KC_K) {
          rgb_start(&(keyboard_state.rgb), ANIM_OFF);
     }
     if (keycode == KC_L) {
          rgb_start(&(keyboard_state.rgb), ANIM_TEST);
     }
     if (keycode == KC_Y) {
          send_dword(counter);
          send_string(" ");
          send_dword(timer_elapsed32(start_time));
          send_string(" | ");
     }




     return false;
}


void matrix_scan_user(void) {
     counter += 1;
     superkey_check_timers(&keyboard_state);
     rgb_update(&(keyboard_state.rgb));
}