#include "countdowns.h"

void countdown_activate(size_t index) {
    countdowns[index].active = true;
    countdowns[index].start_time = timer_read32();
}

void countdown_check_timers(keyboard_state_t* keyboard_state) {
    for (size_t i = 0; i < n_countdowns; i++) {
        if (countdowns[i].active && timer_elapsed32(countdowns[i].start_time) > countdowns[i].duration) {
            if (countdowns[i].function != NULL) {
                countdowns[i].function(keyboard_state);
            }
            countdowns[i].active = false;
        }
    }
}