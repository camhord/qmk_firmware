#include "chocopad.h"

#define _BASE 0
#define _FN1 1
#define _FN2 2

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define KC_XX KC_NO

#define KC_L1 LT(1, KC_P0)
#define KC_L2 LT(2, KC_SPC)
#define KC_RST RESET
#define KC_BSTP BL_STEP
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

enum custom_keycodes {
  NUMPAD = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_kc(
  //,----+----+----+----.
      P7 , P8 , P9 ,BSPC,
  //|----+----+----+----|
      P4 , P5 , P6 ,TAB ,
  //|----+----+----+----|
      P1 , P2 , P3 ,PENT,
  //|----+----+----+----|
      L1 , P0 ,PDOT,PSLS
  //`----+----+----+----'
  ),

  [_FN1] = LAYOUT_kc(
  //,----+----+----+----.
     NLCK,PSLS,PAST,PMNS,
  //|----+----+----+----|
     LEFT,DOWN, UP ,RGHT,
  //|----+----+----+----|
     PPLS,    ,    ,    ,
  //|----+----+----+----|
         ,    ,    ,   
  //`----+----+----+----'
  )
};
