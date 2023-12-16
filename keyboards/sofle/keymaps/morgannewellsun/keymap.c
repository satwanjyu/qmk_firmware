#include QMK_KEYBOARD_H
#if defined(ENCODER_ENABLE) && defined (MIDI_ENABLE)
#include "midi.h"
#endif

// ============================================================================
// SHARED GLOBAL VARIABLES
// ============================================================================

long long ll_time = 0;  // uint16_t timer rolls over every minute

// ============================================================================
// KEYCODES AND LAYERS
// ============================================================================

enum custom_keycodes {

    // MINI and MEGA are ridiculously-overloaded CTRL and ALT
    KC_MINI = SAFE_RANGE,
    KC_MEGA,

    // Momentarily activate the _SYMB layer (optionally, add a tap action)
    KC_SYMB,

    // Tap to toggle to the _QWER layer; hold to toggle to the _GAME layer
    KC_BASE,

    // Momentarily activate the _FUNC layer
    KC_FUNC,

    // Delete a whole line of text
    KC_DELL,

    // Alt-tab forwards and backwards
    // KC_ATFW,  commented because I don't use it
    // KC_ATBK,  commented because I don't use it

    // Undo and redo, as well as "dual" which toggles between the two
    KC_DUAL,
    // KC_UNDO,  commented because already part of HID standard
    KC_REDO,

    // Encoder pushbuttons
    KC_ENCL,
    KC_ENCR,

    // Overcomplicated multipurpose arrow key modifier selection system
    KC_SLMC,  // Acts as CTRL for right-hand left/right keys only; switches left-hand arrow keys modifier to CTRL
    KC_SLMS,  // Acts as SHIFT for right-hand arrow/home/end keys; switches left-hand arrow keys modifier to SHIFT
    KC_SLMA,  // Acts as ALT for right-hand arrow/home/end keys; switches left-hand arrow keys modifier off
    KC_SLRU,  // Right-hand up
    KC_SLRD,  // Right-hand down
    KC_SLRL,  // Right-hand left
    KC_SLRR,  // Right-hand right
    KC_SLRH,  // Right-hand home
    KC_SLRE,  // Right-hand end
    KC_SLLU,  // Left-hand up
    KC_SLLD,  // Left-hand down
    KC_SLLL,  // Left-hand left
    KC_SLLR,  // Left-hand right
};

enum sofle_layers {
    _WORK,
    _QWER,
    _GAME,
    _SYMB,
    _FUNC,
    _MEGA,
    _MINI,
};

