#pragma once

#include QMK_KEYBOARD_H
#include "rgb_engine.h"
#include "superkeys.h"
#include "timeouts.h"
#include "keyboard_state.h"

enum keymap_layers {
    LAYER_BASE_1 = 0,
    LAYER_BASE_2,
    LAYER_BASE_3,
    LAYER_SYMBOLS,
    LAYER_FUNCTION,
    LAYER_UTILITIES,
};

enum custom_keycodes {
    SK_BASE = SAFE_RANGE,
    SK_SYMB,
    SK_OS,
};

enum timeouts {
    UTILITIES_OFF = 0,
};
