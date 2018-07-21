ifneq (,$(findstring lets_split,$(KEYBOARD)))
  BACKLIGHT_ENABLE = no
  BACKLIGHT_BREATHING = no
  AUDIO_ENABLE = no
  USE_I2C = yes
endif

ifneq (,$(findstring vitamins_included,$(KEYBOARD)))
  BACKLIGHT_ENABLE = no
  BACKLIGHT_BREATHING = no
  AUDIO_ENABLE = no
  USE_I2C = no
endif

ifneq (,$(findstring planck,$(KEYBOARD)))
  ifneq (,$(findstring rev4,$(KEYBOARD)))
    BACKLIGHT_ENABLE = yes
    BACKLIGHT_BREATHING = yes
  else
    BACKLIGHT_ENABLE = no
    BACKLIGHT_BREATHING = no
  endif
  AUDIO_ENABLE = yes
endif
