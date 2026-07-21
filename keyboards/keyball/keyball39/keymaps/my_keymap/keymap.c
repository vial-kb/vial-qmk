/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "eeprom.h"
#include "transactions.h"
#include "qmk_settings.h"
#include <lib/lib8tion/lib8tion.h>

#if defined(SPLIT_KEYBOARD)
// Row offsets for this controller's own matrix vs. the peer's relayed rows
// (quantum/matrix_common.c). Used to tell, on the master, which physical
// hand a given key event came from — see the "Mod-key LED color override"
// section below.
extern uint8_t thisHand;
#endif

// Layer + mods + opposite-hand mod override synced to slave via MY_LAYER_SYNC
// RPC (4 bytes: [layer, mods, opposite_mod_active, opposite_mod_hue]).
static uint8_t slave_layer                = 0;
static uint8_t slave_mods                 = 0;
static bool    slave_opposite_mod_active  = false;
static uint8_t slave_opposite_mod_hue     = 0;

static void layer_sync_handler(uint8_t len, const void *data, uint8_t rlen, void *rbuf) {
    if (len >= 4) {
        const uint8_t *d          = (const uint8_t *)data;
        slave_layer                = d[0];
        slave_mods                 = d[1];
        slave_opposite_mod_active  = d[2] != 0;
        slave_opposite_mod_hue     = d[3];
    }
}

// ---------------------------------------------------------------------------
// Custom Auto Mouse Layer (AML) behavior — ported from lib/keyball customization
//   - Trackball movement crossing threshold → activate AML, stay indefinitely.
//   - Mouse button clicks do NOT exit AML.
//   - Only ESC_ML (keyball_escape_mouse_layer) explicitly exits AML.
// All logic lives here in the keymap so the holykeebs keyball lib stays untouched.
// ---------------------------------------------------------------------------
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#include "pointing_device_auto_mouse.h"

static const uint16_t AML_ACTIVATE_THRESHOLD_C = 20;
static const uint16_t AML_NO_MOVE_RESET_MS     = 500;
// Keystroke vibration bursts settle within ~15 ms.  Only count movement toward
// the AML threshold after it has been continuous for this long, so single-
// keystroke shocks never accumulate enough to fire AML.
#define AML_SUSTAIN_MS           25
#define AML_FORCED_EXIT_COOLDOWN 600

static uint16_t aml_no_move_timer     = 0;
static bool     aml_forced_exit       = false;
static uint16_t aml_forced_exit_timer = 0;

// Magnitude of pointer movement in this report.
static uint16_t aml_movement_size(report_mouse_t *r) {
    int16_t x = r->x < 0 ? -r->x : r->x;
    int16_t y = r->y < 0 ? -r->y : r->y;
    return (uint16_t)(x + y);
}

// Override QMK weak function. Returning true keeps the AML timer reset so the
// timeout never fires; AML stays active until keyball_escape_mouse_layer().
bool auto_mouse_activation(report_mouse_t mouse_report) {
    if (aml_forced_exit) {
        if (timer_elapsed(aml_forced_exit_timer) > AML_FORCED_EXIT_COOLDOWN) {
            aml_forced_exit = false;
        } else {
            return false;
        }
    }

    uint16_t movement = aml_movement_size(&mouse_report);
    static uint16_t total         = 0;
    static uint16_t sustain_start = 0;
    if (movement > 0) {
        aml_no_move_timer = 0;
        if (sustain_start == 0) sustain_start = timer_read();
        // Only accumulate once movement has been sustained beyond the vibration
        // window.  This prevents single keystroke shocks from triggering AML.
        if (timer_elapsed(sustain_start) >= AML_SUSTAIN_MS) {
            total += movement;
        }
    } else {
        sustain_start = 0;
        if (!layer_state_is(AUTO_MOUSE_DEFAULT_LAYER)) {
            if (aml_no_move_timer == 0) {
                aml_no_move_timer = timer_read();
            } else if (timer_elapsed(aml_no_move_timer) > AML_NO_MOVE_RESET_MS) {
                total = 0;
                aml_no_move_timer = 0;
            }
        }
    }

    if (AML_ACTIVATE_THRESHOLD_C < total) {
        total = 0;
        return true;
    }
    if (layer_state_is(AUTO_MOUSE_DEFAULT_LAYER)) {
        return true;  // keep AML alive regardless of clicks
    }
    return mouse_report.buttons;
}

// Explicitly exit AML and suppress re-activation for a short cooldown.
void keyball_escape_mouse_layer(void) {
    layer_off(get_auto_mouse_layer());
    aml_forced_exit       = true;
    aml_forced_exit_timer = timer_read();
    aml_no_move_timer     = 0;
}

// Called from layer_state_set_user on every layer change. Previously lived in
// the keyball lib; reduced here to a no-op-safe stub (movement counter is local).
void keyball_handle_auto_mouse_layer_change(layer_state_t state) {
    (void)state;
}
#endif

// Tapping term now lives entirely in QS.tapping_term (quantum/qmk_settings.c),
// the same storage Vial's "QMK Settings" panel reads/writes. This used to be
// a separate g_tapping_term (Dynamic Tapping Term feature) backed by our own
// raw EEPROM bytes 4092-4095 — that meant the value MY_DT_UP/MY_DT_DOWN
// changed and the number shown in Vial's QMK Settings tab were two unrelated
// storages that could never agree. Routing both through QS.tapping_term
// (qsid 7, see the DECLARE_STATIC_SETTING(7, tapping_term) entry in
// quantum/qmk_settings.c) makes them the same value again: adjust it here,
// see it there, and vice versa.
#define QS_QSID_TAPPING_TERM 7
#define DT_ADJUST_STEP        5  // matches stock DYNAMIC_TAPPING_TERM_INCREMENT

