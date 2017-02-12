#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_dvp.h"

// Layer definitions
enum {
    BASE = 0,   // default layer
    PRDV,       // Programmer Dvorak (no numbers, though), Windows-style modifiers
    FKEY,       // Function keys, media
    NUMB,       // number keys
    SUBL,       // Sublime Text
    SKCH,       // Bohemian Sketch
    _DYN,       // Dynamic Macro Recording
    PLVR,       // Plover
};

// OS-specific keys
#define SUPER KC_LGUI
#define MOD(x) (LGUI(x))
#define SMOD(x) (SCMD(x))

// Sketch Layer
#define ICON_ADD HYPR(DP_I)
#define ICON_OUTLINE HYPR(DP_O)
#define DISTR LCTL(LALT(DP_D))
#define SWAP LCTL(LSFT(MOD(DP_L)))
#define ARTB_PREV LSFT(MOD(DP_LBRC))
#define ARTB_NEXT LSFT(MOD(DP_RBRC))
#define RUNR_GO_TO HYPR(DP_G)
#define RUNR_APPLY HYPR(DP_A)
#define RUNR_CREATE HYPR(DP_C)
#define RUNR_INSERT HYPR(DP_N)
#define RUNR_RUN MOD(DP_QUOT)

#define ALGN_LEFT HYPR(KC_LEFT)
#define ALGN_RIGHT HYPR(KC_RIGHT)
#define ALGN_BOTT HYPR(KC_DOWN)
#define ALGN_TOP HYPR(KC_UP)

#define STYLE_CREATE MEH(DP_S)
#define STYLE_COPY LALT(MOD(DP_C))
#define STYLE_PASTE LALT(MOD(DP_V))

#define POS_COPY LCTL(LSFT(DP_C))
#define POS_PASTE LCTL(LSFT(DP_P))

#define TOG_HIDE LSFT(MOD(DP_H))
#define TOG_LOCK LSFT(MOD(DP_L))
#define LAYER_FRONT LCTL(LALT(MOD(KC_UP)))
#define LAYER_BACK LCTL(LALT(MOD(KC_DOWN)))
#define LAYER_FORWARD LALT(MOD(KC_UP))
#define LAYER_BACKWARD LALT(MOD(KC_DOWN))
#define LAYER_COLLAPSE HYPR(DP_S)
#define LAYER_REVEAL LSFT(MOD(DP_J))

// resize artboard to fit
// align to
// user flows add connection
// user flows create diagram
// Zoom Artboard to Fit ( cmd+4 )
// fluid

/*======================================
=            FN Definitions            =
======================================*/

enum {
    JL_NUMB = 0,   // Tap toggle Number layer
    JL_SKCH,       // Tap toggle Sketch layer
};

const uint16_t PROGMEM fn_actions[] = {
    [JL_NUMB] = ACTION_LAYER_TAP_TOGGLE(NUMB),
    [JL_SKCH] = ACTION_LAYER_TAP_TOGGLE(SKCH),
};

/*=====  End of FN Definitions  ======*/



/*=========================================
=            Macro Definitions            =
=========================================*/

// Macro Definitions
enum {
  PLVR_TOG = 0,     // Plover toggle
  PLVR_DICT,        // Plover dictionary
  DBL_P0,           // 00
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {

    case PLVR_TOG: {
        if (record->event.pressed) {
            // this will be interpreted by my Plover dictionary to toggle steno mode
            return MACRO( D(A), D(W), D(H), D(I), D(K), D(N), W(10), U(A), U(W), U(H), U(I), U(K), U(N), END);
        }
        break;
    }
    case PLVR_DICT: {
        if (record->event.pressed) {
            // This will be interpreted by my Plover dictionary to open up the dictionary
            return MACRO( D(N), D(L), D(COMM), D(O), D(T), D(M), D(B), D(D), W(10), U(N), U(L), U(COMM), U(O), U(T), U(M), U(B), U(D), END);
        }
    }
    case DBL_P0: {
        if (record->event.pressed) {
            // puts down two 0s
            return MACRO( T(P0), T(P0), END );
        }
    }

  }
  return MACRO_NONE;
};

