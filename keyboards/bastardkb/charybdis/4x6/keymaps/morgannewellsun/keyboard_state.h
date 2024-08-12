#pragma once

#include QMK_KEYBOARD_H
#include "rgb_engine.h"

typedef struct {
    rgb_state_t rgb;
    uint16_t current_base_layer;
    struct oneshots_state_t {
        bool os_active;
        bool ctrl_active;
        bool alt_active;
    } oneshots;
    struct sk_layer_state_t {
        bool locked;
    } sk_base;
    // struct sk_os_state_t {

    // } sk_os;
    // struct sk_ctrl_state_t {

    // } sk_ctrl;
    // struct sk_alt_state_t {

    // } sk_alt;
} keyboard_state_t;