#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_dvp.h"

// Layer definitions
enum {
    BASE = 0,   // default layer
    FKEY,       // Function keys, media
    NUMB,       // number keys
    SUBL,       // Sublime Text
    SKCH,       // Bohemian Sketch
    _DYN,       // Dynamic Macro Recording
    PLVR,       // Plover
};

// OS-specific keys
#define SUPER KC_LGUI



/*======================================
=            FN Definitions            =
======================================*/

enum {
    JL_NUMB = 0,   // Tap toggle Number layer
};

const uint16_t PROGMEM fn_actions[] = {
    [JL_NUMB] = ACTION_LAYER_TAP_TOGGLE(NUMB),
};

/*=====  End of FN Definitions  ======*/



/*=========================================
=            Macro Definitions            =
=========================================*/

// Macro Definitions
enum {
  PLVR_TOG = 0,     // Plover toggle
  PLVR_DICT,        // Plover dictionary
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
void backlight_toggle() {}

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
    JL_CP = 0         // Paste on single tap, Copy on double tap
};

static void copy_paste (qk_tap_dance_state_t *state, void *user_data) {

    if (state->count == 1) {
        register_code (SUPER);
        register_code (DP_V);
        unregister_code (DP_V);
        unregister_code (SUPER);
    } else {
        register_code (SUPER);
        register_code (DP_C);
        unregister_code (DP_C);
        unregister_code (SUPER);
        reset_tap_dance (state);
    }
}


qk_tap_dance_action_t tap_dance_actions[] = {

    [JL_CP]  = ACTION_TAP_DANCE_FN (copy_paste),

};

/*=====  End of Tap Dance Configuration  ======*/




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// see quantum_keycodes.h
// AlignTo Regex: /\*\*//l2
// Wrapping required keycodes around (parens), typically for MO() and getting back to original layer

[BASE] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_1,               /**/  KC_2,               /**/  KC_3,               /**/  KC_4,               /**/  KC_5,               /**/  KC_6,               /**/  KC_BSLS,            /**/
    /**/  KC_GRV,             /**/  KC_Q,               /**/  KC_W,               /**/  KC_E,               /**/  KC_R,               /**/  KC_T,               /**/  MO(_DYN),           /**/
    /**/  KC_TAB,             /**/  KC_A,               /**/  KC_S,               /**/  KC_D,               /**/  KC_F,               /**/  KC_G,               /**/                      /**/
    /**/  OSM(MOD_LSFT),      /**/  KC_Z,               /**/  KC_X,               /**/  KC_C,               /**/  KC_V,               /**/  KC_B,               /**/  TD(JL_CP),          /**/
    /**/  KC_LCTL,            /**/  KC_HOME,            /**/  KC_WH_D,            /**/  KC_WH_U,            /**/  KC_END,             /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_LALT,            /**/  MO(FKEY),           /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  TG(SKCH),           /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_SPC,             /**/  KC_LGUI,            /**/  F(JL_NUMB),         /**/


    /**/  KC_RBRC,            /**/  KC_7,               /**/  KC_8,               /**/  KC_9,               /**/  KC_0,               /**/  KC_MINS,            /**/  KC_EQL,             /**/
    /**/  KC_DEL,             /**/  KC_Y,               /**/  KC_U,               /**/  KC_I,               /**/  KC_O,               /**/  KC_P,               /**/  KC_LBRC,            /**/
    /**/                      /**/  KC_H,               /**/  KC_J,               /**/  KC_K,               /**/  KC_L,               /**/  KC_SCLN,            /**/  KC_QUOT,            /**/
    /**/  KC_ENT,             /**/  KC_N,               /**/  KC_M,               /**/  KC_COMM,            /**/  KC_DOT,             /**/  KC_SLSH,            /**/  OSM(MOD_RSFT),      /**/
    /**/                      /**/                      /**/  KC_LEFT,            /**/  KC_DOWN,            /**/  KC_UP,              /**/  KC_RGHT,            /**/  KC_RCTL,            /**/

    /**/  KC_PGUP,            /**/  KC_RALT,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_PGDN,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  LT(SUBL, KC_ESC),   /**/  KC_RGUI,            /**/  KC_BSPC             /**/                      /**/                      /**/                      /**/                      /**/
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


    /**/  KC_MUTE,            /**/  KC_TRNS,            /**/  KC_F10,             /**/  KC_F11,             /**/  KC_F12,             /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_VOLU,            /**/  KC_TRNS,            /**/  KC_F7,              /**/  KC_F8,              /**/  KC_F9,              /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_TRNS,            /**/  KC_F4,              /**/  KC_F5,              /**/  KC_F6,              /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_VOLD,            /**/  KC_TRNS,            /**/  KC_F1,              /**/  KC_F2,              /**/  KC_F3,              /**/  KC_TRNS,            /**/  KC_CAPS,            /**/
    /**/                      /**/                      /**/  KC_MPRV,            /**/  KC_TRNS,            /**/  KC_MNXT,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/

    /**/  TG(PLVR),           /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_MPLY             /**/                      /**/                      /**/                      /**/                      /**/
    ),



[NUMB] = KEYMAP(
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DP_D,               /**/  DP_E,               /**/  DP_F,               /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DP_A,               /**/  DP_B,               /**/  DP_C,               /**/  KC_TRNS,            /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  DP_X,               /**/                      /**/                      /**/

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/


    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_PSLS,            /**/  KC_PAST,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_NO,              /**/  KC_P7,              /**/  KC_P8,              /**/  KC_P9,              /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_PDOT,            /**/  KC_P4,              /**/  KC_P5,              /**/  KC_P6,              /**/  KC_PPLS,            /**/  KC_PENT,            /**/
    /**/  KC_TRNS,            /**/  KC_P0,              /**/  KC_P1,              /**/  KC_P2,              /**/  KC_P3,              /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/

    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS             /**/                      /**/                      /**/                      /**/                      /**/
    ),



[SUBL] = KEYMAP(
//  /**/  5                   /**/  4                   /**/  3                   /**/  2                   /**/  1                   /**/  1'                  /**/  2'                  /**/
//  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/  ------------------  /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  // Panel
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/  // Basic
    /**/  KC_TRNS,            /**/  HYPR(DP_COMM),      /**/  MEH(DP_QUOT),       /**/  MEH(DP_DOT),        /**/  MEH(DP_SCLN),       /**/  HYPR(DP_SCLN),      /**/  KC_TRNS,            /**/  // Acejump
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/  // MultiEditUtils
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/


    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/  KC_F11,             /**/  KC_F10,             /**/  KC_TRNS,            /**/  LSFT(KC_F11),       /**/  KC_TRNS,            /**/  // Browser Debug

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


    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/
    /**/                      /**/                      /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS,            /**/

    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/                      /**/                      /**/                      /**/                      /**/                      /**/                      /**/
    /**/  KC_TRNS,            /**/  KC_TRNS,            /**/  KC_TRNS             /**/                      /**/                      /**/                      /**/                      /**/
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

    /**/                      /**/                      /**/                      /**/                      /**/                      /**/  KC_NO,              /**/  (KC_TRNS),            /**/
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
