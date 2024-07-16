#pragma once

#include "quantum.h"
#include "via.h"

/*
 * This should contain all keycodes from keycodes_vX.py
 * so that situations like https://github.com/qmk/qmk_firmware/issues/11157 don't happen
 */

#define C_S(kc) C(S(kc))
#define LCG_T(kc)  MT(MOD_LCTL | MOD_LGUI, kc)
#define RCG_T(kc)  MT(MOD_RCTL | MOD_RGUI, kc)
#define LCG(kc) C(G(kc))
#define RCG(kc) RCTL(RGUI(kc))

#define KC_BSPACE KC_BACKSPACE
#define KC_NUMLOCK KC_NUM_LOCK
#define KC_PSCREEN KC_PRINT_SCREEN
#define KC_SCROLLLOCK KC_SCROLL_LOCK
#define KC_PGDOWN KC_PAGE_DOWN
#define KC_LBRACKET KC_LEFT_BRACKET
#define KC_RBRACKET KC_RIGHT_BRACKET
#define KC_BSLASH KC_BACKSLASH
#define KC_SCOLON KC_SEMICOLON
#define KC_CAPSLOCK KC_CAPS_LOCK
#define KC_LCTRL KC_LEFT_CTRL
#define KC_LSHIFT KC_LEFT_SHIFT
#define KC_RCTRL KC_RIGHT_CTRL
#define KC_RSHIFT KC_RIGHT_SHIFT
#define KC_NONUS_BSLASH KC_NONUS_BACKSLASH
#define KC_RO KC_INTERNATIONAL_1
#define KC_KANA KC_INTERNATIONAL_2
#define KC_JYEN KC_INTERNATIONAL_3
#define KC_HENK KC_INTERNATIONAL_4
#define KC_MHEN KC_INTERNATIONAL_5
#define KC_LANG1 KC_LANGUAGE_1
#define KC_LANG2 KC_LANGUAGE_2
#define KC_GESC QK_GRAVE_ESCAPE
#define KC_LSPO QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN
#define KC_RSPC QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE
#define KC_LCPO QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN
#define KC_RCPC QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE
#define KC_LAPO QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN
#define KC_RAPC QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE
#define KC_SFTENT QK_SPACE_CADET_RIGHT_SHIFT_ENTER
#define AU_TOG QK_AUDIO_TOGGLE
#define CLICKY_TOGGLE QK_AUDIO_CLICKY_TOGGLE
#define CLICKY_UP QK_AUDIO_CLICKY_UP
#define CLICKY_DOWN QK_AUDIO_CLICKY_DOWN
#define CLICKY_RESET QK_AUDIO_CLICKY_RESET
#define MU_TOG QK_MUSIC_TOGGLE
#define MU_MOD QK_MUSIC_MODE_NEXT
#define HPT_ON QK_HAPTIC_ON
#define HPT_OFF QK_HAPTIC_OFF
#define HPT_TOG QK_HAPTIC_TOGGLE
#define HPT_RST QK_HAPTIC_RESET
#define HPT_FBK QK_HAPTIC_FEEDBACK_TOGGLE
#define HPT_BUZ QK_HAPTIC_BUZZ_TOGGLE
#define HPT_MODI QK_HAPTIC_MODE_NEXT
#define HPT_MODD QK_HAPTIC_MODE_PREVIOUS
#define HPT_CONT QK_HAPTIC_CONTINUOUS_TOGGLE
#define HPT_CONI QK_HAPTIC_CONTINUOUS_UP
#define HPT_COND QK_HAPTIC_CONTINUOUS_DOWN
#define HPT_DWLI QK_HAPTIC_DWELL_UP
#define HPT_DWLD QK_HAPTIC_DWELL_DOWN
#define KC_ASDN QK_AUTO_SHIFT_DOWN
#define KC_ASUP QK_AUTO_SHIFT_UP
#define KC_ASRP QK_AUTO_SHIFT_REPORT
#define KC_ASON QK_AUTO_SHIFT_ON
#define KC_ASOFF QK_AUTO_SHIFT_OFF
#define KC_ASTG QK_AUTO_SHIFT_TOGGLE
#define CMB_ON QK_COMBO_ON
#define CMB_OFF QK_COMBO_OFF
#define CMB_TOG QK_COMBO_TOGGLE
#define BL_INC QK_BACKLIGHT_UP
#define BL_DEC QK_BACKLIGHT_DOWN
#define KC__VOLDOWN KC_KB_VOLUME_DOWN
#define KC__VOLUP KC_KB_VOLUME_UP
#define DYN_REC_START1 QK_DYNAMIC_MACRO_RECORD_START_1
#define DYN_REC_START2 QK_DYNAMIC_MACRO_RECORD_START_2
#define DYN_REC_STOP QK_DYNAMIC_MACRO_RECORD_STOP
#define DYN_MACRO_PLAY1 QK_DYNAMIC_MACRO_PLAY_1
#define DYN_MACRO_PLAY2 QK_DYNAMIC_MACRO_PLAY_2
#define MI_C_1 QK_MIDI_NOTE_C_1
#define MI_Cs_1 QK_MIDI_NOTE_C_SHARP_1
#define MI_Db_1 QK_MIDI_NOTE_C_SHARP_1
#define MI_D_1 QK_MIDI_NOTE_D_1
#define MI_Ds_1 QK_MIDI_NOTE_D_SHARP_1
#define MI_Eb_1 QK_MIDI_NOTE_D_SHARP_1
#define MI_E_1 QK_MIDI_NOTE_E_1
#define MI_F_1 QK_MIDI_NOTE_F_1
#define MI_Fs_1 QK_MIDI_NOTE_F_SHARP_1
#define MI_Gb_1 QK_MIDI_NOTE_F_SHARP_1
#define MI_G_1 QK_MIDI_NOTE_G_1
#define MI_Gs_1 QK_MIDI_NOTE_G_SHARP_1
#define MI_Ab_1 QK_MIDI_NOTE_G_SHARP_1
#define MI_A_1 QK_MIDI_NOTE_A_1
#define MI_As_1 QK_MIDI_NOTE_A_SHARP_1
#define MI_Bb_1 QK_MIDI_NOTE_A_SHARP_1
#define MI_B_1 QK_MIDI_NOTE_B_1
#define MI_C_2 QK_MIDI_NOTE_C_2
#define MI_Cs_2 QK_MIDI_NOTE_C_SHARP_2
#define MI_Db_2 QK_MIDI_NOTE_C_SHARP_2
#define MI_D_2 QK_MIDI_NOTE_D_2
#define MI_Ds_2 QK_MIDI_NOTE_D_SHARP_2
#define MI_Eb_2 QK_MIDI_NOTE_D_SHARP_2
#define MI_E_2 QK_MIDI_NOTE_E_2
#define MI_F_2 QK_MIDI_NOTE_F_2
#define MI_Fs_2 QK_MIDI_NOTE_F_SHARP_2
#define MI_Gb_2 QK_MIDI_NOTE_F_SHARP_2
#define MI_G_2 QK_MIDI_NOTE_G_2
#define MI_Gs_2 QK_MIDI_NOTE_G_SHARP_2
#define MI_Ab_2 QK_MIDI_NOTE_G_SHARP_2
#define MI_A_2 QK_MIDI_NOTE_A_2
#define MI_As_2 QK_MIDI_NOTE_A_SHARP_2
#define MI_Bb_2 QK_MIDI_NOTE_A_SHARP_2
#define MI_B_2 QK_MIDI_NOTE_B_2
#define MI_C_3 QK_MIDI_NOTE_C_3
#define MI_Cs_3 QK_MIDI_NOTE_C_SHARP_3
#define MI_Db_3 QK_MIDI_NOTE_C_SHARP_3
#define MI_D_3 QK_MIDI_NOTE_D_3
#define MI_Ds_3 QK_MIDI_NOTE_D_SHARP_3
#define MI_Eb_3 QK_MIDI_NOTE_D_SHARP_3
#define MI_E_3 QK_MIDI_NOTE_E_3
#define MI_F_3 QK_MIDI_NOTE_F_3
#define MI_Fs_3 QK_MIDI_NOTE_F_SHARP_3
#define MI_Gb_3 QK_MIDI_NOTE_F_SHARP_3
#define MI_G_3 QK_MIDI_NOTE_G_3
#define MI_Gs_3 QK_MIDI_NOTE_G_SHARP_3
#define MI_Ab_3 QK_MIDI_NOTE_G_SHARP_3
#define MI_A_3 QK_MIDI_NOTE_A_3
#define MI_As_3 QK_MIDI_NOTE_A_SHARP_3
#define MI_Bb_3 QK_MIDI_NOTE_A_SHARP_3
#define MI_B_3 QK_MIDI_NOTE_B_3
#define MI_C_4 QK_MIDI_NOTE_C_4
#define MI_Cs_4 QK_MIDI_NOTE_C_SHARP_4
#define MI_Db_4 QK_MIDI_NOTE_C_SHARP_4
#define MI_D_4 QK_MIDI_NOTE_D_4
#define MI_Ds_4 QK_MIDI_NOTE_D_SHARP_4
#define MI_Eb_4 QK_MIDI_NOTE_D_SHARP_4
#define MI_E_4 QK_MIDI_NOTE_E_4
#define MI_F_4 QK_MIDI_NOTE_F_4
#define MI_Fs_4 QK_MIDI_NOTE_F_SHARP_4
#define MI_Gb_4 QK_MIDI_NOTE_F_SHARP_4
#define MI_G_4 QK_MIDI_NOTE_G_4
#define MI_Gs_4 QK_MIDI_NOTE_G_SHARP_4
#define MI_Ab_4 QK_MIDI_NOTE_G_SHARP_4
#define MI_A_4 QK_MIDI_NOTE_A_4
#define MI_As_4 QK_MIDI_NOTE_A_SHARP_4
#define MI_Bb_4 QK_MIDI_NOTE_A_SHARP_4
#define MI_B_4 QK_MIDI_NOTE_B_4
#define MI_C_5 QK_MIDI_NOTE_C_5
#define MI_Cs_5 QK_MIDI_NOTE_C_SHARP_5
#define MI_Db_5 QK_MIDI_NOTE_C_SHARP_5
#define MI_D_5 QK_MIDI_NOTE_D_5
#define MI_Ds_5 QK_MIDI_NOTE_D_SHARP_5
#define MI_Eb_5 QK_MIDI_NOTE_D_SHARP_5
#define MI_E_5 QK_MIDI_NOTE_E_5
#define MI_F_5 QK_MIDI_NOTE_F_5
#define MI_Fs_5 QK_MIDI_NOTE_F_SHARP_5
#define MI_Gb_5 QK_MIDI_NOTE_F_SHARP_5
#define MI_G_5 QK_MIDI_NOTE_G_5
#define MI_Gs_5 QK_MIDI_NOTE_G_SHARP_5
#define MI_Ab_5 QK_MIDI_NOTE_G_SHARP_5
#define MI_A_5 QK_MIDI_NOTE_A_5
#define MI_As_5 QK_MIDI_NOTE_A_SHARP_5
#define MI_Bb_5 QK_MIDI_NOTE_A_SHARP_5
#define MI_B_5 QK_MIDI_NOTE_B_5
#define MI_OCT_N2 QK_MIDI_OCTAVE_N2
#define MI_OCT_N1 QK_MIDI_OCTAVE_N1
#define MI_OCT_0 QK_MIDI_OCTAVE_0
#define MI_OCT_1 QK_MIDI_OCTAVE_1
#define MI_OCT_2 QK_MIDI_OCTAVE_2
#define MI_OCT_3 QK_MIDI_OCTAVE_3
#define MI_OCT_4 QK_MIDI_OCTAVE_4
#define MI_OCT_5 QK_MIDI_OCTAVE_5
#define MI_OCT_6 QK_MIDI_OCTAVE_6
#define MI_OCT_7 QK_MIDI_OCTAVE_7
#define MI_ALLOFF QK_MIDI_ALL_NOTES_OFF
#define MI_TRNS_N6 QK_MIDI_TRANSPOSE_N6
#define MI_TRNS_N5 QK_MIDI_TRANSPOSE_N5
#define MI_TRNS_N4 QK_MIDI_TRANSPOSE_N4
#define MI_TRNS_N3 QK_MIDI_TRANSPOSE_N3
#define MI_TRNS_N2 QK_MIDI_TRANSPOSE_N2
#define MI_TRNS_N1 QK_MIDI_TRANSPOSE_N1
#define MI_TRNS_0 QK_MIDI_TRANSPOSE_0
#define MI_TRNS_1 QK_MIDI_TRANSPOSE_1
#define MI_TRNS_2 QK_MIDI_TRANSPOSE_2
#define MI_TRNS_3 QK_MIDI_TRANSPOSE_3
#define MI_TRNS_4 QK_MIDI_TRANSPOSE_4
#define MI_TRNS_5 QK_MIDI_TRANSPOSE_5
#define MI_TRNS_6 QK_MIDI_TRANSPOSE_6
#define MI_TRNSD QK_MIDI_TRANSPOSE_DOWN
#define MI_TRNSU QK_MIDI_TRANSPOSE_UP
#define MI_VEL_0 QK_MIDI_VELOCITY_0
#define MI_VEL_1 QK_MIDI_VELOCITY_1
#define MI_VEL_2 QK_MIDI_VELOCITY_2
#define MI_VEL_3 QK_MIDI_VELOCITY_3
#define MI_VEL_4 QK_MIDI_VELOCITY_4
#define MI_VEL_5 QK_MIDI_VELOCITY_5
#define MI_VEL_6 QK_MIDI_VELOCITY_6
#define MI_VEL_7 QK_MIDI_VELOCITY_7
#define MI_VEL_8 QK_MIDI_VELOCITY_8
#define MI_VEL_9 QK_MIDI_VELOCITY_9
#define MI_VEL_10 QK_MIDI_VELOCITY_10
#define MI_CHD QK_MIDI_CHANNEL_DOWN
#define MI_CHU QK_MIDI_CHANNEL_UP
#define MI_SUS MI_SUST
#define MI_MODSD QK_MIDI_MODULATION_SPEED_DOWN
#define MI_MODSU QK_MIDI_MODULATION_SPEED_UP
#define MI_BENDD QK_MIDI_PITCH_BEND_DOWN
#define MI_BENDU QK_MIDI_PITCH_BEND_UP
#define RESET QK_BOOT
#define FN_MO13 TL_LOWR
#define FN_MO23 TL_UPPR

