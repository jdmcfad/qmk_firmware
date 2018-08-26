#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define ADVENTURE_TIME \
    H__NOTE(_F5),    \
    Q__NOTE(_F5),    \
    H__NOTE(_F5),    \
    H__NOTE(_G5),    \
    H__NOTE(_E5),    \
    H__NOTE(_E5),    \
    H__NOTE(_D5),    \
    H__NOTE(_C5),    \
    HD_NOTE(_C6),

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(ADVENTURE_TIME)
#endif

// for some reason the LSvi rev1 disables action tapping...
#ifdef NO_ACTION_TAPPING
  #undef NO_ACTION_TAPPING
#endif

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 15

// let's split configuration:
#define USE_I2C
#define EE_HANDS

#endif