// NOTE: we do NOT define get_tapping_term() ourselves — quantum/vial.c already
// provides one (it's what GET_TAPPING_TERM() in action_tapping.h actually calls,
// since TAPPING_TERM_PER_KEY is defined by Vial's default build settings), and
// it already returns qs_get_tapping_term() i.e. QS.tapping_term for any key
// without a per-key tap-dance override. That means QS.tapping_term was already
// the real value driving tap/hold decisions even before this change — our own
// previous g_tapping_term (Dynamic Tapping Term) was dead for that purpose,
// only ever feeding the OLED display. Adjusting QS.tapping_term below is what
// actually reaches vial.c's get_tapping_term() and changes real behavior.

// Custom keycodes for escaping the auto mouse layer.
//   ESC_ML      - exit AML only
//   ESC_ML_LNG2 - exit AML then tap LNG2 (英数, switch to English input)
//   ESC_ML_LNG1 - exit AML then tap LNG1 (かな, switch to Japanese input)
//   MY_ANI      - cycle custom LED animation (OFF → PLASMA → AURORA → METEOR → OFF)
// Base is QK_KB_16 (not KEYBALL_SAFE_RANGE/QK_USER_0): Vial's customKeycodes
// array in vial.json is indexed from QK_KB_0, and QK_KB_0..15 are already
// claimed by the keyball driver's built-in keycodes (KBC_RST, CPI_*, etc).
// Starting here keeps our indices in vial.json lined up with our own values.
//
// MY_DT_PRNT/MY_DT_UP/MY_DT_DOWN adjust QS.tapping_term (quantum/qmk_settings.c)
// directly — the same value Vial's "QMK Settings" panel shows and edits — so
// keyboard-side taps and the GUI never disagree. Vial's own keycode tables
// don't know about QMK's separate "Dynamic Tapping Term" feature (it shows up
// unnamed there), so these also give us a nameable key via vial.json's
// customKeycodes.
// LNG1_TO0/LNG2_TO0: tap LNG1/LNG2 then jump to layer 0 — replaces the Vial
// dynamic macros M1/M2 ("tap KC_LANG1/2" then "TO(0)") from the Vial-tuned
// keymap baked in below, so this behavior is compiled in rather than living
// only in EEPROM-recorded macro slots.
enum my_keycodes {
    ESC_ML = QK_KB_16,
    ESC_ML_LNG2,
    ESC_ML_LNG1,
    MY_ANI,
    MY_DT_PRNT,
    MY_DT_UP,
    MY_DT_DOWN,
    LNG1_TO0,
    LNG2_TO0,
};

// Deferred LNG key: sent on the next matrix scan after AML exit so that
// the layer change is fully committed before the HID report is generated.
static uint8_t pending_lang_key = 0;

void matrix_scan_user(void) {
    if (pending_lang_key) {
        tap_code(pending_lang_key);
        pending_lang_key = 0;
    }
}

// ── Custom per-LED animations ──────────────────────────────────────────────────
// MY_ANI cycles: OFF → PLASMA → AURORA → METEOR → OFF.
// Uses rgblight_driver.set_color() × 24 (buffer only, no flush) + rgblight_set()
// × 1 per frame → ~1.5ms DMA busy time, safe for keyboard scanning.
// Both sides render independently using their local 24-LED indices.

typedef enum {
    MY_ANIM_OFF = 0,
    MY_ANIM_PLASMA,   // multi-wave HSV interference: fast, vibrant, full-spectrum
    MY_ANIM_AURORA,   // slow cool-color bands: blue/teal/green drifting gently
    MY_ANIM_METEOR,   // three coloured shooting stars circling the strip
    MY_ANIM_COUNT,
} my_anim_mode_t;

static my_anim_mode_t my_anim       = MY_ANIM_OFF;
static uint16_t       my_anim_timer = 0;
static uint16_t       my_tick       = 0;

#define MY_ANIM_LEDS 24
#define MY_ANIM_MS   20

static void my_draw_anim(void) {
    uint8_t t = (uint8_t)my_tick;

    // Meteor comet parameters (PROGMEM to avoid stack)
    static const uint8_t PROGMEM met_spd[3] = {5, 7, 11};
    static const uint8_t PROGMEM met_hue[3] = {0, 85, 170};

    for (uint8_t i = 0; i < MY_ANIM_LEDS; i++) {
        uint8_t h = 0, s = 255, v = 0;

        switch (my_anim) {
            case MY_ANIM_PLASMA: {
                // Three overlapping sine waves → complex colour interference
                uint8_t w1 = sin8((uint8_t)(i * 8  + t));
                uint8_t w2 = sin8((uint8_t)(i * 13 + t + (t >> 1)));
                uint8_t w3 = sin8((uint8_t)(i * 3  - (t >> 1)));
                h = w1 / 3 + w2 / 3 + w3 / 3;
                v = 130 + sin8((uint8_t)((h >> 1) + t)) / 5;  // 130-181
                break;
            }
            case MY_ANIM_AURORA: {
                // Hue drifts in the blue-teal-green-purple band (130-193)
                h = 130 + sin8((uint8_t)(i * 6 + t / 3)) / 4;
                s = 220;
                v = 80 + sin8((uint8_t)(i * 9 + (t >> 1))) / 3;  // 80-165
                break;
            }
            case MY_ANIM_METEOR: {
                // Three coloured comets (R/G/B) with exponential tails
                for (uint8_t c = 0; c < 3; c++) {
                    uint8_t spd  = pgm_read_byte(&met_spd[c]);
                    uint8_t head = (uint8_t)(((uint16_t)t * spd >> 2) % MY_ANIM_LEDS);
                    uint8_t dist = (uint8_t)((head - i + MY_ANIM_LEDS) % MY_ANIM_LEDS);
                    if (dist < 6) {
                        uint8_t br = (uint8_t)(200 >> dist);  // 200→100→50→25→12→6
                        if (br > v) { h = pgm_read_byte(&met_hue[c]); v = br; }
                    }
                }
                break;
            }
            default: break;
        }

        hsv_t hsv = {h, s, v};
        rgb_t rgb = hsv_to_rgb(hsv);
        // set_color() only writes to buffer; rgblight_set() below does one DMA flush.
        rgblight_driver.set_color(i, rgb.r, rgb.g, rgb.b);
    }
    rgblight_set();
}