#define MAGIC_SWAP_CONTROL_CAPSLOCK      QK_MAGIC_SWAP_CONTROL_CAPS_LOCK
#define MAGIC_UNSWAP_CONTROL_CAPSLOCK    QK_MAGIC_UNSWAP_CONTROL_CAPS_LOCK
#define MAGIC_TOGGLE_CONTROL_CAPSLOCK    QK_MAGIC_TOGGLE_CONTROL_CAPS_LOCK
#define MAGIC_UNCAPSLOCK_TO_CONTROL      QK_MAGIC_CAPS_LOCK_AS_CONTROL_OFF
#define MAGIC_CAPSLOCK_TO_CONTROL        QK_MAGIC_CAPS_LOCK_AS_CONTROL_ON
#define MAGIC_SWAP_LALT_LGUI             QK_MAGIC_SWAP_LALT_LGUI
#define MAGIC_UNSWAP_LALT_LGUI           QK_MAGIC_UNSWAP_LALT_LGUI
#define MAGIC_SWAP_RALT_RGUI             QK_MAGIC_SWAP_RALT_RGUI
#define MAGIC_UNSWAP_RALT_RGUI           QK_MAGIC_UNSWAP_RALT_RGUI
#define MAGIC_UNNO_GUI                   QK_MAGIC_GUI_ON
#define MAGIC_NO_GUI                     QK_MAGIC_GUI_OFF
#define MAGIC_TOGGLE_GUI                 QK_MAGIC_TOGGLE_GUI
#define MAGIC_SWAP_GRAVE_ESC             QK_MAGIC_SWAP_GRAVE_ESC
#define MAGIC_UNSWAP_GRAVE_ESC           QK_MAGIC_UNSWAP_GRAVE_ESC
#define MAGIC_SWAP_BACKSLASH_BACKSPACE   QK_MAGIC_SWAP_BACKSLASH_BACKSPACE
#define MAGIC_UNSWAP_BACKSLASH_BACKSPACE QK_MAGIC_UNSWAP_BACKSLASH_BACKSPACE
#define MAGIC_TOGGLE_BACKSLASH_BACKSPACE QK_MAGIC_TOGGLE_BACKSLASH_BACKSPACE
#define MAGIC_HOST_NKRO                  QK_MAGIC_NKRO_ON
#define MAGIC_UNHOST_NKRO                QK_MAGIC_NKRO_OFF
#define MAGIC_TOGGLE_NKRO                QK_MAGIC_TOGGLE_NKRO
#define MAGIC_SWAP_ALT_GUI               QK_MAGIC_SWAP_ALT_GUI
#define MAGIC_UNSWAP_ALT_GUI             QK_MAGIC_UNSWAP_ALT_GUI
#define MAGIC_TOGGLE_ALT_GUI             QK_MAGIC_TOGGLE_ALT_GUI
#define MAGIC_SWAP_LCTL_LGUI             QK_MAGIC_SWAP_LCTL_LGUI
#define MAGIC_UNSWAP_LCTL_LGUI           QK_MAGIC_UNSWAP_LCTL_LGUI
#define MAGIC_SWAP_RCTL_RGUI             QK_MAGIC_SWAP_RCTL_RGUI
#define MAGIC_UNSWAP_RCTL_RGUI           QK_MAGIC_UNSWAP_RCTL_RGUI
#define MAGIC_SWAP_CTL_GUI               QK_MAGIC_SWAP_CTL_GUI
#define MAGIC_UNSWAP_CTL_GUI             QK_MAGIC_UNSWAP_CTL_GUI
#define MAGIC_TOGGLE_CTL_GUI             QK_MAGIC_TOGGLE_CTL_GUI
#define MAGIC_EE_HANDS_LEFT              QK_MAGIC_EE_HANDS_LEFT
#define MAGIC_EE_HANDS_RIGHT             QK_MAGIC_EE_HANDS_RIGHT
#define MAGIC_SWAP_ESCAPE_CAPSLOCK       QK_MAGIC_SWAP_ESCAPE_CAPS_LOCK
#define MAGIC_UNSWAP_ESCAPE_CAPSLOCK     QK_MAGIC_UNSWAP_ESCAPE_CAPS_LOCK
#define MAGIC_TOGGLE_ESCAPE_CAPSLOCK     QK_MAGIC_TOGGLE_ESCAPE_CAPS_LOCK

