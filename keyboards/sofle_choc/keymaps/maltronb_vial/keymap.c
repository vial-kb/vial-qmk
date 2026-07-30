// Copyright 2026 — Sofle Choc Maltron-B
// SPDX-License-Identifier: GPL-2.0-or-later
// Pure QMK, left-half standalone, Pro Micro RP2040
// No Vial, no tap dance

#include QMK_KEYBOARD_H

// ─── Layers ───────────────────────────────────────────────────
enum layers { _BASE=0, _NUM, _SYM, _NAV, _CFG, _CAT, _GAME, _NUMPAD, _WIN };

// ─── Custom keycodes ──────────────────────────────────────────
enum custom_keycodes {
    CK_ENC = SAFE_RANGE,
    CK_GAMETOG,
    CK_CATTOG,
    CK_NUMPADTOG,
    CK_WINTOG,
    // Windows admin macros (stock Windows 11)
    CK_W_COMPMGMT, CK_W_SERVICES, CK_W_DEVMGMT, CK_W_DISKMGMT,
    CK_W_EVENTVWR, CK_W_PERFMON,  CK_W_TASKSCHD, CK_W_LUSRMGR,
    CK_W_GPEDIT,   CK_W_SECPOL,   CK_W_WF,       CK_W_WMIMGMT,
    CK_W_FSMGMT,   CK_W_CERTMGR,  CK_W_CERTLM,   CK_W_TPM,
    CK_W_PRINTMGR, CK_W_VIRTMGMT, CK_W_OPTFEAT,  CK_W_TASKMGR,
    CK_W_REGEDIT,  CK_W_NCPA,     CK_W_MMSYS,    CK_W_MMSYSREC,
    CK_W_SYSDM,    CK_W_APPWIZ,   CK_W_INETCPL,  CK_W_POWERCFG,
    CK_W_TIMEDATE, CK_W_NETPLWIZ,
    // Modern Settings URIs
    CK_W_SET_DISPLAY, CK_W_SET_BT, CK_W_SET_NET, CK_W_SET_UPDATE,
    CK_W_SET_APPS,    CK_W_SET_DEFENDER, CK_W_SET_SOUND, CK_W_SET_ABOUT,
    CK_W_SET_DISKS,
    // RSAT domain admin
    CK_W_DSA, CK_W_DSSITE, CK_W_DOMAIN, CK_W_ADSIEDIT,
    CK_W_GPMC, CK_W_DNSMGMT, CK_W_DHCPMGMT, CK_W_DFSMGMT, CK_W_RSOP,
    // Dev shells / tools
    CK_W_PWSH,    CK_W_PWSH_ADMIN,
    CK_W_VSCODE,  CK_W_CLAUDE,  CK_W_CODEX,
    CK_W_AWS,     CK_W_AZ,      CK_W_DOCTL,    CK_W_GH,
    CK_W_SCOOP,   CK_W_SYNAPSE,
};

// ─── Keymaps (60 args each) ────────────────────────────────────
// LAYOUT order: row0L row0R row1L row1R row2L row2R
//               row3L k4F k9F row3R thumbL(5) thumbR(5)
//
// _BASE new layout:
//   Row 0: ;  B  W  F  G  Y
//   Row 1: ,  D  L  S  H  I
//   Row 2: '  A  E  T  N  O   (HOME ROW)
//   Row 3: .  P  M  C  R  U
//
// _GAME: tap dance removed — number row = plain digits,
//        surround keys = plain letters.
//        Single/double-tap F-key access removed for stability.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_SCLN,KC_B,   KC_W,   KC_F,   KC_G,   KC_Y,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_COMM,KC_D,   KC_L,   KC_S,   KC_H,   KC_I,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_QUOT,KC_A,   KC_E,   KC_T,   KC_N,   KC_O,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_DOT, KC_P,   KC_M,   KC_C,   KC_R,   KC_U,
    CK_ENC, KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LCTL,KC_LALT,KC_LSFT,LT(_NUM,KC_SPC),LT(_SYM,KC_BSPC),
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),

[_NUM] = LAYOUT(
    KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TAB, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_F11, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_F12, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_MUTE,KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LCTL,KC_LALT,KC_LSFT,MO(_NAV),MO(_SYM),
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),

[_SYM] = LAYOUT(
    KC_LPRN,KC_LBRC,KC_LCBR,KC_LT,  KC_GT,  KC_RPRN,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_DQUO,KC_GRV, KC_BSLS,KC_SLSH,KC_PIPE,KC_QUES,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_PLUS,KC_MINS,KC_ASTR,KC_EQL, KC_UNDS,KC_TILD,
    KC_MUTE,KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LGUI,KC_LALT,KC_LCTL,MO(_NAV),KC_TRNS,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),

[_NAV] = LAYOUT(
    KC_ESC, KC_HOME,KC_UP,  KC_END, KC_PGUP,KC_INS,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TAB, KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,KC_DEL,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_BTN1,KC_MS_L,KC_MS_D,KC_MS_R,KC_BTN2,KC_BTN3,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LGUI,KC_LALT,KC_LCTL,KC_LSFT,MO(_CFG),KC_CAPS,
    KC_MUTE,KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),

[_CFG] = LAYOUT(
    QK_BOOT,EE_CLR, RGB_TOG,RGB_MOD,RGB_HUI,RGB_HUD,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  RGB_VAI,RGB_VAD,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_F5,  KC_F6,  KC_F7,  KC_F8,  RGB_SAI,RGB_SAD,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_F9,  KC_F10, KC_F11, KC_F12, CK_GAMETOG,CK_CATTOG,
    KC_MUTE,KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),

[_CAT] = LAYOUT(
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,CK_CATTOG,
    KC_MUTE,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO
),

// _GAME: plain keycodes, no tap dance
// Row 0: ESC 1  2  3  4  5   (number row — plain digits)
// Row 1: TAB Q  W  E  R  T
// Row 2: SFT A  S  D  F  G
// Row 3: CTL Z  X  C  V  Y
// Thumbs: GTOG ALT SPC ENT BSPC
// F-keys accessible via CFG layer or _NUM layer
[_GAME] = LAYOUT(
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LSFT,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LCTL,KC_Z,   KC_X,   KC_C,   KC_V,   KC_Y,
    KC_MUTE,KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    CK_GAMETOG,KC_LALT,KC_SPC,KC_ENT,KC_BSPC,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),

// _NUMPAD: full-takeover layer — calculator/data-entry style
// Triple-tap LSFT (T2 thumb) toggles on/off
// R1: NUM_LOCK  /  *  -  PRINT_SCREEN  PAUSE
// R2: 7  8  9  +  PG_UP  PG_DOWN
// R3: 4  5  6  NUMPAD_ENTER  HOME  END
// R4: 1  2  3  .  DEL  INS
// Thumbs: 0  LSFT  LCTL  NUMPAD_TOG  NUMPAD_TOG (exit)
[_NUMPAD] = LAYOUT(
    KC_NUM, KC_PSLS,KC_PAST,KC_PMNS,KC_PSCR,KC_PAUS,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_P7,  KC_P8,  KC_P9,  KC_PPLS,KC_PGUP,KC_PGDN,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_P4,  KC_P5,  KC_P6,  KC_PENT,KC_HOME,KC_END,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_P1,  KC_P2,  KC_P3,  KC_PDOT,KC_DEL, KC_INS,
    KC_MUTE,KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_P0,  KC_LSFT,KC_LCTL,CK_NUMPADTOG,CK_NUMPADTOG,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),

// _WIN: Windows admin & dev power-user layer
// Entry: Ctrl+Alt+Shift+W held 900ms (rare chord, never accidentally typed)
// Each key sends Win+R → command → Enter via SEND_STRING
// Row 0 (top):     Modern Settings URIs
// Row 1:           Classic Control Panel .cpl applets
// Row 2 (HOME):    Most-used MSC consoles (best ergonomics)
// Row 3 (bottom):  Security + RSAT domain admin
// Thumbs:          CTL ALT SFT EXIT EXIT
[_WIN] = LAYOUT(
    CK_W_SET_APPS,   CK_W_SET_UPDATE, CK_W_SET_NET,    CK_W_SET_BT,     CK_W_SET_DISPLAY,CK_W_SET_ABOUT,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    CK_W_NCPA,       CK_W_MMSYS,      CK_W_POWERCFG,   CK_W_TIMEDATE,   CK_W_INETCPL,    CK_W_APPWIZ,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    CK_W_COMPMGMT,   CK_W_SERVICES,   CK_W_TASKMGR,    CK_W_DEVMGMT,    CK_W_EVENTVWR,   CK_W_TASKSCHD,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    CK_W_GPEDIT,     CK_W_SECPOL,     CK_W_WF,         CK_W_DSA,        CK_W_GPMC,       CK_W_DNSMGMT,
    KC_MUTE,KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LCTL,KC_LALT,KC_LSFT,CK_WINTOG,CK_WINTOG,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),
};

// ─── Encoder map ──────────────────────────────────────────────
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]={ENCODER_CCW_CW(KC_VOLD,KC_VOLU)},
    [_NUM] ={ENCODER_CCW_CW(KC_PGUP,KC_PGDN)},
    [_SYM] ={ENCODER_CCW_CW(KC_LEFT,KC_RGHT)},
    [_NAV] ={ENCODER_CCW_CW(KC_WH_D,KC_WH_U)},
    [_CFG] ={ENCODER_CCW_CW(RGB_HUD,RGB_HUI)},
    [_CAT] ={ENCODER_CCW_CW(KC_VOLD,KC_VOLU)},
    [_GAME]={ENCODER_CCW_CW(KC_VOLD,KC_VOLU)},
    [_NUMPAD]={ENCODER_CCW_CW(KC_PGUP,KC_PGDN)},
    [_WIN]   ={ENCODER_CCW_CW(KC_VOLD,KC_VOLU)},
};
#endif

// ─── LED LUT ──────────────────────────────────────────────────
static const uint8_t PROGMEM led_lut[5][6] = {
    {28,21,20,11,10, 0},
    {27,22,19,12, 9, 1},
    {26,23,18,13, 8, 2},
    {25,24,17,14, 7, 3},
    {16,15, 6, 5, 4,255},
};
static uint8_t lut(uint8_t r, uint8_t c) {
    return pgm_read_byte(&led_lut[r][c]);
}

// ─── Combo pulse — flashes BOTH keys of the combo ─────────────
static uint8_t  pulse_led1  = 255;
static uint8_t  pulse_led2  = 255;
static uint32_t pulse_until = 0;
static void pulse2(uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2) {
    pulse_led1  = lut(r1, c1);
    pulse_led2  = lut(r2, c2);
    pulse_until = timer_read32() + 300;
}

