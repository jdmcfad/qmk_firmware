#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

typedef struct {
  bool is_press_action;
  int state;
} tap;

typedef struct {
  uint16_t h;
  uint8_t s;
  uint8_t v;
} hsv;

// keycodes used internally
enum tapdance_keycodes {
  KC_TD_SINGLE_HOLD = SAFE_RANGE,
  KC_TD_DOUBLE_HOLD,
  KC_TD_TRIPLE_HOLD,
  KC_TD_QUAD_HOLD
};

enum tapdance_states {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP,
  TRIPLE_HOLD,
  QUAD_TAP,
  QUAD_HOLD,
  END_MAGIC
};

//Tap dance enums
enum TAP_DANCE {
  // https://i.imgur.com/rosLdn2.gif
  TD_ALLONS_Y = 0,
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);
