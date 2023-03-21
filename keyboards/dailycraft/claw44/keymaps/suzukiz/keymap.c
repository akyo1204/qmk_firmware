#include QMK_KEYBOARD_H
#include <keymap_japanese.h>
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _ADJUST,
};

enum my_keycodes {
    VSCROLL = SAFE_RANGE,
    XSCROLL,
};

#define KC_ KC_TRNS
#define KC_RST RESET
#define KC_L_SPC LT(_LOWER, KC_SPC) // lower
#define KC_R_ENT LT(_RAISE, KC_ENT) // raise
#define KC_G_JA LGUI_T(KC_LANG1)    // cmd or win
#define KC_G_EN LGUI_T(KC_LANG2)    // cmd or win
#define KC_C_BS LCTL_T(KC_BSPC)     // ctrl
#define KC_A_DEL ALT_T(KC_DEL)      // alt

// add by suzukiz
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define KC_R_SPC LT(_RAISE, KC_SPC) // raise
#define KC_BLSF RSFT_T(JP_BSLS)
#define KC_DTAL RALT_T(KC_DOT)
#define MC_BSLH A(JP_YEN)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QWERTY] = LAYOUT( \
  //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
     _______, KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , _______,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     _______, KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , JP_SCLN, _______,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     _______, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DTAL , KC_SLSH, _______,
  //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                       KC_LSFT , KC_C_BS, LOWER   , KC_LGUI,     KC_RALT, KC_R_SPC, KC_RSFT, KC_RGUI
  //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
  ),

  //   \ ^ ! & |  @ = + * % -
  // ( # $ " ' ~  ← ↓ ↑ → ` ) 
  //         { [  ] }

  [_RAISE] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, C(KC_A), C(KC_E), KC_HOME, KC_PGUP, KC_TAB ,     JP_COLN, KC_ENT , KC_UP  , JP_AT  , JP_TILD, KC_F12 ,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_F5  , KC_LSFT, _______, KC_END , KC_PGDN,C(KC_TAB),    JP_PIPE, KC_LEFT, KC_DOWN, KC_RGHT, KC_BLSF, KC_F11 ,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, ADJUST, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     _______, JP_DQUO, JP_HASH, JP_DLR , JP_PERC, JP_AMPR,     JP_QUOT, JP_LPRN, JP_RPRN, JP_CIRC, JP_EQL , _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, JP_EXLM, _______, _______, KC_DEL , KC_ESC ,     JP_ASTR, JP_MINS, JP_LBRC, JP_RBRC, JP_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, _______, G(KC_X), G(KC_C),JP_EISU , KC_LNG1,     JP_YEN , MC_BSLH, JP_LABK, JP_RABK, JP_UNDS, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______,  ADJUST, _______, _______
  //                 `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_ADJUST] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, XSCROLL, VSCROLL, KC_BTN2, KC_BTN1, _______,     KC_BTN1, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, C(KC_TAB),   _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______, _______, VSCROLL, _______
  //                 `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),
};
// clang-format on

static inline float limv(float v, float n) {
    return (v > n) ? (v - n) : ((v < -n) ? (v + n) : 0.0f);
}

#define MOUSE_MODE_TIME 900
#define MOVE_SCALE 0.5f
#define ACCEL_SCALE 4.0f
#define MOVE_LIMIT 0.01f
#define MOUSE_MOVE_DECAY 0.955f
#define MOVE_COUNT_THRESHOLD 10

static bool onVScrollMode          = false;
static bool onScrollMode           = false;
static int  mouseModeRemainingTime = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == VSCROLL) {
        onVScrollMode = record->event.pressed;
        return false;
    } else if (keycode == XSCROLL) {
        onScrollMode = record->event.pressed;
        return false;
    } else if (keycode == KC_BTN1) {
        if (mouseModeRemainingTime != 0) {
            // マウスモード中にボタンが押されたらモード継続
            mouseModeRemainingTime = MOUSE_MODE_TIME;
        }
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (onVScrollMode) {
        mouse_report.v = mouse_report.y / 3;
        mouse_report.h = 0;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else if (onScrollMode) {
        mouse_report.v = mouse_report.y / 3;
        mouse_report.h = mouse_report.x / 4;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        static float move_x   = 0.0f;
        static float move_y   = 0.0f;
        static int   move_cnt = 0;
        float        mx       = 0.0f;
        float        my       = 0.0f;

        if (mouse_report.x == 0 && mouse_report.y == 0) {
            move_x *= MOUSE_MOVE_DECAY;
            move_y *= MOUSE_MOVE_DECAY;
            if (move_cnt > 0) move_cnt--;
            if (mouseModeRemainingTime > 0) {
                if (--mouseModeRemainingTime == 0) {
                    layer_off(_ADJUST);
                }
            }
        }
        {
            float x   = (float)mouse_report.x * MOVE_SCALE;
            float y   = (float)mouse_report.y * MOVE_SCALE;
            float spd = fmax(1.0f, limv(sqrt(x * x + y * y), ACCEL_SCALE));
            move_x -= x * spd;
            move_y -= y * spd;

            mx = move_x;
            my = move_y;
        }

        float mvspd = sqrt(move_x * move_x + move_y * move_y);
        if (mvspd > MOVE_LIMIT) {
            // マウスが動いている
            if (mouseModeRemainingTime != 0 || ++move_cnt > MOVE_COUNT_THRESHOLD) {
                // 動き続けているか、モード継続中ならマウスモード
                mouseModeRemainingTime = MOUSE_MODE_TIME;
                layer_on(_ADJUST);
            }
        }
        if (mouseModeRemainingTime == 0) {
            // マウスモードではないなら動かさない
            mx = 0.0f;
            my = 0.0f;
        }

        mouse_report.x = mx;
        mouse_report.y = my;
    }
    return mouse_report;
}

#ifdef OLED_DRIVER_ENABLE

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Layer: Raise"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Layer: Lower"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Layer: Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }
}

void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(logo, false);
}

char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) {
    return keylog_str;
}
const char *read_keylogs(void) {
    return keylogs_str;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        oled_write_ln(read_keylog(), false);
        // oled_write_ln(read_keylogs(), false);
    } else {
        render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

#endif
