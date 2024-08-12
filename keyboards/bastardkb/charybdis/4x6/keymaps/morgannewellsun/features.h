#pragma once

#include QMK_KEYBOARD_H
#include "rgb_engine.h"
#include "superkeys.h"
#include "countdowns.h"
#include "keyboard_state.h"

enum keymap_layers {
    LAYER_BASE_1 = 0,
    LAYER_BASE_2,
    LAYER_BASE_3,
    LAYER_SYMBOLS,
    LAYER_FUNCTION,
    LAYER_UTILITIES
};

enum custom_keycodes {
    SK_BASE = SAFE_RANGE,
    SK_SYMB,
    SK_OS,
};

enum countdowns {
    UTILITIES_AUTO_OFF = 0,
};
