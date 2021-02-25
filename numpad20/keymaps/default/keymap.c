/* Copyright 2018 Yiancar
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
[0] = LAYOUT_numpad_5x4(
		/*
		 * numlock / * - 
		 * 7 8 9 +
		 * 4 5 6 no
		 * 1 2 3 no
		 * 0 no . ent
		 */
    // TG(1),   KC_PSLS, KC_PAST, KC_PMNS,
    TG(1),   KC_PSLS, KC_PAST, KC_PMNS,
    KC_7,   KC_8,   KC_9,   KC_PPLS,
    KC_4,   KC_5,   KC_6,   KC_PPLS,
    KC_1,   KC_2,   KC_3,   KC_PENT,
    KC_0,   KC_0,   KC_DOT, KC_PENT ),

[1] = LAYOUT_numpad_5x4(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_HOME, KC_UP,   KC_PGUP, KC_TRNS,
    KC_LEFT, KC_NO,   KC_RGHT, KC_TRNS,
    KC_END,  KC_DOWN, KC_PGDN, KC_TRNS,
    KC_INS,  KC_INS,   KC_DEL, KC_TRNS),
};
