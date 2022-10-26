/* Copyright 2019 gtips
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
#include <keymap_jp.h>

enum layer_names { _BASE, _LOWER, _RAISE, _ADJUST };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define CT_Q LCTL_T(KC_Q)
#define CT_CM RCTL_T(KC_COMM)
#define SF_Z LSFT_T(KC_Z)
#define SF_SS RSFT_T(KC_SLSH)
#define AL_X LALT_T(KC_X)
#define AL_DT RALT_T(KC_DOT)
#define RA_SP LT(RAISE, KC_SPC)

#define KC_R_SPC LT(_RAISE, KC_SPC) // raise
#define KC_L_BS LT(_LOWER, KC_BSPC) // raise
#define KC_BLSF RSFT_T(JP_BSLS)
#define KC_DTAL RALT_T(KC_DOT)
#define MC_BSLH A(JP_YEN)
#define KC_CMGU RGUI_T(KC_COMM)
#define KC_C_BS LCTL_T(KC_BSPC) // ctrl

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung34(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_CMGU, KC_DTAL, KC_SLSH,
                               KC_C_BS, LOWER,         KC_R_SPC, KC_RSFT
  ),

  [_LOWER] = LAYOUT_reviung34(
    JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, JP_AMPR,       JP_QUOT, JP_LPRN, JP_RPRN, JP_CIRC, JP_EQL,
    JP_EXLM, KC_LCTL, KC_LALT, KC_DEL,  KC_ESC,        JP_ASTR, JP_MINS, JP_LBRC, JP_RBRC, JP_PLUS,
    KC_LSFT, KC_LGUI, _______, JP_EISU, KC_LNG1,       JP_YEN,  MC_BSLH, JP_LABK, JP_RABK, JP_UNDS,
                               _______, _______,       ADJUST,  _______
  ),
  
  [_RAISE] = LAYOUT_reviung34(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_LGUI, KC_LCTL, KC_HOME, KC_PGUP, KC_TAB,        JP_COLN, KC_ENT,  KC_UP,   JP_AT,   JP_TILD,
    KC_LSFT, KC_LALT, KC_END,  KC_PGDN, C(KC_TAB),     JP_PIPE, KC_LEFT, KC_DOWN, KC_RGHT, KC_BLSF,
                               _______, ADJUST,        _______, _______
  ),
  
  [_ADJUST] = LAYOUT_reviung34(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    RGB_TOG, XXXXXXX, XXXXXXX, KC_WH_U, KC_F11,        KC_F12,  KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX,
    AG_TOGG, XXXXXXX, XXXXXXX, KC_WH_D, JP_MHEN,       JP_HENK, KC_MS_L, KC_MS_D, KC_MS_R, RESET,
                               _______, _______,       _______, _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _RAISE:
            rgblight_setrgb(0x00, 0x00, 0xFF);
            break;
        case _LOWER:
            rgblight_setrgb(0x00, 0xFF, 0xFF);
            break;
        case _ADJUST:
            rgblight_setrgb(0x00, 0xFF, 0x00);
            break;
        default: //  for any other layers, or the default layer
            rgblight_setrgb(0xA0, 0x00, 0xFF);
            break;
    }
    // return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}

extern rgblight_config_t rgblight_config;
static int               RGB_mode;

void keyboard_post_init_user(void) {
    RGB_mode = rgblight_config.mode;
    rgblight_setrgb(0xFF, 0xFF, 0xFF);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool result = false;
    switch (keycode) {
        case RGB_MOD:
            if (record->event.pressed) {
                rgblight_mode(RGB_mode);
                rgblight_step();
                RGB_mode = rgblight_config.mode;
            }
            break;
        default:
            result = true;
            break;
    }
    return result;
}