#define kc 0






_Static_assert(QK_LAYER_TAP == 0x4000, "");
_Static_assert(MOD_LCTL == 0x01, "");
_Static_assert(MOD_LSFT == 0x02, "");
_Static_assert(MOD_LALT == 0x04, "");
_Static_assert(MOD_LGUI == 0x08, "");
_Static_assert(MOD_RCTL == 0x11, "");
_Static_assert(MOD_RSFT == 0x12, "");
_Static_assert(MOD_RALT == 0x14, "");
_Static_assert(MOD_RGUI == 0x18, "");
_Static_assert(MOD_HYPR == 0xF, "");
_Static_assert(MOD_MEH == 0x7, "");
_Static_assert(QK_TO == 0x5200, "");
_Static_assert(QK_MOMENTARY == 0x5220, "");
_Static_assert(QK_DEF_LAYER == 0x5240, "");
_Static_assert(QK_TOGGLE_LAYER == 0x5260, "");
_Static_assert(QK_ONE_SHOT_LAYER == 0x5280, "");
_Static_assert(QK_ONE_SHOT_MOD == 0x52A0, "");
_Static_assert(QK_TAP_DANCE == 0x5700, "");
_Static_assert(QK_LAYER_TAP_TOGGLE == 0x52C0, "");
_Static_assert(QK_LAYER_MOD == 0x5000, "");
_Static_assert(QK_MOD_TAP == 0x2000, "");
_Static_assert(ON_PRESS == 1, "");
_Static_assert(QK_LCTL == 0x0100, "");
_Static_assert(QK_LSFT == 0x0200, "");
_Static_assert(QK_LALT == 0x0400, "");
_Static_assert(QK_LGUI == 0x0800, "");
_Static_assert(QK_RCTL == 0x1100, "");
_Static_assert(QK_RSFT == 0x1200, "");
_Static_assert(QK_RALT == 0x1400, "");
_Static_assert(QK_RGUI == 0x1800, "");
_Static_assert(QK_MACRO == 0x7700, "");

_Static_assert(ALL_T(kc) == 0x2f00, "");
_Static_assert(C_S_T(kc) == 0x2300, "");
_Static_assert(C_S(kc) == 0x300, "");
_Static_assert(HYPR(kc) == 0xf00, "");
_Static_assert(LALT_T(kc) == 0x2400, "");
_Static_assert(LALT(kc) == 0x400, "");
_Static_assert(LCA_T(kc) == 0x2500, "");
_Static_assert(LCA(kc) == 0x500, "");
_Static_assert(LCAG_T(kc) == 0x2d00, "");
_Static_assert(LCAG(kc) == 0xd00, "");
_Static_assert(LCG_T(kc) == 0x2900, "");
_Static_assert(LCG(kc) == 0x900, "");
_Static_assert(LCTL_T(kc) == 0x2100, "");
_Static_assert(LCTL(kc) == 0x100, "");
_Static_assert(LGUI_T(kc) == 0x2800, "");
_Static_assert(LGUI(kc) == 0x800, "");
_Static_assert(LSA_T(kc) == 0x2600, "");
_Static_assert(LSA(kc) == 0x600, "");
_Static_assert(LSFT_T(kc) == 0x2200, "");
_Static_assert(LSFT(kc) == 0x200, "");
_Static_assert(MEH_T(kc) == 0x2700, "");
_Static_assert(MEH(kc) == 0x700, "");
_Static_assert(RALT_T(kc) == 0x3400, "");
_Static_assert(RALT(kc) == 0x1400, "");
_Static_assert(RCAG_T(kc) == 0x3d00, "");
_Static_assert(RCG_T(kc) == 0x3900, "");
_Static_assert(RCG(kc) == 0x1900, "");
_Static_assert(RCTL_T(kc) == 0x3100, "");
_Static_assert(RCTL(kc) == 0x1100, "");
_Static_assert(RGUI_T(kc) == 0x3800, "");
_Static_assert(RGUI(kc) == 0x1800, "");
_Static_assert(RSFT_T(kc) == 0x3200, "");
_Static_assert(RSFT(kc) == 0x1200, "");
_Static_assert(SGUI_T(kc) == 0x2a00, "");
_Static_assert(SGUI(kc) == 0xa00, "");