// ─── Combos ───────────────────────────────────────────────────
enum combo_events {
    CB_TAB, CB_ESC, CB_ENT, CB_DEL, CB_CAPS, CB_BSPC,
    CB_K,   CB_J,   CB_Q,   CB_X,   CB_V,    CB_Z,
    CB_UNDO,CB_COPY,CB_PASTE,CB_CUT,CB_SALL,
    CB_PAREN,CB_BRACK,CB_BRACE,CB_ANGLE,
    CB_ARROW,CB_DCOL,CB_NEQ,CB_EQEQ,CB_GE,CB_LE,
    CB_AND, CB_OR,  CB_BCOM,CB_ECOM,CB_INCL,
    CB_HOME,CB_END, CB_LEFT,CB_RIGHT,
    CB_AUTOC,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

// === Combo assignments — ranked by ergonomic accessibility ===
// TIER 1: Letters (highest priority — home row & home-adjacent)
//   V K on home row; X J Z Q on home-column verticals
// TIER 2: Utility (TAB ESC ENT DEL CAPS BSPC) — strong-finger pairs
// TIER 3: Navigation (HOME END LEFT RIGHT) — diagonals
// TIER 4: Brackets — column-vertical pairs
// TIER 5: Operators — remaining ergonomic pairs

// TIER 1 — LETTERS (most accessible)
static const uint16_t PROGMEM c_v[]    = {KC_A,    KC_E,    COMBO_END}; // home r2 c1+c2
static const uint16_t PROGMEM c_k[]    = {KC_A,    KC_O,    COMBO_END}; // home r2 c1+c5 pinky stretch
static const uint16_t PROGMEM c_x[]    = {KC_T,    KC_C,    COMBO_END}; // col 3 r2+r3
static const uint16_t PROGMEM c_j[]    = {KC_N,    KC_R,    COMBO_END}; // col 4 r2+r3
static const uint16_t PROGMEM c_z[]    = {KC_N,    KC_H,    COMBO_END}; // col 4 r1+r2
static const uint16_t PROGMEM c_q[]    = {KC_O,    KC_I,    COMBO_END}; // col 5 r1+r2

// TIER 2 — UTILITY
static const uint16_t PROGMEM c_caps[] = {KC_QUOT, KC_A,    COMBO_END}; // home pinky r2 c0+c1
static const uint16_t PROGMEM c_ent[]  = {KC_E,    KC_T,    COMBO_END}; // home r2 c2+c3
static const uint16_t PROGMEM c_tab[]  = {KC_D,    KC_L,    COMBO_END}; // row 1 c1+c2
static const uint16_t PROGMEM c_bspc[] = {KC_L,    KC_S,    COMBO_END}; // row 1 c2+c3
static const uint16_t PROGMEM c_del[]  = {KC_M,    KC_C,    COMBO_END}; // row 3 c2+c3
static const uint16_t PROGMEM c_esc[]  = {KC_SCLN, KC_COMM, COMBO_END}; // col 0 r0+r1 pinky


// TIER 3 — EDITING (row 3 cluster — easy non-word pairs)
static const uint16_t PROGMEM c_undo[] = {KC_P,    KC_M,    COMBO_END}; // r3 c1+c2
static const uint16_t PROGMEM c_copy[] = {KC_C,    KC_R,    COMBO_END}; // r3 c3+c4
static const uint16_t PROGMEM c_paste[]= {KC_R,    KC_U,    COMBO_END}; // r3 c4+c5
static const uint16_t PROGMEM c_cut[]  = {KC_M,    KC_R,    COMBO_END}; // r3 c2+c4
static const uint16_t PROGMEM c_sall[] = {KC_DOT,  KC_M,    COMBO_END}; // r3 c0+c2
// TIER 3 — NAVIGATION
static const uint16_t PROGMEM c_home[] = {KC_B,    KC_L,    COMBO_END}; // r0c1+r1c2 diag
static const uint16_t PROGMEM c_end[]  = {KC_G,    KC_I,    COMBO_END}; // r0c4+r1c5 diag
static const uint16_t PROGMEM c_left[] = {KC_T,    KC_N,    COMBO_END}; // home r2 c3+c4
static const uint16_t PROGMEM c_rght[] = {KC_E,    KC_O,    COMBO_END}; // home r2 c2+c5
static const uint16_t PROGMEM c_autoc[]= {KC_QUOT, KC_O,    COMBO_END}; // home r2 c0+c5 — Ctrl+Space autocomplete

// TIER 4 — BRACKETS (column-vertical pairs)
static const uint16_t PROGMEM c_paren[]= {KC_B,    KC_D,    COMBO_END}; // col 1 r0+r1
static const uint16_t PROGMEM c_brack[]= {KC_W,    KC_L,    COMBO_END}; // col 2 r0+r1
static const uint16_t PROGMEM c_brace[]= {KC_F,    KC_S,    COMBO_END}; // col 3 r0+r1
static const uint16_t PROGMEM c_angle[]= {KC_G,    KC_H,    COMBO_END}; // col 4 r0+r1

// TIER 5 — OPERATORS (longer reaches OK — less frequent)
static const uint16_t PROGMEM c_arrow[]= {KC_D,    KC_A,    COMBO_END}; // diag r1c1+r2c1
static const uint16_t PROGMEM c_dcol[] = {KC_QUOT, KC_E,    COMBO_END}; // r2 c0+c2 pinky reach
static const uint16_t PROGMEM c_neq[]  = {KC_Y,    KC_I,    COMBO_END}; // col 5 r0+r1
static const uint16_t PROGMEM c_eqeq[] = {KC_A,    KC_T,    COMBO_END}; // r2 c1+c3 2-apart
static const uint16_t PROGMEM c_ge[]   = {KC_D,    KC_S,    COMBO_END}; // r1 c1+c3 2-apart
static const uint16_t PROGMEM c_le[]   = {KC_L,    KC_H,    COMBO_END}; // r1 c2+c4 2-apart
static const uint16_t PROGMEM c_and[]  = {KC_COMM, KC_QUOT, COMBO_END}; // col 0 r1+r2
static const uint16_t PROGMEM c_or[]   = {KC_QUOT, KC_DOT,  COMBO_END}; // col 0 r2+r3
static const uint16_t PROGMEM c_bcom[] = {KC_COMM, KC_D,    COMBO_END}; // r1 c0+c1
static const uint16_t PROGMEM c_ecom[] = {KC_P,    KC_C,    COMBO_END}; // r3 c1+c3 2-apart
static const uint16_t PROGMEM c_incl[] = {KC_DOT,  KC_U,    COMBO_END}; // r3 c0+c5 anchor

combo_t key_combos[] = {
    [CB_TAB]  = COMBO(c_tab, KC_NO),
    [CB_ESC]  = COMBO(c_esc, KC_NO),
    [CB_ENT]  = COMBO(c_ent, KC_NO),
    [CB_DEL]  = COMBO(c_del, KC_NO),
    [CB_CAPS] = COMBO(c_caps, KC_NO),
    [CB_BSPC] = COMBO(c_bspc, KC_NO),
    [CB_K]    = COMBO(c_k, KC_NO),
    [CB_J]    = COMBO(c_j, KC_NO),
    [CB_Q]    = COMBO(c_q, KC_NO),
    [CB_X]    = COMBO(c_x, KC_NO),
    [CB_V]    = COMBO(c_v, KC_NO),
    [CB_Z]    = COMBO(c_z, KC_NO),
    [CB_UNDO] = COMBO(c_undo, KC_NO),
    [CB_COPY] = COMBO(c_copy, KC_NO),
    [CB_PASTE]= COMBO(c_paste, KC_NO),
    [CB_CUT]  = COMBO(c_cut, KC_NO),
    [CB_SALL] = COMBO(c_sall, KC_NO),
    [CB_PAREN]= COMBO(c_paren, KC_NO),
    [CB_BRACK]= COMBO(c_brack, KC_NO),
    [CB_BRACE]= COMBO(c_brace, KC_NO),
    [CB_ANGLE]= COMBO(c_angle, KC_NO),
    [CB_ARROW]= COMBO(c_arrow, KC_NO),
    [CB_DCOL] = COMBO(c_dcol, KC_NO),
    [CB_NEQ]  = COMBO(c_neq, KC_NO),
    [CB_EQEQ] = COMBO(c_eqeq, KC_NO),
    [CB_GE]   = COMBO(c_ge, KC_NO),
    [CB_LE]   = COMBO(c_le, KC_NO),
    [CB_AND]  = COMBO(c_and, KC_NO),
    [CB_OR]   = COMBO(c_or, KC_NO),
    [CB_BCOM] = COMBO(c_bcom, KC_NO),
    [CB_ECOM] = COMBO(c_ecom, KC_NO),
    [CB_INCL] = COMBO(c_incl, KC_NO),
    [CB_HOME] = COMBO(c_home, KC_NO),
    [CB_END]  = COMBO(c_end,  KC_NO),
    [CB_LEFT] = COMBO(c_left, KC_NO),
    [CB_RIGHT]= COMBO(c_rght, KC_NO),
    [CB_AUTOC]= COMBO(c_autoc, KC_NO),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;
    switch (combo_index) {
        case CB_TAB:   tap_code(KC_TAB);               pulse2(1,1,1,2); break;
        case CB_ESC:   tap_code(KC_ESC);               pulse2(0,0,1,0); break;
        case CB_ENT:   tap_code(KC_ENT);               pulse2(2,2,2,3); break;
        case CB_DEL:   tap_code(KC_DEL);               pulse2(3,2,3,3); break;
        case CB_CAPS:  tap_code(KC_CAPS);              pulse2(2,0,2,1); break;
        case CB_BSPC:  tap_code(KC_BSPC);              pulse2(1,2,1,3); break;
        case CB_K:     tap_code(KC_K);                 pulse2(2,1,2,5); break;
        case CB_J:     tap_code(KC_J);                 pulse2(2,4,3,4); break;
        case CB_Q:     tap_code(KC_Q);                 pulse2(2,5,1,5); break;
        case CB_X:     tap_code(KC_X);                 pulse2(2,3,3,3); break;
        case CB_V:     tap_code(KC_V);                 pulse2(2,1,2,2); break;
        case CB_Z:     tap_code(KC_Z);                 pulse2(2,4,1,4); break;
        case CB_UNDO:  tap_code16(LCTL(KC_Z));         pulse2(3,1,3,2); break;
        case CB_COPY:  tap_code16(LCTL(KC_C));         pulse2(3,3,3,4); break;
        case CB_PASTE: tap_code16(LCTL(KC_V));         pulse2(3,4,3,5); break;
        case CB_CUT:   tap_code16(LCTL(KC_X));         pulse2(3,2,3,4); break;
        case CB_SALL:  tap_code16(LCTL(KC_A));         pulse2(3,0,3,2); break;
        case CB_PAREN: SEND_STRING("()"SS_TAP(X_LEFT));pulse2(0,1,1,1); break;
        case CB_BRACK: SEND_STRING("[]"SS_TAP(X_LEFT));pulse2(0,2,1,2); break;
        case CB_BRACE: SEND_STRING("{}"SS_TAP(X_LEFT));pulse2(0,3,1,3); break;
        case CB_ANGLE: SEND_STRING("<>"SS_TAP(X_LEFT));pulse2(0,4,1,4); break;
        case CB_ARROW: SEND_STRING("->");               pulse2(1,1,2,1); break;
        case CB_DCOL:  SEND_STRING("::");               pulse2(2,0,2,2); break;
        case CB_NEQ:   SEND_STRING("!=");               pulse2(0,5,1,5); break;
        case CB_EQEQ:  SEND_STRING("==");               pulse2(2,1,2,3); break;
        case CB_GE:    SEND_STRING(">=");               pulse2(1,1,1,3); break;
        case CB_LE:    SEND_STRING("<=");               pulse2(1,2,1,4); break;
        case CB_AND:   SEND_STRING("&&");               pulse2(1,0,2,0); break;
        case CB_OR:    SEND_STRING("||");               pulse2(2,0,3,0); break;
        case CB_BCOM:  SEND_STRING("/*");               pulse2(1,0,1,1); break;
        case CB_ECOM:  SEND_STRING("*/");               pulse2(3,1,3,3); break;
        case CB_INCL:  SEND_STRING("#include ");        pulse2(3,0,3,5); break;
        case CB_HOME:  tap_code(KC_HOME);              pulse2(0,1,1,2); break;
        case CB_END:   tap_code(KC_END);               pulse2(0,4,1,5); break;
        case CB_LEFT:  tap_code(KC_LEFT);              pulse2(2,3,2,4); break;
        case CB_RIGHT: tap_code(KC_RGHT);              pulse2(2,2,2,5); break;
        case CB_AUTOC: tap_code16(LCTL(KC_SPC));         pulse2(2,0,2,5); break;
    }
}

// ─── SOCD ─────────────────────────────────────────────────────
typedef struct { uint16_t a,b; bool ad,bd; } socd_t;
static socd_t socd[3] = {
    {KC_W,KC_S,false,false},
    {KC_A,KC_D,false,false},
    {KC_Q,KC_E,false,false},
};
static bool socd_handle(uint16_t kc, bool pr) {
    for (uint8_t i=0; i<3; i++) {
        socd_t *p = &socd[i];
        if (kc==p->a) {
            if (pr) { if(p->bd) unregister_code(p->b); register_code(p->a); p->ad=true; }
            else    { unregister_code(p->a); p->ad=false; if(p->bd) register_code(p->b); }
            return false;
        }
        if (kc==p->b) {
            if (pr) { if(p->ad) unregister_code(p->a); register_code(p->b); p->bd=true; }
            else    { unregister_code(p->b); p->bd=false; if(p->ad) register_code(p->a); }
            return false;
        }
    }
    return true;
}

// ─── Chord detection ──────────────────────────────────────────
// CAT  chord: T0+T1+T2 (LCTL+LALT+LSFT) alone 500ms → _CAT on
// GAME chord: DOT + Y held simultaneously 500ms → _GAME on
static bool t0=false,t1=false,t2=false,t3=false,t4=false;
static bool dot_dn=false, y_dn=false;
static uint32_t cat_t=0, game_t=0;
static bool cat_arm=false, game_arm=false;

static void thumb_track(uint16_t kc, bool pr) {
    // Track thumb keys for cat chord
    switch(kc) {
        case KC_LCTL:           t0=pr; break;
        case KC_LALT:           t1=pr; break;
        case KC_LSFT:           t2=pr; break;
        case LT(_NUM,KC_SPC):   t3=pr; break;
        case LT(_SYM,KC_BSPC):  t4=pr; break;
        default: break;
    }
    // Track DOT and Y for game chord
    if (kc == KC_DOT) dot_dn = pr;
    if (kc == KC_Y)   y_dn   = pr;

    // CAT: T0+T1+T2, no other thumbs
    bool ctrio = t0&&t1&&t2&&!t3&&!t4;
    if (ctrio  && !cat_arm)  { cat_arm=true;  cat_t=timer_read32(); }
    else if (!ctrio)          cat_arm=false;

    // GAME: DOT+Y both held
    bool gpair = dot_dn && y_dn;
    if (gpair  && !game_arm) { game_arm=true; game_t=timer_read32(); }
    else if (!gpair)          game_arm=false;
}

static void chord_tick(void) {
    if (cat_arm  && timer_elapsed32(cat_t)  >= 500) {
        cat_arm=false; clear_mods(); layer_on(_CAT);
    }
    if (game_arm && timer_elapsed32(game_t) >= 500) {
        game_arm=false; layer_on(_GAME);
    }
}

// ─── Quad-tap LALT → toggle _WIN ──────────────────────────────
// Count 4 distinct LALT presses within a 900ms window → toggle layer.
// Same approach used by LSFT triple-tap for _NUMPAD.
static uint8_t  alt_taps   = 0;
static uint32_t alt_window = 0;
#define ALT_QUAD_WINDOW 900

static void alt_quad_track(bool pressed) {
    if (!pressed) return;  // count only on press
    uint32_t now = timer_read32();
    if (alt_taps == 0 || (now - alt_window) > ALT_QUAD_WINDOW) {
        alt_taps = 1;
        alt_window = now;
    } else {
        alt_taps++;
        if (alt_taps >= 4) {
            alt_taps = 0;
            clear_mods();
            layer_invert(_WIN);
        }
    }
}

// Quad-tap LCTL (T1) → toggle _GAME
static uint8_t  ctl_taps   = 0;
static uint32_t ctl_window = 0;
#define CTL_QUAD_WINDOW 900

static void ctl_quad_track(bool pressed) {
    if (!pressed) return;
    uint32_t now = timer_read32();
    if (ctl_taps == 0 || (now - ctl_window) > CTL_QUAD_WINDOW) {
        ctl_taps = 1;
        ctl_window = now;
    } else {
        ctl_taps++;
        if (ctl_taps >= 4) {
            ctl_taps = 0;
            clear_mods();
            layer_invert(_GAME);
        }
    }
}

// Quad-tap T5 (LT(_SYM, KC_BSPC)) → toggle _NUMPAD
static uint8_t  t5_taps   = 0;
static uint32_t t5_window = 0;
#define T5_QUAD_WINDOW 900

static void t5_quad_track(bool pressed) {
    if (!pressed) return;
    uint32_t now = timer_read32();
    if (t5_taps == 0 || (now - t5_window) > T5_QUAD_WINDOW) {
        t5_taps = 1;
        t5_window = now;
    } else {
        t5_taps++;
        if (t5_taps >= 4) {
            t5_taps = 0;
            clear_mods();
            layer_invert(_NUMPAD);
        }
    }
}

static void win_run_command(const char *cmd) {
    // Open Run dialog
    register_code(KC_LGUI);
    tap_code(KC_R);
    unregister_code(KC_LGUI);
    wait_ms(150);  // allow Run dialog to open
    // Type the command
    send_string(cmd);
    wait_ms(50);
    // Execute
    tap_code(KC_ENTER);
}

// Count distinct LSFT key-down events within a 500ms window
// 3 taps within window → toggle _NUMPAD layer

// ─── Encoder long-press ───────────────────────────────────────
static uint32_t enc_t = 0;

// ─── process_record_user ──────────────────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) == _GAME) {
        switch (keycode) {
            case KC_W: case KC_S: case KC_A:
            case KC_D: case KC_Q: case KC_E:
                return socd_handle(keycode, record->event.pressed);
        }
    }
    thumb_track(keycode, record->event.pressed);
    // Quad-tap detectors for special-layer toggles (900ms windows):
    //   LALT → _WIN    (T2)
    //   LCTL → _GAME   (T1)
    //   T5   → _NUMPAD (LT(_SYM, KC_BSPC) — counted only on press events)
    if (keycode == KC_LALT) {
        alt_quad_track(record->event.pressed);
    }
    if (keycode == KC_LCTL) {
        ctl_quad_track(record->event.pressed);
    }
    if (keycode == LT(_SYM, KC_BSPC)) {
        t5_quad_track(record->event.pressed);
    }
    switch (keycode) {
        case CK_ENC:
            if (record->event.pressed) {
                enc_t = timer_read32();
            } else {
                if (timer_elapsed32(enc_t) >= 500) {
                    if (layer_state_is(_CAT))    layer_off(_CAT);
                    if (layer_state_is(_GAME))   layer_off(_GAME);
                    if (layer_state_is(_NUMPAD)) layer_off(_NUMPAD);
                    if (layer_state_is(_WIN))    layer_off(_WIN);
                    if (!layer_state_is(_CAT) && !layer_state_is(_GAME) && !layer_state_is(_NUMPAD) && !layer_state_is(_WIN))
                        tap_code(KC_MUTE);
                } else {
                    tap_code(KC_MUTE);
                }
            }
            return false;
        case CK_GAMETOG:
            if (record->event.pressed) layer_invert(_GAME);
            return false;
        case CK_CATTOG:
            if (record->event.pressed) layer_invert(_CAT);
            return false;
        case CK_NUMPADTOG:
            if (record->event.pressed) {
                layer_off(_NUMPAD);
                clear_mods();
            }
            return false;

        // ═══ Windows layer toggle ═══
        case CK_WINTOG:
            if (record->event.pressed) {
                layer_off(_WIN);
                clear_mods();
            }
            return false;

        // ═══ MSC snap-ins (stock Windows 11) ═══
        case CK_W_COMPMGMT:  if (record->event.pressed) win_run_command("compmgmt.msc");  return false;
        case CK_W_SERVICES:  if (record->event.pressed) win_run_command("services.msc");  return false;
        case CK_W_DEVMGMT:   if (record->event.pressed) win_run_command("devmgmt.msc");   return false;
        case CK_W_DISKMGMT:  if (record->event.pressed) win_run_command("diskmgmt.msc");  return false;
        case CK_W_EVENTVWR:  if (record->event.pressed) win_run_command("eventvwr.msc");  return false;
        case CK_W_PERFMON:   if (record->event.pressed) win_run_command("perfmon.msc");   return false;
        case CK_W_TASKSCHD:  if (record->event.pressed) win_run_command("taskschd.msc");  return false;
        case CK_W_LUSRMGR:   if (record->event.pressed) win_run_command("lusrmgr.msc");   return false;
        case CK_W_GPEDIT:    if (record->event.pressed) win_run_command("gpedit.msc");    return false;
        case CK_W_SECPOL:    if (record->event.pressed) win_run_command("secpol.msc");    return false;
        case CK_W_WF:        if (record->event.pressed) win_run_command("wf.msc");        return false;
        case CK_W_WMIMGMT:   if (record->event.pressed) win_run_command("wmimgmt.msc");   return false;
        case CK_W_FSMGMT:    if (record->event.pressed) win_run_command("fsmgmt.msc");    return false;
        case CK_W_CERTMGR:   if (record->event.pressed) win_run_command("certmgr.msc");   return false;
        case CK_W_CERTLM:    if (record->event.pressed) win_run_command("certlm.msc");    return false;
        case CK_W_TPM:       if (record->event.pressed) win_run_command("tpm.msc");       return false;
        case CK_W_PRINTMGR:  if (record->event.pressed) win_run_command("printmanagement.msc"); return false;
        case CK_W_VIRTMGMT:  if (record->event.pressed) win_run_command("virtmgmt.msc");  return false;

        // ═══ Control Panel applets ═══
        case CK_W_APPWIZ:    if (record->event.pressed) win_run_command("appwiz.cpl");    return false;
        case CK_W_NCPA:      if (record->event.pressed) win_run_command("ncpa.cpl");      return false;
        case CK_W_MMSYS:     if (record->event.pressed) win_run_command("mmsys.cpl");     return false;
        case CK_W_MMSYSREC:  if (record->event.pressed) win_run_command("mmsys.cpl ,1");  return false;
        case CK_W_SYSDM:     if (record->event.pressed) win_run_command("sysdm.cpl");     return false;
        case CK_W_INETCPL:   if (record->event.pressed) win_run_command("inetcpl.cpl");   return false;
        case CK_W_POWERCFG:  if (record->event.pressed) win_run_command("powercfg.cpl");  return false;
        case CK_W_TIMEDATE:  if (record->event.pressed) win_run_command("timedate.cpl");  return false;
        case CK_W_NETPLWIZ:  if (record->event.pressed) win_run_command("netplwiz");      return false;

        // ═══ System utilities ═══
        case CK_W_OPTFEAT:   if (record->event.pressed) win_run_command("optionalfeatures"); return false;
        case CK_W_TASKMGR:   if (record->event.pressed) win_run_command("taskmgr");      return false;
        case CK_W_REGEDIT:   if (record->event.pressed) win_run_command("regedit");      return false;

        // ═══ Modern Settings URIs ═══
        case CK_W_SET_DISPLAY:  if (record->event.pressed) win_run_command("ms-settings:display");        return false;
        case CK_W_SET_BT:       if (record->event.pressed) win_run_command("ms-settings:bluetooth");      return false;
        case CK_W_SET_NET:      if (record->event.pressed) win_run_command("ms-settings:network-status"); return false;
        case CK_W_SET_UPDATE:   if (record->event.pressed) win_run_command("ms-settings:windowsupdate");  return false;
        case CK_W_SET_APPS:     if (record->event.pressed) win_run_command("ms-settings:appsfeatures");   return false;
        case CK_W_SET_DEFENDER: if (record->event.pressed) win_run_command("windowsdefender:");           return false;
        case CK_W_SET_SOUND:    if (record->event.pressed) win_run_command("ms-settings:sound");          return false;
        case CK_W_SET_ABOUT:    if (record->event.pressed) win_run_command("ms-settings:about");          return false;
        case CK_W_SET_DISKS:    if (record->event.pressed) win_run_command("ms-settings:disksandvolumes");return false;

        // ═══ RSAT domain admin (requires RSAT installed) ═══
        case CK_W_DSA:       if (record->event.pressed) win_run_command("dsa.msc");      return false;
        case CK_W_DSSITE:    if (record->event.pressed) win_run_command("dssite.msc");   return false;
        case CK_W_DOMAIN:    if (record->event.pressed) win_run_command("domain.msc");   return false;
        case CK_W_ADSIEDIT:  if (record->event.pressed) win_run_command("adsiedit.msc"); return false;
        case CK_W_GPMC:      if (record->event.pressed) win_run_command("gpmc.msc");     return false;
        case CK_W_DNSMGMT:   if (record->event.pressed) win_run_command("dnsmgmt.msc");  return false;
        case CK_W_DHCPMGMT:  if (record->event.pressed) win_run_command("dhcpmgmt.msc"); return false;
        case CK_W_DFSMGMT:   if (record->event.pressed) win_run_command("dfsmgmt.msc");  return false;
        case CK_W_RSOP:      if (record->event.pressed) win_run_command("rsop.msc");     return false;

        // ═══ Dev shells & CLI tools (all target pwsh 7) ═══
        case CK_W_PWSH:      if (record->event.pressed) win_run_command("pwsh");                                                return false;
        case CK_W_PWSH_ADMIN:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh");
                wait_ms(50);
                // Ctrl+Shift+Enter to elevate
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_ENTER);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
        case CK_W_VSCODE:    if (record->event.pressed) win_run_command("code");                                                return false;
        case CK_W_CLAUDE:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh -NoExit -Command \"claude\"");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
        case CK_W_CODEX:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh -NoExit -Command \"codex\"");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
        case CK_W_AWS:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh -NoExit -Command \"aws sts get-caller-identity\"");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
        case CK_W_AZ:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh -NoExit -Command \"az account show\"");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
        case CK_W_DOCTL:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh -NoExit -Command \"doctl account get\"");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
        case CK_W_GH:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh -NoExit -Command \"gh auth status\"");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
        case CK_W_SCOOP:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                send_string("pwsh -NoExit -Command \"scoop status\"");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
        case CK_W_SYNAPSE:
            // Synapse 4 has no Win+R short name — type full path
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code(KC_R);
                unregister_code(KC_LGUI);
                wait_ms(150);
                // Use SS_TAP for the quotes since shifted ' is "
                send_string("\"C:\\Program Files\\Razer\\RazerAppEngine\\RazerAppEngine.exe\" --url-params=apps=synapse");
                wait_ms(50);
                tap_code(KC_ENTER);
            }
            return false;
    }
    return true;
}

