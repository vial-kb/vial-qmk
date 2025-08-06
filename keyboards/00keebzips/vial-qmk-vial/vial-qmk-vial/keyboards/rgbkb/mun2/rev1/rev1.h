/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "mun2.h"

// clang-format off
/* Blank ascii map to reuse, with labeled possible encoder positions
┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│      │      │      │      │      │      │  E1  │  │  E4  │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │  E1  │  │  E4  │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      |      │  E2  │  │  E5  │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │  E2  │  │  E5  │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │  E3  │  E3  │  E3  │      │      │  │      │      │  E6  │  E6  │  E6  │      │      │
└──────┴──────┴──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┴──────┴──────┘
┌──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┐
│  E0↑ │  E0↓ │  E1↑ │  E1↓ │  E2↑ │  E2↓ │  │  E3↑ │  E3↓ │  E4↑ │  E4↓ │  E5↑ │  E5↓ │
└──────┴──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┴──────┘
┌──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┐
│  T0↑ │  T0↓ │      │      │      │                │  T1↑ │  T1↓ │      │      │      │
└──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┘
*/

#define LAYOUT( \
    L10, L02, L03, L04, L05, L06, L07,    R07, R06, R05, R04, R03, R02, R10, \
    L11, L12, L13, L14, L15, L16, L17,    R17, R16, R15, R14, R13, R12, R11, \
    L21, L22, L23, L24, L25, L26, L27,    R27, R26, R25, R24, R23, R22, R21,  \
    L31, L32, L33, L34, L35, L36, L37,    R37, R36, R35, R34, R33, R32, R31,  \
    L30, L42, L43, L44, L45, L46, L47,    R47, R46, R45, R44, R43, R42, R30, \
    \
    E0L, E0R, E1L, E1R, E2L, E2R,    E3L, E3R, E4L, E4R, E5L, E5R, \
    LT0, LT1, LT2, LSL, LSR,              RT0, RT1, RT2, RSL, RSR \
) \
{ \
    /* Left Half */ \
    { KC_NO, KC_NO, L02, L03, L04, L05, L06, L07,}, \
    {   L10,   L11, L12, L13, L14, L15, L16, L17,}, \
    { KC_NO,   L21, L22, L23, L24, L25, L26, L27,}, \
    {   L30,   L31, L32, L33, L34, L35, L36, L37,}, \
    { KC_NO, KC_NO, L42, L43, L44, L45, L46, L47,}, \
    { E0L, E0R, E1L, E1R, E2L, E2R, KC_NO, KC_NO, }, \
    { LT0, LT1, LT2, LSL, LSR, KC_NO, KC_NO, KC_NO }, \
    /* Right Half */ \
    { KC_NO, KC_NO, R02, R03, R04, R05, R06, R07,}, \
    {   R10,   R11, R12, R13, R14, R15, R16, R17,}, \
    { KC_NO,   R21, R22, R23, R24, R25, R26, R27,}, \
    {   R30,   R31, R32, R33, R34, R35, R36, R37,}, \
    { KC_NO, KC_NO, R42, R43, R44, R45, R46, R47,}, \
    { E3L, E3R, E4L, E4R, E5L, E5R, KC_NO, KC_NO,}, \
    { RT0, RT1, RT2, RSL, RSR, KC_NO, KC_NO, KC_NO } \
}
// clang-format on

// weak functions overridable by the user
void render_layer_status(void);
void render_leds_status(void);
void render_touch_status(void);
void render_audio_status(void);

#ifdef RGB_MATRIX_ENABLE
// utility function to cycle active led zones
void rgb_matrix_increase_flags(void);
#endif