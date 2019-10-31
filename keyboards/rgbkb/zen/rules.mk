# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

ifeq ($(strip $(CTPC)), yes)
  CONVERT_TO_PROTON_C=yes
endif

ifeq ($(strip $(CONVERT_TO_PROTON_C)), yes)
  SPLIT_KEYBOARD = no       # currently unsupported on ARM
  RGBLIGHT_ENABLE = no      # currently unsupported on ARM

  EXTRAFLAGS += -DUSE_PROTON_C
else
  # Currently moved to Pro Micro only section because of lack of Proton-C support
  SPLIT_KEYBOARD = yes

  RGBLIGHT_ENABLE         = no        # Enable global lighting effects. Do not enable with RGB Matrix
  RGBLIGHT_ANIMATIONS     = no        # LED animations
  LED_MIRRORED            = no        # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)

  RGB_MATRIX_ENABLE       = WS2812    # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
  RGB_MATRIX_KEYPRESSES   = yes       # Enable reactive per-key effects.
  RGB_MATRIX_FRAMEBUFFER_EFFECTS = yes# Enable frame buffer effects like the typing heatmap.

  RGBLIGHT_FULL_POWER     = no        # Allow maximum RGB brightness for RGBLIGHT or RGB_MAT

endif

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID

SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

DEFAULT_FOLDER = rgbkb/zen/rev2