// ─── housekeeping ─────────────────────────────────────────────
void housekeeping_task_user(void) { chord_tick(); }

// ─── RGB ──────────────────────────────────────────────────────
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            // Dramatic red — deep saturated crimson gradient
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(0, 255, 220);
            rgb_matrix_set_speed_noeeprom(20);
            break;
        case _NUM:
            // Dramatic blue fading to white — cycle left/right gives sweep effect
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(170, 220, 230);
            rgb_matrix_set_speed_noeeprom(25);
            break;
        case _SYM:
            // Ice blue — cool cyan-white gradient, gentle speed
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(148, 120, 200);
            rgb_matrix_set_speed_noeeprom(15);
            break;
        case _NAV:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(85, 255, 200);
            rgb_matrix_set_speed_noeeprom(30);
            break;
        case _CFG:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(170, 255, 200);
            rgb_matrix_set_speed_noeeprom(30);
            break;
        case _CAT:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(213, 255, 200);
            rgb_matrix_set_speed_noeeprom(30);
            break;
        case _GAME:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(191, 255, 140);
            rgb_matrix_set_speed_noeeprom(30);
            break;
        case _NUMPAD:
            // Bright green-blue gradient — calculator/data-entry mode
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(110, 255, 240);
            rgb_matrix_set_speed_noeeprom(35);
            break;
        case _WIN:
            // Windows-blue gradient — admin power-user mode
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(153, 255, 220);
            rgb_matrix_set_speed_noeeprom(25);
            break;
        default:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
            rgb_matrix_sethsv_noeeprom(0, 255, 200);
            rgb_matrix_set_speed_noeeprom(30);
            break;
    }
    return state;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    if (layer == _CAT) {
        RGB v = hsv_to_rgb((HSV){213,255,200});
        for (uint8_t i=led_min; i<led_max; i++) {
            if (i<29) rgb_matrix_set_color(i, v.r, v.g, v.b);
            else      rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

    if (layer == _GAME) {
        RGB wasd = hsv_to_rgb((HSV){30, 255,180});
        RGB sur  = hsv_to_rgb((HSV){15, 255,160});
        RGB num  = hsv_to_rgb((HSV){140,30, 200});
        RGB t5c  = hsv_to_rgb((HSV){38, 30, 200});
        // WASD: W=r1c2, A=r2c1, S=r2c2, D=r2c3
        rgb_matrix_set_color(lut(1,2),wasd.r,wasd.g,wasd.b);
        rgb_matrix_set_color(lut(2,1),wasd.r,wasd.g,wasd.b);
        rgb_matrix_set_color(lut(2,2),wasd.r,wasd.g,wasd.b);
        rgb_matrix_set_color(lut(2,3),wasd.r,wasd.g,wasd.b);
        // Surrounds
        const uint8_t sg[][2]={{1,1},{1,3},{1,4},{2,4},{2,5},
                               {3,1},{3,2},{3,3},{3,4},{1,5},{3,5}};
        for (uint8_t i=0;i<11;i++)
            rgb_matrix_set_color(lut(sg[i][0],sg[i][1]),sur.r,sur.g,sur.b);
        // Number row
        for (uint8_t c=0;c<6;c++)
            rgb_matrix_set_color(lut(0,c),num.r,num.g,num.b);
        // Thumb T5
        rgb_matrix_set_color(lut(4,4),t5c.r,t5c.g,t5c.b);
    }

    // Combo pulse — magenta on BOTH combo keys, always last
    if (timer_read32() < pulse_until) {
        if (pulse_led1 != 255) rgb_matrix_set_color(pulse_led1, 255, 0, 255);
        if (pulse_led2 != 255) rgb_matrix_set_color(pulse_led2, 255, 0, 255);
    } else {
        pulse_led1 = 255;
        pulse_led2 = 255;
    }

    return false;
}

// ─── OLED ─────────────────────────────────────────────────────
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t r) { return OLED_ROTATION_270; }

