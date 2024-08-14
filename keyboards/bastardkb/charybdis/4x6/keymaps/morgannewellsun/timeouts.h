#pragma once

#include QMK_KEYBOARD_H
#include "keyboard_state.h"

#define TIMEOUT_DEFINE(_index, _duration, _function) \
    [_index] = { .function = _function, .start_time = 0, .duration = _duration, .active = false }

typedef struct {   
    void (*function)(keyboard_state_t*);
    uint32_t start_time;
    uint32_t duration;
    bool active;
} timeout_t;

extern timeout_t timeouts[];
extern const size_t n_timeouts;

void timeout_activate(size_t index);
void timeout_check_timers(keyboard_state_t* keyboard_state);