// ── Mod-key LED color override (opposite-hand indicator) ───────────────────
// While Ctrl/Shift/Alt/GUI is held, the underglow on the OPPOSITE hand from
// the one holding it is hijacked to a dedicated solid color; the hand
// actually holding the mod is left completely untouched. Priority when
// several mods are held on the same hand at once: GUI > Ctrl > Alt > Shift.
//
// Whatever is currently running — a native RGBLIGHT effect (breathing,
// rainbow, ...) or the custom my_anim below — keeps running untouched the
// whole time; we never change RGBLIGHT mode for this. Instead, while an
// override is active, this half's own 24 LEDs get repainted solid on top of
// it every MOD_LED_REPAINT_MS (and immediately after my_anim redraws), so
// the override keeps winning against whatever is redrawing underneath. The
// instant the mod releases we simply stop repainting; since the underlying
// effect never stopped updating, it's already showing the correct current
// frame and reappears with no special "restore" step (except the one case
// where nothing else would naturally redraw that half — plain static
// per-layer color — where we do one explicit repaint back to it).
//
// Only the master half runs process_record_user (the slave only relays raw
// matrix state up to master), so master is the only side that can tell
// which physical hand a mod came from. It does so via record->event.key.row:
// quantum/matrix_common.c places this controller's own scanned rows at
// [thisHand, thisHand+ROWS_PER_HAND) and the peer's relayed rows in the
// other half of the combined matrix — this holds regardless of which
// physical side ends up being master. Master learns its own-hand mod state
// locally (own_side_mods) and the peer's (peer_side_mods) the same way; the
// peer's own-hand state doesn't reach the slave until pushed over the
// existing MY_LAYER_SYNC RPC (see housekeeping_task_user below).
#define MOD_LED_HUE_GUI   200  // 蛍光マゼンタ
#define MOD_LED_HUE_CTRL  170  // 蛍光ブルー
#define MOD_LED_HUE_ALT    30  // 蛍光オレンジ
#define MOD_LED_HUE_SHIFT   0  // 蛍光レッド

#define MY_ROWS_PER_HAND    (MATRIX_ROWS / 2)
#define MOD_LED_REPAINT_MS  10  // re-assert cadence while an override is held

static bool    mod_led_active    = false;  // is THIS half currently painting an override
static uint8_t mod_led_hue       = 0;
static uint8_t own_side_mods     = 0;      // mods currently held via keys on master's own matrix
static uint8_t peer_side_mods    = 0;      // mods currently held via keys relayed from the slave
static uint8_t mods_before_event = 0;      // get_mods() snapshot, for diffing in post_process_record_user

static bool my_mod_led_hue(uint8_t mods, uint8_t *out_hue) {
    if (mods & MOD_MASK_GUI) {
        *out_hue = MOD_LED_HUE_GUI;
        return true;
    }
    if (mods & MOD_MASK_CTRL) {
        *out_hue = MOD_LED_HUE_CTRL;
        return true;
    }
    if (mods & MOD_MASK_ALT) {
        *out_hue = MOD_LED_HUE_ALT;
        return true;
    }
    if (mods & MOD_MASK_SHIFT) {
        *out_hue = MOD_LED_HUE_SHIFT;
        return true;
    }
    return false;
}

static uint8_t my_layer_hue(uint8_t highest_layer) {
    switch (highest_layer) {
        case 0: return  85; // 蛍光グリーン（デフォルト）
        case 1: return 128; // 蛍光シアン（マウス・AML）
        case 2: return  43; // 蛍光イエロー
        case 3: return  21; // 蛍光オレンジ（設定・スクロール）
        case 4: return 213; // 蛍光ピンク（ファンクション）
        case 5: return 192; // 蛍光パープル（記号・数字）
        case 6: return   0; // 蛍光レッド（未使用）
        default: return  85;
    }
}

// Paints a solid color directly onto this half's own 24 LEDs, bypassing
// rgblight's synced hue/sat/val state so the two halves can differ (see
// notes above). Whatever effect is currently rendering (native RGBLIGHT
// mode or my_anim) keeps running and will redraw over this on its own next
// update — see housekeeping_task_user for how the override keeps winning.
static void my_paint_solid_local(uint8_t hue) {
    hsv_t hsv = {hue, 255, rgblight_get_val()};
    rgb_t rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < MY_ANIM_LEDS; i++) {
        rgblight_driver.set_color(i, rgb.r, rgb.g, rgb.b);
    }
    rgblight_set();
}

