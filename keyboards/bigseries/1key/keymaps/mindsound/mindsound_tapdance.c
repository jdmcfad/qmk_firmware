#include "mindsound_tapdance.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

// increments for h, s, v
// factors of 360: 1,2,3,4,5,6,8,9,10,12,15,18,20,24,30,36,40,45,60,72,90,120,180,360
#define HUE_INCREMENT 45
#define SAT_INCREMENT 32
#define VAL_INCREMENT 32
#define INIT_DELAY 200

/*
 * Based on the "Quad Function Tap-Dance" implementation in the QMK Tap Dance docs. This
 * implementation assumes there is only one key. This implementation omits the "double'
 * single tap" since I don't plan for the single key to be entered twice quickly.
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (!state->interrupted && state->pressed)  return DOUBLE_HOLD;
  }
  if (state->count == 3) {
    if (!state->interrupted && state->pressed)  return TRIPLE_HOLD;
  }
  if (state->count == 4) {
    if (!state->interrupted && state->pressed)  return QUAD_HOLD;
  }
  return END_MAGIC;
}

static uint16_t delay_runonce;

static tap key_tap_state = {
  .is_press_action = true,
  .state = 0
};

static hsv current_hsv = {
  .h = 200,
  .s = 128,
  .v = 64
};

void key_finished (qk_tap_dance_state_t *state, void *user_data) {
  key_tap_state.state = cur_dance(state);
  switch (key_tap_state.state) {
    case SINGLE_TAP:  register_code(KC_ENTER); break;
    case SINGLE_HOLD: register_code16(KC_TD_SINGLE_HOLD); break;
    case DOUBLE_HOLD: register_code16(KC_TD_DOUBLE_HOLD); break;
    case TRIPLE_HOLD: register_code16(KC_TD_TRIPLE_HOLD); break;
    case QUAD_HOLD:   register_code16(KC_TD_QUAD_HOLD); break;
  }
}

void key_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (key_tap_state.state) {
    case SINGLE_TAP:  unregister_code(KC_ENTER); break;
    case SINGLE_HOLD: unregister_code16(KC_TD_SINGLE_HOLD); break;
    case DOUBLE_HOLD: unregister_code16(KC_TD_DOUBLE_HOLD); break;
    case TRIPLE_HOLD: unregister_code16(KC_TD_TRIPLE_HOLD); break;
    case QUAD_HOLD:   unregister_code16(KC_TD_QUAD_HOLD); break;
  }
  key_tap_state.state = 0;
}

void prepare_to_dong_rgblight_into_submission_I_mean_initialize_it(void) {
  delay_runonce = timer_read();
}

void dong_rgblight_into_submission_I_mean_initialize_it(void) {
  static bool runonce = true;
  if (runonce && timer_elapsed(delay_runonce) > INIT_DELAY) {
    runonce = false;
    update_rgblight();
    rgblight_mode_noeeprom(1);
    rgblight_enable_noeeprom();
  }
}

// simple increment wrapping at 360 degrees
void inc_hue(void) {
  current_hsv.h += HUE_INCREMENT;
  current_hsv.h %= 360;
}

// ramp linearly to 512 -- the math in update_rgblight turns it into a triangle
// with an inflection point at 256
void inc_sat(void) {
  current_hsv.h += VAL_INCREMENT;
  current_hsv.h %= 512;
}

// ramp linearly to 512 -- the math in update_rgblight turns it into a triangle
// with an inflection point at 256
void inc_val(void) {
  current_hsv.h += VAL_INCREMENT;
  current_hsv.h %= 512;
}

void update_rgblight(void) {
  uint8_t s = current_hsv.s > 512 ? (uint8_t) current_hsv.s : (uint8_t)(512 - current_hsv.s);
  uint8_t v = current_hsv.v > 512 ? (uint8_t) current_hsv.v : (uint8_t)(512 - current_hsv.v);
  rgblight_sethsv_noeeprom(current_hsv.h, s, v);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ALLONS_Y]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_finished, key_reset)
};
