SRC += audio_delay.c

# none of my keyboards need LTO and it screws up I2C on my LSVI:
EXTRAFLAGS:=$(filter-out -flto,$(EXTRAFLAGS))

# turning off backlighting and audio for the split keebs
ifneq (,$(findstring lets_split,$(KEYBOARD)))
  BACKLIGHT_ENABLE = no
  AUDIO_ENABLE = no
endif
ifneq (,$(findstring vitamins_included,$(KEYBOARD)))
  BACKLIGHT_ENABLE = no
  AUDIO_ENABLE = no
endif

# both my plancks use audio but only the rev4 has backlighting
ifneq (,$(findstring planck,$(KEYBOARD)))
  ifneq (,$(findstring rev4,$(KEYBOARD)))
    BACKLIGHT_ENABLE = yes
  else
    BACKLIGHT_ENABLE = no
  endif
  AUDIO_ENABLE = yes
endif

BACKLIGHT_BREATHING = no