void housekeeping_task_user(void) {
    // Figure out whether THIS half should show an override right now, and
    // with what hue. Master derives both halves' state directly; slave only
    // knows its own (received via MY_LAYER_SYNC, populated further below).
    uint8_t local_hue = 0;
    bool    local_active;

    if (is_keyboard_master()) {
        local_active = my_mod_led_hue(peer_side_mods, &local_hue);  // master's LEDs show the SLAVE hand's mod
    } else {
        local_active = slave_opposite_mod_active;  // slave's LEDs show the MASTER hand's mod
        local_hue    = slave_opposite_mod_hue;
    }

    bool changed   = (local_active != mod_led_active) || (local_active && local_hue != mod_led_hue);
    mod_led_active = local_active;
    mod_led_hue    = local_hue;

    // Custom per-LED animation keeps advancing regardless of any override
    // (each side drives its own 24 LEDs).
    bool anim_drew = false;
    if (my_anim != MY_ANIM_OFF && timer_elapsed(my_anim_timer) >= MY_ANIM_MS) {
        my_anim_timer = timer_read();
        my_tick++;
        my_draw_anim();
        anim_drew = true;
    }

    static uint16_t mod_led_repaint_timer = 0;
    if (mod_led_active) {
        // Re-assert the hijack often enough to keep winning against
        // whatever native RGBLIGHT effect / my_anim frame just rendered
        // underneath (rgblight_task() always runs earlier in the main loop,
        // before housekeeping_task_user).
        if (changed || anim_drew || timer_elapsed(mod_led_repaint_timer) >= MOD_LED_REPAINT_MS) {
            mod_led_repaint_timer = timer_read();
            my_paint_solid_local(mod_led_hue);
        }
    } else if (changed && my_anim == MY_ANIM_OFF) {
        // Mod just released. If nothing else is actively redrawing this
        // half (e.g. plain static per-layer color), do one explicit repaint
        // so the hijacked color doesn't stay stuck.
        uint8_t hl = is_keyboard_master() ? get_highest_layer(layer_state) : slave_layer;
        my_paint_solid_local(my_layer_hue(hl));
    }

#if defined(SPLIT_KEYBOARD)
    if (is_keyboard_master()) {
        // Tapping term no longer needs an auto-save poll here: qmk_settings_set()
        // in the MY_DT_UP/MY_DT_DOWN handlers above already persists immediately.

        // Auto-save CPI to EEPROM whenever it changes.
        // CPI_I100/CPI_D100 keys only update RAM; without this, CPI resets to
        // KEYBALL_CPI_DEFAULT on every power cycle.  We read-modify-write the
        // keyball config block so sdiv and other fields are preserved.
        static uint16_t last_cpi     = 0;
        static bool     cpi_inited   = false;
        uint16_t        current_cpi  = keyball_get_cpi();
        if (!cpi_inited) {
            last_cpi   = current_cpi;
            cpi_inited = true;
        } else if (current_cpi != last_cpi) {
            keyball_config_t c;
            c.raw = eeconfig_read_kb();
            c.cpi = current_cpi;
            eeconfig_update_kb(c.raw);
            last_cpi = current_cpi;
        }
        // Send layer + mods + own-hand mod override to slave (4 bytes, only on change).
        static uint8_t last_layer      = 255;
        static uint8_t last_mods       = 255;
        static bool    last_own_active = false;
        static uint8_t last_own_hue    = 255;
        uint8_t        l               = get_highest_layer(layer_state);
        uint8_t        m               = get_mods();
        uint8_t        own_hue         = 0;
        bool           own_active      = my_mod_led_hue(own_side_mods, &own_hue);
        if (l != last_layer || m != last_mods || own_active != last_own_active || (own_active && own_hue != last_own_hue)) {
            uint8_t buf[4] = {l, m, (uint8_t)(own_active ? 1 : 0), own_hue};
            if (transaction_rpc_send(MY_LAYER_SYNC, sizeof(buf), buf)) {
                last_layer      = l;
                last_mods       = m;
                last_own_active = own_active;
                last_own_hue    = own_hue;
            }
        }
    }
#endif
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Snapshot mods before this event's action runs, so post_process_record_user
    // can diff against the post-action value and attribute any change to the
    // physical hand this event came from (own_side_mods / peer_side_mods above).
    mods_before_event = get_mods();

    switch (keycode) {
        case ESC_ML:
            if (record->event.pressed) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
                keyball_escape_mouse_layer();
#endif
            }
            return false;
        case ESC_ML_LNG2:
            if (record->event.pressed) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
                keyball_escape_mouse_layer();
#endif
                pending_lang_key = KC_LNG2;
            }
            return false;
        case ESC_ML_LNG1:
            if (record->event.pressed) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
                keyball_escape_mouse_layer();
#endif
                pending_lang_key = KC_LNG1;
            }
            return false;
        case MY_ANI:
            if (record->event.pressed) {
                my_anim = (my_anim_mode_t)((my_anim + 1) % MY_ANIM_COUNT);
                if (my_anim == MY_ANIM_OFF) {
                    layer_state_set_user(layer_state);
                } else {
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                }
            }
            return false;
        case MY_DT_PRNT:
            if (record->event.pressed) {
#ifdef SEND_STRING_ENABLE
                const char *s = get_u16_str(QS.tapping_term, ' ');
                while (*s == ' ') s++;  // skip get_u16_str's left padding
                send_string(s);
#endif
            }
            return false;
        case MY_DT_UP:
            if (record->event.pressed) {
                uint16_t v = QS.tapping_term + DT_ADJUST_STEP;
                qmk_settings_set(QS_QSID_TAPPING_TERM, &v, sizeof(v));
            }
            return false;
        case MY_DT_DOWN:
            if (record->event.pressed) {
                uint16_t v = QS.tapping_term - DT_ADJUST_STEP;
                qmk_settings_set(QS_QSID_TAPPING_TERM, &v, sizeof(v));
            }
            return false;
        case LNG1_TO0:
            if (record->event.pressed) {
                tap_code(KC_LNG1);
                layer_move(0);
            }
            return false;
        case LNG2_TO0:
            if (record->event.pressed) {
                tap_code(KC_LNG2);
                layer_move(0);
            }
            return false;
        case RGB_MOD:
            if (record->event.pressed) {
                if (my_anim != MY_ANIM_OFF) {
                    // inside custom anims: advance or exit back to RGBLIGHT mode 1
                    my_anim_mode_t next = (my_anim_mode_t)(my_anim + 1);
                    if (next >= MY_ANIM_COUNT) {
                        my_anim = MY_ANIM_OFF;
                        layer_state_set_user(layer_state);  // RGBLIGHT already STATIC
                    } else {
                        my_anim = next;
                    }
                } else if (rgblight_get_mode() >= RGBLIGHT_MODES) {
                    // last RGBLIGHT mode → enter first custom anim
                    my_anim = MY_ANIM_PLASMA;
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                } else {
                    rgblight_step_noeeprom();
                }
            }
            return false;
        case RGB_RMOD:
            if (record->event.pressed) {
                if (my_anim != MY_ANIM_OFF) {
                    // inside custom anims: go back or exit to last RGBLIGHT mode
                    if (my_anim == MY_ANIM_PLASMA) {
                        my_anim = MY_ANIM_OFF;
                        layer_state_set_user(layer_state);
                        rgblight_mode_noeeprom(RGBLIGHT_MODES);
                    } else {
                        my_anim = (my_anim_mode_t)(my_anim - 1);
                    }
                } else if (rgblight_get_mode() <= 1) {
                    // first RGBLIGHT mode → enter last custom anim
                    my_anim = (my_anim_mode_t)(MY_ANIM_COUNT - 1);
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                } else {
                    rgblight_step_reverse_noeeprom();
                }
            }
            return false;
    }
    return true;
}

