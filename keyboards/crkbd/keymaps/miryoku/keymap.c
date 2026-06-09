#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _SYM,
    _FUN
};

// Home Row Mods
#define HR_A LGUI_T(KC_A)
#define HR_R LALT_T(KC_R)
#define HR_S LCTL_T(KC_S)
#define HR_T LSFT_T(KC_T)

#define HR_N RSFT_T(KC_N)
#define HR_E RCTL_T(KC_E)
#define HR_I RALT_T(KC_I)
#define HR_O RGUI_T(KC_O)

// Thumb Keys (Miryoku Spec)
// Left Hand: Media, Nav, Mouse
#define TH_MED LT(_MEDIA, KC_ESC)
#define TH_NAV LT(_NAV, KC_SPC)
#define TH_MSE LT(_MOUSE, KC_TAB)

// Right Hand: Sym, Num, Fun
#define TH_SYM LT(_SYM, KC_ENT)
#define TH_NUM LT(_NUM, KC_BSPC)
#define TH_FUN LT(_FUN, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_TRNS,
        KC_TRNS, HR_A,    HR_R,    HR_S,    HR_T,    KC_G,                      KC_M,    HR_N,    HR_E,    HR_I,    HR_O,    KC_TRNS,
        KC_TRNS, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                      KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
                                    TH_MED,  TH_NAV,  TH_MSE,                    TH_SYM,  TH_NUM,  TH_FUN
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS,
        KC_TRNS, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_TRNS,                   KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_MOUSE] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_TRNS,                   KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_BTN1, KC_BTN2, KC_BTN3
    ),

    [_MEDIA] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_TRNS,                   KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_MSTP, KC_MPLY, KC_MUTE
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                    KC_TRNS, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, KC_TRNS,
        KC_TRNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_DOT,  KC_0,    KC_MINS,                   KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                   KC_TRNS, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, KC_TRNS,
        KC_TRNS, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_LPRN, KC_RPRN, KC_UNDS,                   KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_FUN] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                   KC_TRNS, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, KC_TRNS,
        KC_TRNS, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_APP,  KC_SPC,  KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
    )
};