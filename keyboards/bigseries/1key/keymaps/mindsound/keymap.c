#include QMK_KEYBOARD_H
#include "mindsound_tapdance.h"

// debug message to evaluate QMK_KEYBOARD_H for use in VS Code config file:
//#pragma message "QMK_KEYBOARD_H=" STR(QMK_KEYBOARD_H)

#define PARTY_RATE_MS 10
#define PARTY_INC 8
#define UPDATE_RATE_MS 50

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(TD(TD_ALLONS_Y)),
};

void matrix_init_user(void) {
  prepare_to_dong_rgblight_into_submission_I_mean_initialize_it();
}

void matrix_scan_user(void) {
  dong_rgblight_into_submission_I_mean_initialize_it();

  // party mode supersedes all other modes
  if (party_mode_active && timer_elapsed(party_mode_timer) > PARTY_RATE_MS) {
    party_mode_timer = timer_read();
    update_party_mode(PARTY_INC);
  }

  // if we're holding a key and the timer has elapsed:
  if (held_keycode > 0 && timer_elapsed(held_keycode_timer) > UPDATE_RATE_MS) {
    // 1. reset the timer
    held_keycode_timer = timer_read();

    // 2. take action for whatever the held keycode is:
    switch (held_keycode) {
    case KC_TD_SINGLE_HOLD: inc_hue(); break;
    case KC_TD_DOUBLE_HOLD: inc_sat(); break;
    case KC_TD_TRIPLE_HOLD: inc_val(); break;
    }
  }
}