/*=====  End of Macro Definitions  ======*/



/*=====================================
=            Dynamic Macro            =
=====================================*/

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV,
  DYNAMIC_MACRO_RANGE,
};

// dummy function?
void backlight_toggle(void) {}

#include "dynamic_macro.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    // <...THE REST OF THE FUNCTION...>
    return true;
}

/*=====  End of Dynamic Macro  ======*/


/*===============================================
=            Tap Dance Configuration            =
===============================================*/

// Declarations
enum {
    JL_CP = 0,         // Paste on single tap, Copy on double tap
    JL_ICON,        // Sketch: icon insert
    JL_LAYER_LIST,

    PRDV_AMPR, // programmer dvorak special keys
    PRDV_DLR,
    PRDV_BSLS,
    PRDV_AT,
    PRDV_HASH,
    PRDV_SLASH,
    PRDV_MINS,
};

static void copy_paste (qk_tap_dance_state_t *state, void *user_data) {

    switch (state->count) {
        case 1:
            register_code (SUPER);
            register_code (DP_V);
            unregister_code (DP_V);
            unregister_code (SUPER);
            break;
        case 2:
            register_code (SUPER);
            register_code (DP_C);
            unregister_code (DP_C);
            unregister_code (SUPER);
            break;
        case 3:
            register_code (SUPER);
            register_code (DP_X);
            unregister_code (DP_X);
            unregister_code (SUPER);
            reset_tap_dance (state);
            break;

    }
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [JL_CP]  = ACTION_TAP_DANCE_FN (copy_paste),
    [JL_ICON] = ACTION_TAP_DANCE_DOUBLE(ICON_ADD, ICON_OUTLINE),
    [JL_LAYER_LIST] = ACTION_TAP_DANCE_DOUBLE(LAYER_COLLAPSE, LAYER_REVEAL),

    [PRDV_AMPR] = ACTION_TAP_DANCE_DOUBLE(KC_AMPR, KC_PERC),
    [PRDV_DLR] = ACTION_TAP_DANCE_DOUBLE(KC_DLR, KC_TILD),
    [PRDV_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, LSFT(KC_BSLS)),
    [PRDV_AT] = ACTION_TAP_DANCE_DOUBLE(KC_AT, KC_CIRC),
    [PRDV_HASH] = ACTION_TAP_DANCE_DOUBLE(KC_HASH, KC_GRV),
    [PRDV_SLASH] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, LSFT(KC_SLASH)),
    [PRDV_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, LSFT(KC_MINS)),
};

/*=====  End of Tap Dance Configuration  ======*/




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// see tmk_core/common/keycode.h
// see quantum/quantum_keycodes.h
// AlignTo Regex: /\*\*//l2
// Wrapping required keycodes around (parens), typically for MO() and getting back to original layer

