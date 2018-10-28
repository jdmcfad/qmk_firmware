#include QMK_KEYBOARD_H

#ifdef BACKLIGHT_ENABLE
#include "flicker.h"
#endif

// TODO: guard everything with ifdef AUDIO_ENABLE
#include "audio_delay.h"

extern keymap_config_t keymap_config;

audio_delay_queue queue;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

// keycodes custom to this keymap:
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BL_FLICKER
};

// audio delay stuff:
float delay_song[][2] = {{440, 1}};

// flicker state:
#ifdef BACKLIGHT_ENABLE
bool flicker_enable = true;
bool flicker_isdown = false;
const uint8_t flicker_min_levels = 2;
const uint8_t flicker_max_levels = 7;
uint8_t flicker_restore_level = 0;
#endif

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// mod tap definitions:
#define CTRL_ESC MT(MOD_LCTL, KC_ESC)
#define HYPR_SPC MT(MOD_HYPR, KC_SPC)

// wait DELAY ms before unregistering media keys
#define MEDIA_KEY_DELAY 10


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | '    |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Del  | GUI  | Alt  |Lower |HyprSp|Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  CTRL_ESC, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_MPLY,  KC_DEL,  KC_LGUI, KC_LALT, LOWER, HYPR_SPC, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY  \
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |Clicky|ClkDn |ClkUp |ClkRst|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  MAGIC_UNHOST_NKRO, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,                  \
  _______,           _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,                 \
  _______,           MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, BL_TOGG, BL_DEC,  BL_INC,  BL_FLICKER,                 \
  _______,           _______, _______, _______, _______, _______, _______, _______, CLICKY_TOGGLE, CLICKY_DOWN, CLICKY_UP, CLICKY_RESET \
),

}; // end keymaps

// if backlighting is enabled, configure it on boot
void matrix_init_user(void) {
#ifdef BACKLIGHT_ENABLE
  // set to max
  backlight_level(BACKLIGHT_LEVELS);
  flicker_restore_level = get_backlight_level();

  // if breathing happens to be compiled in, turn it off
#ifdef BACKLIGHT_BREATHING
  breathing_disable();
#endif
#endif // BACKLIGHT_ENABLE

  audio_delay_clear(&queue);
}

void matrix_scan_user(void) {
  audio_delay_event *event = audio_delay_polling_pop(&queue);
  if (event == NULL) {
    return;
  }

  delay_song[0][0] = event->freq1;
  delay_song[0][1] = event->duration;
  play_notes(&delay_song, 1, false);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  return MACRO_NONE;
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // handle the _ADJUST layer and custom keycodes:
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
#ifdef BACKLIGHT_ENABLE
    case BL_FLICKER:
      if (record->event.pressed) {
        flicker_toggle();
      }
      return false;
      break;
#endif
  } // end switch case over custom keycodes

#ifdef BACKLIGHT_ENABLE
  if (flicker_enable) {
    if (record->event.pressed) {
      flicker_keydown();
    } else {
      flicker_keyup();
    }
  }
#endif

  if (record->event.pressed) {
    static int counter;
    const int echoes = 8;
    const int base_duration = 11; // must be greater than echoes!
    const uint32_t initial_delay = 30;
    const uint32_t base_delay = 1700;
    const float freq_detune = 0.998f;
    const float delay_stretch = 0.08f;

    // random diatonic frequency
    // float freq = 440.0f * (float)pow(2.0d, floor((((double)rand())/((double)RAND_MAX)) * 48.0d) / 12.0d);

    // random pentatonic frequency
    #define PENTATONIC_SCALE_LENGTH 5
    double pentatonic_scale[PENTATONIC_SCALE_LENGTH] = {0, 2, 4, 7, 9};
    #define PENTATONIC_FREQS_LENGTH 18
    float pentatonic_freqs[PENTATONIC_FREQS_LENGTH];
    for (int ii = 0; ii < PENTATONIC_FREQS_LENGTH; ii++) {
      double note = pentatonic_scale[ii % PENTATONIC_SCALE_LENGTH];
      double octave = ii / PENTATONIC_SCALE_LENGTH;
      pentatonic_freqs[ii] = 440.0f * (float)(pow(2.0d, note/12.0d) * pow(2.0d, octave));
    }

    // count up and down
    counter += 1;
    bool countup = (counter / PENTATONIC_FREQS_LENGTH) % 2 == 0;
    int pentatonic_freq_index;
    if (countup)
      pentatonic_freq_index = counter % PENTATONIC_FREQS_LENGTH;
    else
      pentatonic_freq_index = PENTATONIC_FREQS_LENGTH - (counter % PENTATONIC_FREQS_LENGTH) - 1;

    // 40% chance of picking a note a few notes away but carefully bound the values
    if (rand() % 5 < 1) {
      pentatonic_freq_index += 2 * ((rand() % 7) - 3);
    }
    if (pentatonic_freq_index < 0)
      pentatonic_freq_index = 0;
    if (pentatonic_freq_index >= PENTATONIC_FREQS_LENGTH)
      pentatonic_freq_index = PENTATONIC_FREQS_LENGTH - 1;

    float freq = pentatonic_freqs[pentatonic_freq_index];

    for (int ii = 0; ii < echoes; ii++) {

      // lower the frequency slightly each iteration
      freq *= freq_detune;

      uint32_t delay = initial_delay + (uint32_t)(((float)(base_delay * ii)) * (delay_stretch * (float)(ii + 1)));
      uint32_t duration = base_duration - ii;

      audio_delay_push(&queue,  delay, (audio_delay_event){freq, 0.0f, duration});
    }
  }

  return true;
}

void encoder_update(bool clockwise) {
  // handle layers
  if (IS_LAYER_ON(_RAISE)) {
    if (clockwise) {
      clicky_freq_up();
      clicky_play();
    } else {
      clicky_freq_down();
      clicky_play();
    }

    return;
  }

  // handle base layer
  uint16_t held_keycode_timer = timer_read();
  if (clockwise) {
    register_code(KC_VOLU);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
      // no-op
    }
    unregister_code(KC_VOLU);
  } else {
    register_code(KC_VOLD);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
      // no-op
    }
    unregister_code(KC_VOLD);
  }
}

// flicker implementation:
#ifdef BACKLIGHT_ENABLE
void flicker_toggle(void) {
  flicker_enable = !flicker_enable;
}

void flicker_keydown(void) {
  // guard condition: only set the level to restore if the flicker is NOT already down
  if (!flicker_isdown) {
    flicker_restore_level = get_backlight_level();
    flicker_isdown = true;
  }

  // calculate a random flicker level between min and max
  uint8_t flicker_level = (rand() % (flicker_max_levels - flicker_min_levels)) + flicker_min_levels;
  uint8_t level_to_set = flicker_level <= flicker_restore_level ? flicker_restore_level - flicker_level : 0;
  backlight_level(level_to_set);
}

void flicker_keyup(void) {
  backlight_level(flicker_restore_level);
  flicker_isdown = false;
}
#endif