_Static_assert(OSM(MOD_LSFT) == 0x52A2, "");
_Static_assert(OSM(MOD_LCTL) == 0x52A1, "");
_Static_assert(OSM(MOD_LALT) == 0x52A4, "");
_Static_assert(OSM(MOD_LGUI) == 0x52A8, "");
_Static_assert(OSM(MOD_RSFT) == 0x52B2, "");
_Static_assert(OSM(MOD_RCTL) == 0x52B1, "");
_Static_assert(OSM(MOD_RALT) == 0x52B4, "");
_Static_assert(OSM(MOD_RGUI) == 0x52B8, "");
_Static_assert(OSM(MOD_LCTL|MOD_LSFT) == 0x52A3, "");
_Static_assert(OSM(MOD_LCTL|MOD_LALT) == 0x52A5, "");
_Static_assert(OSM(MOD_LCTL|MOD_LGUI) == 0x52A9, "");
_Static_assert(OSM(MOD_LSFT|MOD_LALT) == 0x52A6, "");
_Static_assert(OSM(MOD_LSFT|MOD_LGUI) == 0x52AA, "");
_Static_assert(OSM(MOD_LALT|MOD_LGUI) == 0x52AC, "");
_Static_assert(OSM(MOD_LCTL|MOD_LSFT|MOD_LGUI) == 0x52AB, "");
_Static_assert(OSM(MOD_LCTL|MOD_LALT|MOD_LGUI) == 0x52AD, "");
_Static_assert(OSM(MOD_LSFT|MOD_LALT|MOD_LGUI) == 0x52AE, "");
_Static_assert(OSM(MOD_MEH) == 0x52A7, "");
_Static_assert(OSM(MOD_HYPR) == 0x52AF, "");

_Static_assert(LT(1, KC_A) == 0x4104, "");
_Static_assert(TO(1) == 0x5201, "");
_Static_assert(MO(1) == 0x5221, "");
_Static_assert(DF(1) == 0x5241, "");
_Static_assert(TG(1) == 0x5261, "");
_Static_assert(OSL(1) == 0x5281, "");
_Static_assert(LM(1, KC_A) == 0x5024, "");
_Static_assert(OSM(MOD_RSFT) == 0x52B2, "");
_Static_assert(TT(1) == 0x52C1, "");
_Static_assert(MT(MOD_RSFT, KC_A) == 0x3204, "");
_Static_assert(TD(1) == 0x5701, "");