[BASE] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_1,               /**/  KC_2,               /**/  KC_3,               /**/  KC_4,               /**/  KC_5,               /**/  KC_6,               /**/  KC_BSLS,            /**/
    /**/  KC_GRV,             /**/  KC_Q,               /**/  KC_W,               /**/  KC_E,               /**/  KC_R,               /**/  KC_T,               /**/  MO(_DYN),           /**/
    /**/  KC_TAB,             /**/  KC_A,               /**/  KC_S,               /**/  KC_D,               /**/  KC_F,               /**/  KC_G,               /**/                      /**/
    /**/  OSM(MOD_LSFT),      /**/  KC_Z,               /**/  KC_X,               /**/  KC_C,               /**/  KC_V,               /**/  KC_B,               /**/  KC_DEL,             /**/
    /**/  KC_LCTL,            /**/  KC_HOME,            /**/  KC_WH_D,            /**/  KC_WH_U,            /**/  KC_END,             /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_LALT,            /**/  MO(FKEY),           /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  F(JL_SKCH),         /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_SPC,             /**/  KC_LGUI,            /**/  F(JL_NUMB),         /**/


    /**/  KC_RBRC,            /**/  KC_7,               /**/  KC_8,               /**/  KC_9,               /**/  KC_0,               /**/  KC_MINS,            /**/  KC_EQL,             /**/
    /**/  TD(JL_CP),          /**/  KC_Y,               /**/  KC_U,               /**/  KC_I,               /**/  KC_O,               /**/  KC_P,               /**/  KC_LBRC,            /**/
    /**/                      /**/  KC_H,               /**/  KC_J,               /**/  KC_K,               /**/  KC_L,               /**/  KC_SCLN,            /**/  KC_QUOT,            /**/
    /**/  KC_ENT,             /**/  KC_N,               /**/  KC_M,               /**/  KC_COMM,            /**/  KC_DOT,             /**/  KC_SLSH,            /**/  OSM(MOD_RSFT),      /**/
    /**/                      /**/                      /**/  KC_LEFT,            /**/  KC_DOWN,            /**/  KC_UP,              /**/  KC_RGHT,            /**/  KC_RCTL,            /**/

    /**/  KC_PGUP,            /**/  KC_RALT,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_PGDN,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  LT(SUBL, KC_ESC),   /**/  KC_RGUI,            /**/  KC_BSPC             /**/                      /**/                      /**/                      /**/                      /**/
    ),


[PRDV] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  TD(PRDV_AMPR),      /**/  KC_LBRC,            /**/  KC_LCBR,            /**/  KC_RCBR,            /**/  KC_LPRN,            /**/  KC_EQL,             /**/  TD(PRDV_BSLS),      /**/
    /**/  TD(PRDV_DLR),       /**/  KC_SCLN,            /**/  KC_COMM,            /**/  KC_DOT,             /**/  KC_P,               /**/  KC_Y,               /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_A,               /**/  KC_O,               /**/  KC_E,               /**/  KC_U,               /**/  KC_I,               /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_QUOTE,           /**/  KC_Q,               /**/  KC_J,               /**/  KC_K,               /**/  KC_X,               /**/  KC_TRNS,            /**/
    /**/  KC_LGUI,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_LCTL,            /**/  KC_TRNS,            /**/


    /**/  TD(PRDV_AT),        /**/  KC_ASTR,            /**/  KC_RPRN,            /**/  KC_PLUS,            /**/  KC_RBRC,            /**/  KC_EXLM,            /**/  TD(PRDV_HASH),      /**/
    /**/  KC_TRNS,            /**/  KC_F,               /**/  KC_G,               /**/  KC_C,               /**/  KC_R,               /**/  KC_L,               /**/  TD(PRDV_SLASH),        /**/
    /**/                      /**/  KC_D,               /**/  KC_H,               /**/  KC_T,               /**/  KC_N,               /**/  KC_S,               /**/  TD(PRDV_MINS),      /**/
    /**/  KC_TRNS,            /**/  KC_B,               /**/  KC_M,               /**/  KC_W,               /**/  KC_V,               /**/  KC_Z,               /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_RGUI,            /**/

    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  (KC_TRNS),          /**/  KC_RCTL,            /**/  KC_TRNS             /**/                      /**/                      /**/                      /**/                      /**/
    ),


[FKEY] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  (KC_TRNS),          /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/


    /**/  KC_MUTE,            /**/  KC_TRNS,            /**/  KC_F10,             /**/  KC_F11,             /**/  KC_F12,             /**/  KC_TRNS,            /**/  RESET,              /**/
    /**/  KC_VOLU,            /**/  KC_TRNS,            /**/  KC_F7,              /**/  KC_F8,              /**/  KC_F9,              /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_TRNS,            /**/  KC_F4,              /**/  KC_F5,              /**/  KC_F6,              /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_VOLD,            /**/  KC_TRNS,            /**/  KC_F1,              /**/  KC_F2,              /**/  KC_F3,              /**/  KC_TRNS,            /**/  KC_CAPS,            /**/
    /**/                      /**/                      /**/  KC_MPRV,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_MNXT,            /**/  KC_TRNS,            /**/

    /**/  TG(PLVR),           /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_MPLY             /**/                      /**/                      /**/                      /**/                      /**/
    ),



