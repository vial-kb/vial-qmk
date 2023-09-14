enum combo_events{
MS_RBTN2_COMBO,
LS_COMBO,
COMMADOT_COMBO,
AS_COMBO,
QW_COMBO,
WE_COMBO,
OP_COMBO,
LQUOTE_COMBO,
FJ_COMBO,
REST_COMBO,
KL_COMBO,
ALTCTL_COMBO,
F1_COMBO,
F2_COMBO,
F3_COMBO,
F4_COMBO,
F5_COMBO,
F6_COMBO,
F7_COMBO,
F8_COMBO,
F9_COMBO,
G0_COMBO,
G1_COMBO,
G2_COMBO,
G3_COMBO,
G4_COMBO,
G5_COMBO,
G6_COMBO,
G7_COMBO,
G8_COMBO,
G9_COMBO,
JC_COMBO,
JX_COMBO,
JV_COMBO,
COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM ms_rbtn2_combo[] = {KC_MS_R,KC_BTN2,COMBO_END};
const uint16_t PROGMEM ls_combo[] = {KC_L,KC_S,COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {KC_COMMA,MT(MOD_RSFT,KC_DOT),COMBO_END};
const uint16_t PROGMEM as_combo[] = {LT(_NAV,KC_A),KC_S,COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q,KC_W,COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W,KC_E,COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O,KC_P,COMBO_END};
const uint16_t PROGMEM lquote_combo[] = {KC_L,KC_QUOT,COMBO_END};
const uint16_t PROGMEM fj_combo[] = {KC_F,KC_J,COMBO_END};
const uint16_t PROGMEM rest_combo[] = {KC_R,KC_E,KC_S,KC_T,COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K,KC_L,COMBO_END};
const uint16_t PROGMEM altctl_combo[] = {KC_RALT,KC_LCTL,COMBO_END};
const uint16_t PROGMEM f1_combo[] = {KC_F,KC_1,COMBO_END};
const uint16_t PROGMEM f2_combo[] = {KC_F,KC_2,COMBO_END};
const uint16_t PROGMEM f3_combo[] = {KC_F,KC_3,COMBO_END};
const uint16_t PROGMEM f4_combo[] = {KC_F,KC_4,COMBO_END};
const uint16_t PROGMEM f5_combo[] = {KC_F,KC_5,COMBO_END};
const uint16_t PROGMEM f6_combo[] = {KC_F,KC_6,COMBO_END};
const uint16_t PROGMEM f7_combo[] = {KC_F,KC_7,COMBO_END};
const uint16_t PROGMEM f8_combo[] = {KC_F,KC_8,COMBO_END};
const uint16_t PROGMEM f9_combo[] = {KC_F,KC_9,COMBO_END};
const uint16_t PROGMEM g0_combo[] = {KC_G,KC_0,COMBO_END};
const uint16_t PROGMEM g1_combo[] = {KC_G,KC_1,COMBO_END};
const uint16_t PROGMEM g2_combo[] = {KC_G,KC_2,COMBO_END};
const uint16_t PROGMEM g3_combo[] = {KC_G,KC_3,COMBO_END};
const uint16_t PROGMEM g4_combo[] = {KC_G,KC_4,COMBO_END};
const uint16_t PROGMEM g5_combo[] = {KC_G,KC_5,COMBO_END};
const uint16_t PROGMEM g6_combo[] = {KC_G,KC_6,COMBO_END};
const uint16_t PROGMEM g7_combo[] = {KC_G,KC_7,COMBO_END};
const uint16_t PROGMEM g8_combo[] = {KC_G,KC_8,COMBO_END};
const uint16_t PROGMEM g9_combo[] = {KC_G,KC_9,COMBO_END};
const uint16_t PROGMEM jc_combo[] = {KC_J,KC_C,COMBO_END};
const uint16_t PROGMEM jx_combo[] = {KC_J,KC_X,COMBO_END};
const uint16_t PROGMEM jv_combo[] = {KC_J,KC_V,COMBO_END};
combo_t key_combos[] = {
[MS_RBTN2_COMBO] = COMBO_ACTION(ms_rbtn2_combo),
[LS_COMBO] = COMBO_ACTION(ls_combo),
[COMMADOT_COMBO] = COMBO_ACTION(commadot_combo),
[AS_COMBO] = COMBO_ACTION(as_combo),
[QW_COMBO] = COMBO_ACTION(qw_combo),
[WE_COMBO] = COMBO_ACTION(we_combo),
[OP_COMBO] = COMBO_ACTION(op_combo),
[LQUOTE_COMBO] = COMBO_ACTION(lquote_combo),
[FJ_COMBO] = COMBO_ACTION(fj_combo),
[REST_COMBO] = COMBO_ACTION(rest_combo),
[KL_COMBO] = COMBO_ACTION(kl_combo),
[ALTCTL_COMBO] = COMBO_ACTION(altctl_combo),
[F1_COMBO] = COMBO_ACTION(f1_combo),
[F2_COMBO] = COMBO_ACTION(f2_combo),
[F3_COMBO] = COMBO_ACTION(f3_combo),
[F4_COMBO] = COMBO_ACTION(f4_combo),
[F5_COMBO] = COMBO_ACTION(f5_combo),
[F6_COMBO] = COMBO_ACTION(f6_combo),
[F7_COMBO] = COMBO_ACTION(f7_combo),
[F8_COMBO] = COMBO_ACTION(f8_combo),
[F9_COMBO] = COMBO_ACTION(f9_combo),
[G0_COMBO] = COMBO_ACTION(g0_combo),
[G1_COMBO] = COMBO_ACTION(g1_combo),
[G2_COMBO] = COMBO_ACTION(g2_combo),
[G3_COMBO] = COMBO_ACTION(g3_combo),
[G4_COMBO] = COMBO_ACTION(g4_combo),
[G5_COMBO] = COMBO_ACTION(g5_combo),
[G6_COMBO] = COMBO_ACTION(g6_combo),
[G7_COMBO] = COMBO_ACTION(g7_combo),
[G8_COMBO] = COMBO_ACTION(g8_combo),
[G9_COMBO] = COMBO_ACTION(g9_combo),
[JC_COMBO] = COMBO_ACTION(jc_combo),
[JX_COMBO] = COMBO_ACTION(jx_combo),
[JV_COMBO] = COMBO_ACTION(jv_combo),
};
void process_combo_event(uint16_t combo_index, bool pressed) {
switch(combo_index) {
case MS_RBTN2_COMBO:
if (pressed) {layer_move(_BASE);}
break;
case LS_COMBO:
if (pressed) {layer_move(_MOU);}
break;
case COMMADOT_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_SLSH));}
break;
case AS_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_TAB));}
break;
case QW_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_ESC));}
break;
case WE_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_GRV));}
break;
case OP_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_BSPC));}
break;
case LQUOTE_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_ENT));}
break;
case FJ_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_BSLS));}
break;
case REST_COMBO:
if (pressed) {reset_keyboard();}
break;
case KL_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_DEL));}
break;
case ALTCTL_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_LGUI));}
break;
case F1_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F1));}
break;
case F2_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F2));}
break;
case F3_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F3));}
break;
case F4_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F4));}
break;
case F5_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F5));}
break;
case F6_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F6));}
break;
case F7_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F7));}
break;
case F8_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F8));}
break;
case F9_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F9));}
break;
case G0_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F10));}
break;
case G1_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F11));}
break;
case G2_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F12));}
break;
case G3_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F13));}
break;
case G4_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F14));}
break;
case G5_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F15));}
break;
case G6_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F16));}
break;
case G7_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F17));}
break;
case G8_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F18));}
break;
case G9_COMBO:
if (pressed) {SEND_STRING(SS_TAP(X_F19));}
break;
case JC_COMBO:
if (pressed) {SEND_STRING(SS_LCTL("c"));}
break;
case JX_COMBO:
if (pressed) {SEND_STRING(SS_LCTL("x"));}
break;
case JV_COMBO:
if (pressed) {SEND_STRING(SS_LCTL("v"));}
break;
}
}