#if defined(SPLIT_KEYBOARD)
// Runs only on master (see the "Mod-key LED color override" notes above).
// Diffs get_mods() against the pre-action snapshot taken in
// process_record_user to see whether this event changed the mod state, and
// if so, attributes the change to whichever physical hand the key sits on.
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods_after = get_mods();
    uint8_t changed     = mods_before_event ^ mods_after;
    if (!changed) return;

    uint8_t turned_on  = changed & mods_after;
    uint8_t turned_off = changed & mods_before_event;

    bool is_own_row = record->event.key.row >= thisHand &&
                       record->event.key.row <  thisHand + MY_ROWS_PER_HAND;
    if (is_own_row) {
        own_side_mods |= turned_on;
    } else {
        peer_side_mods |= turned_on;
    }
    own_side_mods  &= (uint8_t)~turned_off;
    peer_side_mods &= (uint8_t)~turned_off;
}
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_universal(
    KC_Q , KC_W , KC_E , KC_R , KC_T ,                            KC_Y , KC_U , KC_I , KC_O , KC_P ,
    LALT_T(KC_A) , LGUI_T(KC_S) , LCTL_T(KC_D) , LSFT_T(KC_F) , KC_G ,                            KC_H , RSFT_T(KC_J) , RCTL_T(KC_K) , RGUI_T(KC_L) , RALT_T(KC_SCLN) ,
    KC_Z , KC_X , KC_C , KC_V , KC_B ,                            KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH ,
    KC_LCTL , KC_LALT , KC_LGUI , LT(5,KC_SPC) , LT(2,KC_SPC) , LT(3,KC_MINS) ,      LT(4,KC_ENT) , LCTL_T(KC_BSPC) , LSFT_T(KC_LNG2) , KC_RALT , KC_RGUI , KC_ESC
  ),

  [1] = LAYOUT_universal(
    KC_NO , LGUI(KC_X) , LGUI(KC_C) , LGUI(KC_V) , LGUI(KC_W) ,                            RGB_TOG , LNG2_TO0 , LNG1_TO0 , KC_NO , KC_DEL ,
    KC_LALT , KC_LGUI , KC_LCTL , KC_LSFT , KC_NO ,                            LCTL(KC_N) , KC_BTN1 , MO(3) , KC_BTN2 , KC_NO ,
    KC_NO , LCTL(KC_X) , LCTL(KC_C) , LCTL(KC_V) , LCTL(KC_W) ,                            LGUI(KC_N) , LCTL(KC_LEFT) , LCTL(KC_UP) , LCTL(KC_RGHT) , KC_NO ,
    KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,      KC_TRNS , KC_TRNS , KC_NO , KC_RALT , KC_RGUI , KC_NO
  ),

  [2] = LAYOUT_universal(
    KC_TAB , LGUI(KC_X) , LGUI(KC_C) , LGUI(KC_V) , KC_NO ,                            LGUI(KC_W) , LCTL(KC_PGUP) , KC_UP , LCTL(KC_PGDN) , LGUI(KC_T) ,
    KC_LALT , KC_LGUI , KC_LCTL , KC_LSFT , LSFT(KC_SPC) ,                            KC_PGUP , KC_LEFT , KC_DOWN , KC_RGHT , KC_NO ,
    KC_NO , LCTL(KC_X) , LCTL(KC_C) , LCTL(KC_V) , KC_NO ,                            KC_PGDN , LCTL(KC_LEFT) , LCTL(KC_UP) , LCTL(KC_RGHT) , KC_NO ,
    LGUI(KC_PPLS) , LGUI(KC_P0) , LGUI(KC_PMNS) , KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS , KC_TRNS , KC_NO , KC_NO , LGUI(KC_0) , KC_DEL
  ),

  [3] = LAYOUT_universal(
    RGB_TOG , AML_TO , AML_I50 , AML_D50 , MY_ANI ,                            MY_DT_DOWN , MY_DT_UP , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD , RGB_HUI , RGB_SAI , RGB_VAI , KBC_SAVE ,                            KBC_SAVE , KC_NO , KC_NO , KC_NO , KC_NO ,
    RGB_RMOD , RGB_HUD , RGB_SAD , RGB_VAD , KC_NO ,                            CPI_D1K , CPI_D100 , CPI_I100 , CPI_I1K , KBC_SAVE ,
    QK_BOOT , KBC_RST , KC_NO , KC_NO , KC_NO , KC_NO ,      KC_LNG2 , KC_LNG1 , KC_NO , KC_NO , KBC_RST , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
    KC_F6 , KC_F7 , KC_F8 , KC_F9 , KC_F10 ,                            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
    KC_F11 , KC_F12 , KC_NO , KC_NO , KC_NO ,                            KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,
    KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,      KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO
  ),

  [5] = LAYOUT_universal(
    KC_1 , KC_2 , KC_3 , KC_4 , KC_5 ,                            KC_6 , KC_7 , KC_8 , KC_9 , KC_0 ,
    LSFT(KC_1) , LSFT(KC_2) , LSFT(KC_3) , LSFT(KC_4) , LSFT(KC_5) ,                            LSFT(KC_6) , LSFT(KC_7) , LSFT(KC_8) , LSFT(KC_9) , LSFT(KC_0) ,
    LSFT(KC_MINS) , LSFT(KC_EQL) , LSFT(KC_BSLS) , KC_LBRC , KC_RBRC ,                            LSFT(KC_GRV) , KC_EQL , KC_NUBS , KC_LBRC , KC_RBRC ,
    LSFT(KC_QUOT) , KC_QUOT , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS , KC_TRNS , KC_NO , KC_NO , KC_NO , KC_GRV
  ),

  [6] = LAYOUT_universal(
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                            KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                            KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                            KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
  ),

};
// clang-format on