// ============================================================================
// KEYMAPS
// ============================================================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * WORK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |                    |   7  |   8  |   9  |   0  |   -  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Enter|   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   ;  |  Tab |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Bspc |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------|  ENCL |    | ENCR  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   M  |   C  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            | Down |  Up  | MINI | Space| / MEGA /        \ BASE \  | SYMB | FUNC | Left | Right|
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_WORK] = LAYOUT(
KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,                               KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,
KC_ENTER,   KC_Q,       KC_D,       KC_R,       KC_W,       KC_B,                               KC_J,       KC_F,       KC_U,       KC_P,       KC_SCLN,    KC_TAB,
KC_BSPC,    KC_A,       KC_S,       KC_H,       KC_T,       KC_G,                               KC_Y,       KC_N,       KC_E,       KC_O,       KC_I,       KC_QUOT,
KC_LSFT,    KC_Z,       KC_X,       KC_M,       KC_C,       KC_V,       KC_ENCL,    KC_ENCR,    KC_K,       KC_L,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                        KC_DOWN,    KC_UP,      KC_MINI,    KC_SPC,     KC_MEGA,    KC_BASE,    KC_SYMB,    KC_FUNC,    KC_LEFT,    KC_RIGHT
),
/*
 * QWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |                    |   7  |   8  |   9  |   0  |   -  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Enter|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  Tab |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Bspc |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  ENCL |    | ENCR  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            | Down |  Up  |  Alt | Space| / Ctrl /        \ BASE \  | SYMB | FUNC | Left | Right|
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_QWER] = LAYOUT(
KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,                               KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,
KC_ENTER,   KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_TAB,
KC_BSPC,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                               KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_TRNS,    KC_TRNS,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                        KC_DOWN,    KC_UP,      KC_LALT,    KC_SPC,     KC_LCTL,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_LEFT,    KC_RIGHT
),
/*
 * GAME
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |                    |   7  |   8  |   9  |   0  |   -  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Enter|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |  Up  |   O  |   P  |  Tab |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Bspc |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  | Left | Down | Right|   ;  |  '   |
 * |------+------+------+------+------+------|  ENCL |    | ENCR  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |  Tab |  Alt | Space| Ctrl | /  Esc /        \ BASE \  |   I  |   J  |   K  |   L  |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_GAME] = LAYOUT(
KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,                               KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,
KC_ENTER,   KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_UP,      KC_O,       KC_P,       KC_TAB,
KC_BSPC,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                               KC_H,       KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_SCLN,    KC_QUOT,
KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_TRNS,    KC_TRNS,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                        KC_TAB,     KC_LALT,    KC_SPC,     KC_LCTL,    KC_ESC,     KC_TRNS,    KC_I,       KC_J,       KC_K,       KC_L
),
/*
 * SYMB
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   {  |   }  |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   ~  |   `  |   (  |   )  |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|  ENCL |    | ENCR  |------+------+------+------+------+------|
 * |      |      |      |   [  |   ]  |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      | MINI | Space| / MEGA /        \      \  | SYMB |      |      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_SYMB] = LAYOUT(
KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,                              KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
KC_NO,      KC_NO,      KC_NO,      KC_LCBR,    KC_RCBR,    KC_NO,                              KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
KC_NO,      KC_TILDE,   KC_GRAVE,   KC_LPRN,    KC_RPRN,    KC_NO,                              KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
KC_NO,      KC_NO,      KC_NO,      KC_LBRC,    KC_RBRC,    KC_NO,      KC_TRNS,    KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                        KC_NO,      KC_NO,      KC_MINI,    KC_SPC,     KC_MEGA,    KC_NO,      KC_TRNS,    KC_NO,      KC_NO,      KC_NO
),
/*
 * FUNC
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |                    |  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|  ENCL |    | ENCR  |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |-------|    |-------|      |      |      |      |      | Shift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      |  Alt | Space| / Ctrl /        \ Boot \  |      | FUNC |      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

[_FUNC] = LAYOUT(
KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,                              KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,                             KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,     KC_F24,
KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,                              KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
KC_LSFT,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_TRNS,    KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_RSFT,
                        KC_NO,      KC_NO,      KC_LALT,    KC_SPC,     KC_LCTL,    QK_BOOT,    KC_NO,      KC_TRNS,    KC_NO,      KC_NO
),
/*
 * MEGA
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |                    |   7  |   8  |   9  |   0  |   -  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Enter|   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   ;  |  Tab |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Bspc |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------|  ENCL |    | ENCR  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   M  |   C  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            | CDown|  CUp |  Alt | Space| / MEGA /        \      \  |      |      | CLeft|CRight|
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_MEGA] = LAYOUT(
KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,                               KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,
KC_ENTER,   KC_Q,       KC_D,       KC_R,       KC_W,       KC_B,                               KC_J,       KC_F,       KC_U,       KC_P,       KC_SCLN,    KC_TAB,
KC_BSPC,    KC_A,       KC_S,       KC_H,       KC_T,       KC_G,                               KC_Y,       KC_N,       KC_E,       KC_O,       KC_I,       KC_QUOT,
KC_LSFT,    KC_Z,       KC_X,       KC_M,       KC_C,       KC_V,       KC_ENCL,    KC_ENCR,    KC_K,       KC_L,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                        C(KC_DOWN), C(KC_UP),   KC_LALT,    KC_SPC,     KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      C(KC_LEFT), C(KC_RIGHT)
),
/*
 * MINI
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | SLLL | SLLU | SLLR |      |                    |      | SLRH | SLRU | SLRE |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | SLMA | SLMC | SLMS |      |-------.    ,-------|      | SLRL | SLRD | SLRR |      |      |
 * |------+------+------+------+------+------|  ENCL |    | ENCR  |------+------+------+------+------+------|
 * | Boot |      |      | SLLD |      |      |-------|    |-------|      | CBspc| DelL | CDel |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            | Down |  Up  | MINI | Space| / Ctrl /        \      \  |      |      | Left | Right|
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

[_MINI] = LAYOUT(
KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,                              KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
KC_NO,      KC_NO,      KC_SLLL,    KC_SLLU,    KC_SLLR,    KC_NO,                              KC_NO,      KC_SLRH,    KC_SLRU,    KC_SLRE,    KC_NO,      KC_NO,
KC_NO,      KC_NO,      KC_SLMA,    KC_SLMC,    KC_SLMS,    KC_NO,                              KC_NO,      KC_SLRL,    KC_SLRD,    KC_SLRR,    KC_NO,      KC_NO,
QK_BOOT,    KC_NO,      KC_NO,      KC_SLLD,    KC_NO,      KC_NO,      KC_TRNS,    KC_TRNS,    KC_NO,      C(KC_BSPC), KC_DELL,    C(KC_DEL),  KC_NO,      KC_NO,
                        KC_DOWN,    KC_UP,      KC_TRNS,    KC_SPC,     KC_LCTL,    KC_NO,      KC_NO,      KC_NO,      KC_LEFT,    KC_RIGHT
),
};

// ============================================================================
// OLED
// ============================================================================

#ifdef OLED_ENABLE

// TODO: This is the default implementation; needs modification

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0xff,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };
    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_90;
    } else {
        return OLED_ROTATION_270;
    }
}

bool oled_task_user(void) {
    render_logo();
    return false;
}

#endif

// ============================================================================
// ENCODERS
// ============================================================================

#if defined(ENCODER_ENABLE) && defined (MIDI_ENABLE)

#define ENCODER_CHANNEL_SENS 8

extern MidiDevice midi_device;

#define ENCODER_LEFT_CHANNEL 1
#define ENCODER_RIGHT_CHANNEL 2
uint8_t encoder_left_value = 0;
uint8_t encoder_right_value = 0;
bool encoder_left_pressed = false;
bool encoder_right_pressed = false;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (!encoder_left_pressed) {
            if (clockwise) {
                encoder_left_value += (encoder_left_value < 127) ? (1) : (0);
            } else {
                encoder_left_value -= (encoder_left_value > 0) ? (1) : (0);
            }
            midi_send_cc(&midi_device, 0, ENCODER_LEFT_CHANNEL, encoder_left_value);
        }
    } else if (index == 1) {
        if (!encoder_right_pressed) {
            if (clockwise) {
                encoder_right_value += (encoder_right_value < 127) ? (1) : (0);
            } else {
                encoder_right_value -= (encoder_right_value > 0) ? (1) : (0);
            }
            midi_send_cc(&midi_device, 0, ENCODER_RIGHT_CHANNEL, encoder_right_value);
        }
    }
    return false;
}

static bool process_enco(bool pressed, bool right) {
    if (right) {
        if (pressed) {
            encoder_right_value = 0;
        }
    } else {
        if (pressed) {
            encoder_left_value = 0;
        }
    }
    return false;
}

#endif

// ============================================================================
// RGB INDICATORS
// ============================================================================

#ifdef RGBLIGHT_ENABLE

// One-shot modifiers and caps-word are represented with saturated colors
#define HUE_MAIN 115  // Main color for MEGA and MINI modifier animations
#define HUE_MINI_ACCENT 80  // Accent color for MINI modifier animations
#define HUE_MEGA_ACCENT 170  // Accent color for MEGA modifier animations
#define HUE_DRIFT_AMP 10  // Amount by which the hue drifts while an oneshot modifier is active

// Alternative base layers, as well as capsword, are represented with near-white colors
#define SAT_BASE 0  // Saturation used while the QWER or GAME layer is active
#define HUE_QWER_ACCENT 15  // Accent color for the QWER layer
#define HUE_GAME_ACCENT 190  // Accent color for the GAME layer
#define HUE_CAPSWORD_ACCENT HUE_MAIN  // Main color for caps word

#define MAX_N_RGB_WAYPOINTS 16
#define RGB_UPDATE_INTERVAL 5

HSV rgb_waypoints[MAX_N_RGB_WAYPOINTS];
long long rgb_times[MAX_N_RGB_WAYPOINTS];
HSV rgb_current_state = {HSV_BLACK};
int rgb_current_start_idx = 0;
int n_rgb_waypoints = 0;
long long rgb_next_update_time = 0LL;

static HSV hsv_lerp(HSV start_hsv, HSV end_hsv, float ratio) {
    HSV result;
    if (ratio < 0.0f) {
        ratio = 0.0f;
    }
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    int h_difference = (int)end_hsv.h - (int)start_hsv.h;
    if (start_hsv.v == 0) {
        h_difference = 0;
    }
    if (h_difference > 127) {
        h_difference -= 256;
    } else if (h_difference < -127) {
        h_difference += 256;
    }
    int h_interpolated = (int)start_hsv.h + (int)(h_difference * ratio);
    if (h_interpolated < 0) {
        h_interpolated += 256;
    } else if (h_interpolated > 255) {
        h_interpolated -= 256;
    }
    result.h = (uint8_t)h_interpolated;
    result.s = (uint8_t)(start_hsv.s + (int)(((int)end_hsv.s - (int)start_hsv.s) * ratio));
    result.v = (uint8_t)(start_hsv.v + (int)(((int)end_hsv.v - (int)start_hsv.v) * ratio));
    return result;
}

static uint8_t nudge_hue(uint8_t base_hue, uint8_t target_hue, int magnitude) {
    int forward_distance = ((int)target_hue - (int)base_hue + 256) % 256;
    int backward_distance = ((int)base_hue - (int)target_hue + 256) % 256;
    int direction = forward_distance <= backward_distance ? 1 : -1;
    int new_hue = (int)base_hue + direction * magnitude;
    new_hue = (new_hue + 256) % 256;
    return (uint8_t)new_hue;
}

static void rgb_set_first_waypoint(uint8_t h, uint8_t s, uint8_t v, uint16_t duration) {
    n_rgb_waypoints = 0;
    rgb_current_start_idx = 0;
    rgb_times[0] = ll_time;
    rgb_times[1] = ll_time + duration;
    rgb_waypoints[0].h = rgb_current_state.h;
    rgb_waypoints[0].s = rgb_current_state.s;
    rgb_waypoints[0].v = rgb_current_state.v;
    rgb_waypoints[1].h = h;
    rgb_waypoints[1].s = s;
    rgb_waypoints[1].v = v;
    n_rgb_waypoints = 1;
}

static void rgb_set_next_waypoint(uint8_t h, uint8_t s, uint8_t v, uint16_t duration) {
    n_rgb_waypoints++;
    rgb_times[n_rgb_waypoints] = rgb_times[n_rgb_waypoints - 1] + duration;
    rgb_waypoints[n_rgb_waypoints].h = h;
    rgb_waypoints[n_rgb_waypoints].s = s;
    rgb_waypoints[n_rgb_waypoints].v = v;
}

#endif

// ============================================================================
// KEY OVERRIDES
// ============================================================================

#ifdef KEY_OVERRIDE_ENABLE

const key_override_t key_override_nine = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_PIPE);
const key_override_t key_override_zero = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_BACKSLASH);
// const key_override_t key_override_minus = ko_make_basic(MOD_MASK_SHIFT, KC_MINUS, KC_GRAVE);

const key_override_t **key_overrides = (const key_override_t *[]){
    &key_override_nine,
    &key_override_zero,
    NULL
};

#endif

// ============================================================================
// SYMBOL TAP-HOLD
// ============================================================================


// #define SYMB_TAP_KC KC_UNDS
#ifdef SYMB_TAP_KC
#define SYMB_TAPPING_TERM 150LL
#endif

bool symb_interrupt_on = false;
bool symb_was_interrupted = false;
long long symb_start_time = 0;

static void symb_interrupt(bool interrupt_pressed, uint16_t keycode) {
    if (interrupt_pressed && keycode != KC_SYMB) {
        symb_interrupt_on = false;
        symb_was_interrupted = true;
    }
}

static bool process_symb(bool pressed, long long time) {
    if (pressed) {
        layer_on(_SYMB);
        symb_interrupt_on = true;
        symb_was_interrupted = false;
        symb_start_time = time;
    } else {
        layer_off(_SYMB);
        symb_interrupt_on = false;
#ifdef SYMB_TAP_KC
        if (!symb_was_interrupted && time - symb_start_time < SYMB_TAPPING_TERM) {
            tap_code16(SYMB_TAP_KC);
        }
#endif
    }
    return false;
}

// ============================================================================
// CAPS WORD
// ============================================================================

#ifdef CAPS_WORD_ENABLE

void caps_word_set_user(bool active) {
    if (active) {
        rgb_set_first_waypoint(HUE_CAPSWORD_ACCENT, 255, 0, 0);
        rgb_set_next_waypoint(HUE_CAPSWORD_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
        rgb_set_next_waypoint(HUE_CAPSWORD_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
        rgb_set_next_waypoint(HUE_CAPSWORD_ACCENT, SAT_BASE, RGBLIGHT_LIMIT_VAL, 500);
        rgb_set_next_waypoint(HUE_CAPSWORD_ACCENT, SAT_BASE, RGBLIGHT_LIMIT_VAL, 500);
    } else {
        rgb_set_first_waypoint(HUE_CAPSWORD_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
        rgb_set_next_waypoint(HUE_CAPSWORD_ACCENT, 255, 0, 100);
        rgb_set_next_waypoint(HUE_CAPSWORD_ACCENT, 255, 0, 100);
    }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key
            return true;

        // Keycodes that continue Caps Word, without shifting
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MEGA:  // Allow MEGA key through (process_mega will handle deactivation of caps word)
        case KC_MINI:  // Allow MINI key through (process_mini will handle deactivation of caps word)
        case KC_BASE:  // Allow BASE key through (process_base will handle deactivation of caps word)
#ifdef SYMB_TAP_KC
        case KC_SYMB:
#endif
            return true;

        default:
            return false;  // Deactivate Caps Word
    }
}

#endif

// ============================================================================
// MOMENTARY FUNCTION LAYER
// ============================================================================

static bool process_func(bool pressed) {
    if (pressed) {
        layer_on(_FUNC);
    } else {
        layer_off(_FUNC);
    }
    return false;
}

// ============================================================================
// DELETE LINE
// ============================================================================

static bool process_dell(bool pressed) {
    if (pressed) {
        tap_code(KC_MINUS);
        tap_code(KC_END);
        tap_code(KC_END);
        tap_code16(S(KC_HOME));
        tap_code16(S(KC_HOME));
        tap_code16(S(KC_LEFT));
        tap_code(KC_BSPC);
    }
    return false;
}

// ============================================================================
// DUAL UNDO/REDO
// ============================================================================

bool redo_next = false;

static bool process_dual(bool pressed) {
    if (pressed) {
        if (redo_next) {
            tap_code16(C(S(KC_Z)));
            redo_next = false;
        } else {
            tap_code16(C(KC_Z));
            redo_next = true;
        }
    }
    return false;
}

static bool process_undo(bool pressed) {
    if (pressed) {
        register_code16(C(KC_Z));
        redo_next = true;
    } else {
        unregister_code16(C(KC_Z));
    }
    return false;
}

static bool process_redo(bool pressed) {
    if (pressed) {
        register_code16(C(S(KC_Z)));
        redo_next = false;
    } else {
        unregister_code16(C(S(KC_Z)));
    }
    return false;
}

// ============================================================================
// ARROW KEY MODIFIER SELECTION
// ============================================================================

/*

This functionality serves two purposes. It only applies to when the MINI layer is active.
- While typing, use the right-hand IJKL keys as arrow keys, and use U/O as home/end.
    - Apply the CTRL to only J (left) and L (right) using KC_SLMC.
    - Apply the SHIFT modifer to any of these keys using KC_SLMS.
    - Apply the ALT modifier to any of these keys using KC_SLMA.
- While mousing with the right hand, use left-hand DXCV as arrow keys.
    - By default, ALT is applied to these keys.
    - Press KC_SLMC to switch this to CTRL.
    - Press KC_SLMS to switch this to SHIFT.
    - Press KC_SLMA to switch this to nothing.

 */

