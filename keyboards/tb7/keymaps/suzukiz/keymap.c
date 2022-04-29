#include QMK_KEYBOARD_H

#include "paw3204.h"
#include "pointing_device.h"

bool isScrollMode;

enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
};

enum custom_keycodes {
    // clang-format off
    BASE = SAFE_RANGE,
    RAISE,
    LOWER,
    MBTN1,
    MBTN2,
    MBTN3,
    SCRL
    // clang-format on
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
  [_BASE] = LAYOUT( \
                KC_SPC,   RAISE,
     C(KC_TAB), KC_LSFT,  LOWER,
     MBTN1,     MBTN2,    MBTN3
  ),
  [_RAISE] = LAYOUT( \
                KC_SPC,   KC_TRNS, 
     KC_ENT,    KC_ESC,   KC_BSPC,
     KC_LCTL,   KC_LGUI,  KC_LSFT
  ),
  [_LOWER] = LAYOUT( \
                KC_SPC,   KC_DEL,
     KC_TAB,    KC_LALT,  KC_TRNS,
     KC_LCTL,   KC_LGUI,  KC_LSFT
  )
    // clang-format on
};

void report_button(bool pressed, int btn) {
    report_mouse_t currentReport = pointing_device_get_report();
    if (pressed) {
        currentReport.buttons |= btn;
    } else {
        currentReport.buttons &= ~btn;
    }
    pointing_device_set_report(currentReport);
    pointing_device_send();
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MBTN1:
            report_button(record->event.pressed, MOUSE_BTN1);
            return false;
        case MBTN2:
            report_button(record->event.pressed, MOUSE_BTN2);
            return false;
        case MBTN3:
            report_button(record->event.pressed, MOUSE_BTN3);
            return false;
        case SCRL:
            if (record->event.pressed) {
                isScrollMode = true;
            } else {
                isScrollMode = false;
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
    }
    return true;
}

void matrix_init_user(void) { init_paw3204(); }

void keyboard_post_init_user() {
    debug_enable = true;
    debug_mouse  = true;
}

struct MoveCursor {
    float point;
    float history[10];
    int   count;
    float threshold;
    float decelerate;
};
static struct MoveCursor moveCursor[4];

static int mcUpdate(struct MoveCursor* mc, float n) {
    int count          = mc->count;
    int index          = count % 10;
    mc->history[index] = n;
    count++;
    mc->count = count;
    if (count > 10) count = 10;
    float avg = 0.0f;
    for (int i = 0; i < count; i++) {
        avg += mc->history[i];
        mc->history[i] *= mc->decelerate;
    }
    float point = mc->point + avg / (float)count;
    int   dir   = 0;
    if (point > mc->threshold) {
        point -= mc->threshold;
        dir = 1;
    } else if (point < -mc->threshold) {
        point += mc->threshold;
        dir = -1;
    }
    mc->point = point;
    return dir;
}

static void mcClear(struct MoveCursor* mc) {
    mc->point = 0.0f;
    mc->count = 0;
    for (int i = 0; i < 0; i++) {
        mc->history[i] = 0.0f;
    }
}

static int curmove_solo(int ch, int spd, int key, int pl, int mi) {
    struct MoveCursor* mc = &moveCursor[ch];
    mc->threshold         = 40.0f;
    mc->decelerate        = 0.0f;
    int hDir              = mcUpdate(mc, spd);
    if (hDir > 0) {
        if (key != pl) {
            unregister_code(key);
            key = pl;
            register_code(key);
        }
    } else if (hDir < 0) {
        if (key != mi) {
            unregister_code(key);
            key = mi;
            register_code(key);
        }
    } else {
        unregister_code(key);
        key = KC_NO;
    }
    return key;
}

static void curmove(int x, int y) {
    static int hKey = KC_NO;
    static int vKey = KC_NO;
    hKey            = curmove_solo(0, x, hKey, KC_LEFT, KC_RIGHT);
    vKey            = curmove_solo(1, y, vKey, KC_DOWN, KC_UP);
}

static int moment_spd(float spd, int ch) {
    struct MoveCursor* mc = &moveCursor[ch + 2];
    mc->threshold         = 20.0f;
    mc->decelerate        = 1.0f;
    return mcUpdate(mc, spd);
}

void moment_clr(void) {
    for (int i = 0; i < 4; i++) {
        mcClear(&moveCursor[i]);
    }
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;

    report_mouse_t mouse_rep = pointing_device_get_report();

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t  x, y;

        read_paw3204(&stat, &x, &y);

        if (isScrollMode || IS_LAYER_ON(_RAISE)) {
            int yspd    = -y;
            int xspd    = -x;
            mouse_rep.h = moment_spd(yspd, 0);
            mouse_rep.v = moment_spd(xspd, 1);
        } else if (IS_LAYER_ON(_LOWER)) {
            curmove(y, x);
        } else {
            float spd = 1.5f;
            float xs  = fabs(x);
            float ys  = fabs(y);
            xs        = fmax(1.0f, (xs / 20.0f));
            ys        = fmax(1.0f, (ys / 15.0f));
            float mx  = fmin(127.0f, fmax(-127.0f, x * xs * xs * spd));
            float my  = fmin(127.0f, fmax(-127.0f, y * ys * ys * spd));

            // const float lowspd = 1.0f;
            // if (mx > lowspd)
            //     mx -= lowspd;
            // else if (mx < -lowspd)
            //     mx += lowspd;
            // else
            //     mx = 0.0f;
            // if (my > lowspd)
            //     my -= lowspd;
            // else if (my < -lowspd)
            //     my += lowspd;
            // else
            //     my = 0.0f;
            mouse_rep.x = -my;
            mouse_rep.y = mx;
            moment_clr();
        }

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        } else if (IS_LAYER_ON(_RAISE)) {
            pointing_device_set_report(mouse_rep);
        }
    }
}
