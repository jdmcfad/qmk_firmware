#include "mindsound_tapdance.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

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

static tap key_tap_state = {
  .is_press_action = true,
  .state = 0
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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ALLONS_Y]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_finished, key_reset)
};