static const char PROGMEM bmp_base[72]={
    0x00,0x00,0xFE,0x82,0x82,0x82,0xFE,0x00,0xFE,0x12,0x12,0x12,
    0xEC,0x00,0xFE,0x82,0x82,0x7C,0x00,0xFE,0x10,0x28,0x44,0x00,
    0x00,0x00,0xFF,0x81,0x81,0x81,0xFF,0x00,0xFF,0x00,0x00,0x00,
    0xFF,0x00,0xFF,0x81,0x81,0x7E,0x00,0xFF,0x00,0x00,0x00,0x00,
    0x00,0x00,0x3F,0x20,0x20,0x20,0x3F,0x00,0x3F,0x20,0x20,0x20,
    0x3F,0x00,0x3F,0x20,0x20,0x1F,0x00,0x3F,0x00,0x00,0x00,0x00,
};
static const char PROGMEM bmp_num[72]={
    0x00,0x08,0xF8,0x00,0xF0,0x08,0x08,0xF0,0x00,0xF0,0x88,0x88,
    0x70,0x00,0x18,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xFF,0x00,0x0F,0x08,0x08,0x0F,0x00,0x0F,0x08,0x08,
    0x0F,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x3F,0x00,0x38,0x20,0x20,0x3F,0x00,0x38,0x20,0x20,
    0x38,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,
};
static const char PROGMEM bmp_sym[72]={
    0x00,0x00,0xC0,0xE0,0x30,0x18,0x0C,0x06,0x06,0x0C,0x18,0x30,
    0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x03,0x07,0x0C,0x18,0x30,0x60,0x60,0x30,0x18,0x0C,
    0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
static const char PROGMEM bmp_nav[72]={
    0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xF8,0xF0,0xE0,0xC0,
    0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x01,0x03,0xFF,0x03,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
static const char PROGMEM bmp_cfg[72]={
    0x00,0x60,0x70,0x38,0x1C,0x0E,0x0E,0x1C,0x38,0x70,0x60,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x06,0x0E,0x1C,0x38,0x70,0x70,0x38,0x1C,0x0E,0x06,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
static const char PROGMEM bmp_cat[72]={
    0x00,0xC0,0xE0,0x70,0x38,0x38,0x18,0x18,0x18,0x18,0x18,0x18,
    0x38,0x38,0x70,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xFF,0xFF,0x00,0x00,0xC3,0xE7,0xE7,0xC3,0x00,0x00,0x18,
    0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x03,0x07,0x0E,0x1C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x1C,0x0E,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
static const char PROGMEM bmp_numpad[72]={
    // Page 0 (top 8 rows): outer border top + top row of buttons
    0xFF,0x81,0x81,0xFF,0x81,0x81,0xFF,0x81,
    0x81,0xFF,0x81,0x81,0xFF,0x81,0x81,0xFF,
    0x81,0x81,0xFF,0x81,0x81,0xFF,0xFF,0xFF,
    // Page 1 (middle 8 rows): button grid lines
    0xFF,0x81,0x81,0xFF,0x81,0x81,0xFF,0x81,
    0x81,0xFF,0x81,0x81,0xFF,0x81,0x81,0xFF,
    0x81,0x81,0xFF,0x81,0x81,0xFF,0xFF,0xFF,
    // Page 2 (bottom 8 rows): bottom button row + base
    0xFF,0x81,0x81,0xFF,0x81,0x81,0xFF,0x81,
    0x81,0xFF,0x81,0x81,0xFF,0x81,0x81,0xFF,
    0x81,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

static const char PROGMEM bmp_game[72]={
    0x00,0xF0,0xFC,0xFE,0xFF,0x0F,0x07,0x07,0x0F,0xFF,0xFE,0xFC,
    0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xFF,0xFF,0xFF,0xFF,0xE0,0xC0,0xC0,0xE0,0xFF,0xFF,0xFF,
    0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0F,0x3F,0x7F,0xFF,0xF0,0xE0,0xE0,0xF0,0xFF,0x7F,0x3F,
    0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

// ─── Windows flag bitmaps (3-frame waving animation) ──────────
// 24x24 pixels = 72 bytes (3 pages × 24 columns)
// Four-quadrant flag with wavy borders
static const char PROGMEM bmp_win_flag1[72] = {
    // Page 0 (top 8 rows)
    0x00,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x00,
    0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x00,0x00,
    0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x00,0x00,
    // Page 1 (middle 8 rows — dividing line at bit 0/4)
    0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x00,0xF0,
    0xF0,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x0F,
    0x0F,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,
    // Page 2 (bottom 8 rows)
    0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x00,0x7F,
    0x7F,0x7F,0x7F,0x7F,0x7F,0x00,0x00,0x7F,
    0x7F,0x7F,0x7F,0x7F,0x7F,0x00,0x00,0x00,
};
static const char PROGMEM bmp_win_flag2[72] = {
    // Same flag shifted slightly - simulates wave
    0x00,0xFC,0xFE,0xFE,0xFE,0xFC,0xFC,0x00,
    0xFC,0xFE,0xFE,0xFE,0xFC,0xFC,0x00,0x00,
    0xFC,0xFE,0xFE,0xFE,0xFC,0xFC,0x00,0x00,
    0x1F,0x0F,0x0F,0x0F,0x0F,0x1F,0x00,0xF8,
    0xF0,0xF0,0xF0,0xF0,0xF8,0x00,0x00,0x1F,
    0x0F,0x0F,0x0F,0x0F,0x1F,0x00,0x00,0x00,
    0x3F,0x7F,0x7F,0x7F,0x7F,0x3F,0x00,0x3F,
    0x7F,0x7F,0x7F,0x7F,0x3F,0x00,0x00,0x3F,
    0x7F,0x7F,0x7F,0x7F,0x3F,0x00,0x00,0x00,
};
static const char PROGMEM bmp_win_flag3[72] = {
    0x00,0xFE,0xFC,0xFC,0xFC,0xFE,0xFE,0x00,
    0xFE,0xFC,0xFC,0xFC,0xFE,0xFE,0x00,0x00,
    0xFE,0xFC,0xFC,0xFC,0xFE,0xFE,0x00,0x00,
    0x0F,0x1F,0x1F,0x1F,0x1F,0x0F,0x00,0xF0,
    0xF8,0xF8,0xF8,0xF8,0xF0,0x00,0x00,0x0F,
    0x1F,0x1F,0x1F,0x1F,0x0F,0x00,0x00,0x00,
    0x7F,0x3F,0x3F,0x3F,0x3F,0x7F,0x00,0x7F,
    0x3F,0x3F,0x3F,0x3F,0x7F,0x00,0x00,0x7F,
    0x3F,0x3F,0x3F,0x3F,0x7F,0x00,0x00,0x00,
};


// ─── Rotating torus — cheap-math 4D projection ────────────────
// Math budget per frame: all integer.
//   - 128-entry sin LUT (256 bytes)
//   - 96 vertices, parameterized as (u_idx, v_idx) into sin_lut
//   - Rotation: integer matrix mult with 8.8 fixed point
//   - Projection: simple perspective divide using int32
//   - Per-frame work: ~96 verts × ~30 ops = ~3000 ops, well under budget
static const int8_t PROGMEM sin_lut[128] = {
       0,    6,   12,   19,   25,   31,   37,   43,   49,   54,   60,   65,   71,   76,   81,   85,
      90,   94,   98,  102,  106,  109,  112,  115,  117,  120,  122,  123,  125,  126,  126,  127,
     127,  127,  126,  126,  125,  123,  122,  120,  117,  115,  112,  109,  106,  102,   98,   94,
      90,   85,   81,   76,   71,   65,   60,   54,   49,   43,   37,   31,   25,   19,   12,    6,
       0,   -6,  -12,  -19,  -25,  -31,  -37,  -43,  -49,  -54,  -60,  -65,  -71,  -76,  -81,  -85,
     -90,  -94,  -98, -102, -106, -109, -112, -115, -117, -120, -122, -123, -125, -126, -126, -127,
    -127, -127, -126, -126, -125, -123, -122, -120, -117, -115, -112, -109, -106, -102,  -98,  -94,
     -90,  -85,  -81,  -76,  -71,  -65,  -60,  -54,  -49,  -43,  -37,  -31,  -25,  -19,  -12,   -6,
};

// Inline sin/cos via LUT — index wraps every 128 (one full revolution)
static inline int16_t lut_sin(uint8_t i) { return (int16_t)(int8_t)pgm_read_byte(&sin_lut[i & 127]); }
static inline int16_t lut_cos(uint8_t i) { return lut_sin((uint8_t)(i + 32)); }

// 96 vertex parameter table: each entry is (u_idx, v_idx)
static const uint8_t PROGMEM torus_verts[96][2] = {
    {  0,  0}, {  0, 16}, {  0, 32}, {  0, 48}, {  0, 64}, {  0, 80}, {  0, 96}, {  0,112},
    { 10,  0}, { 10, 16}, { 10, 32}, { 10, 48}, { 10, 64}, { 10, 80}, { 10, 96}, { 10,112},
    { 21,  0}, { 21, 16}, { 21, 32}, { 21, 48}, { 21, 64}, { 21, 80}, { 21, 96}, { 21,112},
    { 32,  0}, { 32, 16}, { 32, 32}, { 32, 48}, { 32, 64}, { 32, 80}, { 32, 96}, { 32,112},
    { 42,  0}, { 42, 16}, { 42, 32}, { 42, 48}, { 42, 64}, { 42, 80}, { 42, 96}, { 42,112},
    { 53,  0}, { 53, 16}, { 53, 32}, { 53, 48}, { 53, 64}, { 53, 80}, { 53, 96}, { 53,112},
    { 64,  0}, { 64, 16}, { 64, 32}, { 64, 48}, { 64, 64}, { 64, 80}, { 64, 96}, { 64,112},
    { 74,  0}, { 74, 16}, { 74, 32}, { 74, 48}, { 74, 64}, { 74, 80}, { 74, 96}, { 74,112},
    { 85,  0}, { 85, 16}, { 85, 32}, { 85, 48}, { 85, 64}, { 85, 80}, { 85, 96}, { 85,112},
    { 96,  0}, { 96, 16}, { 96, 32}, { 96, 48}, { 96, 64}, { 96, 80}, { 96, 96}, { 96,112},
    {106,  0}, {106, 16}, {106, 32}, {106, 48}, {106, 64}, {106, 80}, {106, 96}, {106,112},
    {117,  0}, {117, 16}, {117, 32}, {117, 48}, {117, 64}, {117, 80}, {117, 96}, {117,112},
};
#define TORUS_VERT_COUNT 96
#define TORUS_MAJOR_R    40   // major radius (8.8 fixed = 40 = 0.156 in display units)
#define TORUS_MINOR_R    16   // minor radius

// Rotation angles — advance each frame for "4D-feel" multi-axis motion
static uint8_t torus_rot_x = 0;
static uint8_t torus_rot_y = 0;
static uint8_t torus_rot_z = 0;

// Render the torus into a 32×32 region at the top of the OLED.
// In OLED_ROTATION_270 the panel is 32 wide × 128 tall, so this fills
// the top 32 rows = top 25% of the screen.
//
// Algorithm:
//   For each vertex (u, v):
//     1. Compute 3D position on torus surface:
//          x = (R + r·cos(v)) · cos(u)
//          y = (R + r·cos(v)) · sin(u)
//          z = r·sin(v)
//     2. Rotate around X, Y, Z by torus_rot_*
//     3. Project to 2D with simple perspective divide
//     4. Plot pixel
//
// All math is integer. Coordinates are 8.8 fixed point internally,
// truncated to pixel coordinates at the end.
static void draw_torus(uint8_t origin_row) {
    uint8_t rx = torus_rot_x;
    uint8_t ry = torus_rot_y;
    uint8_t rz = torus_rot_z;

    int16_t cos_rx = lut_cos(rx), sin_rx = lut_sin(rx);
    int16_t cos_ry = lut_cos(ry), sin_ry = lut_sin(ry);
    int16_t cos_rz = lut_cos(rz), sin_rz = lut_sin(rz);

    for (uint8_t i = 0; i < TORUS_VERT_COUNT; i++) {
        uint8_t u_idx = pgm_read_byte(&torus_verts[i][0]);
        uint8_t v_idx = pgm_read_byte(&torus_verts[i][1]);

        // 1) Torus parametric position (values scaled to ~ ±56)
        int16_t cos_u = lut_cos(u_idx);
        int16_t sin_u = lut_sin(u_idx);
        int16_t cos_v = lut_cos(v_idx);
        int16_t sin_v = lut_sin(v_idx);

        // tube_x = (R + r·cos_v/127); tube_z = r·sin_v/127
        int16_t tube_x = TORUS_MAJOR_R + ((TORUS_MINOR_R * cos_v) >> 7);
        int16_t tube_z = (TORUS_MINOR_R * sin_v) >> 7;

        int16_t x = (tube_x * cos_u) >> 7;
        int16_t y = (tube_x * sin_u) >> 7;
        int16_t z = tube_z;

        // 2) Rotate around X
        int16_t y1 = ((y * cos_rx) - (z * sin_rx)) >> 7;
        int16_t z1 = ((y * sin_rx) + (z * cos_rx)) >> 7;
        int16_t x1 = x;
        // Rotate around Y
        int16_t x2 = ((x1 * cos_ry) + (z1 * sin_ry)) >> 7;
        int16_t z2 = ((-x1 * sin_ry) + (z1 * cos_ry)) >> 7;
        int16_t y2 = y1;
        // Rotate around Z
        int16_t x3 = ((x2 * cos_rz) - (y2 * sin_rz)) >> 7;
        int16_t y3 = ((x2 * sin_rz) + (y2 * cos_rz)) >> 7;
        int16_t z3 = z2;

        // 3) Perspective divide — fake 4D by varying viewer distance
        // viewer_dist = 80 + small wobble (this gives the "4D" feel)
        int16_t viewer_dist = 80 + (lut_sin((uint8_t)(rx + ry)) >> 3);
        int16_t denom = viewer_dist - z3;
        if (denom <= 8) denom = 8;   // safety: avoid div-by-near-zero

        int16_t px = ((int32_t)x3 * 32) / denom + 16;  // center at col 16
        int16_t py = ((int32_t)y3 * 32) / denom + 16;  // center at row 16 within 32-row region

        // 4) Plot if inside the 32×32 area
        if (px >= 0 && px < 32 && py >= 0 && py < 32) {
            oled_write_pixel((uint8_t)px, origin_row + (uint8_t)py, true);
        }
    }
}

// Tick rotation angles — irrational ratios keep the motion non-repeating
static void torus_tick(void) {
    torus_rot_x += 1;
    torus_rot_y += 2;
    torus_rot_z += 3;
}



// ─── Half-torus (SYM layer) ───────────────────────────────────
// Half of the major-axis revolution (the C-shape / U-shape arc) — 48 vertices.
// Rendered with 90° fixed rotation about Z so the cut faces the viewer,
// then animated with the same XYZ tumble + 4D-feel viewer wobble as the
// full torus on BASE.
//
// Reuses sin_lut and 8.8 fixed-point math from torus.

#define HALF_TORUS_VERT_COUNT 48
static const uint8_t PROGMEM half_torus_verts[HALF_TORUS_VERT_COUNT][2] = {
    {  0,  0}, {  0, 16}, {  0, 32}, {  0, 48},
    {  0, 64}, {  0, 80}, {  0, 96}, {  0,112},
    { 10,  0}, { 10, 16}, { 10, 32}, { 10, 48},
    { 10, 64}, { 10, 80}, { 10, 96}, { 10,112},
    { 21,  0}, { 21, 16}, { 21, 32}, { 21, 48},
    { 21, 64}, { 21, 80}, { 21, 96}, { 21,112},
    { 32,  0}, { 32, 16}, { 32, 32}, { 32, 48},
    { 32, 64}, { 32, 80}, { 32, 96}, { 32,112},
    { 42,  0}, { 42, 16}, { 42, 32}, { 42, 48},
    { 42, 64}, { 42, 80}, { 42, 96}, { 42,112},
    { 53,  0}, { 53, 16}, { 53, 32}, { 53, 48},
    { 53, 64}, { 53, 80}, { 53, 96}, { 53,112},
};

// Independent rotation angles so SYM and BASE animate separately
static uint8_t htorus_rot_x = 32;  // start offset for variety
static uint8_t htorus_rot_y = 16;
static uint8_t htorus_rot_z = 64;  // 64 = 180° = the 90° rotation baseline

static void draw_half_torus(uint8_t origin_row) {
    uint8_t rx = htorus_rot_x;
    uint8_t ry = htorus_rot_y;
    uint8_t rz = htorus_rot_z;  // includes the 90° "cut faces viewer" offset

    int16_t cos_rx = lut_cos(rx), sin_rx = lut_sin(rx);
    int16_t cos_ry = lut_cos(ry), sin_ry = lut_sin(ry);
    int16_t cos_rz = lut_cos(rz), sin_rz = lut_sin(rz);

    for (uint8_t i = 0; i < HALF_TORUS_VERT_COUNT; i++) {
        uint8_t u_idx = pgm_read_byte(&half_torus_verts[i][0]);
        uint8_t v_idx = pgm_read_byte(&half_torus_verts[i][1]);

        int16_t cos_u = lut_cos(u_idx);
        int16_t sin_u = lut_sin(u_idx);
        int16_t cos_v = lut_cos(v_idx);
        int16_t sin_v = lut_sin(v_idx);

        // Torus surface position
        int16_t tube_x = TORUS_MAJOR_R + ((TORUS_MINOR_R * cos_v) >> 7);
        int16_t tube_z = (TORUS_MINOR_R * sin_v) >> 7;

        int16_t x = (tube_x * cos_u) >> 7;
        int16_t y = (tube_x * sin_u) >> 7;
        int16_t z = tube_z;

        // Rotate around X
        int16_t y1 = ((y * cos_rx) - (z * sin_rx)) >> 7;
        int16_t z1 = ((y * sin_rx) + (z * cos_rx)) >> 7;
        int16_t x1 = x;
        // Rotate around Y
        int16_t x2 = ((x1 * cos_ry) + (z1 * sin_ry)) >> 7;
        int16_t z2 = ((-x1 * sin_ry) + (z1 * cos_ry)) >> 7;
        int16_t y2 = y1;
        // Rotate around Z (includes the fixed 90° baseline offset)
        int16_t x3 = ((x2 * cos_rz) - (y2 * sin_rz)) >> 7;
        int16_t y3 = ((x2 * sin_rz) + (y2 * cos_rz)) >> 7;
        int16_t z3 = z2;

        // 4D-feel viewer wobble
        int16_t viewer_dist = 80 + (lut_sin((uint8_t)(rx + ry)) >> 3);
        int16_t denom = viewer_dist - z3;
        if (denom <= 8) denom = 8;

        int16_t px = ((int32_t)x3 * 32) / denom + 16;
        int16_t py = ((int32_t)y3 * 32) / denom + 16;

        if (px >= 0 && px < 32 && py >= 0 && py < 32) {
            oled_write_pixel((uint8_t)px, origin_row + (uint8_t)py, true);
        }
    }
}

// Tick rotation angles — same coprime increments as full torus
static void htorus_tick(void) {
    htorus_rot_x += 1;
    htorus_rot_y += 2;
    htorus_rot_z += 3;
}

// Hand-drawn katakana glyphs (6x8 bitmap, column-major, LSB top)
// 24 characters, 144 bytes flash total — random selection per cell
#define KATAKANA_COUNT 24
static const uint8_t PROGMEM katakana_glyphs[24][6] = {
    {0x4F, 0x7E, 0x3A, 0x06, 0x06, 0x00},
    {0x40, 0x70, 0x1C, 0x07, 0x01, 0x00},
    {0x22, 0x12, 0x0B, 0x0A, 0x06, 0x00},
    {0x21, 0x21, 0x3F, 0x21, 0x21, 0x00},
    {0x32, 0x1A, 0x0F, 0x7A, 0x02, 0x00},
    {0x32, 0x1E, 0x07, 0x0A, 0x32, 0x02},
    {0x47, 0x62, 0x3F, 0x02, 0x03, 0x00},
    {0x41, 0x69, 0x1D, 0x0B, 0x09, 0x00},
    {0x38, 0x07, 0x00, 0x00, 0x07, 0x38},
    {0x21, 0x11, 0x79, 0x45, 0x03, 0x00},
    {0x12, 0x0F, 0x42, 0x3E, 0x02, 0x02},
    {0x09, 0x4D, 0x25, 0x1F, 0x01, 0x00},
    {0x23, 0x11, 0x09, 0x05, 0x03, 0x00},
    {0x01, 0x01, 0x22, 0x34, 0x18, 0x00},
    {0x61, 0x31, 0x19, 0x75, 0x03, 0x01},
    {0x42, 0x23, 0x1D, 0x0B, 0x08, 0x08},
    {0x21, 0x21, 0x21, 0x21, 0x3F, 0x00},
    {0x04, 0x82, 0x80, 0x48, 0x31, 0x00},
    {0x11, 0x09, 0x19, 0x35, 0x43, 0x00},
    {0x42, 0x47, 0x7A, 0x47, 0x42, 0x22},
    {0x22, 0x10, 0x0A, 0x05, 0x01, 0x00},
    {0x12, 0x1B, 0x4D, 0x3B, 0x08, 0x00},
    {0x04, 0x45, 0x3F, 0x15, 0x15, 0x14},
    {0x21, 0x12, 0x08, 0x07, 0x00, 0x3F},
};


// ─── 4D Tesseract (NAV layer) ────────────────────────────────
// 16 vertices, 32 edges. Rotated through 4D planes (XW, YW, ZW)
// in addition to standard 3D rotations, then projected to 2D.
// All integer math — uses the sin_lut already defined for the torus.
//
// Math budget per frame: 16 vert projections + 32 line draws ~= 5000 ops.
// Well under the 50ms QMK task budget on RP2040 @ 133MHz.

static const int8_t PROGMEM tess_verts[16][4] = {
    { -64, -64, -64, -64},
    {  64, -64, -64, -64},
    { -64,  64, -64, -64},
    {  64,  64, -64, -64},
    { -64, -64,  64, -64},
    {  64, -64,  64, -64},
    { -64,  64,  64, -64},
    {  64,  64,  64, -64},
    { -64, -64, -64,  64},
    {  64, -64, -64,  64},
    { -64,  64, -64,  64},
    {  64,  64, -64,  64},
    { -64, -64,  64,  64},
    {  64, -64,  64,  64},
    { -64,  64,  64,  64},
    {  64,  64,  64,  64},
};

static const uint8_t PROGMEM tess_edges[32][2] = {
    { 0, 1},
    { 0, 2},
    { 0, 4},
    { 0, 8},
    { 1, 3},
    { 1, 5},
    { 1, 9},
    { 2, 3},
    { 2, 6},
    { 2,10},
    { 3, 7},
    { 3,11},
    { 4, 5},
    { 4, 6},
    { 4,12},
    { 5, 7},
    { 5,13},
    { 6, 7},
    { 6,14},
    { 7,15},
    { 8, 9},
    { 8,10},
    { 8,12},
    { 9,11},
    { 9,13},
    {10,11},
    {10,14},
    {11,15},
    {12,13},
    {12,14},
    {13,15},
    {14,15},
};


// Rotation angles for 4D — six possible rotation planes in 4D:
// XY, XZ, XW, YZ, YW, ZW. We use four to keep things lively.
static uint8_t tess_rot_xy = 0;
static uint8_t tess_rot_xw = 0;
static uint8_t tess_rot_yz = 0;
static uint8_t tess_rot_zw = 0;

// Drawing area: 32×32 region at top of OLED (rows 0..31)
#define TESS_X_CENTER 16
#define TESS_Y_CENTER 16
#define TESS_DRAW_W 32
#define TESS_DRAW_H 32

// Bresenham line draw — clipped to draw region
static void tess_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    int16_t dx = x1 > x0 ? x1 - x0 : x0 - x1;
    int16_t dy = y1 > y0 ? y1 - y0 : y0 - y1;
    int16_t sx = x0 < x1 ? 1 : -1;
    int16_t sy = y0 < y1 ? 1 : -1;
    int16_t err = (dx > dy ? dx : -dy) / 2;
    int16_t e2;

    while (1) {
        if (x0 >= 0 && x0 < TESS_DRAW_W && y0 >= 0 && y0 < TESS_DRAW_H) {
            oled_write_pixel((uint8_t)x0, (uint8_t)y0, true);
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
}

// Project a single 4D vertex to 2D screen coordinates.
// Returns the 2D point; performs:
//   1. XW rotation in 4D (the "hypercube folding" effect)
//   2. ZW rotation in 4D
//   3. Project 4D->3D by perspective divide on W
//   4. XY/YZ rotation in 3D
//   5. Project 3D->2D by perspective divide on Z
static void tess_project(int8_t vx, int8_t vy, int8_t vz, int8_t vw,
                         int16_t *out_x, int16_t *out_y) {
    int16_t x = vx, y = vy, z = vz, w = vw;

    // ── 4D rotation in XW plane ──
    int16_t cos_xw = lut_cos(tess_rot_xw);
    int16_t sin_xw = lut_sin(tess_rot_xw);
    int16_t x1 = (x * cos_xw - w * sin_xw) >> 7;
    int16_t w1 = (x * sin_xw + w * cos_xw) >> 7;

    // ── 4D rotation in YW plane ──
    int16_t cos_yw = lut_cos(tess_rot_yz);  // reused for variety
    int16_t sin_yw = lut_sin(tess_rot_yz);
    int16_t y1 = (y * cos_yw - w1 * sin_yw) >> 7;
    int16_t w2 = (y * sin_yw + w1 * cos_yw) >> 7;

    // ── 4D rotation in ZW plane ──
    int16_t cos_zw = lut_cos(tess_rot_zw);
    int16_t sin_zw = lut_sin(tess_rot_zw);
    int16_t z1 = (z * cos_zw - w2 * sin_zw) >> 7;
    // w not needed past this point — discard

    // ── Project 4D -> 3D (perspective divide on collapsed W) ──
    // viewer_w_dist constant — adjust for "4D zoom"
    int16_t w_dist = 200;
    int16_t scale4d = w_dist - (w2 >> 2);  // small W influence on scale
    if (scale4d < 32) scale4d = 32;
    int16_t x3 = (int32_t)x1 * 96 / scale4d;
    int16_t y3 = (int32_t)y1 * 96 / scale4d;
    int16_t z3 = (int32_t)z1 * 96 / scale4d;

    // ── 3D rotation in XY plane (Z axis) ──
    int16_t cos_xy = lut_cos(tess_rot_xy);
    int16_t sin_xy = lut_sin(tess_rot_xy);
    int16_t x4 = (x3 * cos_xy - y3 * sin_xy) >> 7;
    int16_t y4 = (x3 * sin_xy + y3 * cos_xy) >> 7;
    int16_t z4 = z3;

    // ── Project 3D -> 2D (perspective divide on Z) ──
    int16_t cam_z = 96;
    int16_t denom = cam_z - z4;
    if (denom < 16) denom = 16;
    *out_x = (int32_t)x4 * 16 / denom + TESS_X_CENTER;
    *out_y = (int32_t)y4 * 16 / denom + TESS_Y_CENTER;
}

static void tess_draw(uint8_t origin_row) {
    // Clear region
    for (uint8_t r = origin_row; r < origin_row + TESS_DRAW_H; r++) {
        for (uint8_t c = 0; c < TESS_DRAW_W; c++) {
            oled_write_pixel(c, r, false);
        }
    }

    // Project all 16 vertices to screen coords
    int16_t sx[16], sy[16];
    for (uint8_t i = 0; i < 16; i++) {
        int8_t vx = pgm_read_byte(&tess_verts[i][0]);
        int8_t vy = pgm_read_byte(&tess_verts[i][1]);
        int8_t vz = pgm_read_byte(&tess_verts[i][2]);
        int8_t vw = pgm_read_byte(&tess_verts[i][3]);
        int16_t x, y;
        tess_project(vx, vy, vz, vw, &x, &y);
        sx[i] = x;
        sy[i] = y + origin_row;
    }

    // Draw all 32 edges
    for (uint8_t e = 0; e < 32; e++) {
        uint8_t a = pgm_read_byte(&tess_edges[e][0]);
        uint8_t b = pgm_read_byte(&tess_edges[e][1]);
        tess_draw_line(sx[a], sy[a], sx[b], sy[b]);
    }
}

// Tick all four rotation angles — different rates keep motion non-repeating
static void tess_tick(void) {
    tess_rot_xy += 1;
    tess_rot_xw += 2;
    tess_rot_yz += 1;
    tess_rot_zw += 3;
}


// ─── Matrix rain (NUM and CFG layers) ─────────────────────────
// OLED is 32 wide × 128 tall (rotation 270). At 6×8 font: 5 cols × 16 rows.
// Cadence: 60% faster than typical Matrix rain. Typical rain ticks every
// ~150ms; we tick every 60ms. Three column speed classes (slow/med/fast)
// give depth. State is tiny: 5 columns × {y position, speed class}.

#define MTRX_COLS 5
#define MTRX_ROWS 16    // we paint into top 8 rows (= 64 px top region)
#define MTRX_TOP_ROWS 8

typedef struct {
    uint8_t y;       // current head row (0..MTRX_ROWS-1)
    uint8_t speed;   // 1=slow, 2=medium, 3=fast — rows to advance per tick
    uint8_t tail;    // tail length for fade effect
} mtrx_col_t;

static mtrx_col_t mcols[MTRX_COLS];
static bool mtrx_inited = false;
static uint16_t mtrx_tick_ms = 0;
#define MTRX_TICK_MS 25

// Pseudo-random — xorshift8 (cheap, integer)
static uint8_t prng_state = 0xA3;
static inline uint8_t prng(void) {
    prng_state ^= prng_state << 3;
    prng_state ^= prng_state >> 5;
    prng_state ^= prng_state << 2;
    return prng_state;
}

static void mtrx_init(void) {
    for (uint8_t i = 0; i < MTRX_COLS; i++) {
        mcols[i].y = prng() & 0x0F;             // random start 0-15
        mcols[i].speed = 1 + (prng() % 3);      // 1, 2, or 3
        mcols[i].tail = 3 + (prng() & 0x03);    // 3-6 row tail
    }
    mtrx_inited = true;
}

static void mtrx_draw(void) {
    if (!mtrx_inited) mtrx_init();

    // Tick — only advance if enough ms passed
    mtrx_tick_ms++;
    if (mtrx_tick_ms < (MTRX_TICK_MS / 10)) {
        // Still draw frame but don't advance
    } else {
        mtrx_tick_ms = 0;
        for (uint8_t i = 0; i < MTRX_COLS; i++) {
            mcols[i].y += mcols[i].speed;
            if (mcols[i].y >= MTRX_TOP_ROWS) {
                // Reset column at top with new random params
                mcols[i].y = 0;
                mcols[i].speed = 1 + (prng() % 3);
                mcols[i].tail = 3 + (prng() & 0x03);
            }
        }
    }

    // Render: clear top region, then draw each column's head + tail
    // Top region = rows 0..7 of the 16-row text grid
    for (uint8_t r = 0; r < MTRX_TOP_ROWS; r++) {
        oled_set_cursor(0, r);
        oled_write_P(PSTR("     "), false);  // 5 blanks = clear row
    }
    for (uint8_t i = 0; i < MTRX_COLS; i++) {
        // Head: bright (inverted) digit at y position
        uint8_t y = mcols[i].y;
        if (y < MTRX_TOP_ROWS) {
            oled_set_cursor(i, y);
            char d = '0' + (prng() % 10);
            oled_write_char(d, true);  // inverted = "bright" head
        }
        // Tail: dimmer digits trailing behind
        for (uint8_t t = 1; t < mcols[i].tail; t++) {
            int8_t ty = (int8_t)y - t;
            if (ty < 0) break;
            oled_set_cursor(i, (uint8_t)ty);
            char d = '0' + (prng() % 10);
            oled_write_char(d, false);
        }
    }
}

// Draw a single katakana glyph at (text_col, text_row) — 6×8 pixels
// glyph_idx must be 0..KATAKANA_COUNT-1
// inverted: true = bright head, false = dim trail
static void draw_kata_glyph(uint8_t text_col, uint8_t text_row, uint8_t glyph_idx, bool inverted) {
    uint8_t px = text_col * 6;
    uint8_t py = text_row * 8;
    for (uint8_t c = 0; c < 6; c++) {
        uint8_t col_byte = pgm_read_byte(&katakana_glyphs[glyph_idx][c]);
        for (uint8_t r = 0; r < 8; r++) {
            bool on = (col_byte >> r) & 1;
            // For inverted (head) — flip on/off to get bright background
            if (inverted) on = !on;
            oled_write_pixel(px + c, py + r, on);
        }
    }
}

// Matrix rain with katakana characters (70% katakana / 30% digits)
// Used on the NUM layer. Same column-state engine as mtrx_draw.
static void mtrx_draw_kata(void) {
    if (!mtrx_inited) mtrx_init();

    mtrx_tick_ms++;
    if (mtrx_tick_ms >= (MTRX_TICK_MS / 10)) {
        mtrx_tick_ms = 0;
        for (uint8_t i = 0; i < MTRX_COLS; i++) {
            mcols[i].y += mcols[i].speed;
            if (mcols[i].y >= MTRX_TOP_ROWS) {
                mcols[i].y = 0;
                mcols[i].speed = 1 + (prng() % 3);
                mcols[i].tail = 3 + (prng() & 0x03);
            }
        }
    }

    // Clear rain region
    for (uint8_t r = 0; r < MTRX_TOP_ROWS; r++) {
        oled_set_cursor(0, r);
        oled_write_P(PSTR("     "), false);
    }

    // Render each column's head + tail
    for (uint8_t i = 0; i < MTRX_COLS; i++) {
        uint8_t y = mcols[i].y;
        if (y < MTRX_TOP_ROWS) {
            // 70% katakana, 30% digit
            uint8_t roll = prng();
            if ((roll % 10) < 7) {
                // Katakana head — inverted (bright background)
                uint8_t g = prng() % KATAKANA_COUNT;
                draw_kata_glyph(i, y, g, true);
            } else {
                oled_set_cursor(i, y);
                char d = '0' + (prng() % 10);
                oled_write_char(d, true);
            }
        }
        // Tail
        for (uint8_t t = 1; t < mcols[i].tail; t++) {
            int8_t ty = (int8_t)y - t;
            if (ty < 0) break;
            uint8_t roll = prng();
            if ((roll % 10) < 7) {
                uint8_t g = prng() % KATAKANA_COUNT;
                draw_kata_glyph(i, (uint8_t)ty, g, false);
            } else {
                oled_set_cursor(i, (uint8_t)ty);
                char d = '0' + (prng() % 10);
                oled_write_char(d, false);
            }
        }
    }
}



// ─── Doom-style shotgun (GAME layer) ──────────────────────────
// Hand-drawn 32×32 pixel art. 3-frame muzzle-flash loop.
// Stored as 128 bytes each (4 pages × 32 cols, page-stacked).
static const char PROGMEM bmp_doom_cool[128] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x2C, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x2C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x38, 0x38, 0x38, 0x38, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x20,
};

static const char PROGMEM bmp_doom_small[128] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x2E, 0x3E, 0x3F, 0x3F, 0x3F, 0x3F, 0x3E, 0x2E, 0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x2C, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x2C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x38, 0x38, 0x38, 0x38, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x20,
};

static const char PROGMEM bmp_doom_big[128] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E, 0x1E, 0xDF, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0xDF, 0x1E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x2C, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x2C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x38, 0x38, 0x38, 0x38, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x20,
};


// ─── WPM tier indicator (BASE layer only, bottom 30%) ─────────
// ≤25:    [ O ]
// 26-99:  [ Ø ]  (O with diagonal slash)
// ≥100:   [ ! ]  (30% larger exclamation, hand-drawn at 8×11)
//
// Brackets animate: each tick draws one more row from bottom upward,
// cycling every 4 frames (~80ms at 20ms tick).

static uint8_t wpm_bracket_frame = 0;

// Draw a left bracket at (x, top_row) — 8 rows tall, filled up to frame_height
static void draw_left_bracket(uint8_t x, uint8_t top_row, uint8_t frame_height) {
    // Vertical bar (rightmost column of bracket region)
    for (uint8_t r = 0; r < frame_height && r < 8; r++) {
        uint8_t row = top_row + 7 - r;  // grow from bottom
        oled_write_pixel(x, row, true);
    }
    // Top and bottom serifs — drawn only when grown enough
    if (frame_height >= 7) {
        oled_write_pixel(x + 1, top_row, true);
        oled_write_pixel(x + 2, top_row, true);
        oled_write_pixel(x + 1, top_row + 7, true);
        oled_write_pixel(x + 2, top_row + 7, true);
    }
}

static void draw_right_bracket(uint8_t x, uint8_t top_row, uint8_t frame_height) {
    for (uint8_t r = 0; r < frame_height && r < 8; r++) {
        uint8_t row = top_row + 7 - r;
        oled_write_pixel(x, row, true);
    }
    if (frame_height >= 7) {
        oled_write_pixel(x - 1, top_row, true);
        oled_write_pixel(x - 2, top_row, true);
        oled_write_pixel(x - 1, top_row + 7, true);
        oled_write_pixel(x - 2, top_row + 7, true);
    }
}

// Draw an O (just the standard 6x8 font char, centered)
static void draw_wpm_O(uint8_t pixel_x, uint8_t pixel_y) {
    // We'll use text mode for this — quicker
    oled_set_cursor(2, 14);  // middle column, bottom area
    oled_write_char('O', false);
}

// Draw an Ø — O with a diagonal slash
static void draw_wpm_O_slash(uint8_t pixel_x, uint8_t pixel_y) {
    oled_set_cursor(2, 14);
    oled_write_char('O', false);
    // Overlay diagonal slash pixels
    for (uint8_t i = 0; i < 8; i++) {
        oled_write_pixel(pixel_x + i, pixel_y + i, true);
    }
}

// Draw an 8x11 exclamation point (30% larger than default 6x8)
static void draw_wpm_bang(uint8_t pixel_x, uint8_t pixel_y) {
    // Vertical bar — 7 rows tall, 2 wide
    for (uint8_t r = 0; r < 7; r++) {
        oled_write_pixel(pixel_x + 3, pixel_y + r, true);
        oled_write_pixel(pixel_x + 4, pixel_y + r, true);
    }
    // Wider top of bar (taper)
    oled_write_pixel(pixel_x + 2, pixel_y + 0, true);
    oled_write_pixel(pixel_x + 5, pixel_y + 0, true);
    oled_write_pixel(pixel_x + 2, pixel_y + 1, true);
    oled_write_pixel(pixel_x + 5, pixel_y + 1, true);
    // Gap row at y+8
    // Dot at bottom (2x2)
    oled_write_pixel(pixel_x + 3, pixel_y + 9, true);
    oled_write_pixel(pixel_x + 4, pixel_y + 9, true);
    oled_write_pixel(pixel_x + 3, pixel_y + 10, true);
    oled_write_pixel(pixel_x + 4, pixel_y + 10, true);
}

// Render the WPM tier indicator at bottom of screen
static void draw_wpm_tier(void) {
    uint8_t wpm = 0;
#ifdef WPM_ENABLE
    wpm = get_current_wpm();
#endif
    // Choose tier
    uint8_t tier = 0;  // 0=O, 1=Ø, 2=!
    if (wpm >= 100)     tier = 2;
    else if (wpm > 25)  tier = 1;
    else                tier = 0;

    // Position: bottom area, pixel rows ~104-118 (oled rows 13-14 of 16)
    uint8_t pixel_y = 108;

    // Bracket grow animation — cycles 4 frames
    wpm_bracket_frame = (wpm_bracket_frame + 1) & 7;
    uint8_t grow = (wpm_bracket_frame >= 4) ? 8 : (wpm_bracket_frame * 2 + 2);

    draw_left_bracket(2, pixel_y, grow);
    draw_right_bracket(29, pixel_y, grow);

    // Center symbol — pixel-positioned
    switch (tier) {
        case 0: draw_wpm_O(12, pixel_y);       break;
        case 1: draw_wpm_O_slash(12, pixel_y); break;
        case 2: draw_wpm_bang(12, pixel_y);    break;
    }
}


// At 32 wide, ~5 chars, we have rows 0-15 to fill
// Draw via text: 0 character is built-in; overlay / via separate row offset
// ─── Windows flag waving animation + status display ──────────
// Used when _WIN layer is active. Layout:
//   Rows 0-2:  Waving Windows flag (24x24 bitmap, 3-frame loop)
//   Row 4:     "WIN" label
//   Row 6:     CAPS / NUM indicators
//   Row 8-9:   CTL / SFT / ALT / GUI mod indicators
//   Row 11-12: WPM display
static uint8_t win_frame = 0;
static uint16_t win_frame_count = 0;
#define WIN_FRAME_DURATION 30  // ~500ms per frame for slow wave

static void draw_win_display(void) {
    // Pick current flag frame for animation
    const char *flag;
    switch (win_frame) {
        case 0:  flag = bmp_win_flag1; break;
        case 1:  flag = bmp_win_flag2; break;
        default: flag = bmp_win_flag3; break;
    }
    // Draw flag in top 3 pages (24 rows)
    for (uint8_t p = 0; p < 3; p++) {
        oled_set_cursor(0, p);
        oled_write_raw_P(flag + p*24, 24);
    }
    // Layer label
    oled_set_cursor(0, 4);
    oled_write_P(PSTR("WIN  "), true);

    // Lock state indicators (CAPS / NUM)
    led_t leds = host_keyboard_led_state();
    oled_set_cursor(0, 6);
    oled_write_P(PSTR("CAPS "), leds.caps_lock);
    oled_set_cursor(0, 7);
    oled_write_P(PSTR("NUM  "), leds.num_lock);

    // Modifier indicators
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_set_cursor(0, 9);
    oled_write_P(PSTR("CTL "), (mods & MOD_MASK_CTRL)  ? true : false);
    oled_set_cursor(0, 10);
    oled_write_P(PSTR("ALT "), (mods & MOD_MASK_ALT)   ? true : false);
    oled_set_cursor(0, 11);
    oled_write_P(PSTR("SFT "), (mods & MOD_MASK_SHIFT) ? true : false);
    oled_set_cursor(0, 12);
    oled_write_P(PSTR("GUI "), (mods & MOD_MASK_GUI)   ? true : false);

#ifdef WPM_ENABLE
    // WPM at bottom
    char wpm_str[6];
    uint8_t wpm = get_current_wpm();
    snprintf(wpm_str, sizeof(wpm_str), "%3uwp", wpm);
    oled_set_cursor(0, 14);
    oled_write(wpm_str, false);
#endif
}

// Doom shotgun frame counter
static uint8_t  doom_frame = 0;
static uint16_t doom_frame_count = 0;
#define DOOM_FRAME_DURATION 12  // ~200ms per frame for cool-flash-flash cycle

// Status line: layer name + mods, drawn at row 8 (middle 20%)
static void draw_status_line(uint8_t layer) {
    oled_set_cursor(0, 8);
    switch (layer) {
        case _BASE:   oled_write_P(PSTR("BASE "), false); break;
        case _NUM:    oled_write_P(PSTR("NUM  "), false); break;
        case _SYM:    oled_write_P(PSTR("SYM  "), false); break;
        case _NAV:    oled_write_P(PSTR("NAV  "), false); break;
        case _CFG:    oled_write_P(PSTR("CFG  "), false); break;
        case _CAT:    oled_write_P(PSTR("CAT  "), true);  break;
        case _GAME:   oled_write_P(PSTR("GAME "), false); break;
        case _NUMPAD: oled_write_P(PSTR("NPAD "), true);  break;
        default:      oled_write_P(PSTR("---- "), false); break;
    }
    // Mods at row 10
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_set_cursor(0, 10);
    oled_write_P(PSTR("C"), (mods & MOD_MASK_CTRL)  ? true : false);
    oled_write_P(PSTR("A"), (mods & MOD_MASK_ALT)   ? true : false);
    oled_write_P(PSTR("S"), (mods & MOD_MASK_SHIFT) ? true : false);
    oled_write_P(PSTR("G"), (mods & MOD_MASK_GUI)   ? true : false);
}

bool oled_task_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    // ─── _WIN: Windows flag waving + status (unchanged) ─────
    if (layer == _WIN) {
        win_frame_count++;
        if (win_frame_count >= WIN_FRAME_DURATION) {
            win_frame_count = 0;
            win_frame = (win_frame + 1) % 3;
            oled_clear();
        }
        draw_win_display();
        return false;
    }

    // ─── _GAME: Doom-style shotgun firing on loop ───────────
    if (layer == _GAME) {
        doom_frame_count++;
        if (doom_frame_count >= DOOM_FRAME_DURATION) {
            doom_frame_count = 0;
            // Cycle: cool(4 ticks), small flash(1), big flash(1), small(1)
            doom_frame = (doom_frame + 1) % 8;
            oled_clear();
        }
        const char *frame;
        if      (doom_frame == 5) frame = bmp_doom_small;
        else if (doom_frame == 6) frame = bmp_doom_big;
        else if (doom_frame == 7) frame = bmp_doom_small;
        else                       frame = bmp_doom_cool;
        // Draw 32×32 = 4 pages at top
        for (uint8_t p = 0; p < 4; p++) {
            oled_set_cursor(0, p);
            oled_write_raw_P(frame + p*32, 32);
        }
        draw_status_line(layer);
        return false;
    }

    // ─── _BASE: Torus + status + WPM tier indicator ─────────
    if (layer == _BASE) {
        // Clear torus region only
        for (uint8_t row = 0; row < 32; row++) {
            for (uint8_t col = 0; col < 32; col++) {
                oled_write_pixel(col, row, false);
            }
        }
        draw_torus(0);
        torus_tick();

        // Status line in middle
        draw_status_line(layer);

#ifdef WPM_ENABLE
        // WPM number at row 12
        char wpm_buf[6];
        snprintf(wpm_buf, sizeof(wpm_buf), "%3uw", get_current_wpm());
        oled_set_cursor(0, 12);
        oled_write(wpm_buf, false);
#endif
        // Animated bracketed WPM tier at bottom
        // Clear bottom pixel region
        for (uint8_t row = 104; row < 128; row++) {
            for (uint8_t col = 0; col < 32; col++) {
                oled_write_pixel(col, row, false);
            }
        }
        draw_wpm_tier();
        return false;
    }

    // ─── _NUM: Matrix rain with KATAKANA + status ───────────
    if (layer == _NUM) {
        mtrx_draw_kata();
        draw_status_line(layer);
#ifdef WPM_ENABLE
        char wpm_buf[6];
        snprintf(wpm_buf, sizeof(wpm_buf), "%3uw", get_current_wpm());
        oled_set_cursor(0, 12);
        oled_write(wpm_buf, false);
#endif
        return false;
    }

    // ─── _CFG: Matrix rain with digits + status ─────────────
    if (layer == _CFG) {
        mtrx_draw();
        draw_status_line(layer);
#ifdef WPM_ENABLE
        char wpm_buf[6];
        snprintf(wpm_buf, sizeof(wpm_buf), "%3uw", get_current_wpm());
        oled_set_cursor(0, 12);
        oled_write(wpm_buf, false);
#endif
        return false;
    }

    // ─── _NAV: 4D tesseract + status ────────────────────────
    if (layer == _NAV) {
        tess_draw(0);
        tess_tick();
        draw_status_line(layer);
#ifdef WPM_ENABLE
        char wpm_buf[6];
        snprintf(wpm_buf, sizeof(wpm_buf), "%3uw", get_current_wpm());
        oled_set_cursor(0, 12);
        oled_write(wpm_buf, false);
#endif
        return false;
    }

    // ─── _SYM: Half-torus + status ──────────────────────────
    if (layer == _SYM) {
        // Clear top region (rows 0-31)
        for (uint8_t row = 0; row < 32; row++) {
            for (uint8_t col = 0; col < 32; col++) {
                oled_write_pixel(col, row, false);
            }
        }
        draw_half_torus(0);
        htorus_tick();
        draw_status_line(layer);
#ifdef WPM_ENABLE
        char wpm_buf[6];
        snprintf(wpm_buf, sizeof(wpm_buf), "%3uw", get_current_wpm());
        oled_set_cursor(0, 12);
        oled_write(wpm_buf, false);
#endif
        return false;
    }

    // ─── _CAT, _NUMPAD, fallback: status-only display ───────
    // No animation — just the layer name (large, inverted),
    // mods, and WPM. Used for layers where the OLED should be
    // minimal/quiet (CAT lockout, NUMPAD data entry).
    oled_set_cursor(0, 1);
    switch (layer) {
        case _CAT:    oled_write_P(PSTR(" CAT "), true);  break;
        case _NUMPAD: oled_write_P(PSTR("NPAD "), true);  break;
        default:      oled_write_P(PSTR(" ?   "), false); break;
    }
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("LAYER"), false);

    // Mods at row 6
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_set_cursor(0, 6);
    oled_write_P(PSTR("C"), (mods & MOD_MASK_CTRL)  ? true : false);
    oled_write_P(PSTR("A"), (mods & MOD_MASK_ALT)   ? true : false);
    oled_write_P(PSTR("S"), (mods & MOD_MASK_SHIFT) ? true : false);
    oled_write_P(PSTR("G"), (mods & MOD_MASK_GUI)   ? true : false);

    // Locks at row 8
    led_t leds = host_keyboard_led_state();
    oled_set_cursor(0, 8);
    oled_write_P(PSTR("CAPS "), leds.caps_lock);
    oled_set_cursor(0, 9);
    oled_write_P(PSTR("NUM  "), leds.num_lock);

#ifdef WPM_ENABLE
    char wpm_buf[6];
    snprintf(wpm_buf, sizeof(wpm_buf), "%3uw", get_current_wpm());
    oled_set_cursor(0, 12);
    oled_write(wpm_buf, false);
#endif
    return false;
}
#endif

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
    rgb_matrix_sethsv_noeeprom(0,255,200);
    rgb_matrix_set_speed_noeeprom(30);
}
