#include "superkeys.h"

void superkey_handle_event(keyboard_state_t* keyboard_state, uint16_t keycode, bool pressed) {
    uint32_t time = timer_read32();
    for (size_t i = 0; i < n_superkeys; i++) {
        superkey_state_t* superkey_state = &(superkeys[i].state);
        superkey_config_t* superkey_config = &(superkeys[i].config);

        // Handle superkey presses and releases
        if (keycode == superkey_config->keycode) {
            
            if (pressed) {

                // Call user-specfied down function and reset stuff
                if (superkey_config->down != NULL) {
                    superkey_config->down(keyboard_state, superkey_state);
                }
                superkey_state->tap_start_time = time;
                superkey_state->was_interrupted = 0;
                superkey_state->was_timed_out = 0;
                superkey_state->interrupt_is_on = true;
                superkey_state->timer_is_on = true;

            } else {

                // Multitap logic
                if (superkey_state->was_interrupted == 0 && superkey_state->was_timed_out == 0) {
                    // The current event is a multitap if the previous event was a tap/multitap and occured in the last multitap_term milliseconds
                    if (superkey_state->prev_was_tap && timer_elapsed32(superkey_state->multitap_start_time) < superkey_config->multitap_term) {
                        superkey_state->was_multitapped++;
                    } else {
                        superkey_state->was_multitapped = 0;
                    }
                    // Prepare to check if the next tap is a multitap
                    superkey_state->multitap_start_time = time;
                    superkey_state->prev_was_tap = true;
                } else {
                    // Neither this event nor the next event can be a multitap
                    superkey_state->was_multitapped = 0;
                    superkey_state->prev_was_tap = false;
                }

                // Call user-specfied up function and reset stuff
                if (superkey_config->up != NULL) {
                    superkey_config->up(keyboard_state, superkey_state);
                }
                superkey_state->interrupt_is_on = false;
                superkey_state->timer_is_on = false;

            }

        // Handle a potential interrupt
        } else if (superkey_state->interrupt_is_on && pressed) {
            superkey_state->interrupting_keycode = keycode;
            if (superkey_config->interrupt != NULL) {
                if (superkey_config->interrupt(keyboard_state, superkey_state)) {
                    superkey_state->was_interrupted = superkey_state->was_timed_out == 0 ? 1 : 2;
                    superkey_state->interrupt_is_on = false;
                }
            }
        }
    }
}

void superkey_check_timers(keyboard_state_t* keyboard_state) {
    for (size_t i = 0; i < n_superkeys; i++) {
        superkey_state_t* superkey_state = &(superkeys[i].state);
        superkey_config_t* superkey_config = &(superkeys[i].config);

        // Handle a timeout
        if (superkey_state->timer_is_on && timer_elapsed32(superkey_state->tap_start_time) > superkey_config->tap_term) {
            if (superkey_config->timeout != NULL) {
                superkey_config->timeout(keyboard_state, superkey_state);
            }
            superkey_state->was_timed_out = superkey_state->was_interrupted == 0 ? 1 : 2;
            superkey_state->timer_is_on = false;
        }
    }
}
