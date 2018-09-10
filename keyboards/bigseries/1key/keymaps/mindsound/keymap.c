#include QMK_KEYBOARD_H
#include "mindsound_tapdance.h"

// debug message to evaluate QMK_KEYBOARD_H for use in VS Code config file:
//#pragma message "QMK_KEYBOARD_H=" STR(QMK_KEYBOARD_H)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(TD(TD_ALLONS_Y)),
};

// static uint16_t tapdance_timer;

static hsv current_hsv;

void matrix_init_user(void) {
  // hmm this gets blown away by breathing
  rgblight_sethsv(current_hsv.h, current_hsv.s, current_hsv.v);
}

