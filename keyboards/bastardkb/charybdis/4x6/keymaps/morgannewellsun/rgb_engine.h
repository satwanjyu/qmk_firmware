/*

Requirements in keymaps.c:

Define an enum of animation names, and also define the corresponding animations:

enum rgb_animation_names {
    ANIMATION_1,
    ANIMATION_2,
};
rgb_animation_t rgb_animations[] = {
    [ANIMATION_1] = {...},
    [ANIMATION_2] = {...},
    ...
};

Animations can be started by calling:

rgb_start(&(keyboard_state.rgb), ANIMATION_NAME)

In void keyboard_post_init_user, rgb_setup must be called:

void keyboard_post_init_user(void) {
    ...
    rgb_setup(&(keyboard_state.rgb))
    ...
}

In matrix_scan_user, rgb_update must be called:

rgb_update(&(keyboard_state.rgb));

*/

#pragma once

#include QMK_KEYBOARD_H

#define MAX_ANIMATION_SIZE 4
#define RGB_UPDATE_INTERVAL 5
#define RGB_MAX_BRIGHTNESS 120

#define HSV_EQUAL(a, b) ((a.h == b.h) && (a.s == b.s) && (a.v == b.v))

typedef struct {
    uint32_t start_duration;  // start_duration is the time it takes to interpolate from the current color to colors[0]
    uint32_t durations[MAX_ANIMATION_SIZE];  // durations[i] is the time it takes to interpolate from colors[i ] to colors[i+1]
    HSV colors[MAX_ANIMATION_SIZE];
    uint8_t loop_start_idx;  // inclusive
    uint8_t loop_stop_idx;  // exclusive
} rgb_animation_t;

typedef struct {
    float lerp_duration_inv;
    HSV current_color;
    HSV lerp_final_color;
    HSV lerp_initial_color;
    uint32_t last_update_time;
    uint32_t lerp_duration;
    uint32_t lerp_initial_time;
    size_t lerp_final_idx;
    size_t lerp_initial_idx;
    size_t animation_idx;
} rgb_state_t;

extern rgb_animation_t rgb_animations[];

void rgb_setup(rgb_state_t* rgb_state);
void rgb_start(rgb_state_t* rgb_state, size_t animation_idx);
void rgb_update(rgb_state_t* rgb_state);