// Override weak function from keyball.c to preserve division remainder across
// report cycles. The original discards the remainder each cycle, causing a
// dead zone at the start of every scroll gesture.
//
// (Also tried: HID Resolution Multiplier / hi-res scroll here, and a
// report-rate throttle before that, both aimed at the Obsidian scroll issue
// documented below. Neither helped — hi-res scroll in particular made
// scrolling wildly oversensitive, most likely because macOS doesn't honor
// the Resolution Multiplier feature report, so it read the inflated raw
// values as whole clicks instead of fractional ones. Reverted back to the
// plain version; see config.h for the revert note.)
void keyball_on_apply_motion_to_mouse_scroll(report_mouse_t *report, report_mouse_t *output, bool is_left) {
    static int16_t rem_h = 0;
    static int16_t rem_v = 0;

    int16_t div = 1 << (keyball_get_scroll_div() - 1);
    int16_t x   = report->x + rem_h;
    int16_t y   = report->y + rem_v;
    int16_t qx  = x / div;
    int16_t qy  = y / div;
    rem_h = x - qx * div;
    rem_v = y - qy * div;

    int8_t cx = qx > 127 ? 127 : qx < -127 ? -127 : (int8_t)qx;
    int8_t cy = qy > 127 ? 127 : qy < -127 ? -127 : (int8_t)qy;

    output->h = -cx;
    output->v = cy;
    if (is_left) {
        output->h = -output->h;
        output->v = -output->v;
    }

    // Scroll-axis snap (SSNP_VRT/SSNP_HOR/SSNP_FRE), lost when this function
    // fully replaced keyball.c's original (which had this block after its
    // own h/v computation). Without it, scrollsnap_mode changes correctly
    // but scrolling always stays free/both-axis, and some apps (Electron
    // among others) mishandle simultaneous h+v wheel input.
#if KEYBALL_SCROLLSNAP_ENABLE == 2
    switch (keyball_get_scrollsnap_mode()) {
        case KEYBALL_SCROLLSNAP_MODE_VERTICAL:
            output->h = 0;
            break;
        case KEYBALL_SCROLLSNAP_MODE_HORIZONTAL:
            output->v = 0;
            break;
        default:
            break;
    }
#endif
}

// Pointer movement dead zone + software velocity scale.
//
// Background: on RP2040 (vs Pro Micro / ATmega32U4) the cursor feels less responsive
// at the same physical CPI, probably due to faster split-sync draining the sensor's
// burst register before sufficient motion accumulates. The typical workaround is to
// raise CPI, but high CPI amplifies keystroke-vibration noise and triggers AML.
//
// Better approach: keep physical CPI low (fewer vibration counts) and compensate with
// a software multiplier applied here — before the HID report is sent and before AML
// sees the report. AML thus receives dead-zone-filtered, unscaled counts, so it is
// not affected by the speed boost.
//
// Tune TRACKBALL_DEADZONE  : counts below which a report is treated as vibration noise.
// Tune MOVE_SCALE_NUM/DEN  : software cursor speed multiplier.
//   Pair with KEYBALL_CPI_DEFAULT in config.h so that
//   (physical CPI) × (MOVE_SCALE_NUM / MOVE_SCALE_DEN) ≈ desired effective CPI.
//   Example: 1000 CPI × 11/10 = 1100 effective CPI.
// Tune AXIS_SNAP_RATIO      : when one axis >= N × the other, zero the weaker axis.
//   Prevents diagonal drift when rolling nominally straight.
//   4 means a 4:1 or stronger imbalance triggers the snap; pure diagonals (2:1, 3:2) pass.
#define TRACKBALL_DEADZONE 1   // suppress only true zero; mag≥1 passes
#define MOVE_SCALE_NUM     11
#define MOVE_SCALE_DEN     7
#define AXIS_SNAP_RATIO    4

static inline int8_t clamp8(int16_t v) {
    return v > 127 ? 127 : v < -127 ? -127 : (int8_t)v;
}

