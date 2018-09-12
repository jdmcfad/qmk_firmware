#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

typedef struct {
  bool is_press_action;
  int state;
} tap;

// NOTE: I'm using 16 bit types for s and v so I don't have to worry about overflow in my math
typedef struct {
  uint16_t h;
  uint16_t s;
  uint16_t v;
} hsv;

// keycodes used internally
enum tapdance_keycodes {
  KC_TD_SINGLE_HOLD = SAFE_RANGE,
  KC_TD_DOUBLE_HOLD,
  KC_TD_TRIPLE_HOLD,
  KC_TD_QUAD_HOLD,
  KC_TD_PENTA_HOLD
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
  PENTA_TAP,
  PENTA_HOLD,
  END_MAGIC
};

// https://i.imgur.com/rosLdn2.gif
enum TAP_DANCE {
  TD_ALLONS_Y = 0,
};

// state variables for dealing with custom held keys
volatile bool party_mode_active;
volatile uint16_t party_mode_hue;
volatile uint16_t party_mode_timer;
volatile uint16_t held_keycode;
volatile uint16_t held_keycode_timer;

int cur_dance (qk_tap_dance_state_t *state);
void key_finished (qk_tap_dance_state_t *state, void *user_data);
void key_reset (qk_tap_dance_state_t *state, void *user_data);

// HSV helper functions
void prepare_to_dong_rgblight_into_submission_I_mean_initialize_it(void);
void dong_rgblight_into_submission_I_mean_initialize_it(void);
void inc_hue(void);
void inc_sat(void);
void inc_val(void);
void reset_rgblight(void);
void update_rgblight(void);
void update_party_mode(uint16_t inc_hue);
