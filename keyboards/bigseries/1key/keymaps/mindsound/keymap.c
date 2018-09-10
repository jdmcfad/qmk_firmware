#include QMK_KEYBOARD_H
#include "mindsound_tapdance.h"

// debug message to evaluate QMK_KEYBOARD_H for use in VS Code config file:
//#pragma message "QMK_KEYBOARD_H=" STR(QMK_KEYBOARD_H)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(TD(TD_ALLONS_Y)),
};

// static uint16_t tapdance_timer;

void matrix_init_user(void) {
  prepare_to_dong_rgblight_into_submission_I_mean_initialize_it();
}

void matrix_scan_user(void) {
  dong_rgblight_into_submission_I_mean_initialize_it();
}