void keyball_on_apply_motion_to_mouse_move(report_mouse_t *report, report_mouse_t *output, bool is_left) {
    // Indexed by side [0=left, 1=right] so the no-ball side's reset never
    // contaminates the ball side's accumulator.  Without this,
    // pointing_device_task_combined_kb calls this function twice per frame
    // (once per keyboard half), and the no-ball call (x=0,y=0) always hits
    // the else-branch and wipes the shared rem_x/rem_y before the ball call.
    static int16_t rem_x[2] = {0, 0};
    static int16_t rem_y[2] = {0, 0};
    uint8_t side = is_left ? 0 : 1;

    int16_t x   = report->x;
    int16_t y   = report->y;
    int16_t abx = x < 0 ? -x : x;
    int16_t aby = y < 0 ? -y : y;
    int16_t mag = abx + aby;

    if (mag >= TRACKBALL_DEADZONE) {
        // Axis snap: when one axis strongly dominates, suppress the weaker one.
        if      (abx >= AXIS_SNAP_RATIO * aby) { y = 0; rem_y[side] = 0; }
        else if (aby >= AXIS_SNAP_RATIO * abx) { x = 0; rem_x[side] = 0; }

        // Fixed-point scaling with per-side remainder carry-over across frames.
        int32_t sx = (int32_t)x * MOVE_SCALE_NUM + rem_x[side];
        int32_t sy = (int32_t)y * MOVE_SCALE_NUM + rem_y[side];
        int16_t ox = (int16_t)(sx / MOVE_SCALE_DEN);
        int16_t oy = (int16_t)(sy / MOVE_SCALE_DEN);
        rem_x[side] = (int16_t)(sx - (int32_t)ox * MOVE_SCALE_DEN);
        rem_y[side] = (int16_t)(sy - (int32_t)oy * MOVE_SCALE_DEN);
        output->x = clamp8(ox);
        output->y = clamp8(oy);
    } else {
        rem_x[side] = 0;
        rem_y[side] = 0;
    }
}

void keyboard_post_init_user(void) {
    dprintf("is_master: %d\n", is_keyboard_master());
    if (!is_keyboard_master()) {
        transaction_register_rpc(MY_LAYER_SYNC, layer_sync_handler);
        return;
    }
    set_auto_mouse_layer(1);
    set_auto_mouse_enable(true);
    // QS.tapping_term (quantum/qmk_settings.c) is already loaded from EEPROM
    // by qmk_settings_init(), which runs earlier in keyboard_setup() — nothing
    // to load here.
}

layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    keyball_handle_auto_mouse_layer_change(state); // ← これを追加
  #endif
    // Layer 3 のときスクロールモード ON
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    // 現在の明るさを維持しつつレイヤーで色を変える（Mod押下中はそちらを優先）
    if (!mod_led_active && my_anim == MY_ANIM_OFF) {
        rgblight_sethsv_noeeprom(my_layer_hue(get_highest_layer(state)), 255, rgblight_get_val());
    }

    return state;
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"

// Right-justify unsigned 16-bit value in a 4-char space-padded field.
static void oled_write_num4(uint16_t n) {
    char    buf[5] = "    ";
    uint8_t i      = 4;
    buf[i]         = '\0';
    if (n == 0) {
        buf[--i] = '0';
    } else {
        while (n > 0 && i > 0) {
            buf[--i] = '0' + (n % 10);
            n /= 10;
        }
    }
    oled_write(buf, false);
}

// Lower nibble of x as a hex digit.
static char nibble_hex(uint8_t x) {
    x &= 0x0f;
    return x < 10 ? x + '0' : x + 'a' - 10;
}

// Both OLEDs mounted vertically, connector pins at the bottom.
// OLED_ROTATION_270 renders text top-to-bottom in portrait orientation.
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// Bitmap tables – each byte: bit4=col0(left) … bit0=col4(right).
// Layer digits: 7 digits × 3 rows (compact, placed at OLED bottom).
// Bit layout per row: bit4=col0(left) … bit0=col4(right).
//   .###. = 14   .#.#. = 10   ..##. = 6   .##.. = 12   ...#. = 2   ..#.. = 4
static const uint8_t PROGMEM big_digit_data[7][3] = {
    {14, 10, 14},  // 0: .###. / .#.#. / .###.
    { 4,  4, 14},  // 1: ..#.. / ..#.. / .###.
    {14,  6, 12},  // 2: .###. / ..##. / .##..
    {14,  6, 14},  // 3: .###. / ..##. / .###.
    {10, 14,  2},  // 4: .#.#. / .###. / ...#.
    {12, 14,  6},  // 5: .##.. / .###. / ..##.
    {14, 12, 14},  // 6: .###. / .##.. / .###.
};

// Layer digits: 7 digits × 5 rows (large, for slave OLED).
//   #...# = 17   ####. = 30   ##### = 31   #.... = 16   ....# = 1
static const uint8_t PROGMEM big_digit_data5[7][5] = {
    {14, 17, 17, 17, 14},  // 0: .###. / #...# / #...# / #...# / .###.
    {12,  4,  4,  4, 14},  // 1: .##.. / ..#.. / ..#.. / ..#.. / .###.
    {14,  1,  6, 16, 31},  // 2: .###. / ....# / ..##. / #.... / #####
    {14,  1,  6,  1, 14},  // 3: .###. / ....# / ..##. / ....# / .###.
    {17, 17, 31,  1,  1},  // 4: #...# / #...# / ##### / ....# / ....#
    {31, 16, 30,  1, 14},  // 5: ##### / #.... / ####. / ....# / .###.
    {14, 16, 30, 17, 14},  // 6: .###. / #.... / ####. / #...# / .###.
};

// Renders a 5-wide bitmap from PROGMEM over `rows` display rows.
// Blank rows (data byte = 0) are never inverted, keeping them dark regardless of pressed.
static void oled_write_big_bitmap(const uint8_t *data, uint8_t rows, bool pressed) {
    for (uint8_t r = 0; r < rows; r++, data++) {
        uint8_t b = pgm_read_byte(data);
        bool inv = pressed && b;
        uint8_t m = 0x10;
        for (uint8_t c = 0; c < 5; c++) {
            oled_write_char(b & m ? '#' : ' ', inv);
            m >>= 1;
        }
    }
}