enum select_mods {
    SELECT_ALT,
    SELECT_CTRL,
    SELECT_SHIFT,
    SELECT_NONE,
};

bool select_ctrl_pressed = false;
bool select_shift_pressed = false;
bool select_alt_pressed = false;
int select_last_modifier = SELECT_ALT;
uint16_t keycode_to_send;

static bool process_slxx(bool pressed, uint16_t keycode) {
    switch (keycode) {

        case KC_SLMC:
            if (pressed) {
                select_ctrl_pressed = true;
                select_last_modifier = SELECT_CTRL;
            } else {
                select_ctrl_pressed = false;
            }
            return false;
        case KC_SLMS:
            if (pressed) {
                select_shift_pressed = true;
                select_last_modifier = SELECT_SHIFT;
            } else {
                 select_shift_pressed = false;
            }
            return false;
        case KC_SLMA:
            if (pressed) {
                 select_alt_pressed = true;
                 select_last_modifier = SELECT_NONE;
            } else {
                 select_alt_pressed = false;
            }
            return false;

        case KC_SLRU ... KC_SLRE:
            switch (keycode) {
                case KC_SLRU:
                    keycode_to_send = KC_UP;
                    break;
                case KC_SLRD:
                    keycode_to_send = KC_DOWN;
                    break;
                case KC_SLRL:
                    keycode_to_send = KC_LEFT;
                    if (select_ctrl_pressed) {
                        keycode_to_send = C(keycode_to_send);
                    }
                    break;
                case KC_SLRR:
                    keycode_to_send = KC_RIGHT;
                    if (select_ctrl_pressed) {
                        keycode_to_send = C(keycode_to_send);
                    }
                    break;
                case KC_SLRH:
                    keycode_to_send = KC_HOME;
                    break;
                case KC_SLRE:
                    keycode_to_send = KC_END;
                    break;
                default:
                    return false;
            }
            if (select_shift_pressed) {
                keycode_to_send = S(keycode_to_send);
            }
            if (select_alt_pressed) {
                keycode_to_send = A(keycode_to_send);
            }
            if (pressed) {
                register_code16(keycode_to_send);
            } else {
                unregister_code16(keycode_to_send);
            }
            return false;

        case KC_SLLU ... KC_SLLR:
            switch (keycode) {
                case KC_SLLU:
                    keycode_to_send = KC_UP;
                    break;
                case KC_SLLD:
                    keycode_to_send = KC_DOWN;
                    break;
                case KC_SLLL:
                    keycode_to_send = KC_LEFT;
                    break;
                case KC_SLLR:
                    keycode_to_send = KC_RIGHT;
                    break;
                default:
                    return false;
            }
            switch (select_last_modifier) {
                case SELECT_CTRL:
                    keycode_to_send = C(keycode_to_send);
                    break;
                case SELECT_SHIFT:
                    keycode_to_send = S(keycode_to_send);
                    break;
                case SELECT_ALT:
                    keycode_to_send = A(keycode_to_send);
                    break;
                case SELECT_NONE:
                    break;
                default:
                    return false;
            }
            if (pressed) {
                register_code16(keycode_to_send);
            } else {
                unregister_code16(keycode_to_send);
            }
            return false;
        default:
            return false;
    }
}

