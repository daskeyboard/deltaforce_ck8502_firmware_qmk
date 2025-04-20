/* Copyright (C) 2022 jonylee@hfd
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
// clang-format off
enum __layers {
    WIN_B,
    WIN_FN,
    MAC_B,
    MAC_FN
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define KC_SIRI LGUI(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT_ansi( /* Base */
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                 KC_DEL,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,      KC_HOME,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,      KC_END,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                 KC_PGUP,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(WIN_FN),KC_RCTL,    KC_LEFT,  KC_DOWN, KC_RGHT),

    [WIN_FN] = LAYOUT_ansi( /* FN */
		_______, KC_BRID, KC_BRIU, KC_MAIL, KC_WSCH, KC_CALC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,                RGB_TOG,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD,       _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,
		_______, _______, DF(MAC_B),_______,_______, _______, _______, _______, _______, _______, _______, _______, _______,                RGB_HUI,
		_______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,               RGB_VAI,
		_______, GU_TOGG, _______,                   _______,                            _______, _______, _______,      RGB_SPD, RGB_VAD, RGB_SPI),

    [MAC_B] = LAYOUT_ansi( /* Base */
		KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_SIRI, KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,                KC_DEL,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_HOME,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_END,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                 KC_PGUP,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,               KC_UP,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, MO(MAC_FN),KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN] = LAYOUT_ansi( /* FN */
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                 RGB_TOG,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD,       _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,
		_______, DF(WIN_B),_______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                RGB_HUI,
		_______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,                RGB_VAI,
		_______, _______, _______,                   _______,                            _______, _______, _______,       RGB_SPD, RGB_VAD, RGB_SPI)
};
// clang-format on
uint16_t pressed_code;
uint16_t pressed_time = 0;
bool     process_record_user(uint16_t keycode, keyrecord_t *record) {
    // if (!process_record_keychron(keycode, record)) {
    //     return false;
    // }
    switch (keycode) {
        case EE_CLR: {
            if (record->event.pressed) {
                pressed_time = timer_read();
            } else {
                pressed_time = 0;
            }
            pressed_code = EE_CLR;
            return false;
        }
        case DF(WIN_B):
            if (record->event.pressed) {
                pressed_time = timer_read();
            } else {
                pressed_time = 0;
            }
            pressed_code = DF(WIN_B);
            return false;
        case DF(MAC_B):
            if (record->event.pressed) {
                pressed_time = timer_read();
            } else {
                pressed_time = 0;
            }
            pressed_code = DF(MAC_B);
            return false;
        default:
            return true;
    }
}

void housekeeping_task_user(void) {
    if (pressed_time && (timer_elapsed(pressed_time) >= 1500)) {
        pressed_time = 0;
        switch (pressed_code) {
            case EE_CLR:
                eeconfig_init();
                eeconfig_update_rgb_matrix_default();
                break;
            case DF(WIN_B):
                set_single_persistent_default_layer(WIN_B);
                writePin(B13, false);
                break;
            case DF(MAC_B):
                set_single_persistent_default_layer(MAC_B);
                writePin(B13, true);
                break;
            default:
                break;
        }
    }
}
