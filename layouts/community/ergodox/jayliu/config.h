#ifndef CONFIG_JAYLIU_H
#define CONFIG_JAYLIU_H

#include QMK_KEYBOARD_CONFIG_H

// because I ... want to override stuff?
// this trying to get around the warning as error.
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_WHEEL_MAX_SPEED
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#undef IS_COMMAND

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    5
#define MOUSEKEY_MAX_SPEED      2
// #define MOUSEKEY_WHEEL_DELAY    100 // doesn't actually do anything?
#define MOUSEKEY_WHEEL_MAX_SPEED    2
#define MOUSEKEY_WHEEL_TIME_TO_MAX  255

#define TAPPING_TOGGLE  1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

#ifdef SUBPROJECT_ez
    #include "ez/config.h"
#endif
#ifdef SUBPROJECT_infinity
    #include "infinity/config.h"
#endif

#endif
