#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    RGBRST = SAFE_RANGE,
    LOWER,
    RAISE,
    KANJI,
};

// enum tapdances{
//   TD_CODO = 0,
//   TD_SLRO,
// };

// Layer Mode aliases
#define KC_MLAD MO(_ADJUST)

// Base layer mod tap
#define KC_A_SF LSFT_T(KC_A)
#define KC_A_CT LCTL_T(KC_A)
#define KC_Z_SF LSFT_T(KC_Z)
#define KC_Z_CT LCTL_T(KC_Z)
#define KC_Z_GU LGUI_T(KC_Z)
#define KC_X_AL LALT_T(KC_X)
#define KC_C_GU LGUI_T(KC_C)
#define KC_SSCT RCTL_T(KC_SLSH)
#define KC_SCCT RCTL_T(JP_SCLN)
#define KC_SCSF RSFT_T(JP_SCLN)
#define KC_SSSF RSFT_T(KC_SLSH)
#define KC_BLCT RCTL_T(JP_BSLS)
#define KC_BLSF RSFT_T(JP_BSLS)
#define KC_TICT RCTL_T(JP_TILD)
#define KC_ENSF RSFT_T(KC_ENT)
#define KC_DTAL RALT_T(KC_DOT)
#define KC_DTCT RCTL_T(KC_DOT)
#define KC_CMGU LGUI_T(KC_COMM)
#define KC_QUCT RCTL_T(JP_QUES)
#define KC_QUSF RSFT_T(JP_QUES)
#define KC_L_SF RSFT_T(KC_L)
#define KC_L_CT RCTL_T(KC_L)
#define KC_S_SF RSFT_T(KC_S)
#define KC_S_CT RCTL_T(KC_S)

// Lower layer mod tap
#define KC_F6SF LSFT_T(KC_F6)
#define KC_EXSF LSFT_T(JP_EXLM)
#define KC_11CT LCTL_T(KC_F11)
#define KC_12AL LALT_T(KC_F12)

// Layer tap
#define KC_BSLO LT(_LOWER, KC_BSPC)
#define KC_SPRA LT(_RAISE, KC_SPC)

#define MC_BSLH A(JP_YEN)

// Tap dance
// #define KC_CODO  TD(TD_CODO)
// #define KC_SLRO  TD(TD_SLRO)

// qk_tap_dance_action_t tap_dance_actions[] = {
//   [TD_CODO] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_DOT),
//   [TD_SLRO] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_RO),
// };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_A_SF,  KC_S_CT,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,  KC_L_CT,  KC_SCSF,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
          KC_Z,  KC_X_AL,  KC_C_GU,     KC_V,     KC_B,     KC_N,     KC_M,  KC_CMGU,  KC_DTAL,  KC_SSSF,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_BSLO,  KC_SPRA
  //                                        `---------|---------'
  ),

  [_LOWER] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
       JP_DQUO,  JP_HASH,   JP_DLR,  JP_PERC,  JP_AMPR,  JP_QUOT,  JP_LPRN,  JP_RPRN,  JP_CIRC,   JP_EQL,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       JP_EXLM,  C(KC_S),  KC_LALT,   KC_DEL,   KC_ESC,  JP_ASTR,  JP_MINS,  JP_LBRC,  JP_RBRC,  JP_PLUS,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       C(KC_Z),  C(KC_X),  C(KC_C),  KC_LCTL, KC_LANG1,   JP_YEN,  MC_BSLH,  JP_LABK,  JP_RABK,  JP_UNDS,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               _______,  KC_MLAD
  //                                        `---------|---------'
  ),

  [_RAISE] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LSFT,  KC_LCTL,  KC_HOME,  KC_PGUP,   KC_TAB,  JP_COLN,   KC_ENT,    KC_UP,    JP_AT,  JP_TILD,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LGUI,  KC_LALT,   KC_END,  KC_PGDN,C(KC_TAB),  JP_PIPE,  KC_LEFT,  KC_DOWN,  KC_RGHT,  JP_QUES,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_MLAD,  _______
  //                                        `---------|---------'
  ),

  [_ADJUST] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
        RESET,    RGBRST,  AG_NORM,  AG_SWAP,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_INS,  KC_PSCR,
  //|---------+---------+---------+---------+---------+--------+---------+---------+---------+---------|
       RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,   KC_F12,  KC_F11,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_NLCK,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  JP_MHEN, JP_HENK,  KC_MS_L,  KC_MS_D,  KC_MS_R,  XXXXXXX,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               _______,  _______
  //                                        `---------|---------'
  )
};
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BSLO:
            return TAPPING_LAYER_TERM;
        case KC_SPRA:
            return TAPPING_LAYER_TERM;
        default:
            return TAPPING_TERM;
    }
}

int  RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool result = false;
    switch (keycode) {
        case KANJI:
            if (record->event.pressed) {
                if (keymap_config.swap_lalt_lgui == false) {
                    register_code(KC_LANG2);
                } else {
                    SEND_STRING(SS_LALT("`"));
                }
            } else {
                unregister_code(KC_LANG2);
            }
            break;
#ifdef RGBLIGHT_ENABLE
        // led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
        case RGB_MOD:
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
            break;
        case RGBRST:
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
            break;
#endif
        default:
            result = true;
            break;
    }

    return result;
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}
