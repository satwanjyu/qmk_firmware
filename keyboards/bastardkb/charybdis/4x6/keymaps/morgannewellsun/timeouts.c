#include "timeouts.h"

void timeout_activate(size_t index) {
    timeouts[index].active = true;
    timeouts[index].start_time = timer_read32();
}

void timeout_check_timers(keyboard_state_t* keyboard_state) {
    for (size_t i = 0; i < n_timeouts; i++) {
        if (timeouts[i].active && timer_elapsed32(timeouts[i].start_time) > timeouts[i].duration) {
            if (timeouts[i].function != NULL) {
                timeouts[i].function(keyboard_state);
            }
            timeouts[i].active = false;
        }
    }
}