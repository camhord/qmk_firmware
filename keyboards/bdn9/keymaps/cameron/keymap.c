/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        HYPR(KC_4),HYPR(KC_5),HYPR(KC_6), \
        HYPR(KC_1),HYPR(KC_2),HYPR(KC_3), \
        KC_MPRV, KC_MPLY, KC_MNXT \
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(MOD_MEH | KC_FN9);
        } else {
            tap_code(MOD_MEH | KC_FN10);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(MOD_MEH | KC_FN11);
        } else {
            tap_code(MOD_MEH | KC_FN12);
        }
    }
}

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
};