// ============================================================================
// OVERLOADED MODIFIER KEYS
// ============================================================================

/*

- MEGA and MINI modifier keys serve as heavily-overloaded versions of CTRL and ALT

- Tapping MEGA or MINI once:
    - Activates a one-shot modifier
        - Both one-shot modifiers can be stacked together
        - One-shot modifier processing is customizable
    - Emits an arbitrary keycode for AHK integration

- Tapping MEGA or MINI again, slowly:
    - Turns off the one-shot modifier if you haven't used it
    - Emits an arbitrary keycode (intended for AHK integration)

- Tapping MEGA or MINI multiple times, rapidly:
    - Emits an arbitrary keycode (could be a normal keycode or something for AHK integration)
    - Does not keep turning the one-shot modifier on and off

- Holding MEGA or MINI:
    - After a delay, activates a modifier, in this case CTRL and ALT
    - Instantly activates the respective keymap layer
        - Pressing any keys on this keymap layer:
            - Intercepts any tap actions, like HOLD_ON_OTHER_KEY_PRESS
            - Deactivates the aforementioned modifier

 */

#define MEGA_DUAL_KEYCODE KC_M  // Not a one-shot
#define MEGA_UNDO_KEYCODE KC_H  // Not a one-shot
#define MEGA_REDO_KEYCODE KC_R  // Not a one-shot
// #define MEGA_ATFW_KEYCODE KC_  // Not a one-shot, disabled
// #define MEGA_ATBK_KEYCODE KC_  // Not a one-shot, disabled
#define MEGA_DEL_KEYCODE KC_G  // Is an one-shot
#define MEGA_ESC_KEYCODE KC_T  // Is an one-shot
#define MEGA_GUI_KEYCODE KC_S  // Is an one-shot
#define MEGA_PSCR_KEYCODE KC_A  // Is an one-shot

