// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "bitbanger.h"
#include "matrix.h"

#include <stdio.h>

// https://stackoverflow.com/a/3208376
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')








// a LUT per yanfali
const uint16_t BITBANGER_LUT[128] = {
  KC_NO, // THIS IS ON LINE 30 SO THE LINE # MINUS 30 IS THE ASCII CODE OMGGGG
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  LCTL(KC_G),
  KC_BSPACE,
  KC_TAB,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_ENT,
  KC_NO,
  KC_NO,
  KC_NO,
  RESET, // device control 1
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_ESCAPE,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_NO,
  KC_SPACE,
  KC_EXCLAIM,
  KC_DOUBLE_QUOTE,
  KC_HASH,
  KC_DOLLAR,
  KC_PERCENT,
  KC_AMPERSAND,
  KC_QUOTE,
  KC_LEFT_PAREN,
  KC_RIGHT_PAREN,
  KC_ASTERISK,
  KC_PLUS,
  KC_COMMA,
  KC_MINUS,
  KC_DOT,
  KC_SLASH,
  KC_0,
  KC_1,
  KC_2,
  KC_3,
  KC_4,
  KC_5,
  KC_6,
  KC_7,
  KC_8,
  KC_9,
  KC_COLON,
  KC_SCOLON,
  KC_LT,
  KC_EQUAL,
  KC_GT,
  KC_QUESTION,
  KC_AT,
  LSFT(KC_A),
  LSFT(KC_B),
  LSFT(KC_C),
  LSFT(KC_D),
  LSFT(KC_E),
  LSFT(KC_F),
  LSFT(KC_G),
  LSFT(KC_H),
  LSFT(KC_I),
  LSFT(KC_J),
  LSFT(KC_K),
  LSFT(KC_L),
  LSFT(KC_M),
  LSFT(KC_N),
  LSFT(KC_O),
  LSFT(KC_P),
  LSFT(KC_Q),
  LSFT(KC_R),
  LSFT(KC_S),
  LSFT(KC_T),
  LSFT(KC_U),
  LSFT(KC_V),
  LSFT(KC_W),
  LSFT(KC_X),
  LSFT(KC_Y),
  LSFT(KC_Z),
  KC_LBRACKET,
  KC_BSLASH,
  KC_RBRACKET,
  KC_CIRCUMFLEX,
  KC_UNDERSCORE,
  KC_GRAVE,
  KC_A,
  KC_B,
  KC_C,
  KC_D,
  KC_E,
  KC_F,
  KC_G,
  KC_H,
  KC_I,
  KC_J,
  KC_K,
  KC_L,
  KC_M,
  KC_N,
  KC_O,
  KC_P,
  KC_Q,
  KC_R,
  KC_S,
  KC_T,
  KC_U,
  KC_V,
  KC_W,
  KC_X,
  KC_Y,
  KC_Z,
  KC_LEFT_CURLY_BRACE,
  KC_PIPE,
  KC_RIGHT_CURLY_BRACE,
  KC_TILDE,
  KC_DELETE
};

uint8_t bitbanger_bits = 0x0;
uint8_t bitbanger_current_bit = 8; // textual representation of base two is MSB!

// keycodes custom to this keymap:
enum bitbanger_keycodes {
  BITBANGER_0 = SAFE_RANGE,
  BITBANGER_1
};

// actual physical key matrix:
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = {
	{BITBANGER_1, BITBANGER_0}
  }
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
};

void matrix_scan_user(void) {
};

void matrix_init_user() {
  // HACK Enable backlight
  DDRB |= (1<<5) | (1<<6);
  PORTB |= (1<<5) | (1<<6);
};

// if the user has entered a complete uint8_t by pressing 8 individual bit keystrokes, change the keycode to what it SHOULD BE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // only handle keydown (no reason to wait for keyup)
  if (record->event.pressed) {
    switch (keycode) {
      case BITBANGER_0:
        bitbanger_bits &= ~(1 << (--bitbanger_current_bit));
        if (bitbanger_current_bit == 0) {
          bitbanger_output(bitbanger_bits);
          bitbanger_current_bit = 8;
        }
        return false;
        break;

      case BITBANGER_1:
        bitbanger_bits |= (1 << (--bitbanger_current_bit));
        if (bitbanger_current_bit == 0) {
          bitbanger_output(bitbanger_bits);
          bitbanger_current_bit = 8;
        }
        return false;
        break;
    }
  }

  // SWALLOW EVERYTHING BY DEFAULT
  return false;
}

// given a bit vector, presses the corresponding keycode
void bitbanger_output(uint8_t bits) {
  // awesome for debugging -- just types the bits as zeroes and ones
  // char buffer[50];
  // sprintf(buffer, BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(bits));
  // send_string(buffer);

  // (only doing 7-bit at the moment, implying first bit must be 0)
  if (bits > 127) {
    return;
  }

  uint16_t banged_keycode = BITBANGER_LUT[bits];

  // special case: RESET isn't a regular keycode
  if (banged_keycode == RESET) {
    reset_keyboard();
    return;
  }

  register_code16(banged_keycode);
  unregister_code16(banged_keycode);
}
