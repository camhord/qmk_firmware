/* Copyright 2019 Takuya Urakawa (dm9records.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "i2c_master.h"

extern keymap_config_t keymap_config;

enum plaid_layers {
  _QWERTY,
  _RAISE
};

enum plaid_keycodes {
  QWERTY = SAFE_RANGE,
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_0
};

#define RAISE MO(_RAISE)

// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
    KC_LCTL,
    KC_RCTL,
    KC_LALT,
    KC_RALT,
    KC_LSFT,
    KC_RSFT,
    KC_LGUI,
    KC_RGUI,
	KC_CAPS,
    RAISE
};

//Setup consts for LED modes
#define LEDMODE_ON 1 //always on
#define LEDMODE_OFF 0 //always off
#define LEDMODE_MODS 2 //On with modifiers
#define LEDMODE_BLINKIN 3 //blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4 //On with any keypress, off with key release
#define LEDMODE_CAPS 5 // On with enter key
#define GREEN_OFFSET 0x08 // Offset for green led
#define RED_OFFSET 0x10 // Offset for red led

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty */
[_QWERTY] = LAYOUT_60_ansi_split_bs_rshift(
    KC_ESC,   KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL,
    KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,
    KC_CAPS,  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,
    KC_LSFT,            KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,    KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_RSFT,
    KC_LCTL,  KC_LGUI,  KC_LALT,                       KC_SPC,                          KC_RALT,  RAISE   ,  KC_APP,  KC_RCTL),

/* RAISE */
[_RAISE] = LAYOUT_60_ansi_split_bs_rshift(
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL, KC_TRNS,
    KC_TRNS,  LED_1,    LED_3,    LED_5,    LED_7,    LED_9,    KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_PSCR,  KC_INS,   RESET,    KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,   KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_TRNS,            KC_TRNS,
    KC_TRNS,            LED_2,    LED_4,    LED_6,    LED_8,    LED_0,    KC_TRNS,  KC_MPLY,  KC_MPRV,  KC_MNXT,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),
};

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

uint8_t curr_led_state = 0x0;

void set_led_high(uint8_t led) {
    uint8_t send_data = curr_led_state | led;
    curr_led_state = send_data;
    i2c_writeReg((PORT_EXPANDER_ADDRESS << 1), 0x09, &send_data, 1, 20);
}

void set_led_low(uint8_t led) {
    uint8_t send_data = curr_led_state & ~(led);
    curr_led_state = send_data;
    i2c_writeReg((PORT_EXPANDER_ADDRESS << 1), 0x09, &send_data, 1, 20);
}

//Setup config struct for LED
typedef union {
  uint32_t raw;
  struct {
    uint8_t  red_mode :8;
    uint8_t  green_mode :8;
  };
} led_config_t;
led_config_t led_config;

void led_set_user(uint8_t usb_led){
    if(led_config.red_mode==LEDMODE_CAPS){
        if (IS_LED_ON(usb_led, 1)){
            set_led_high(RED_OFFSET);
        } else {
            set_led_low(RED_OFFSET);
        }
    }
    if(led_config.green_mode==LEDMODE_CAPS){
        if (IS_LED_ON(usb_led, 1)){
            set_led_high(GREEN_OFFSET);
        } else {
            set_led_low(GREEN_OFFSET);
        }
    }
}

//Set leds to saved state during powerup
void keyboard_post_init_user(void) {
  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  if(led_config.red_mode == LEDMODE_ON) {
      set_led_high(RED_OFFSET);
  }

  if(led_config.green_mode == LEDMODE_ON) {
      set_led_high(GREEN_OFFSET);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_ON;
  led_config.green_mode = LEDMODE_CAPS;
      eeconfig_update_user(led_config.raw);
  eeconfig_update_user(led_config.raw);
}

/*uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _FUNC, _RAISE, _ADJUST);
}*/

void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
    switch (led_mode) {
      case LEDMODE_MODS:
        for (int i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++) {
          if(keycode==modifiers[i]) {
            if (record->event.pressed) {
              set_led_high(led);
            }
            else {
              set_led_low(led);
            }
          }
        }
        break;
      case LEDMODE_BLINKIN:
        if (record->event.pressed) {
          if(rand() % 2 == 1) {
            if(rand() % 2 == 0) {
              set_led_low(led);
            }
            else {
              set_led_high(led);
            }
          }
        }
        break;
      case LEDMODE_KEY:
        if (record->event.pressed) {
          set_led_high(led);
          return;
        }
        else {
          set_led_low(led);
          return;
        }
        break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* If the either led mode is keypressed based, call the led updater
     then let it fall through the keypress handlers. Just to keep
     the logic out of this procedure */
  if (led_config.red_mode >= LEDMODE_MODS && led_config.red_mode <= LEDMODE_CAPS) {
      led_keypress_update(RED_OFFSET, led_config.red_mode, keycode, record);
  }
  if (led_config.green_mode >= LEDMODE_MODS && led_config.green_mode <= LEDMODE_CAPS) {
      led_keypress_update(GREEN_OFFSET, led_config.green_mode, keycode, record);
  }
  switch (keycode) {
    case LED_1:
      if (record->event.pressed) {
        if (led_config.red_mode==LEDMODE_ON) {
            led_config.red_mode=LEDMODE_OFF;
            set_led_low(RED_OFFSET);
        }
        else {
            led_config.red_mode=LEDMODE_ON;
            set_led_high(RED_OFFSET);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_2:
      if (record->event.pressed) {
        if (led_config.green_mode==LEDMODE_ON) {
            led_config.green_mode=LEDMODE_OFF;
            set_led_low(GREEN_OFFSET);
        }
        else {
            led_config.green_mode=LEDMODE_ON;
            set_led_high(GREEN_OFFSET);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_3:
      led_config.red_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_4:
      led_config.green_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_5:
      led_config.red_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_6:
      led_config.green_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_7:
      led_config.red_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_8:
      led_config.green_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_9:
      led_config.red_mode=LEDMODE_CAPS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_0:
      led_config.green_mode=LEDMODE_CAPS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
  }
  return true;
}
