#include "rev2.h"

// #ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // I don't think these are in order but they're effectively unused
    { 0,  1,  2,  3,  4,  5, NO_LED },
    { 6,  7,  8,  9,  10, 11, 12 },
    { 13, 14, 15, 16, 17, 18, 19 },
    { 20, 21, 22, 23, 24, 25, 26 },
    { 27, 28, 29, 30, 31, 32, 33 }
}, {
    // first three rows and part of the fourth are in spatial order
    {  11,  14 }, {  28,  14 }, {  42,  14 }, {  56,  14 }, {  70,  14 }, {  84,  14 }, //  0 -  5
    {  11,  28 }, {  28,  28 }, {  42,  28 }, {  56,  28 }, {  70,  28 }, {  84,  28 }, //  6 - 11
    {  11,  42 }, {  28,  42 }, {  42,  42 }, {  56,  42 }, {  70,  42 }, {  84,  42 }, // 12 - 17
    {  11,  56 }, {  28,  56 }, {  42,  56 }, {  56,  56 }, {  70,  56 },               // 18 - 22

    // starting with the 6th LED on the 4th row, keys are out of spatial order
    {  84,  56 }, // row 4 col 6
    {  11,  70 }, // row 5 col 1
    {  28,  70 }, // row 5 col 2
    {  42,  70 }, // row 5 col 3
    {  56,  70 }, // row 5 col 4
    {  70,  70 }, // row 5 col 5
    {  98,  56 }, // row 4 col 7 shares RGB with thumb 1

    // thumbs seem to be addressed differently somehow? thumb 1 gets the same RGB as row 4 col 7
    {  105, 63 }, // thumb 2 -- contiguous with row 4 col 7 address so moving it artificially northwest a bit
    {    1,  1 }, // unused?
    {    1,  1 }, // unused?
    {    1,  1 }, // unused?

}, {
    // in order
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4,

    // out of order
    // 7th one is the same LED as the left thumb?
    4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
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
