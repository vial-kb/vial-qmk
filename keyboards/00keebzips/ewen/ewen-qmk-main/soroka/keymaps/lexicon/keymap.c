#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

// Layer definitions
#define _BL 0
#define _SYMBOLS 1
#define _NUM 2
#define _WORDS 3
#define _NAV 4

enum custom_keycodes {
  Q_QUOTE = SAFE_RANGE,
  W_WITH,
  E_HE,
  R_ARE,
  T_THE,
  Y_WHY,
  U_YOU,
  I_IN,
  O_OR,
  P_PLAY,
  A_AND,
  S_SAID,
  D_DONT,
  F_FROM,
  G_GET,
  H_HOW,
  J_JUST,
  K_KNOW,
  L_WILL,
  Z_ZERO,
  X_SHE,
  C_CAN,
  V_VERY,
  B_BUT,
  N_NOT,
  M_MORE,
  ESC_THIS,
  TAB_THAT,
};

enum unicode_names {
    U_BANG,
    U_EMDASH,
    U_ENDASH,
    U_OPENQ,
    U_CLOSEQ,
    U_ELLIPSIS,
    U_ACCENT_E,
    U_BULLET,
    U_DAGGER,
    U_COPYRT,
    U_DEGREE,
    U_MANICULE,
    U_SECTION,
    U_FLEURON,
    U_ASTERISM,
    U_D_DAGGER,
    U_BOLUS,
    U_MULTIP,
    U_YEN,
    U_POUND,
    U_CENT,
    U_ENYE,
    U_NUMERO,
    U_PILCROW,
    U_HALF,
    U_QUARTER,
    U_ROOT,
    U_EURO,
    U_NOTEQUAL
};

