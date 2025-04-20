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
enum layers {
    WIN_BASE,
    WIN_FN,
    MAC_BASE,
    MAC_FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_ansi(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [WIN_FN] = LAYOUT_ansi(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [MAC_BASE] = LAYOUT_ansi(
        EE_CLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          KC_MUTE,
        RGB_MOD, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, RGB_HUD, RGB_HUI, TG(1),            _______,
        _______, _______, KC_SLEP, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_END, _______,          _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI, _______,                   _______, RGB_VAI, _______,
        _______, GU_TOGG, _______,                            _______,                            KC_APP,  _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    [MAC_FN] = LAYOUT_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    )
};
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [WIN_FN] = { ENCODER_CCW_CW(_______, _______) },
    [MAC_BASE] = { ENCODER_CCW_CW(KC_BRIU, KC_BRID) },
    [MAC_FN] = { ENCODER_CCW_CW(_______, _______) }
};
#endif
// clang-format on
uint16_t pressed_code;
uint16_t pressed_time = 0;
bool     process_record_user(uint16_t keycode, keyrecord_t *record) {
    // if (!process_record_keychron(keycode, record)) {
    //     return false;
    // }
    switch (keycode) {
        case GU_TOGG:
        case EE_CLR: {
            pressed_code = keycode;
            if (record->event.pressed) {
                pressed_time = timer_read();
            } else {
                pressed_time = 0;
            }
            return false;
        }
        case KC_BSPC:
            if ((get_mods() & MOD_MASK_SG)) {
                if (record->event.pressed) {
                    register_code(KC_DEL);
                } else {
                    unregister_code(KC_DEL);
                }
                return false;
            }
        default:
            return true;
    }
}
static uint32_t EE_CLR_press_cnt  = 0;
static uint32_t EE_CLR_press_time = 0;
static bool     EE_CLR_flag       = false;

void housekeeping_task_user(void) {
    if (pressed_time && (timer_elapsed(pressed_time) >= 1500)) {
        pressed_time = 0;
        switch (pressed_code) {
            case EE_CLR:{
                if (!EE_CLR_flag) {
                    EE_CLR_flag       = true;
                    EE_CLR_press_time = timer_read32();
                    EE_CLR_press_cnt  = 1;
                    rgb_matrix_enable_noeeprom();
                }
            } break;
            case GU_TOGG:
                keymap_config.no_gui = !keymap_config.no_gui;
                break;
            default:
                break;
        }
    }
}
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (EE_CLR_flag) {
        if (timer_elapsed32(EE_CLR_press_time) >= EE_CLR_press_cnt * 250) {
            EE_CLR_press_cnt++;
        }
        if (EE_CLR_press_cnt >= 11) {
            EE_CLR_press_time = 0;
            EE_CLR_press_cnt  = 0;
            EE_CLR_flag       = false;
            eeconfig_init();
            eeconfig_update_rgb_matrix_default();
            keymap_config.no_gui = 0;
            eeconfig_update_keymap(keymap_config.raw);
        }
        if (EE_CLR_press_cnt & 0x1) {
            rgb_matrix_set_color_all(100, 100, 100);
        } else {
            rgb_matrix_set_color_all(0, 0, 0);
        }
        return false;
    }
    return true;
}