_Static_assert(KC_NO == 0x00, "");
_Static_assert(KC_TRNS == 0x01, "");
_Static_assert(KC_NUMLOCK == 0x53, "");
_Static_assert(KC_KP_SLASH == 0x54, "");
_Static_assert(KC_KP_ASTERISK == 0x55, "");
_Static_assert(KC_KP_MINUS == 0x56, "");
_Static_assert(KC_KP_PLUS == 0x57, "");
_Static_assert(KC_KP_ENTER == 0x58, "");
_Static_assert(KC_KP_1 == 0x59, "");
_Static_assert(KC_KP_2 == 0x5A, "");
_Static_assert(KC_KP_3 == 0x5B, "");
_Static_assert(KC_KP_4 == 0x5C, "");
_Static_assert(KC_KP_5 == 0x5D, "");
_Static_assert(KC_KP_6 == 0x5E, "");
_Static_assert(KC_KP_7 == 0x5F, "");
_Static_assert(KC_KP_8 == 0x60, "");
_Static_assert(KC_KP_9 == 0x61, "");
_Static_assert(KC_KP_0 == 0x62, "");
_Static_assert(KC_KP_DOT == 0x63, "");
_Static_assert(KC_KP_EQUAL == 0x67, "");
_Static_assert(KC_KP_COMMA == 0x85, "");
_Static_assert(KC_PSCREEN == 0x46, "");
_Static_assert(KC_SCROLLLOCK == 0x47, "");
_Static_assert(KC_PAUSE == 0x48, "");
_Static_assert(KC_INSERT == 0x49, "");
_Static_assert(KC_HOME == 0x4A, "");
_Static_assert(KC_PGUP == 0x4B, "");
_Static_assert(KC_DELETE == 0x4C, "");
_Static_assert(KC_END == 0x4D, "");
_Static_assert(KC_PGDOWN == 0x4E, "");
_Static_assert(KC_RIGHT == 0x4F, "");
_Static_assert(KC_LEFT == 0x50, "");
_Static_assert(KC_DOWN == 0x51, "");
_Static_assert(KC_UP == 0x52, "");
_Static_assert(KC_A == 0x04, "");
_Static_assert(KC_B == 0x05, "");
_Static_assert(KC_C == 0x06, "");
_Static_assert(KC_D == 0x07, "");
_Static_assert(KC_E == 0x08, "");
_Static_assert(KC_F == 0x09, "");
_Static_assert(KC_G == 0x0A, "");
_Static_assert(KC_H == 0x0B, "");
_Static_assert(KC_I == 0x0C, "");
_Static_assert(KC_J == 0x0D, "");
_Static_assert(KC_K == 0x0E, "");
_Static_assert(KC_L == 0x0F, "");
_Static_assert(KC_M == 0x10, "");
_Static_assert(KC_N == 0x11, "");
_Static_assert(KC_O == 0x12, "");
_Static_assert(KC_P == 0x13, "");
_Static_assert(KC_Q == 0x14, "");
_Static_assert(KC_R == 0x15, "");
_Static_assert(KC_S == 0x16, "");
_Static_assert(KC_T == 0x17, "");
_Static_assert(KC_U == 0x18, "");
_Static_assert(KC_V == 0x19, "");
_Static_assert(KC_W == 0x1A, "");
_Static_assert(KC_X == 0x1B, "");
_Static_assert(KC_Y == 0x1C, "");
_Static_assert(KC_Z == 0x1D, "");
_Static_assert(KC_1 == 0x1E, "");
_Static_assert(KC_2 == 0x1F, "");
_Static_assert(KC_3 == 0x20, "");
_Static_assert(KC_4 == 0x21, "");
_Static_assert(KC_5 == 0x22, "");
_Static_assert(KC_6 == 0x23, "");
_Static_assert(KC_7 == 0x24, "");
_Static_assert(KC_8 == 0x25, "");
_Static_assert(KC_9 == 0x26, "");
_Static_assert(KC_0 == 0x27, "");
_Static_assert(KC_ENTER == 0x28, "");
_Static_assert(KC_ESCAPE == 0x29, "");
_Static_assert(KC_BSPACE == 0x2A, "");
_Static_assert(KC_TAB == 0x2B, "");
_Static_assert(KC_SPACE == 0x2C, "");
_Static_assert(KC_MINUS == 0x2D, "");
_Static_assert(KC_EQUAL == 0x2E, "");
_Static_assert(KC_LBRACKET == 0x2F, "");
_Static_assert(KC_RBRACKET == 0x30, "");
_Static_assert(KC_BSLASH == 0x31, "");
_Static_assert(KC_SCOLON == 0x33, "");
_Static_assert(KC_QUOTE == 0x34, "");
_Static_assert(KC_GRAVE == 0x35, "");
_Static_assert(KC_COMMA == 0x36, "");
_Static_assert(KC_DOT == 0x37, "");
_Static_assert(KC_SLASH == 0x38, "");
_Static_assert(KC_CAPSLOCK == 0x39, "");
_Static_assert(KC_F1 == 0x3A, "");
_Static_assert(KC_F2 == 0x3B, "");
_Static_assert(KC_F3 == 0x3C, "");
_Static_assert(KC_F4 == 0x3D, "");
_Static_assert(KC_F5 == 0x3E, "");
_Static_assert(KC_F6 == 0x3F, "");
_Static_assert(KC_F7 == 0x40, "");
_Static_assert(KC_F8 == 0x41, "");
_Static_assert(KC_F9 == 0x42, "");
_Static_assert(KC_F10 == 0x43, "");
_Static_assert(KC_F11 == 0x44, "");
_Static_assert(KC_F12 == 0x45, "");
_Static_assert(KC_APPLICATION == 0x65, "");
_Static_assert(KC_LCTRL == 0xE0, "");
_Static_assert(KC_LSHIFT == 0xE1, "");
_Static_assert(KC_LALT == 0xE2, "");
_Static_assert(KC_LGUI == 0xE3, "");
_Static_assert(KC_RCTRL == 0xE4, "");
_Static_assert(KC_RSHIFT == 0xE5, "");
_Static_assert(KC_RALT == 0xE6, "");
_Static_assert(KC_RGUI == 0xE7, "");
_Static_assert(KC_TILD == 0x235, "");
_Static_assert(KC_EXLM == 0x21E, "");
_Static_assert(KC_AT == 0x21F, "");
_Static_assert(KC_HASH == 0x220, "");
_Static_assert(KC_DLR == 0x221, "");
_Static_assert(KC_PERC == 0x222, "");
_Static_assert(KC_CIRC == 0x223, "");
_Static_assert(KC_AMPR == 0x224, "");
_Static_assert(KC_ASTR == 0x225, "");
_Static_assert(KC_LPRN == 0x226, "");
_Static_assert(KC_RPRN == 0x227, "");
_Static_assert(KC_UNDS == 0x22D, "");
_Static_assert(KC_PLUS == 0x22E, "");
_Static_assert(KC_LCBR == 0x22F, "");
_Static_assert(KC_RCBR == 0x230, "");
_Static_assert(KC_LT == 0x236, "");
_Static_assert(KC_GT == 0x237, "");
_Static_assert(KC_COLN == 0x233, "");
_Static_assert(KC_PIPE == 0x231, "");
_Static_assert(KC_QUES == 0x238, "");
_Static_assert(KC_DQUO == 0x234, "");
_Static_assert(KC_NONUS_HASH == 0x32, "");
_Static_assert(KC_NONUS_BSLASH == 0x64, "");
_Static_assert(KC_RO == 0x87, "");
_Static_assert(KC_KANA == 0x88, "");
_Static_assert(KC_JYEN == 0x89, "");
_Static_assert(KC_HENK == 0x8A, "");
_Static_assert(KC_MHEN == 0x8B, "");
_Static_assert(KC_LANG1 == 0x90, "");
_Static_assert(KC_LANG2 == 0x91, "");
_Static_assert(KC_GESC == 0x7C16, "");
_Static_assert(KC_LSPO == 0x7C1A, "");
_Static_assert(KC_RSPC == 0x7C1B, "");
_Static_assert(KC_LCPO == 0x7C18, "");
_Static_assert(KC_RCPC == 0x7C19, "");
_Static_assert(KC_LAPO == 0x7C1C, "");
_Static_assert(KC_RAPC == 0x7C1D, "");
_Static_assert(KC_SFTENT == 0x7C1E, "");
_Static_assert(MAGIC_SWAP_CONTROL_CAPSLOCK == 0x7000, "");
_Static_assert(MAGIC_UNSWAP_CONTROL_CAPSLOCK == 0x7001, "");
_Static_assert(MAGIC_CAPSLOCK_TO_CONTROL == 0x7004, "");
_Static_assert(MAGIC_UNCAPSLOCK_TO_CONTROL == 0x7003, "");
_Static_assert(MAGIC_SWAP_LCTL_LGUI == 0x7017, "");
_Static_assert(MAGIC_UNSWAP_LCTL_LGUI == 0x7018, "");
_Static_assert(MAGIC_SWAP_RCTL_RGUI == 0x7019, "");
_Static_assert(MAGIC_UNSWAP_RCTL_RGUI == 0x701A, "");
_Static_assert(MAGIC_SWAP_CTL_GUI == 0x701B, "");
_Static_assert(MAGIC_UNSWAP_CTL_GUI == 0x701C, "");
_Static_assert(MAGIC_TOGGLE_CTL_GUI == 0x701D, "");
_Static_assert(MAGIC_SWAP_LALT_LGUI == 0x7005, "");
_Static_assert(MAGIC_UNSWAP_LALT_LGUI == 0x7006, "");
_Static_assert(MAGIC_SWAP_RALT_RGUI == 0x7007, "");
_Static_assert(MAGIC_UNSWAP_RALT_RGUI == 0x7008, "");
_Static_assert(MAGIC_SWAP_ALT_GUI == 0x7014, "");
_Static_assert(MAGIC_UNSWAP_ALT_GUI == 0x7015, "");
_Static_assert(MAGIC_TOGGLE_ALT_GUI == 0x7016, "");
_Static_assert(MAGIC_NO_GUI == 0x700A, "");
_Static_assert(MAGIC_UNNO_GUI == 0x7009, "");
_Static_assert(MAGIC_SWAP_GRAVE_ESC == 0x700C, "");
_Static_assert(MAGIC_UNSWAP_GRAVE_ESC == 0x700D, "");
_Static_assert(MAGIC_SWAP_BACKSLASH_BACKSPACE == 0x700E, "");
_Static_assert(MAGIC_UNSWAP_BACKSLASH_BACKSPACE == 0x700F, "");
_Static_assert(MAGIC_HOST_NKRO == 0x7011, "");
_Static_assert(MAGIC_UNHOST_NKRO == 0x7012, "");
_Static_assert(MAGIC_TOGGLE_NKRO == 0x7013, "");
_Static_assert(MAGIC_EE_HANDS_LEFT == 0x701E, "");
_Static_assert(MAGIC_EE_HANDS_RIGHT == 0x701F, "");
_Static_assert(AU_ON == 0x7480, "");
_Static_assert(AU_OFF == 0x7481, "");
_Static_assert(AU_TOG == 0x7482, "");
_Static_assert(CLICKY_TOGGLE == 0x748A, "");
_Static_assert(CLICKY_UP == 0x748D, "");
_Static_assert(CLICKY_DOWN == 0x748E, "");
_Static_assert(CLICKY_RESET == 0x748F, "");
_Static_assert(MU_ON == 0x7490, "");
_Static_assert(MU_OFF == 0x7491, "");
_Static_assert(MU_TOG == 0x7492, "");
_Static_assert(MU_MOD == 0x7493, "");
_Static_assert(HPT_ON == 0x7C40, "");
_Static_assert(HPT_OFF == 0x7C41, "");
_Static_assert(HPT_TOG == 0x7C42, "");
_Static_assert(HPT_RST == 0x7C43, "");
_Static_assert(HPT_FBK == 0x7C44, "");
_Static_assert(HPT_BUZ == 0x7C45, "");
_Static_assert(HPT_MODI == 0x7C46, "");
_Static_assert(HPT_MODD == 0x7C47, "");
_Static_assert(HPT_CONT == 0x7C48, "");
_Static_assert(HPT_CONI == 0x7C49, "");
_Static_assert(HPT_COND == 0x7C4A, "");
_Static_assert(HPT_DWLI == 0x7C4B, "");
_Static_assert(HPT_DWLD == 0x7C4C, "");
_Static_assert(KC_ASDN == 0x7C10, "");
_Static_assert(KC_ASUP == 0x7C11, "");
_Static_assert(KC_ASRP == 0x7C12, "");
_Static_assert(KC_ASON == 0x7C13, "");
_Static_assert(KC_ASOFF == 0x7C14, "");
_Static_assert(KC_ASTG == 0x7C15, "");
_Static_assert(CMB_ON == 0x7C50, "");
_Static_assert(CMB_OFF == 0x7C51, "");
_Static_assert(CMB_TOG == 0x7C52, "");
_Static_assert(BL_TOGG == 0x7802, "");
_Static_assert(BL_STEP == 0x7805, "");
_Static_assert(BL_BRTG == 0x7806, "");
_Static_assert(BL_ON == 0x7800, "");
_Static_assert(BL_OFF == 0x7801, "");
_Static_assert(BL_INC == 0x7804, "");
_Static_assert(BL_DEC == 0x7803, "");
_Static_assert(RGB_TOG == 0x7820, "");
_Static_assert(RGB_MOD == 0x7821, "");
_Static_assert(RGB_RMOD == 0x7822, "");
_Static_assert(RGB_HUI == 0x7823, "");
_Static_assert(RGB_HUD == 0x7824, "");
_Static_assert(RGB_SAI == 0x7825, "");
_Static_assert(RGB_SAD == 0x7826, "");
_Static_assert(RGB_VAI == 0x7827, "");
_Static_assert(RGB_VAD == 0x7828, "");
_Static_assert(RGB_SPI == 0x7829, "");
_Static_assert(RGB_SPD == 0x782A, "");
_Static_assert(RGB_M_P == 0x782B, "");
_Static_assert(RGB_M_B == 0x782C, "");
_Static_assert(RGB_M_R == 0x782D, "");
_Static_assert(RGB_M_SW == 0x782E, "");
_Static_assert(RGB_M_SN == 0x782F, "");
_Static_assert(RGB_M_K == 0x7830, "");
_Static_assert(RGB_M_X == 0x7831, "");
_Static_assert(RGB_M_G == 0x7832, "");
_Static_assert(RGB_M_T == 0x7833, "");
_Static_assert(KC_F13 == 104, "");
_Static_assert(KC_F14 == 105, "");
_Static_assert(KC_F15 == 106, "");
_Static_assert(KC_F16 == 107, "");
_Static_assert(KC_F17 == 108, "");
_Static_assert(KC_F18 == 109, "");
_Static_assert(KC_F19 == 110, "");
_Static_assert(KC_F20 == 111, "");
_Static_assert(KC_F21 == 112, "");
_Static_assert(KC_F22 == 113, "");
_Static_assert(KC_F23 == 114, "");
_Static_assert(KC_F24 == 115, "");
_Static_assert(KC_PWR == 165, "");
_Static_assert(KC_SLEP == 166, "");
_Static_assert(KC_WAKE == 167, "");
_Static_assert(KC_EXEC == 116, "");
_Static_assert(KC_HELP == 117, "");
_Static_assert(KC_SLCT == 119, "");
_Static_assert(KC_STOP == 120, "");
_Static_assert(KC_AGIN == 121, "");
_Static_assert(KC_UNDO == 122, "");
_Static_assert(KC_CUT == 123, "");
_Static_assert(KC_COPY == 124, "");
_Static_assert(KC_PSTE == 125, "");
_Static_assert(KC_FIND == 126, "");
_Static_assert(KC_CALC == 178, "");
_Static_assert(KC_MAIL == 177, "");
_Static_assert(KC_MSEL == 175, "");
_Static_assert(KC_MYCM == 179, "");
_Static_assert(KC_WSCH == 180, "");
_Static_assert(KC_WHOM == 181, "");
_Static_assert(KC_WBAK == 182, "");
_Static_assert(KC_WFWD == 183, "");
_Static_assert(KC_WSTP == 184, "");
_Static_assert(KC_WREF == 185, "");
_Static_assert(KC_WFAV == 186, "");
_Static_assert(KC_BRIU == 189, "");
_Static_assert(KC_BRID == 190, "");
_Static_assert(KC_MPRV == 172, "");
_Static_assert(KC_MNXT == 171, "");
_Static_assert(KC_MUTE == 168, "");
_Static_assert(KC_VOLD == 170, "");
_Static_assert(KC_VOLU == 169, "");
_Static_assert(KC__VOLDOWN == 129, "");
_Static_assert(KC__VOLUP == 128, "");
_Static_assert(KC_MSTP == 173, "");
_Static_assert(KC_MPLY == 174, "");
_Static_assert(KC_MRWD == 188, "");
_Static_assert(KC_MFFD == 187, "");
_Static_assert(KC_EJCT == 176, "");
_Static_assert(KC_MS_U == 0xCD, "");
_Static_assert(KC_MS_D == 0xCE, "");
_Static_assert(KC_MS_L == 0xCF, "");
_Static_assert(KC_MS_R == 0xD0, "");
_Static_assert(KC_BTN1 == 0xD1, "");
_Static_assert(KC_BTN2 == 0xD2, "");
_Static_assert(KC_BTN3 == 0xD3, "");
_Static_assert(KC_BTN4 == 0xD4, "");
_Static_assert(KC_BTN5 == 0xD5, "");
_Static_assert(KC_WH_U == 0xD9, "");
_Static_assert(KC_WH_D == 0xDA, "");
_Static_assert(KC_WH_L == 0xDB, "");
_Static_assert(KC_WH_R == 0xDC, "");
_Static_assert(KC_ACL0 == 0xDD, "");
_Static_assert(KC_ACL1 == 0xDE, "");
_Static_assert(KC_ACL2 == 0xDF, "");
_Static_assert(KC_LCAP == 130, "");
_Static_assert(KC_LNUM == 131, "");
_Static_assert(KC_LSCR == 132, "");
_Static_assert(DYN_REC_START1 == 0x7C53, "");
_Static_assert(DYN_REC_START2 == 0x7C54, "");
_Static_assert(DYN_REC_STOP == 0x7C55, "");
_Static_assert(DYN_MACRO_PLAY1 == 0x7C56, "");
_Static_assert(DYN_MACRO_PLAY2 == 0x7C57, "");
_Static_assert(MI_C == 0x7103, "");
_Static_assert(MI_Cs == 0x7104, "");
_Static_assert(MI_D == 0x7105, "");
_Static_assert(MI_Ds == 0x7106, "");
_Static_assert(MI_E == 0x7107, "");
_Static_assert(MI_F == 0x7108, "");
_Static_assert(MI_Fs == 0x7109, "");
_Static_assert(MI_G == 0x710A, "");
_Static_assert(MI_Gs == 0x710B, "");
_Static_assert(MI_A == 0x710C, "");
_Static_assert(MI_As == 0x710D, "");
_Static_assert(MI_B == 0x710E, "");
_Static_assert(MI_C_1 == 0x710F, "");
_Static_assert(MI_Cs_1 == 0x7110, "");
_Static_assert(MI_D_1 == 0x7111, "");
_Static_assert(MI_Ds_1 == 0x7112, "");
_Static_assert(MI_E_1 == 0x7113, "");
_Static_assert(MI_F_1 == 0x7114, "");
_Static_assert(MI_Fs_1 == 0x7115, "");
_Static_assert(MI_G_1 == 0x7116, "");
_Static_assert(MI_Gs_1 == 0x7117, "");
_Static_assert(MI_A_1 == 0x7118, "");
_Static_assert(MI_As_1 == 0x7119, "");
_Static_assert(MI_B_1 == 0x711A, "");
_Static_assert(MI_C_2 == 0x711B, "");
_Static_assert(MI_Cs_2 == 0x711C, "");
_Static_assert(MI_D_2 == 0x711D, "");
_Static_assert(MI_Ds_2 == 0x711E, "");
_Static_assert(MI_E_2 == 0x711F, "");
_Static_assert(MI_F_2 == 0x7120, "");
_Static_assert(MI_Fs_2 == 0x7121, "");
_Static_assert(MI_G_2 == 0x7122, "");
_Static_assert(MI_Gs_2 == 0x7123, "");
_Static_assert(MI_A_2 == 0x7124, "");
_Static_assert(MI_As_2 == 0x7125, "");
_Static_assert(MI_B_2 == 0x7126, "");
_Static_assert(MI_C_3 == 0x7127, "");
_Static_assert(MI_Cs_3 == 0x7128, "");
_Static_assert(MI_D_3 == 0x7129, "");
_Static_assert(MI_Ds_3 == 0x712A, "");
_Static_assert(MI_E_3 == 0x712B, "");
_Static_assert(MI_F_3 == 0x712C, "");
_Static_assert(MI_Fs_3 == 0x712D, "");
_Static_assert(MI_G_3 == 0x712E, "");
_Static_assert(MI_Gs_3 == 0x712F, "");
_Static_assert(MI_A_3 == 0x7130, "");
_Static_assert(MI_As_3 == 0x7131, "");
_Static_assert(MI_B_3 == 0x7132, "");
_Static_assert(MI_C_4 == 0x7133, "");
_Static_assert(MI_Cs_4 == 0x7134, "");
_Static_assert(MI_D_4 == 0x7135, "");
_Static_assert(MI_Ds_4 == 0x7136, "");
_Static_assert(MI_E_4 == 0x7137, "");
_Static_assert(MI_F_4 == 0x7138, "");
_Static_assert(MI_Fs_4 == 0x7139, "");
_Static_assert(MI_G_4 == 0x713A, "");
_Static_assert(MI_Gs_4 == 0x713B, "");
_Static_assert(MI_A_4 == 0x713C, "");
_Static_assert(MI_As_4 == 0x713D, "");
_Static_assert(MI_B_4 == 0x713E, "");
_Static_assert(MI_C_5 == 0x713F, "");
_Static_assert(MI_Cs_5 == 0x7140, "");
_Static_assert(MI_D_5 == 0x7141, "");
_Static_assert(MI_Ds_5 == 0x7142, "");
_Static_assert(MI_E_5 == 0x7143, "");
_Static_assert(MI_F_5 == 0x7144, "");
_Static_assert(MI_Fs_5 == 0x7145, "");
_Static_assert(MI_G_5 == 0x7146, "");
_Static_assert(MI_Gs_5 == 0x7147, "");
_Static_assert(MI_A_5 == 0x7148, "");
_Static_assert(MI_As_5 == 0x7149, "");
_Static_assert(MI_B_5 == 0x714A, "");
_Static_assert(MI_ALLOFF == 0x7185, "");
_Static_assert(MI_OCT_N2 == 0x714B, "");
_Static_assert(MI_OCT_N1 == 0x714C, "");
_Static_assert(MI_OCT_0 == 0x714D, "");
_Static_assert(MI_OCT_1 == 0x714E, "");
_Static_assert(MI_OCT_2 == 0x714F, "");
_Static_assert(MI_OCT_3 == 0x7150, "");
_Static_assert(MI_OCT_4 == 0x7151, "");
_Static_assert(MI_OCT_5 == 0x7152, "");
_Static_assert(MI_OCT_6 == 0x7153, "");
_Static_assert(MI_OCT_7 == 0x7154, "");
_Static_assert(MI_OCTD == 0x7155, "");
_Static_assert(MI_OCTU == 0x7156, "");
_Static_assert(MI_TRNS_N6 == 0x7157, "");
_Static_assert(MI_TRNS_N5 == 0x7158, "");
_Static_assert(MI_TRNS_N4 == 0x7159, "");
_Static_assert(MI_TRNS_N3 == 0x715A, "");
_Static_assert(MI_TRNS_N2 == 0x715B, "");
_Static_assert(MI_TRNS_N1 == 0x715C, "");
_Static_assert(MI_TRNS_0 == 0x715D, "");
_Static_assert(MI_TRNS_1 == 0x715E, "");
_Static_assert(MI_TRNS_2 == 0x715F, "");
_Static_assert(MI_TRNS_3 == 0x7160, "");
_Static_assert(MI_TRNS_4 == 0x7161, "");
_Static_assert(MI_TRNS_5 == 0x7162, "");
_Static_assert(MI_TRNS_6 == 0x7163, "");
_Static_assert(MI_TRNSD == 0x7164, "");
_Static_assert(MI_TRNSU == 0x7165, "");
_Static_assert(MI_VEL_1 == 0x7167, "");
_Static_assert(MI_VEL_2 == 0x7168, "");
_Static_assert(MI_VEL_3 == 0x7169, "");
_Static_assert(MI_VEL_4 == 0x716A, "");
_Static_assert(MI_VEL_5 == 0x716B, "");
_Static_assert(MI_VEL_6 == 0x716C, "");
_Static_assert(MI_VEL_7 == 0x716D, "");
_Static_assert(MI_VEL_8 == 0x716E, "");
_Static_assert(MI_VEL_9 == 0x716F, "");
_Static_assert(MI_VEL_10 == 0x7170, "");
_Static_assert(MI_VELD == 0x7171, "");
_Static_assert(MI_VELU == 0x7172, "");
_Static_assert(MI_CH1 == 0x7173, "");
_Static_assert(MI_CH2 == 0x7174, "");
_Static_assert(MI_CH3 == 0x7175, "");
_Static_assert(MI_CH4 == 0x7176, "");
_Static_assert(MI_CH5 == 0x7177, "");
_Static_assert(MI_CH6 == 0x7178, "");
_Static_assert(MI_CH7 == 0x7179, "");
_Static_assert(MI_CH8 == 0x717A, "");
_Static_assert(MI_CH9 == 0x717B, "");
_Static_assert(MI_CH10 == 0x717C, "");
_Static_assert(MI_CH11 == 0x717D, "");
_Static_assert(MI_CH12 == 0x717E, "");
_Static_assert(MI_CH13 == 0x717F, "");
_Static_assert(MI_CH14 == 0x7180, "");
_Static_assert(MI_CH15 == 0x7181, "");
_Static_assert(MI_CH16 == 0x7182, "");
_Static_assert(MI_CHD == 0x7183, "");
_Static_assert(MI_CHU == 0x7184, "");
_Static_assert(MI_SUS == 0x7186, "");
_Static_assert(MI_PORT == 0x7187, "");
_Static_assert(MI_SOST == 0x7188, "");
_Static_assert(MI_SOFT == 0x7189, "");
_Static_assert(MI_LEG == 0x718A, "");
_Static_assert(MI_MOD == 0x718B, "");
_Static_assert(MI_MODSD == 0x718C, "");
_Static_assert(MI_MODSU == 0x718D, "");
_Static_assert(MI_BENDD == 0x718E, "");
_Static_assert(MI_BENDU == 0x718F, "");

