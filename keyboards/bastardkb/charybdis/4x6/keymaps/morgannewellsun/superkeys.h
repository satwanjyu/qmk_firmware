/*
This implements "superkeys", which are highly overloaded keys.
The functionality of superkeys is highly similar to and in many ways redundant with tap-dance.
However, superkey behavior can change when held for a certain duration or interrupted by other keys.

Requirements in keymaps.c:

Superkeys should be the first custom keycodes for memory efficiency:

    enum custom_keycodes {
        SC_KEY_1 = SAFE_RANGE,
        SC_KEY_2,
        ...
        KC_OTHERS
    };

An array of superkeys, and the size of this array, must be defined:

    superkey_t superkeys[] = {
        [SC_OFFSET(SC_KEY_1)] = SC_DEFINE(SC_KEY_1, ...),
        [SC_OFFSET(SC_KEY_2)] = SC_DEFINE(SC_KEY_2, ...),
        ...
    };
    const size_t n_superkeys = sizeof(superkeys) / sizeof(superkeys[0]);

Superkeys can be used in keymaps normally:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        ..., SC_KEY_1, SC_KEY_2, ...
    };

In process_record_user, superkey_handle_event must be called:

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        ...
        superkey_handle_event(keyboard_state, keycode, record->event.pressed);
        ...
    }

In matrix_scan_user, superkey_check_timers must be called:

    void matrix_scan_user(void) {
        ...
        superkey_check_timers(keyboard_state);
        ...
    }
*/

#pragma once

#include QMK_KEYBOARD_H
#include "state_machine.h"

#define SUPERKEY_RANGE SAFE_RANGE
#define SK_INDEX(KC) (KC - SUPERKEY_RANGE)
#define SK_DEFINE(_keycode, _tap_term, _multitap_term, _down, _up, _interrupt, _timeout) \
    { .config = {.keycode = _keycode, .tap_term = _tap_term, .multitap_term = _multitap_term, .down = _down, .up = _up, .interrupt = _interrupt, .timeout = _timeout} }

typedef struct {   
    uint32_t multitap_start_time;
    uint32_t tap_start_time;
    uint16_t interrupting_keycode;
    uint8_t was_interrupted;
    uint8_t was_timed_out;
    uint8_t was_multitapped;
    bool interrupt_is_on;
    bool timer_is_on;
    bool prev_was_tap;
} superkey_state_t;

typedef struct {  
    void (*down)(keyboard_state_t*, superkey_state_t*);
    bool (*interrupt)(keyboard_state_t*, superkey_state_t*);  // returns whether or not to interrupt
    void (*timeout)(keyboard_state_t*, superkey_state_t*);
    void (*up)(keyboard_state_t*, superkey_state_t*);
    uint16_t keycode;
    uint16_t multitap_term;
    uint16_t tap_term;
} superkey_config_t;

typedef struct {
    superkey_state_t state;
    superkey_config_t config;
} superkey_t;

extern superkey_t superkeys[];
extern const size_t n_superkeys;

void superkey_handle_event(keyboard_state_t* keyboard_state, uint16_t keycode, bool pressed);
void superkey_check_timers(keyboard_state_t* keyboard_state);

