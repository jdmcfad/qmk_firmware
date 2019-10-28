#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// mod tap definitions:
#define CTRL_ESC MT(MOD_LCTL, KC_ESC)
#define HYPR_SPC MT(MOD_HYPR, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.              .-----------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |              |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |              |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+------..------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |RGBPrv||RGBNxt|   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Media | Del  | GUI  | Alt  |Raise |HSpace|Enter || Bksp |Space |Lower | Left | Down | Up   |Right |
   * `----------------------------------+-------------''------------------------------------------------'
   *                                    |HSpace|Enter || Bksp |Space |
   *                                    '-------------''-------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_GESC,   KC_1,    KC_2,    KC_3,    KC_4,  KC_5,                       KC_6,     KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,                       KC_Y,     KC_U,  KC_I,    KC_O,    KC_P,    KC_BSLS, \
    CTRL_ESC,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                       KC_H,     KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,    KC_N,   KC_B,      KC_N,     KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
    KC_MPLY,   KC_DEL,  KC_LGUI, KC_LALT, LOWER, HYPR_SPC,KC_ENT, KC_BSPC,   KC_SPACE, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,\
                                                 HYPR_SPC,KC_ENT, KC_BSPC,   KC_SPACE \
  ),

  /* LOWER
   */
  [_LOWER] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    KC_TILD, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, RGB_SAI, RGB_VAI, RGB_SAD, _______, _______,                   _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
    _______, RGB_HUD, RGB_VAD, RGB_HUI, _______, _______, RGB_RMOD,RGB_MOD, _______, _______, _______, KC_HOME, KC_END,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                                                 _______, _______, _______, _______ \
  ),

  /* RAISE
   */
  [_RAISE] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    KC_GRV,  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, RGB_SAI, RGB_VAI, RGB_SAD, _______, _______,                   _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
    _______, RGB_HUD, RGB_VAD, RGB_HUI, _______, _______, RGB_RMOD,RGB_MOD, _______, _______, _______, KC_PGUP, KC_PGDN, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                                                 _______, _______, _______, _______ \
  ),

};

// void encoder_update_user(uint8_t index, bool clockwise) {
//   if (index == 0) { /* First encoder */
//     if (clockwise) {
//       tap_code(KC_PGDN);
//     } else {
//       tap_code(KC_PGUP);
//     }
//   } else if (index == 1) { /* Second encoder from slave */
//     if (clockwise) {
//       tap_code(KC_UP);
//     } else {
//       tap_code(KC_DOWN);
//     }
//   }
// }