// 5-wide × 5-row mod letter bitmaps (used when 1-2 mods active, 10 rows available).
static const uint8_t PROGMEM big_mod_C5[5] = {14, 16, 16, 16, 14}; // .###./#..../#..../#..../.###.
static const uint8_t PROGMEM big_mod_S5[5] = {15, 16, 14,  1, 30}; // .####/#..../.###./....#/####.
static const uint8_t PROGMEM big_mod_A5[5] = { 4, 10, 31, 17, 17}; // ..#../.#.#./#####/#...#/#...#
static const uint8_t PROGMEM big_mod_G5[5] = {14, 16, 19, 17, 15}; // .###./#..../#..##/#...#/.####

// 5-wide × 3-row mod letter bitmaps (compact, used when 3-4 mods active).
static const uint8_t PROGMEM big_mod_C3[3] = {14, 16, 14}; // .###./#..../.###.
static const uint8_t PROGMEM big_mod_S3[3] = {30, 14, 15}; // ####./.###./.####
static const uint8_t PROGMEM big_mod_A3[3] = { 4, 31, 17}; // ..#../#####/#...#
static const uint8_t PROGMEM big_mod_G3[3] = {14, 19, 15}; // .###./#..##/.####

// ── Master OLED – key / ball / layer (portrait 5 chars/row) ──────────────────
// Note: writing exactly 5 chars auto-wraps to the next row via oled_advance_char().
// Do NOT call oled_advance_page() after a 5-char write — it would skip an extra row.

void oledkit_render_info_user(void) {
    // Row 0: key position  "R?C? "
    oled_write_char('R', false);
    oled_write_char(nibble_hex(keyball.last_pos.row), false);
    oled_write_char('C', false);
    oled_write_char(nibble_hex(keyball.last_pos.col), false);
    oled_write_char(' ', false);

    // Row 1: keycode  "K??  "
    oled_write_char('K', false);
    oled_write_char(nibble_hex(keyball.last_kc >> 4), false);
    oled_write_char(nibble_hex(keyball.last_kc), false);
    oled_write_P(PSTR("  "), false);

    // Row 2: pressing keys (always exactly 5 chars)
    for (uint8_t i = 0; i < 5; i++) oled_write_char(keyball.pressing_keys[i], false);

    // Rows 3-4: ball x, y  "x NNN" / "y NNN"
#define WB(label, val) do { \
    int8_t _v = (val); \
    oled_write_char((label), false); \
    oled_write_num4((uint16_t)(_v < 0 ? -(int)_v : (int)_v)); \
} while (0)
    WB('x', keyball.last_mouse.x);
    WB('y', keyball.last_mouse.y);
#undef WB

    // Row 5: CPI  "CNNNN"
    oled_write_char('C', false);
    oled_write_num4(keyball_get_cpi());

    // Row 6: AML status
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    if (!get_auto_mouse_enable()) {
        oled_write_P(PSTR("AmOff"), false);
    } else if (layer_state_is(AUTO_MOUSE_DEFAULT_LAYER)) {
        oled_write_P(PSTR("Am:AC"), false);
    } else {
        oled_write_P(PSTR("Am:On"), false);
    }
#endif

    // Row 7: tapping term  "T NNN"
    oled_write_char('T', false);
    oled_write_num4(QS.tapping_term);

    // Rows 8-10: blank (former MOD rows removed)
    oled_write_P(PSTR("               "), false);

    // Rows 11-15: large 5-row layer digit (same style as slave OLED)
    {
        uint8_t l = get_highest_layer(layer_state);
        if (l < 7) {
            oled_write_big_bitmap(big_digit_data5[l], 5, false);
        } else {
            oled_write_P(PSTR("                         "), false);
        }
    }
}

// ── Slave OLED – active mod letters (top) + layer digit (bottom) ─────────────
// Rows 0-9:  active mod letters (10 rows); Div:N when no mods pressed.
//   1-2 mods → 5 rows each   3-4 mods → 10/n rows each (compact)
// Row 10:    blank separator (implicit via oled_clear + oled_set_cursor).
// Rows 11-15: large 5-row layer digit.
void oledkit_render_logo_user(void) {
    oled_clear();

    // Rows 0-9: active mod letters.
    // combined = L|R for each mod: bit0=Ctrl bit1=Shift bit2=Alt bit3=GUI
    uint8_t cm = (slave_mods | (slave_mods >> 4)) & 0x0F;
    if (cm == 0) {
        oled_write_P(PSTR("Div:"), false);
        oled_write_char('0' + keyball_get_scroll_div(), false);
    } else {
        uint8_t n    = (uint8_t)__builtin_popcount(cm);
        uint8_t rows = (n <= 2) ? 5 : (10 / n);
        static const uint8_t * const mod5[4] = {big_mod_C5, big_mod_S5, big_mod_A5, big_mod_G5};
        static const uint8_t * const mod3[4] = {big_mod_C3, big_mod_S3, big_mod_A3, big_mod_G3};
        static const uint8_t mod_bit[4]      = {0x01, 0x02, 0x04, 0x08};
        for (uint8_t i = 0; i < 4; i++) {
            if (cm & mod_bit[i]) {
                oled_write_big_bitmap((n <= 2) ? mod5[i] : mod3[i], rows, false);
            }
        }
    }

    // Rows 11-15: large 5-row layer digit, fixed at bottom via oled_set_cursor.
    oled_set_cursor(0, 11);
    uint8_t l = slave_layer;
    if (l < 7) {
        oled_write_big_bitmap(big_digit_data5[l], 5, false);
    } else {
        oled_write_P(PSTR("                         "), false);
    }
}
#endif

// Combos are configured entirely through Vial's Combo editor (GUI-editable,
// stored in EEPROM by quantum/vial.c) — no keymap-local key_combos[] table.
void process_combo_event(uint16_t combo_index, bool pressed) {
    if (pressed) {
        dprintf("combo fired: %u\n", combo_index);
    }
}
