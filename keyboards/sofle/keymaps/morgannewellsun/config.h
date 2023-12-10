#pragma once

// Handedness by EEPROM
// Flash the left half with `qmk flash -kb sofle -km morgannewellsun -bl uf2-split-left -e CONVERT_TO=promicro_rp2040`
// Flash the right half with `qmk flash -kb sofle -km morgannewellsun -bl uf2-split-right -e CONVERT_TO=promicro_rp2040`
// This is only necessary once; you can just flash your firmware normally afterwards
#define EE_HANDS

// NKRO
#define FORCE_NKRO

// MIDI
#define MIDI_BASIC

// Caps word
#ifdef TAPPING_TERM
#undef TAPPING_TERM
#define TAPPING_TERM 175
#endif
#define CAPS_WORD_IDLE_TIMEOUT 0
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// RGB
#define WS2812_DI_PIN D3
#define RGBLIGHT_LIMIT_VAL 120  // Higher values may cause controller to crash
#define RGBLED_NUM 72  // (29 per key + 6 bottom + 1 top) * 2
#define RGBLED_SPLIT { 36, 36 }