[NUMB] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DP_D,               /**/  DP_E,               /**/  DP_F,               /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DP_A,               /**/  DP_B,               /**/  DP_C,               /**/  KC_X,               /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_WH_U,            /**/  KC_END,             /**/  KC_UP,              /**/  KC_HOME,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_WH_D,            /**/  KC_LEFT,            /**/  KC_DOWN,            /**/  KC_RGHT,            /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  (KC_TRNS),          /**/


    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_PSLS,            /**/  KC_PAST,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_P7,              /**/  KC_P8,              /**/  KC_P9,              /**/  KC_PMNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_TRNS,            /**/  KC_P4,              /**/  KC_P5,              /**/  KC_P6,              /**/  KC_PPLS,            /**/  KC_PENT,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_P1,              /**/  KC_P2,              /**/  KC_P3,              /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/  KC_P0,              /**/  M(DBL_P0),          /**/  KC_PDOT,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/

    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  TG(PRDV),           /**/  KC_TRNS,            /**/  KC_TRNS             /**/                      /**/                      /**/                      /**/                      /**/
    ),



#define JMP_CHAR MEH(DP_QUOT)
#define JMP_IN_LINE HYPR(DP_COMM)
#define JMP_LINE MEH(DP_DOT)
#define JMP_WORD MEH(DP_SCLN)
#define JMP_SELECT HYPR(DP_SCLN)

#define BKMK_TOG MOD(KC_F2)
#define BKMK_NEXT KC_F2
#define BKMK_PREV LSFT(KC_F2)
#define BKMK_CLEAR SMOD(KC_F2)

#define STEP_IN KC_F11
#define STEP_OVER KC_F10
#define STEP_OUT LSFT(KC_F11)

#define FILE_DUP HYPR(DP_D)
#define FILE_REN HYPR(DP_R)

#define SETTING_WDWP HYPR(DP_W) // doesn't work. just takes a screenshot I think. try meh instead

#define SEL_SPLIT SMOD(DP_L)

#define DEL_LINE LSFT(LCTL(DP_K))
#define DEL_TO_EOL HYPR(DP_RBRC)
#define DEL_TO_SOL HYPR(DP_LBRC)

#define VIEW_PREV SMOD(DP_LBRC)
#define VIEW_NEXT SMOD(DP_RBRC)


[SUBL] = KEYMAP(
//  /**/  5                   /**/  4                   /**/  3                   /**/  2                   /**/  1                   /**/  1'                  /**/  2'                  /**/
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  FILE_DUP,           /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  FILE_REN,           /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  // File
    /**/  SEL_SPLIT,          /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  VIEW_PREV,          /**/  VIEW_NEXT,          /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  // Basic
    /**/  KC_TRNS,            /**/  JMP_IN_LINE,        /**/  JMP_CHAR,           /**/  JMP_LINE,           /**/  JMP_WORD,           /**/  JMP_SELECT,         /**/                      /**/  // Acejump
    /**/  BKMK_CLEAR,         /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  BKMK_NEXT,          /**/  BKMK_PREV,          /**/  BKMK_TOG,           /**/  KC_TRNS,            /**/  // Bookmark
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DEL_TO_SOL,         /**/  DEL_LINE,           /**/  DEL_TO_EOL,         /**/                      /**/                      /**/  // Deleting
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/

//  /**/  2'                  /**/  1'                  /**/  1                   /**/  2                   /**/  3                   /**/  4                   /**/  5                   /**/
    /**/  KC_TRNS,            /**/  SETTING_WDWP,       /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/  STEP_IN,            /**/  STEP_OVER,          /**/  KC_TRNS,            /**/  STEP_OUT,           /**/  KC_TRNS,            /**/  // Browser Debug

    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS             /**/                      /**/                      /**/                      /**/                      /**/
    ),