_Static_assert(RESET == 0x7C00, "");

_Static_assert(FN_MO13 == 0x7C77, "");
_Static_assert(FN_MO23 == 0x7C78, "");

/* Ensure that we have 64 USERxx keycodes */
_Static_assert(QK_KB == 0x7E00, "");
_Static_assert(QK_KB_MAX == 0x7E3F, "");


#undef C_S
#undef LCG_T
#undef RCG_T
#undef LCG
#undef RCG
#undef kc

#undef KC_BSPACE
#undef KC_NUMLOCK
#undef KC_PSCREEN
#undef KC_SCROLLLOCK
#undef KC_PGDOWN
#undef KC_LBRACKET
#undef KC_RBRACKET
#undef KC_BSLASH
#undef KC_SCOLON
#undef KC_CAPSLOCK
#undef KC_LCTRL
#undef KC_LSHIFT
#undef KC_RCTRL
#undef KC_RSHIFT
#undef KC_NONUS_BSLASH
#undef KC_RO
#undef KC_KANA
#undef KC_JYEN
#undef KC_HENK
#undef KC_MHEN
#undef KC_LANG1
#undef KC_LANG2
#undef KC_GESC
#undef KC_LSPO
#undef KC_RSPC
#undef KC_LCPO
#undef KC_RCPC
#undef KC_LAPO
#undef KC_RAPC
#undef KC_SFTENT
#undef AU_TOG
#undef CLICKY_TOGGLE
#undef CLICKY_UP
#undef CLICKY_DOWN
#undef CLICKY_RESET
#undef MU_TOG
#undef MU_MOD
#undef HPT_ON
#undef HPT_OFF
#undef HPT_TOG
#undef HPT_RST
#undef HPT_FBK
#undef HPT_BUZ
#undef HPT_MODI
#undef HPT_MODD
#undef HPT_CONT
#undef HPT_CONI
#undef HPT_COND
#undef HPT_DWLI
#undef HPT_DWLD
#undef KC_ASDN
#undef KC_ASUP
#undef KC_ASRP
#undef KC_ASON
#undef KC_ASOFF
#undef KC_ASTG
#undef CMB_ON
#undef CMB_OFF
#undef CMB_TOG
#undef BL_INC
#undef BL_DEC
#undef KC__VOLDOWN
#undef KC__VOLUP
#undef DYN_REC_START1
#undef DYN_REC_START2
#undef DYN_REC_STOP
#undef DYN_MACRO_PLAY1
#undef DYN_MACRO_PLAY2
#undef MI_C_1
#undef MI_Cs_1
#undef MI_Db_1
#undef MI_D_1
#undef MI_Ds_1
#undef MI_Eb_1
#undef MI_E_1
#undef MI_F_1
#undef MI_Fs_1
#undef MI_Gb_1
#undef MI_G_1
#undef MI_Gs_1
#undef MI_Ab_1
#undef MI_A_1
#undef MI_As_1
#undef MI_Bb_1
#undef MI_B_1
#undef MI_C_2
#undef MI_Cs_2
#undef MI_Db_2
#undef MI_D_2
#undef MI_Ds_2
#undef MI_Eb_2
#undef MI_E_2
#undef MI_F_2
#undef MI_Fs_2
#undef MI_Gb_2
#undef MI_G_2
#undef MI_Gs_2
#undef MI_Ab_2
#undef MI_A_2
#undef MI_As_2
#undef MI_Bb_2
#undef MI_B_2
#undef MI_C_3
#undef MI_Cs_3
#undef MI_Db_3
#undef MI_D_3
#undef MI_Ds_3
#undef MI_Eb_3
#undef MI_E_3
#undef MI_F_3
#undef MI_Fs_3
#undef MI_Gb_3
#undef MI_G_3
#undef MI_Gs_3
#undef MI_Ab_3
#undef MI_A_3
#undef MI_As_3
#undef MI_Bb_3
#undef MI_B_3
#undef MI_C_4
#undef MI_Cs_4
#undef MI_Db_4
#undef MI_D_4
#undef MI_Ds_4
#undef MI_Eb_4
#undef MI_E_4
#undef MI_F_4
#undef MI_Fs_4
#undef MI_Gb_4
#undef MI_G_4
#undef MI_Gs_4
#undef MI_Ab_4
#undef MI_A_4
#undef MI_As_4
#undef MI_Bb_4
#undef MI_B_4
#undef MI_C_5
#undef MI_Cs_5
#undef MI_Db_5
#undef MI_D_5
#undef MI_Ds_5
#undef MI_Eb_5
#undef MI_E_5
#undef MI_F_5
#undef MI_Fs_5
#undef MI_Gb_5
#undef MI_G_5
#undef MI_Gs_5
#undef MI_Ab_5
#undef MI_A_5
#undef MI_As_5
#undef MI_Bb_5
#undef MI_B_5
#undef MI_OCT_N2
#undef MI_OCT_N1
#undef MI_OCT_0
#undef MI_OCT_1
#undef MI_OCT_2
#undef MI_OCT_3
#undef MI_OCT_4
#undef MI_OCT_5
#undef MI_OCT_6
#undef MI_OCT_7
#undef MI_ALLOFF
#undef MI_TRNS_N6
#undef MI_TRNS_N5
#undef MI_TRNS_N4
#undef MI_TRNS_N3
#undef MI_TRNS_N2
#undef MI_TRNS_N1
#undef MI_TRNS_0
#undef MI_TRNS_1
#undef MI_TRNS_2
#undef MI_TRNS_3
#undef MI_TRNS_4
#undef MI_TRNS_5
#undef MI_TRNS_6
#undef MI_TRNSD
#undef MI_TRNSU
#undef MI_VEL_0
#undef MI_VEL_1
#undef MI_VEL_2
#undef MI_VEL_3
#undef MI_VEL_4
#undef MI_VEL_5
#undef MI_VEL_6
#undef MI_VEL_7
#undef MI_VEL_8
#undef MI_VEL_9
#undef MI_VEL_10
#undef MI_CHD
#undef MI_CHU
#undef MI_SUS
#undef MI_MODSD
#undef MI_MODSU
#undef MI_BENDD
#undef MI_BENDU
#undef RESET
#undef FN_MO13
#undef FN_MO23