const uint32_t PROGMEM unicode_map[] = {
    [U_BANG]  = 0x203D,  // ‽
    [U_EMDASH] = 0x2014, // —
    [U_ENDASH] = 0x2013, // –
    [U_OPENQ] = 0x201C, // “
    [U_CLOSEQ] = 0x201D, // ”
    [U_ELLIPSIS] = 0x2026, // …
    [U_ACCENT_E] = 0x00E9, // é
    [U_BULLET] = 0x2022, // •
    [U_DAGGER] = 0x2020, // †
    [U_COPYRT] = 0x00A9, // ©
    [U_DEGREE] = 0x00B0, // °
    [U_MANICULE] = 0x261E, // ☞
    [U_SECTION] = 0x00A7, // §
    [U_FLEURON] = 0x2767, // ❧
    [U_ASTERISM] = 0x2042, // ⁂
    [U_D_DAGGER] = 0x2021, // ‡
    [U_BOLUS] = 0x00F7, // ÷
    [U_MULTIP] = 0x00D7, // ×
    [U_YEN] = 0x00A5, // ¥
    [U_POUND] = 0x00A3, // £
    [U_CENT] = 0x00A2, // ¢
    [U_ENYE] = 0x00F1, // ñ
    [U_NUMERO] = 0x2116, // №
    [U_PILCROW] = 0x00B6, // ¶
    [U_HALF] = 0x00BD, // ½
    [U_QUARTER] = 0x00BC, // ¼
    [U_ROOT] = 0x221A, // √
    [U_EURO] = 0x20AC, // €
    [U_NOTEQUAL] = 0x2260 // ≠
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    [_BL] = LAYOUT(
        QK_GESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_MINUS,   C(KC_I), KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUES,  KC_RSFT,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_A, LT(_SYMBOLS, KC_SPC), KC_TRNS,  LT(_NUM, KC_SPC), KC_TRNS, LT(_WORDS, KC_SPC), KC_TRNS,   KC_RALT, KC_RCTL, KC_TRNS, MO(_NAV)
    ),
    [_SYMBOLS] = LAYOUT(
        KC_TILD,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  X(U_EMDASH),   KC_TRNS, C(KC_Z),
        KC_BSLS, X(U_MANICULE), X(U_COPYRT), X(U_ACCENT_E), X(U_SECTION), X(U_FLEURON), X(U_DEGREE), X(U_ASTERISM), X(U_BULLET), X(U_DAGGER), X(U_D_DAGGER), X(U_OPENQ), KC_ENT,
        KC_TRNS, X(U_BOLUS), X(U_MULTIP), X(U_YEN), X(U_POUND), X(U_CENT), X(U_ENYE), X(U_NUMERO), X(U_PILCROW), X(U_ELLIPSIS),  X(U_BANG),  KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_WORDS] = LAYOUT(
        ESC_THIS,   Q_QUOTE,  W_WITH,   E_HE,     R_ARE,    T_THE,    Y_WHY,    U_YOU,    I_IN,     O_OR,     P_PLAY,  X(U_ENDASH),   KC_TRNS, KC_DEL,
        TAB_THAT,   A_AND,    S_SAID,   D_DONT,   F_FROM,   G_GET,    H_HOW,    J_JUST,   K_KNOW,   L_WILL,    KC_SCLN, X(U_CLOSEQ),          KC_TRNS,
        KC_TRNS,          Z_ZERO,    X_SHE,   C_CAN,    V_VERY,   B_BUT,    N_NOT,    M_MORE,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NUM] = LAYOUT(
        KC_GRV,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,   KC_TRNS,      KC_TRNS,
        KC_PIPE,   KC_F1,  KC_F2,    KC_F3, KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_F11,    KC_F12,  X(U_BOLUS),   X(U_MULTIP), X(U_ROOT),  X(U_EURO),  X(U_NOTEQUAL),    KC_LBRC,   KC_RBRC,    KC_SLSH,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NAV] = LAYOUT(
        KC_TRNS,  KC_PGUP,  KC_UP,    KC_PGDN,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,   KC_TRNS,      KC_TRNS,
        UC_MOD,   KC_LEFT,  KC_DOWN,    KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_HOME, KC_TRNS,   KC_END,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case Q_QUOTE:
      if (record->event.pressed) {
        SEND_STRING("quote");
      } else {
      }
      break;
    case W_WITH:
      if (record->event.pressed) {
        SEND_STRING("with");
      } else {
      }
      break;
    case E_HE:
      if (record->event.pressed) {
        SEND_STRING("he");
      } else {
      }
      break;
    case R_ARE:
      if (record->event.pressed) {
        SEND_STRING("are");
      } else {
      }
      break;
    case T_THE:
      if (record->event.pressed) {
        SEND_STRING("the");
      } else {
      }
      break;
    case U_YOU:
      if (record->event.pressed) {
        SEND_STRING("you");
      } else {
      }
      break;
    case Y_WHY:
      if (record->event.pressed) {
        SEND_STRING("why");
      } else {
      }
      break;
    case I_IN:
      if (record->event.pressed) {
        SEND_STRING("in");
      } else {
      }
      break;
    case O_OR:
      if (record->event.pressed) {
        SEND_STRING("or");
      } else {
      }
      break;
    case P_PLAY:
      if (record->event.pressed) {
        SEND_STRING("play");
      } else {
      }
      break;
    case A_AND:
      if (record->event.pressed) {
        SEND_STRING("and");
      } else {
      }
      break;
    case S_SAID:
      if (record->event.pressed) {
        SEND_STRING("said");
      } else {
      }
      break;
    case D_DONT:
      if (record->event.pressed) {
        SEND_STRING("don't");
      } else {
      }
      break;
    case F_FROM:
      if (record->event.pressed) {
        SEND_STRING("from");
      } else {
      }
      break;
    case G_GET:
      if (record->event.pressed) {
        SEND_STRING("get");
      } else {
      }
      break;
    case H_HOW:
      if (record->event.pressed) {
        SEND_STRING("how");
      } else {
      }
      break;
    case J_JUST:
      if (record->event.pressed) {
        SEND_STRING("just");
      } else {
      }
      break;
    case K_KNOW:
      if (record->event.pressed) {
        SEND_STRING("know");
      } else {
      }
      break;
    case L_WILL:
      if (record->event.pressed) {
        SEND_STRING("will");
      } else {
      }
      break;
    case Z_ZERO:
      if (record->event.pressed) {
        SEND_STRING("zero");
      } else {
      }
      break;
    case X_SHE:
      if (record->event.pressed) {
        SEND_STRING("she");
      } else {
      }
      break;
    case C_CAN:
      if (record->event.pressed) {
        SEND_STRING("can");
      } else {
      }
      break;
    case V_VERY:
      if (record->event.pressed) {
        SEND_STRING("very");
      } else {
      }
      break;
    case B_BUT:
      if (record->event.pressed) {
        SEND_STRING("but");
      } else {
      }
      break;
    case N_NOT:
      if (record->event.pressed) {
        SEND_STRING("now");
      } else {
      }
      break;
    case M_MORE:
      if (record->event.pressed) {
        SEND_STRING("more");
      } else {
      }
      break;
    case ESC_THIS:
      if (record->event.pressed) {
        SEND_STRING("this");
      } else {
      }
      break;
    case TAB_THAT:
      if (record->event.pressed) {
        SEND_STRING("that");
      } else {
      }
      break;
  }
  return true;
}

void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_WINC);
}