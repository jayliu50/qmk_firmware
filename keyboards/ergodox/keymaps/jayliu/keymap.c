#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_dvp.h"

// Layer definitions
#define BASE 0 // default layer
#define FKEY 1 // Function keys, media
#define NUMB 3 // number keys
#define SUBL 4 // Sublime Text
#define SKCH 5 // Bohemian Sketch
#define _DYN 6 // Dynamic Macro Recording

// FN definitions
#define JL_NUMB KC_FN1

// Macro definitions



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


// see quantum_keycodes.h
// AlignTo Regex: /\*\*//l2

[BASE] = KEYMAP(

    /**/  KC_1,              /**/  KC_2,           /**/  KC_3,          /**/  KC_4,         /**/  KC_5,          /**/  KC_6,           /**/  KC_BSLS,        /**/
    /**/  KC_GRV,            /**/  KC_Q,           /**/  KC_W,          /**/  KC_E,         /**/  KC_R,          /**/  KC_T,           /**/  KC_TAB,         /**/
    /**/  KC_TAB,            /**/  KC_A,           /**/  KC_S,          /**/  KC_D,         /**/  KC_F,          /**/  KC_G,           /**/                  /**/
    /**/  OSM(MOD_LSFT),     /**/  KC_Z,           /**/  KC_X,          /**/  KC_C,         /**/  KC_V,          /**/  KC_B,           /**/  KC_ESC,         /**/
    /**/  KC_LCTL,           /**/  KC_HOME,        /**/  KC_WH_D,       /**/  KC_WH_U,      /**/  KC_END,        /**/                  /**/                  /**/
    /**/                     /**/                  /**/                 /**/                /**/                 /**/  KC_LALT,        /**/  MO(FKEY),       /**/
    /**/                     /**/                  /**/                 /**/                /**/                 /**/                  /**/  KC_TRNS,        /**/
    /**/                     /**/                  /**/                 /**/                /**/  KC_SPC,        /**/  KC_LGUI,        /**/  JL_NUMB,        /**/


    /**/  KC_RBRC,           /**/  KC_7,           /**/  KC_8,          /**/  KC_9,         /**/  KC_0,          /**/  KC_MINS,        /**/  KC_EQL,         /**/
    /**/  KC_DEL,            /**/  KC_Y,           /**/  KC_U,          /**/  KC_I,         /**/  KC_O,          /**/  KC_P,           /**/  KC_LBRC,        /**/
    /**/                     /**/  KC_H,           /**/  KC_J,          /**/  KC_K,         /**/  KC_L,          /**/  KC_SCLN,        /**/  KC_QUOT,        /**/
    /**/  KC_ENT,            /**/  KC_N,           /**/  KC_M,          /**/  KC_COMM,      /**/  KC_DOT,        /**/  KC_SLSH,        /**/  OSM(MOD_RSFT),  /**/
    /**/                     /**/                  /**/  KC_LEFT,       /**/  KC_DOWN,      /**/  KC_UP,         /**/  KC_RGHT,        /**/  KC_RCTL,        /**/
    /**/  KC_PGUP,           /**/  KC_RALT,        /**/                 /**/                /**/                 /**/                  /**/                  /**/
    /**/  KC_PGDN,           /**/                  /**/                 /**/                /**/                 /**/                  /**/                  /**/
    /**/  LT(SUBL, KC_ESC),  /**/  KC_RGUI,        /**/  KC_BSPC        /**/                /**/                 /**/                  /**/                  /**/
    ),


