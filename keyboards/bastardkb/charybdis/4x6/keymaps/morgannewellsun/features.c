#include "features.h"

// ============================================================================
// KEY OVERRIDES
// ============================================================================

// const key_override_t key_override_nine = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_PIPE);
// const key_override_t key_override_zero = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_BACKSLASH);

// const key_override_t **key_overrides = (const key_override_t *[]){
//     &key_override_nine,
//     &key_override_zero,
//     NULL
// };

// ============================================================================
// RGB ANIMATIONS
// ============================================================================

enum rgb_animation_names {
    ANIM_OFF,
    ANIM_TEST
};

rgb_animation_t rgb_animations[] = {
    [ANIM_OFF] = {100, {1000}, {{0, 0, 0}}, 0, 1},
    [ANIM_TEST] = {100, {1000, 1000, 1000}, {{85, 255, RGB_MAX_BRIGHTNESS}, {170, 255, RGB_MAX_BRIGHTNESS}, {0, 255, RGB_MAX_BRIGHTNESS}}, 0, 3}
};

// ============================================================================
// LAYER SWITCHING
// ============================================================================

void sk_base_down_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    if (keyboard_state->current_base_layer == LAYER_BASE_1) {
        keyboard_state->sk_base.locked = false;
    } else if (keyboard_state->current_base_layer == LAYER_BASE_2) {
        // TODO RGB: base layer 2 to 1
        keyboard_state->current_base_layer = LAYER_BASE_1;
        keyboard_state->sk_base.locked = true;
        layer_off(LAYER_BASE_2);
        tap_code(KC_1);
    } else if (keyboard_state->current_base_layer == LAYER_BASE_3) {
        // TODO RGB: base layer 3 to 1
        keyboard_state->current_base_layer = LAYER_BASE_1;
        keyboard_state->sk_base.locked = true;
        layer_off(LAYER_BASE_3);
        tap_code(KC_1);
    }
}

void sk_base_up_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    if (keyboard_state->sk_base.locked) {
        return;
    } else if (keyboard_state->current_base_layer == LAYER_BASE_1) {
        if (!superkey_state->was_timed_out) {
            // TODO RGB: base layer 1 to 2
            keyboard_state->current_base_layer = LAYER_BASE_2;
            layer_on(LAYER_BASE_2);
            tap_code(KC_2);
        }
    }
}

void sk_base_timeout_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    if (keyboard_state->sk_base.locked) {
        return;
    } else if (keyboard_state->current_base_layer == LAYER_BASE_1) {
        // TODO RGB: base layer 1 to 3
        keyboard_state->current_base_layer = LAYER_BASE_3;
        keyboard_state->sk_base.locked = true;
        layer_on(LAYER_BASE_3);
        tap_code(KC_3);
    }
}

// ============================================================================
// EXTRA SYMBOLS
// ============================================================================

void sk_symb_down_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    layer_on(LAYER_SYMBOLS);
}

void sk_symb_up_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    layer_off(LAYER_SYMBOLS);
}

// ============================================================================
// OS ONESHOT AND ASSOCIATED FUNCTIONS
// ============================================================================

void sk_os_down_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    layer_on(LAYER_FUNCTION);
}

void sk_os_up_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    layer_off(LAYER_FUNCTION);
    if (superkey_state->was_multitapped > 0) {
        reset_keyboard();
    } else if (superkey_state->was_interrupted == 0 && superkey_state->was_timed_out == 0) {
        if (keyboard_state->oneshots.os_active) {
           if (keyboard_state->oneshots.ctrl_active || keyboard_state->oneshots.alt_active) {
                // TODO RGB: more than one oneshots active, deactivate all oneshots
            } else {
                // TODO RGB: OS is only oneshot active, deactivate all oneshots
            }
            keyboard_state->oneshots.os_active = false;    
            keyboard_state->oneshots.ctrl_active = false;
            keyboard_state->oneshots.alt_active = false;

        } else {
            if (keyboard_state->oneshots.ctrl_active || keyboard_state->oneshots.alt_active) {
                // TODO RGB: some oneshots active, activate OS oneshot
            } else {
                // TODO RGB: no oneshots active, activate OS oneshot
            }
            keyboard_state->oneshots.os_active = true;

        }
    }
}

// ============================================================================
// CTRL ONESHOT AND ASSOCIATED FUNCTIONS
// ============================================================================

// void sk_ctrl_down_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
    
// }

// void sk_ctrl_up_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
//     // If interrupted or timed out, release CTRL.
//     // Else, if tapped, 
// }
 
// void sk_ctrl_interrupt_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
//     // If already timed out do nothing. Otherwise, start holding CTRL. In either case, begin holding the interrupting key. 

// }

// void sk_ctrl_timeout_fn(keyboard_state_t* keyboard_state, superkey_state_t* superkey_state) {
//     // If already interrupted, do nothing. Otherwise, start holding CTRL and flash the indicator lights.
// }


// ============================================================================
// SUPERKEY LIST
// ============================================================================

#define DEFAULT_TAP_TERM 175
#define DEFAULT_MULTITAP_TERM 175

superkey_t superkeys[] = {
    SK_DEFINE(SK_BASE,  DEFAULT_TAP_TERM,   DEFAULT_MULTITAP_TERM,  &sk_base_down_fn,   &sk_base_up_fn, NULL,   &sk_base_timeout_fn),
    SK_DEFINE(SK_SYMB,  DEFAULT_TAP_TERM,   DEFAULT_MULTITAP_TERM,  &sk_symb_down_fn,   &sk_symb_up_fn, NULL,   NULL),
    SK_DEFINE(SK_OS,    DEFAULT_TAP_TERM,   DEFAULT_MULTITAP_TERM,  &sk_os_down_fn,     &sk_os_up_fn,   NULL,   NULL),
};
const size_t n_superkeys = sizeof(superkeys) / sizeof(superkeys[0]);

// ============================================================================
// COUNTDOWN FUNCTIONS
// ============================================================================

countdown_t countdowns[] = {
    // COUNTDOWN_DEFINE(UTILITIES_AUTO_OFF,    DEFAULT_MULTITAP_TERM, );
};
const size_t n_countdowns = sizeof(countdowns) / sizeof(countdowns[0]);