// // Numpad that gets toggled on/off using MEGA (unsure about if I want this or not, it's not implemented yet)
// #define MEGA_1_KEYCODE KC_L
// #define MEGA_2_KEYCODE KC_COMM
// #define MEGA_3_KEYCODE KC_DOT
// #define MEGA_4_KEYCODE KC_N
// #define MEGA_5_KEYCODE KC_E
// #define MEGA_6_KEYCODE KC_O
// #define MEGA_7_KEYCODE KC_F
// #define MEGA_8_KEYCODE KC_U
// #define MEGA_9_KEYCODE KC_P
// #define MEGA_0_KEYCODE KC_I

#define N_MKEYS 2
#define MKEY_MULTITAPPING_TERM 300LL

const uint16_t MKEY_TOGGLE_KEYCODES[] = {KC_F19, KC_F24};
const uint16_t MKEY_MODIFIER_KEYCODES[] = {KC_LALT, KC_LCTL};
const uint16_t MKEY_MULTITAP_KEYCODES[] = {C(A(KC_DEL)), C(S(KC_ESC))};
const uint8_t MKEY_LAYERS[] = {_MINI, _MEGA};
const int MKEY_TAPPING_TERM[] = {600, 200};
const bool MKEY_EAGER[] = {false, true};
const bool MKEY_MOD_UP_ON_INTERRUPT[] = {true, false};

bool mkey_interrupt_on[N_MKEYS] = {false};
bool mkey_timer_on[N_MKEYS] = {false};
bool mkey_was_interrupted[N_MKEYS] = {false};
bool mkey_was_timed_out[N_MKEYS] = {false};
long long mkey_down_start_time[N_MKEYS] = {0};

bool mkey_oneshot_suppression = false;
bool mkey_oneshot_active[N_MKEYS] = {false};
bool mkey_multitap_possible[N_MKEYS] = {false};
long long mkey_multitap_start_time[N_MKEYS] = {0};
bool mkey_multitap_streak[N_MKEYS] = {false};

static void activate_oneshot(int mkey_idx) {
    tap_code16(MKEY_TOGGLE_KEYCODES[mkey_idx]);
    mkey_oneshot_active[mkey_idx] = true;
    if (mkey_idx == 1) {
        redo_next = false;  // Reset dual undo/redo
    }
#ifdef RGBLIGHT_ENABLE
    if (mkey_idx == 0) {
        if (mkey_oneshot_active[1]) {
            rgb_set_first_waypoint(HUE_MINI_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 200);
            rgb_set_next_waypoint(HUE_MINI_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 300);
            rgb_set_next_waypoint(HUE_MAIN, 255, RGBLIGHT_LIMIT_VAL, 500);
        } else {
            rgb_set_first_waypoint(HUE_MINI_ACCENT, 255, 0, 0);
            rgb_set_next_waypoint(HUE_MINI_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_MINI_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_MAIN, 255, RGBLIGHT_LIMIT_VAL, 500);
        }
        rgb_set_next_waypoint(nudge_hue(HUE_MAIN, HUE_MINI_ACCENT, -1 * HUE_DRIFT_AMP), 255, RGBLIGHT_LIMIT_VAL, 2000);
        rgb_set_next_waypoint(nudge_hue(HUE_MAIN, HUE_MINI_ACCENT, HUE_DRIFT_AMP), 255, RGBLIGHT_LIMIT_VAL, 4000);
    } else if (mkey_idx == 1) {
        if (mkey_oneshot_active[0]) {
            rgb_set_first_waypoint(HUE_MEGA_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 200);
            rgb_set_next_waypoint(HUE_MEGA_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 300);
            rgb_set_next_waypoint(HUE_MAIN, 255, RGBLIGHT_LIMIT_VAL, 500);
        } else {
            rgb_set_first_waypoint(HUE_MEGA_ACCENT, 255, 0, 0);
            rgb_set_next_waypoint(HUE_MEGA_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_MEGA_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_MAIN, 255, RGBLIGHT_LIMIT_VAL, 500);
        }
        rgb_set_next_waypoint(nudge_hue(HUE_MAIN, HUE_MEGA_ACCENT, -1 * HUE_DRIFT_AMP), 255, RGBLIGHT_LIMIT_VAL, 2000);
        rgb_set_next_waypoint(nudge_hue(HUE_MAIN, HUE_MEGA_ACCENT, HUE_DRIFT_AMP), 255, RGBLIGHT_LIMIT_VAL, 4000);
    }
#endif
}