[FKEY] = KEYMAP(
/**/        KC_TRNS,        /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/        KC_TRNS,        /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/        KC_TRNS,        /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/                  /**/
/**/        KC_TRNS,        /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/        KC_TRNS,        /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/  KC_TRNS,  /**/            /**/                  /**/
/**/                        /**/            /**/            /**/            /**/            /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/                        /**/            /**/            /**/            /**/            /**/            /**/     KC_TRNS,     /**/
/**/                        /**/            /**/            /**/            /**/  KC_TRNS,  /**/  KC_TRNS,  /**/     KC_TRNS,     /**/

/**/        KC_MUTE,        /**/  KC_TRNS,  /**/  KC_F10,   /**/  KC_F11,   /**/  KC_F12,   /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/        KC_VOLU,        /**/  KC_TRNS,  /**/   KC_F7,   /**/   KC_F8,   /**/   KC_F9,   /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/                        /**/  KC_TRNS,  /**/   KC_F4,   /**/   KC_F5,   /**/   KC_F6,   /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/        KC_VOLD,        /**/  KC_TRNS,  /**/   KC_F1,   /**/   KC_F2,   /**/   KC_F3,   /**/  KC_TRNS,  /**/     KC_TRNS,     /**/
/**/                        /**/            /**/  KC_MPRV,  /**/  KC_TRNS,  /**/  KC_MNXT,  /**/  KC_TRNS,  /**/     KC_TRNS,     /**/

/**/        KC_TRNS,        /**/  KC_TRNS,  /**/            /**/            /**/            /**/            /**/                  /**/
/**/        KC_TRNS,        /**/            /**/            /**/            /**/            /**/            /**/                  /**/
/**/        KC_TRNS,        /**/  KC_TRNS,  /**/  KC_MPLY   /**/            /**/            /**/            /**/                  /**/
    ),



[NUMB] = KEYMAP(
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  DP_D,          /**/  DP_E,         /**/  DP_F,          /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  DP_A,          /**/  DP_B,         /**/  DP_C,          /**/  KC_TRNS,        /**/                  /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  DP_X,          /**/                  /**/                  /**/
    /**/                     /**/                  /**/                 /**/                /**/                 /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/                     /**/                  /**/                 /**/                /**/                 /**/                  /**/  KC_TRNS,        /**/
    /**/                     /**/                  /**/                 /**/                /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/


    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_PSLS,       /**/  KC_PAST,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/  KC_TRNS,           /**/  KC_NO,          /**/  KC_P7,         /**/  KC_P8,        /**/  KC_P9,         /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/                     /**/  KC_PDOT,        /**/  KC_P4,         /**/  KC_P5,        /**/  KC_P6,         /**/  KC_PPLS,        /**/  KC_PENT,        /**/
    /**/  KC_TRNS,           /**/  KC_P0,          /**/  KC_P1,         /**/  KC_P2,        /**/  KC_P3,         /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/                     /**/                  /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/

    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/                 /**/                /**/                 /**/                  /**/                  /**/
    /**/  KC_TRNS,           /**/                  /**/                 /**/                /**/                 /**/                  /**/                  /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS        /**/                /**/                 /**/                  /**/                  /**/
    ),



[SUBL] = KEYMAP(
//  /**/  5                  /**/  4               /**/  3              /**/  2             /**/  1              /**/  1'              /**/  2'              /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/  // Panel
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/                  /**/  // Basic
    /**/  KC_TRNS,           /**/  HYPR(DP_COMM),  /**/  MEH(DP_QUOT),  /**/  MEH(DP_DOT),  /**/  MEH(DP_SCLN),  /**/  HYPR(DP_SCLN),  /**/  KC_TRNS,        /**/  // Acejump
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/                  /**/                  /**/  // MultiEditUtils
    /**/                     /**/                  /**/                 /**/                /**/                 /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/                     /**/                  /**/                 /**/                /**/                 /**/                  /**/  KC_TRNS,        /**/
    /**/                     /**/                  /**/                 /**/                /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/


    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/                     /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS,       /**/  KC_TRNS,      /**/  KC_TRNS,       /**/  KC_TRNS,        /**/  KC_TRNS,        /**/
    /**/                     /**/                  /**/  KC_F11,        /**/  KC_F10,       /**/  KC_TRNS,       /**/  LSFT(KC_F11),   /**/  KC_TRNS,        /**/  // Browser Debug

    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/                 /**/                /**/                 /**/                  /**/                  /**/
    /**/  KC_TRNS,           /**/                  /**/                 /**/                /**/                 /**/                  /**/                  /**/
    /**/  KC_TRNS,           /**/  KC_TRNS,        /**/  KC_TRNS        /**/                /**/                 /**/                  /**/                  /**/
    ),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(NUMB)                // FN1 - Momentary Layer 1 (Numbers)
};


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
            break;
        case NUMB:
            ergodox_right_led_2_on();
            break;
        case SUBL:
            ergodox_right_led_3_on();
            break;
        case SKCH:
            ergodox_right_led_1_on();
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
