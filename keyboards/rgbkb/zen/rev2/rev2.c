#include "rev2.h"

// #ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    { 0,  1,  2,  3,  4,  5, NO_LED },
    { 6,  7,  8,  9,  10, 11, 12 },
    { 13, 14, 15, 16, 17, 18, 19 },
    { 20, 21, 22, 23, 24, 25, 26 },
    { 27, 28, 29, 30, 31, 32, 33 },
    { 34, 35, 36, 37, 38, 39, NO_LED },
    { 40, 41, 42, 43, 44, 45, 46 },
    { 47, 48, 49, 50, 51, 52, 53 },
    { 54, 55, 56, 57, 58, 59, 60 },
    { 61, 62, 63, 64, 65, 66, 67 }
}, {
    {  11,  14 }, {  28,  14 }, {  42,  14 }, {  56,  14 }, {  70,  14 }, {  84,  14 },
    {  11,  28 }, {  28,  28 }, {  42,  28 }, {  56,  28 }, {  70,  28 }, {  84,  28 },
    {  11,  42 }, {  28,  42 }, {  42,  42 }, {  56,  42 }, {  70,  42 }, {  84,  42 },
    {  11,  56 }, {  28,  56 }, {  42,  56 }, {  56,  56 }, {  70,  56 }, {  84,  56 }, {  98,  53 },
    {  11,  70 }, {  28,  70 }, {  42,  70 }, {  56,  70 }, {  70,  70 }, {  83,  87 }, {  93,  97 },
                                                                          {  83, 107 }, {  93, 117 },
    { 213,  14 }, { 196,  14 }, { 182,  14 }, { 168,  14 }, { 154,  14 }, { 140,  14 },
    { 213,  28 }, { 196,  28 }, { 182,  28 }, { 168,  28 }, { 154,  28 }, { 140,  28 },
    { 213,  42 }, { 196,  42 }, { 182,  42 }, { 168,  42 }, { 154,  42 }, { 140,  42 },
    { 213,  56 }, { 196,  56 }, { 182,  56 }, { 168,  56 }, { 154,  56 }, { 140,  56 }, { 126,  53 },
    { 213,  70 }, { 196,  70 }, { 182,  70 }, { 168,  70 }, { 154,  70 }, { 141,  87 }, { 131,  97 },
                                                                          { 141, 107 }, { 131, 117 }

}, {
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 4,
    1, 1, 1, 1, 1, 1, 1,
                   1, 1,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 4,
    1, 1, 1, 1, 1, 1, 1,
                   1, 1
} };
// #endif

#ifdef OLED_DRIVER_ENABLE
#include "split_util.h"
#include "oled_driver.h"

__attribute__((weak))
void render_logo(void) {
  static const char PROGMEM sol_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(sol_logo, false);
}

__attribute__((weak))
const char* layer_name_user(uint32_t layer) {
  switch (layer) {
    default:
      return PSTR("UNDEF\n");
  }
}

__attribute__((weak))
void render_status(void) {
  // Setup for 270 degree rendering because it's awesome!
  // It can house 16 lines of text, with 5 letters each line
  // Render to mode icon
  static const char PROGMEM mode_logo[2][4] = {
    {0x97,0x98,0x0a,0},
    {0xb7,0xb8,0x0a,0} };

  oled_write_P(mode_logo[0], false); // Line 1
  oled_write_P(mode_logo[1], false); // Line 2

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  oled_set_cursor(0, 3); // Line 3
  oled_write_P(PSTR("Layer"), false); // Line 4
  oled_write_P(layer_name_user(biton32(layer_state)), false);

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_set_cursor(0, oled_max_lines() - 4); // Line 13
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLK") : PSTR("     "), false); // Line 14
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLK") : PSTR("     "), false); // Line 15
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("     "), false); // Line 16
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;  // flips the display 270 degrees if mainhand
  return rotation;
}

__attribute__((weak))
void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
}

#endif