static void deactivate_all_oneshots(void) {
#ifdef RGBLIGHT_ENABLE
    if (mkey_oneshot_active[0] && mkey_oneshot_active[1]) {
        rgb_set_first_waypoint(HUE_MAIN, 255, RGBLIGHT_LIMIT_VAL, 50);
        rgb_set_next_waypoint(HUE_MAIN, 255, 0, 100);
        rgb_set_next_waypoint(HUE_MAIN, 255, 0, 100);
    } else if (mkey_oneshot_active[0]) {
        rgb_set_first_waypoint(HUE_MINI_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
        rgb_set_next_waypoint(HUE_MINI_ACCENT, 255, 0, 100);
        rgb_set_next_waypoint(HUE_MINI_ACCENT, 255, 0, 100);
    } else if (mkey_oneshot_active[1]) {
        rgb_set_first_waypoint(HUE_MEGA_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
        rgb_set_next_waypoint(HUE_MEGA_ACCENT, 255, 0, 100);
        rgb_set_next_waypoint(HUE_MEGA_ACCENT, 255, 0, 100);
    }
#endif
    for (int i = 0; i < N_MKEYS; i++) {
        if (mkey_oneshot_active[i]) {
            tap_code16(MKEY_TOGGLE_KEYCODES[i]);
            mkey_oneshot_active[i] = false;
        }
    }
}

static void mkey_activate_layer(int mkey_idx) {
    layer_on(MKEY_LAYERS[mkey_idx]);
    if (mkey_idx == 0) {
        select_last_modifier = SELECT_ALT;
    }
}

static void mkey_deactivate_layer(int mkey_idx) {
    layer_off(MKEY_LAYERS[mkey_idx]);
}

static bool mkey_down(int mkey_idx) {
    mkey_activate_layer(mkey_idx);
    if (mkey_oneshot_active[mkey_idx]) {
        deactivate_all_oneshots();
        mkey_oneshot_suppression = true;  // Since we're turning off the oneshot modifier, don't turn it back on when we release the key
    } else {
        mkey_oneshot_suppression = false;
    }
    if (MKEY_EAGER[mkey_idx]) {
        register_code16(MKEY_MODIFIER_KEYCODES[mkey_idx]);
    }
    return false;
}

static bool mkey_up_tap(long long time, int mkey_idx) {
    mkey_deactivate_layer(mkey_idx);
    if (MKEY_EAGER[mkey_idx]) {
        unregister_code16(MKEY_MODIFIER_KEYCODES[mkey_idx]);
    }
    if (!mkey_multitap_possible[mkey_idx] || time - mkey_multitap_start_time[mkey_idx] >= MKEY_MULTITAPPING_TERM) {
        if (!mkey_oneshot_suppression) {
            activate_oneshot(mkey_idx);
        }
        mkey_multitap_streak[mkey_idx] = false;
    } else if (!mkey_multitap_streak[mkey_idx]) {
        tap_code16(MKEY_MULTITAP_KEYCODES[mkey_idx]);
        mkey_multitap_streak[mkey_idx] = true;
    } else {
        tap_code16(MKEY_MULTITAP_KEYCODES[mkey_idx]);
    }
    mkey_multitap_possible[mkey_idx] = true;
    mkey_multitap_start_time[mkey_idx] = mkey_down_start_time[mkey_idx];
    return false;
}

static bool mkey_up_interrupted(int mkey_idx) {
    mkey_deactivate_layer(mkey_idx);
    mkey_multitap_possible[mkey_idx] = false;
    if (!MKEY_MOD_UP_ON_INTERRUPT[mkey_idx]) {
        unregister_code16(MKEY_MODIFIER_KEYCODES[mkey_idx]);
    }
    return false;
}

static bool mkey_up_hold(int mkey_idx) {
    mkey_deactivate_layer(mkey_idx);
    if (!mkey_was_interrupted[mkey_idx]) {
        mkey_interrupt_on[mkey_idx] = false;
        unregister_code16(MKEY_MODIFIER_KEYCODES[mkey_idx]);
    }
    mkey_multitap_possible[mkey_idx] = false;
    return false;
}

static void mkey_interrupt(bool interrupt_pressed, uint16_t keycode, int mkey_idx) {
    if (interrupt_pressed && keycode != KC_MINI && keycode != KC_MEGA && keycode != KC_LSFT && keycode != KC_RSFT && keycode != KC_LCTL && keycode != KC_RCTL && keycode != KC_LALT && keycode != KC_RALT) {
        if (mkey_was_timed_out[mkey_idx]) {
            mkey_interrupt_on[mkey_idx] = false;
            mkey_was_interrupted[mkey_idx] = true;
            if (MKEY_MOD_UP_ON_INTERRUPT[mkey_idx]) {
                unregister_code16(MKEY_MODIFIER_KEYCODES[mkey_idx]);
            }
        } else {
            mkey_interrupt_on[mkey_idx] = false;
            mkey_timer_on[mkey_idx] = false;
            mkey_was_interrupted[mkey_idx] = true;
            if (MKEY_MOD_UP_ON_INTERRUPT[mkey_idx] && MKEY_EAGER[mkey_idx]) {
                unregister_code16(MKEY_MODIFIER_KEYCODES[mkey_idx]);
            }
        }
    }
}

static void mkey_timeout(int mkey_idx) {
    mkey_timer_on[mkey_idx] = false;
    mkey_was_timed_out[mkey_idx] = true;
    if (!MKEY_EAGER[mkey_idx]) {
        register_code16(MKEY_MODIFIER_KEYCODES[mkey_idx]);
    }
#ifdef RGBLIGHT_ENABLE
    if (!MKEY_EAGER[mkey_idx]) {
        if (mkey_idx == 0) {
            rgb_set_first_waypoint(HUE_MINI_ACCENT, 255, 0, 0);
            rgb_set_next_waypoint(HUE_MINI_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_MAIN, 255, RGBLIGHT_LIMIT_VAL, 300);
            rgb_set_next_waypoint(HUE_MAIN, 255, 0, 500);
            rgb_set_next_waypoint(HUE_MAIN, 255, 0, 500);
        } else if (mkey_idx == 1) {
            rgb_set_first_waypoint(HUE_MEGA_ACCENT, 255, 0, 0);
            rgb_set_next_waypoint(HUE_MEGA_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_MAIN, 255, RGBLIGHT_LIMIT_VAL, 300);
            rgb_set_next_waypoint(HUE_MAIN, 255, 0, 500);
            rgb_set_next_waypoint(HUE_MAIN, 255, 0, 500);
        }
    }
#endif
}

static bool process_mkey(bool pressed, long long time, int mkey_idx) {
    if (pressed) {
        if (is_caps_word_on()) {
            // If we're using this key to turn off caps word, don't do anything on the up event if tapped
            caps_word_off();
            mkey_interrupt_on[mkey_idx] = true;
            mkey_timer_on[mkey_idx] = true;
            mkey_was_interrupted[mkey_idx] = false;
            mkey_was_timed_out[mkey_idx] = false;
            mkey_down_start_time[mkey_idx] = time;
            bool return_value = mkey_down(mkey_idx);
            mkey_oneshot_suppression = true;
            return return_value;
        } else {
            mkey_interrupt_on[mkey_idx] = true;
            mkey_timer_on[mkey_idx] = true;
            mkey_was_interrupted[mkey_idx] = false;
            mkey_was_timed_out[mkey_idx] = false;
            mkey_down_start_time[mkey_idx] = time;
            return mkey_down(mkey_idx);
        }
    } else if (mkey_was_interrupted[mkey_idx]) {
        return mkey_up_interrupted(mkey_idx);
    } else if (mkey_was_timed_out[mkey_idx]) {
        return mkey_up_hold(mkey_idx);
    } else {
        mkey_interrupt_on[mkey_idx] = false;
        mkey_timer_on[mkey_idx] = false;
        return mkey_up_tap(time, mkey_idx);
    }
}

// ============================================================================
// BASE LAYER TOGGLE
// ============================================================================

#define BASE_TAPPING_TERM 300

bool base_timer_on = false;
bool base_timed_out = false;
long long base_start_time = 0;
bool base_toggle_suppression = false;
bool base_complete_suppression = false;

static void base_activate_layer(uint8_t layer) {
    switch (layer) {
        case _WORK:
#ifdef RGBLIGHT_ENABLE
            if (layer_state_is(_GAME)) {
                rgb_set_first_waypoint(HUE_GAME_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
                rgb_set_next_waypoint(HUE_GAME_ACCENT, 255, 0, 100);
                rgb_set_next_waypoint(HUE_GAME_ACCENT, 255, 0, 100);
            } else {
                rgb_set_first_waypoint(HUE_QWER_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
                rgb_set_next_waypoint(HUE_QWER_ACCENT, 255, 0, 100);
                rgb_set_next_waypoint(HUE_QWER_ACCENT, 255, 0, 100);
            }

#endif
            layer_off(_QWER);
            layer_off(_GAME);
            return;
        case _QWER:
            layer_on(_QWER);
            layer_off(_GAME);
#ifdef RGBLIGHT_ENABLE
            rgb_set_first_waypoint(HUE_QWER_ACCENT, 255, 0, 0);
            rgb_set_next_waypoint(HUE_QWER_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_QWER_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_QWER_ACCENT, SAT_BASE, RGBLIGHT_LIMIT_VAL, 500);
            rgb_set_next_waypoint(HUE_QWER_ACCENT, SAT_BASE, RGBLIGHT_LIMIT_VAL, 500);
#endif
            return;
        case _GAME:
            layer_off(_QWER);
            layer_on(_GAME);
#ifdef RGBLIGHT_ENABLE
            rgb_set_first_waypoint(HUE_GAME_ACCENT, 255, 0, 0);
            rgb_set_next_waypoint(HUE_GAME_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_GAME_ACCENT, 255, RGBLIGHT_LIMIT_VAL, 50);
            rgb_set_next_waypoint(HUE_GAME_ACCENT, SAT_BASE, RGBLIGHT_LIMIT_VAL, 500);
            rgb_set_next_waypoint(HUE_GAME_ACCENT, SAT_BASE, RGBLIGHT_LIMIT_VAL, 500);
#endif
            return;
        default:
            return;
    }
}

static void base_timeout(void) {
    base_timer_on = false;
    base_timed_out = true;
    if (!mkey_oneshot_active[0] && !mkey_oneshot_active[1]) {
        base_activate_layer(_GAME);
    }
}

static bool process_base(bool pressed, long long time) {

    // If we're using this key to turn off caps word, don't do anything for either the down or up events
    if (is_caps_word_on()) {
        caps_word_off();
        base_complete_suppression = true;
        return false;
    }
    if (base_complete_suppression) {
        base_complete_suppression = false;
        return false;
    }

    // If there's a one-shot modifier active, don't do anything
    if (mkey_oneshot_active[0] || mkey_oneshot_active[1]) {
        return false;
    }

    // Normal processing
    if (pressed) {
        if (layer_state_is(_QWER) || layer_state_is(_GAME)) {
            base_activate_layer(_WORK);
            base_toggle_suppression = true;  // Since we just switched to _WORK, don't switch to something else when we release the key
        } else {
            base_timer_on = true;
            base_timed_out = false;
            base_start_time = time;
            base_toggle_suppression = false;
        }
    } else if (!base_toggle_suppression && !base_timed_out) {
        base_timer_on = false;
        if (layer_state_is(_QWER) || layer_state_is(_GAME)) {
            base_activate_layer(_WORK);
        } else {
            base_activate_layer(_QWER);
        }
    }
    return false;
}

// ============================================================================
// AUTO ALT-TAB
// ============================================================================

// #define ATAB_DURATION 1000LL

// bool atab_interrupt_and_timer_on = false;
// long long atab_start_time = 0;

// static void atab_interrupt(uint16_t keycode) {
//     bool interrupt = true;
//     interrupt = interrupt && keycode != KC_ATFW && keycode != KC_ATBK;
//     interrupt = interrupt && (!mkey_oneshot_active[1] || (keycode != MEGA_ATFW_KEYCODE && keycode != MEGA_ATBK_KEYCODE));
//     if (interrupt) {
//         atab_interrupt_and_timer_on = false;
//         unregister_code(KC_LALT);
//     }
// }

// static void atab_timeout(void) {
//     atab_interrupt_and_timer_on = false;
//     unregister_code(KC_LALT);
// }

// static bool process_atab(bool pressed, long long time, bool backwards) {
//     if (pressed) {
//         if (!atab_interrupt_and_timer_on) {
//             atab_interrupt_and_timer_on = true;
//             register_code(KC_LALT);
//         }
//         atab_start_time = time;
//         if (backwards) {
//             tap_code16(S(KC_TAB));
//         } else {
//             tap_code(KC_TAB);
//         }
//     }
//     return false;
// }

// ============================================================================
// ONESHOT LOGIC
// ============================================================================

static bool keycode_is_basic(uint16_t keycode) {
    return keycode >= KC_A && keycode <= KC_F24;
}

static bool oneshot_mega_mini(uint16_t keycode, bool pressed) {
    if (!keycode_is_basic(keycode)) {
        return true;
    } else if (!pressed) {
        return true;
    } else {
        tap_code16(LCA(keycode));
        deactivate_all_oneshots();
        return false;
    }
}

static bool oneshot_mega(uint16_t keycode, long long time, bool pressed) {
    // It's called "oneshot" but I turned it into more of a toggle by removing deactivate_oneshot()
    if (!keycode_is_basic(keycode)) {
        return false;
    } else {
        switch (keycode) {
            case MEGA_DUAL_KEYCODE:
                return process_dual(pressed);
            case MEGA_UNDO_KEYCODE:
                return process_undo(pressed);
            case MEGA_REDO_KEYCODE:
                return process_redo(pressed);
            // case MEGA_ATFW_KEYCODE:
            //     return process_atab(pressed, time, false);
            // case MEGA_ATBK_KEYCODE:
            //     return process_atab(pressed, time, true);
            case MEGA_DEL_KEYCODE:
                tap_code(KC_DEL);
                deactivate_all_oneshots();
                return false;
            case MEGA_ESC_KEYCODE:
                tap_code(KC_ESC);
                deactivate_all_oneshots();
                return false;
            case MEGA_GUI_KEYCODE:
                tap_code(KC_LGUI);
                deactivate_all_oneshots();
                return false;
            case MEGA_PSCR_KEYCODE:
                tap_code(KC_PSCR);
                deactivate_all_oneshots();
                return false;
            default:
                return true;
        }
    }
}

static bool oneshot_mini(uint16_t keycode, bool pressed) {
    if (!keycode_is_basic(keycode)) {
        return true;
    } else if (!pressed) {
        return true;
    } else {
        tap_code16(A(keycode));
        deactivate_all_oneshots();
        return false;
    }
}

static bool process_other(bool pressed, long long time, uint16_t keycode) {
    if (mkey_oneshot_active[0] && mkey_oneshot_active[1]) {
        return oneshot_mega_mini(keycode, pressed);
    } else if (mkey_oneshot_active[0]) {
        return oneshot_mini(keycode, pressed);
    } else if (mkey_oneshot_active[1]) {
        return oneshot_mega(keycode, time, pressed);
    } else {
        return true;
    }
}

// ============================================================================
// PROCESS_RECORD_USER AND MATRIX_SCAN_USER
// ============================================================================

static void check_hold_interrupts(bool pressed, uint16_t keycode) {
    if (symb_interrupt_on) {
        symb_interrupt(pressed, keycode);
    }
    // if (atab_interrupt_and_timer_on) {
    //     atab_interrupt(keycode);
    // }
    for (int i = 0; i < N_MKEYS; i++) {
        if (mkey_interrupt_on[i]) {
            mkey_interrupt(pressed, keycode, i);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    check_hold_interrupts(record->event.pressed, keycode);
    switch (keycode) {
        case KC_MINI:
            return process_mkey(record->event.pressed, ll_time, 0);
        case KC_MEGA:
            return process_mkey(record->event.pressed, ll_time, 1);
        case KC_SYMB:
            return process_symb(record->event.pressed, ll_time);
        case KC_BASE:
            return process_base(record->event.pressed, ll_time);
        case KC_FUNC:
            return process_func(record->event.pressed);
        case KC_DELL:
            return process_dell(record->event.pressed);
        // case KC_ATFW:
        //     return process_atab(record->event.pressed, ll_time, false);
        // case KC_ATBK:
        //     return process_atab(record->event.pressed, ll_time, true);
        case KC_DUAL:
            return process_dual(record->event.pressed);
        case KC_UNDO:
            return process_undo(record->event.pressed);
        case KC_REDO:
            return process_redo(record->event.pressed);
#if defined(ENCODER_ENABLE) && defined (MIDI_ENABLE)
        case KC_ENCL:
            return process_enco(record->event.pressed, false);
        case KC_ENCR:
            return process_enco(record->event.pressed, true);
#else
        case KC_ENCL:
            return false;
        case KC_ENCR:
            return false;
#endif
        case KC_SLMC ... KC_SLLR:
            return process_slxx(record->event.pressed, keycode);
        default:
            return process_other(record->event.pressed, ll_time, keycode);
    }
}

uint16_t prev_time = 0;
void matrix_scan_user(void) {

    // Maintain a long long timer to prevent bugs from rollovers
    ll_time += timer_elapsed(prev_time);
    prev_time = timer_read();

    // Alt tab timer
    // if (atab_interrupt_and_timer_on && ll_time - atab_start_time >= ATAB_DURATION) {
    //     atab_timeout();
    // }

    // Base layer timer
    if (base_timer_on && ll_time - base_start_time >= BASE_TAPPING_TERM) {
        base_timeout();
    }

    // M-key timers
    for (int i = 0; i < N_MKEYS; i++) {
        if (mkey_timer_on[i] && ll_time - mkey_down_start_time[i] >= MKEY_TAPPING_TERM[i]) {
            mkey_timeout(i);
        }
    }

#ifdef RGBLIGHT_ENABLE
    // RGB engine
    float ratio;
    HSV temp_waypoint;
    float temp_duration;
    if (n_rgb_waypoints > 0 && ll_time > rgb_next_update_time) {
        rgb_next_update_time = ll_time + RGB_UPDATE_INTERVAL;
        ratio = ((float)(ll_time - rgb_times[rgb_current_start_idx])) / (rgb_times[rgb_current_start_idx + 1] - rgb_times[rgb_current_start_idx]);
        rgb_current_state = hsv_lerp(rgb_waypoints[rgb_current_start_idx], rgb_waypoints[rgb_current_start_idx + 1], ratio);
        rgblight_sethsv_noeeprom(rgb_current_state.h, rgb_current_state.s, rgb_current_state.v);
        if (ratio > 1) {
            if (rgb_current_start_idx == n_rgb_waypoints - 1) {
                if (rgb_waypoints[rgb_current_start_idx].h == rgb_waypoints[rgb_current_start_idx + 1].h
                    && rgb_waypoints[rgb_current_start_idx].s == rgb_waypoints[rgb_current_start_idx + 1].s
                    && rgb_waypoints[rgb_current_start_idx].v == rgb_waypoints[rgb_current_start_idx + 1].v) {
                        n_rgb_waypoints = 0;
                } else {
                    // keep looping the last two waypoints
                    temp_duration = rgb_times[rgb_current_start_idx + 1] - rgb_times[rgb_current_start_idx];
                    temp_waypoint.h = rgb_waypoints[rgb_current_start_idx].h;
                    temp_waypoint.s = rgb_waypoints[rgb_current_start_idx].s;
                    temp_waypoint.v = rgb_waypoints[rgb_current_start_idx].v;
                    rgb_times[rgb_current_start_idx] = rgb_times[rgb_current_start_idx + 1];
                    rgb_times[rgb_current_start_idx + 1] = rgb_times[rgb_current_start_idx] + temp_duration;
                    rgb_waypoints[rgb_current_start_idx].h = rgb_waypoints[rgb_current_start_idx + 1].h;
                    rgb_waypoints[rgb_current_start_idx].s = rgb_waypoints[rgb_current_start_idx + 1].s;
                    rgb_waypoints[rgb_current_start_idx].v = rgb_waypoints[rgb_current_start_idx + 1].v;
                    rgb_waypoints[rgb_current_start_idx + 1].h = temp_waypoint.h;
                    rgb_waypoints[rgb_current_start_idx + 1].s = temp_waypoint.s;
                    rgb_waypoints[rgb_current_start_idx + 1].v = temp_waypoint.v;
                }
            } else {
                rgb_current_start_idx++;
            }
        }
    }
#endif

}