[SKCH] = KEYMAP(
//  /**/  5                   /**/  4                   /**/  3                   /**/  2                   /**/  1                   /**/  1'                  /**/  2'                  /**/
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/

//  /**/  2'                  /**/  1' Reposition       /**/  1 Editing           /**/  2 Add               /**/  3 Style             /**/  4 Style Grab        /**/  5 Layer Mgmt        /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  LAYER_FORWARD,      /**/
    /**/  KC_TRNS,            /**/  SWAP,               /**/  TOG_LOCK,           /**/  TD(JL_ICON),        /**/  STYLE_PASTE,        /**/  STYLE_COPY,         /**/  LAYER_FRONT,        /**/
    /**/                      /**/  DISTR,              /**/  TOG_HIDE,           /**/  RUNR_INSERT,        /**/  RUNR_APPLY,         /**/  STYLE_CREATE,       /**/  TD(JL_LAYER_LIST),  /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  RUNR_CREATE,        /**/  POS_PASTE,          /**/  POS_COPY,           /**/  LAYER_BACK,         /**/
    /**/                      /**/                      /**/  ALGN_LEFT,          /**/  ALGN_BOTT,          /**/  ALGN_TOP,           /**/  ALGN_RIGHT,         /**/  LAYER_BACKWARD,     /**/

    /**/  ARTB_PREV,          /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  ARTB_NEXT,          /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/  RUNR_RUN,           /**/  RUNR_GO_TO          /**/                      /**/                      /**/                      /**/                      /**/
    ),



[_DYN] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DYN_REC_START1,     /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  (KC_TRNS),          /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DYN_MACRO_PLAY1,    /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/


    /**/  DYN_REC_START2,     /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  DYN_MACRO_PLAY2,    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/

    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS             /**/                      /**/                      /**/                      /**/                      /**/
    ),


[PLVR] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/
    /**/  KC_NO,              /**/  KC_1,               /**/  KC_2,               /**/  KC_3,               /**/  KC_4,               /**/  KC_5,               /**/  KC_NO,              /**/
    /**/  KC_NO,              /**/  KC_Q,               /**/  KC_W,               /**/  KC_E,               /**/  KC_R,               /**/  KC_T,               /**/                      /**/
    /**/  KC_NO,              /**/  KC_A,               /**/  KC_S,               /**/  KC_D,               /**/  KC_F,               /**/  KC_G,               /**/  KC_NO,              /**/
    /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_NO,              /**/  (KC_TRNS),          /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  M(PLVR_DICT),       /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_C,               /**/  KC_V,               /**/  MAGIC_TOGGLE_NKRO,  /**/


    /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/  KC_NO,              /**/
    /**/  M(PLVR_TOG),        /**/  KC_6,               /**/  KC_7,               /**/  KC_8,               /**/  KC_9,               /**/  KC_0,               /**/  KC_NO,              /**/
    /**/                      /**/  KC_Y,               /**/  KC_U,               /**/  KC_I,               /**/  KC_O,               /**/  KC_P,               /**/  KC_LBRC,            /**/
    /**/  KC_NO,              /**/  KC_H,               /**/  KC_J,               /**/  KC_K,               /**/  KC_L,               /**/  KC_SCLN,            /**/  KC_QUOT,            /**/
    /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_NO,              /**/

    /**/  (KC_TRNS),          /**/  KC_NO,              /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  (KC_TRNS),          /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  (KC_TRNS),          /**/  KC_N,               /**/  KC_M                /**/                      /**/                      /**/                      /**/                      /**/
    ),


}; // end of keymap definitions


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case FKEY:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case NUMB:
            ergodox_right_led_2_on();
            break;
        case SUBL:
            ergodox_right_led_3_on();
            break;
        case SKCH:
            ergodox_right_led_1_on();
            break;
        case PRDV:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case PLVR:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case _DYN:
            ergodox_board_led_on();
            break;

        default:
            // none
            break;
    }
};
