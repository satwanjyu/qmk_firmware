#include QMK_KEYBOARD_H
#include "features.h"


keyboard_state_t keyboard_state = {0};

// void test_down_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
// }

// void test_up_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
// }

// bool test_interrupt_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
//     return true;
// }

// void test_timeout_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
// }



// ============================================================================
// SUPERKEYS
// ============================================================================



// ============================================================================
// KEYMAPS
// ============================================================================

// [LAYER_ALL_TRNS] = LAYOUT(
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//                                                     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//                                                                     KC_TRNS,        KC_TRNS,        KC_TRNS
// ),
// [LAYER_ALL_TRNS] = LAYOUT(
//     KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
//     KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
//     KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
//     KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
//                                                     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//                                                                     KC_TRNS,        KC_TRNS,        KC_TRNS
// ),

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_BASE_1] = LAYOUT(
    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        KC_EQL,
    KC_ENT,         KC_Q,           KC_D,           KC_R,           KC_W,           KC_B,           KC_J,           KC_F,           KC_U,           KC_P,           KC_SCLN,        KC_TAB,
    KC_BSPC,        KC_A,           KC_S,           KC_H,           KC_T,           KC_G,           KC_Y,           KC_N,           KC_E,           KC_O,           KC_I,           KC_QUOT,
    KC_LSFT,        KC_Z,           KC_X,           KC_M,           KC_C,           KC_V,           KC_K,           KC_L,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                                                    QK_BOOT,        KC_SPC,         DRAGSCROLL_MODE,        SK_BASE,        SK_SYMB,
                                                                    KC_TRNS,        KC_TRNS,        SK_OS
),
[LAYER_BASE_2] = LAYOUT(
    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        KC_EQL,
    KC_ENT,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_TAB,
    KC_BSPC,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[LAYER_BASE_3] = LAYOUT(  // TODO
    KC_0,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        KC_EQL,
    KC_ENT,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_TAB,
    KC_BSPC,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[LAYER_SYMBOLS] = LAYOUT(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_LCBR,        KC_RCBR,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_TILDE,       KC_GRAVE,       KC_LPRN,        KC_RPRN,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_LBRC,        KC_RBRC,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[LAYER_FUNCTION] = LAYOUT(
    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
    KC_F13,         KC_F14,         KC_F15,         KC_F16,         KC_F17,         KC_F18,         KC_F19,         KC_F20,         KC_F21,         KC_F22,         KC_F23,         KC_F24,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[LAYER_UTILITIES] = LAYOUT(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                    KC_TRNS,        KC_TRNS,        KC_TRNS
),
};
// clang-format on

void keyboard_post_init_user(void) {
    rgb_setup(&(keyboard_state.rgb));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_BOOT) { return true; }
    return superkey_handle_event(&keyboard_state, keycode, record->event.pressed);
    // rgb_start(&(keyboard_state.rgb), ANIM_OFF);
    // rgb_start(&(keyboard_state.rgb), ANIM_TEST);
}

void matrix_scan_user(void) {
    superkey_check_timers(&keyboard_state);
    countdown_check_timers(&keyboard_state);
    rgb_update(&(keyboard_state.rgb));
}