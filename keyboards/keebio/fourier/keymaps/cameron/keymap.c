#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _FN2 2
#define _FN3 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

#define KC_ KC_TRNS
#define KC_FN1 LT(_FN1, KC_NO)
#define KC_FN2 LT(_FN2, KC_NO)
#define KC_RST RESET
#define KC_DBUG DEBUG
#define KC_FN3 TT(_FN3)
#define KC_SPFN1 LT(_FN1, KC_SPACE)
#define KC_BSFN2 LT(_FN2, KC_BSPC)
#define KC_SFTENTR RSFT_T(KC_ENTER)
 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    TAB , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  , DEL,BSPC,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
    ESC  , A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN,  QUOT  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
    LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH,SFTENTR,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
    LCTL ,LALT,  FN2,   ,  FN1   ,  SPACE  , FN1 , RALT, RGUI ,ENTER
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
  ),

  [_FN1] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    GRV , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,    ,    ,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
     F12 ,    ,HOME,PGUP,PGDN,END ,LEFT,DOWN, UP ,RIGHT,   ,  BSLS  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           , FN3,    ,    ,    ,    ,    ,MPLY,MPRV,MNXT,VOLD,VOLU  ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,         ,        ,    ,     ,     ,    
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
  ),

  [_FN2] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    TILD,EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,UNDS,PLUS,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
     F12 , F1  ,F2 , F3 , F4 , F5 , F6 ,MINS, EQL,LBRC,RBRC,  PIPE  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           , F7 , F8 , F9 , F10, F11,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,        ,        ,     ,     ,     ,     
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
  ),
  
  [_FN3] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
        ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,        ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,  SPACE ,        ,     ,     ,     ,     
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
  )

};

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
};
