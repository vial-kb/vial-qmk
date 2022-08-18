#include "qmk_settings.h"

#include <stddef.h>
#include <string.h>

#include "progmem.h"
#include "dynamic_keymap.h"
#include "process_auto_shift.h"
#include "mousekey.h"
#include "process_combo.h"
#include "action_tapping.h"

static int eeprom_settings_get(const qmk_settings_proto_t *proto, void *setting, size_t maxsz);
static int eeprom_settings_set(const qmk_settings_proto_t *proto, const void *setting, size_t maxsz);
static int magic_settings_get(const qmk_settings_proto_t *proto, void *setting, size_t maxsz);
static int magic_settings_set(const qmk_settings_proto_t *proto, const void *setting, size_t maxsz);

qmk_settings_t QS;

#define DECLARE_SETTING_NOTIFY(id, _get, _set, _notify)  { .qsid=id, .get=_get, .set=_set, .notify=_notify }
#define DECLARE_SETTING(id, _get, _set) DECLARE_SETTING_NOTIFY(id, _get, _set, NULL)
#define DECLARE_STATIC_SETTING_NOTIFY(id, field, notify_)  { .qsid=id, .ptr=&QS.field, .sz=sizeof(QS.field), .get=eeprom_settings_get, .set=eeprom_settings_set, .notify=notify_ }
#define DECLARE_STATIC_SETTING(id, field) DECLARE_STATIC_SETTING_NOTIFY(id, field, NULL)

static void auto_shift_timeout_apply(void) {
    set_autoshift_timeout(QS.auto_shift_timeout);
}

#ifdef MOUSEKEY_ENABLE
static void mousekey_apply(void) {
    mk_delay = QS.mousekey_delay / 10;
    mk_interval = QS.mousekey_interval;
    mk_max_speed = QS.mousekey_max_speed;
    mk_time_to_max = QS.mousekey_time_to_max;
    mk_wheel_delay = QS.mousekey_wheel_delay / 10;
    mk_wheel_interval    = QS.mousekey_wheel_interval;
    mk_wheel_max_speed   = QS.mousekey_wheel_max_speed;
    mk_wheel_time_to_max = QS.mousekey_wheel_time_to_max;
}
#endif

static const qmk_settings_proto_t protos[] PROGMEM = {
   DECLARE_STATIC_SETTING(1, grave_esc_override),
   DECLARE_STATIC_SETTING(2, combo_term),
   DECLARE_STATIC_SETTING(3, auto_shift),
   DECLARE_STATIC_SETTING_NOTIFY(4, auto_shift_timeout, auto_shift_timeout_apply),
   DECLARE_STATIC_SETTING(5, osk_tap_toggle),
   DECLARE_STATIC_SETTING(6, osk_timeout),
   DECLARE_STATIC_SETTING(7, tapping_term),
   DECLARE_STATIC_SETTING(8, tapping),
#ifdef MOUSEKEY_ENABLE
   DECLARE_STATIC_SETTING_NOTIFY(9, mousekey_delay, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(10, mousekey_interval, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(11, mousekey_move_delta, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(12, mousekey_max_speed, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(13, mousekey_time_to_max, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(14, mousekey_wheel_delay, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(15, mousekey_wheel_interval, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(16, mousekey_wheel_max_speed, mousekey_apply),
   DECLARE_STATIC_SETTING_NOTIFY(17, mousekey_wheel_time_to_max, mousekey_apply),
#endif
   DECLARE_STATIC_SETTING(18, tap_code_delay),
   DECLARE_STATIC_SETTING(19, tap_hold_caps_delay),
   DECLARE_STATIC_SETTING(20, tapping_toggle),
   DECLARE_SETTING(21, magic_settings_get, magic_settings_set),
};

static void eeprom_settings_load(void) {
    for (size_t i = 0; i < sizeof(qmk_settings_t); ++i) {
        uint8_t byte;
        byte = dynamic_keymap_get_qmk_settings(i);
        memcpy((char*)&QS + i, &byte, 1);
    }
}

static void eeprom_settings_save(void) {
    for (size_t i = 0; i < sizeof(qmk_settings_t); ++i) {
        uint8_t old_byte, new_byte;
        old_byte = dynamic_keymap_get_qmk_settings(i);
        memcpy(&new_byte, (char*)&QS + i, 1);
        if (old_byte != new_byte)
            dynamic_keymap_set_qmk_settings(i, new_byte);
    }
}

static int eeprom_settings_get(const qmk_settings_proto_t *proto, void *setting, size_t maxsz) {
    uint16_t sz = pgm_read_word(&proto->sz);
    if (sz > maxsz)
        return -1;
    memcpy(setting, pgm_read_ptr(&proto->ptr), sz);
    return 0;
}

static int eeprom_settings_set(const qmk_settings_proto_t *proto, const void *setting, size_t maxsz) {
    uint16_t sz = pgm_read_word(&proto->sz);
    if (pgm_read_word(&proto->sz) > maxsz)
        return -1;
    memcpy(pgm_read_ptr(&proto->ptr), setting, sz);
    eeprom_settings_save();
    return 0;
}

static int magic_settings_get(const qmk_settings_proto_t *proto, void *setting, size_t maxsz) {
    uint32_t flags;

    if (maxsz < sizeof(flags))
        return -1;

    flags = \
        (keymap_config.swap_control_capslock << 0) |
        (keymap_config.capslock_to_control << 1) |
        (keymap_config.swap_lalt_lgui << 2) |
        (keymap_config.swap_ralt_rgui << 3) |
        (keymap_config.no_gui << 4) |
        (keymap_config.swap_grave_esc << 5) |
        (keymap_config.swap_backslash_backspace << 6) |
        (keymap_config.nkro << 7) |
        (keymap_config.swap_lctl_lgui << 8) |
        (keymap_config.swap_rctl_rgui << 9) |
        0;

    memcpy(setting, &flags, sizeof(flags));
    return 0;
}

static int magic_settings_set(const qmk_settings_proto_t *proto, const void *setting, size_t maxsz) {
    uint32_t flags;

    if (maxsz < sizeof(flags))
        return -1;

    memcpy(&flags, setting, sizeof(flags));

    /* must call clear_keyboard for the NKRO setting to not cause stuck keys */
    clear_keyboard();
    keymap_config.swap_control_capslock = !!(flags & (1 << 0));
    keymap_config.capslock_to_control = !!(flags & (1 << 1));
    keymap_config.swap_lalt_lgui = !!(flags & (1 << 2));
    keymap_config.swap_ralt_rgui = !!(flags & (1 << 3));
    keymap_config.no_gui = !!(flags & (1 << 4));
    keymap_config.swap_grave_esc = !!(flags & (1 << 5));
    keymap_config.swap_backslash_backspace = !!(flags & (1 << 6));
    keymap_config.nkro = !!(flags & (1 << 7));
    keymap_config.swap_lctl_lgui = !!(flags & (1 << 8));
    keymap_config.swap_rctl_rgui = !!(flags & (1 << 9));
    eeconfig_update_keymap(keymap_config.raw);

    return 0;
}

void qmk_settings_init(void) {
    eeprom_settings_load();
    /* execute all callbacks to initialize the settings */
    for (size_t i = 0; i < sizeof(protos)/sizeof(*protos); ++i) {
        const qmk_settings_proto_t *proto = &protos[i];
        qmk_settings_notify_t notify = pgm_read_ptr(&proto->notify);
        if (notify)
            notify();
    }
}

void qmk_settings_reset(void) {
    QS.grave_esc_override = 0;
    QS.auto_shift = (
      0
#ifndef AUTO_SHIFT_DISABLED_AT_STARTUP
      | _QS_auto_shift_enable_bit
#endif
#ifdef AUTO_SHIFT_MODIFIERS
      | _QS_auto_shift_modifiers_bit
#endif
#ifdef NO_AUTO_SHIFT_SPECIAL
      | _QS_auto_shift_no_auto_shift_special_bit
#endif
#ifdef NO_AUTO_SHIFT_NUMERIC
      | _QS_auto_shift_no_auto_shift_numeric_bit
#endif
#ifdef NO_AUTO_SHIFT_ALPHA
      | _QS_auto_shift_no_auto_shift_alpha_bit
#endif
#ifdef AUTO_SHIFT_REPEAT
      | _QS_auto_shift_repeat_bit
#endif
#ifdef AUTO_SHIFT_NO_AUTO_REPEAT
      | _QS_auto_shift_no_auto_repeat_bit
#endif
    );
    QS.auto_shift_timeout = AUTO_SHIFT_TIMEOUT;
    QS.osk_tap_toggle = ONESHOT_TAP_TOGGLE;
    QS.osk_timeout = ONESHOT_TIMEOUT;

#ifdef MOUSEKEY_ENABLE
    QS.mousekey_delay = MOUSEKEY_DELAY;
    QS.mousekey_interval = MOUSEKEY_INTERVAL;
    QS.mousekey_move_delta = MOUSEKEY_MOVE_DELTA;
    QS.mousekey_max_speed = MOUSEKEY_MAX_SPEED;
    QS.mousekey_time_to_max = MOUSEKEY_TIME_TO_MAX;
    QS.mousekey_wheel_delay = MOUSEKEY_WHEEL_DELAY;
    QS.mousekey_wheel_interval = MOUSEKEY_WHEEL_INTERVAL;
    QS.mousekey_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
    QS.mousekey_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
#endif

    QS.combo_term = COMBO_TERM;
    QS.tapping_term = TAPPING_TERM;
    QS.tapping = 0;
    QS.tap_code_delay = TAP_CODE_DELAY;
    QS.tap_hold_caps_delay = TAP_HOLD_CAPS_DELAY;
    QS.tapping_toggle = TAPPING_TOGGLE;

    eeprom_settings_save();

    /* must call clear_keyboard for the NKRO setting to not cause stuck keys */
    clear_keyboard();
    keymap_config.raw = 0;
    keymap_config.oneshot_enable = 1;
    eeconfig_update_keymap(keymap_config.raw);

    /* to trigger all callbacks */
    qmk_settings_init();
}

void qmk_settings_query(uint16_t qsid_gt, void *buffer, size_t sz) {
    /* set all FFs, so caller can identify when all settings are retrieved by looking for an 0xFFFF entry */
    memset(buffer, 0xFF, sz);

    size_t buffer_offset = 0;
    for (size_t i = 0; i < sizeof(protos)/sizeof(*protos); ++i) {
        uint16_t qsid;

        /* if output buffer has no space left, bail out */
        if (buffer_offset + sizeof(qsid) > sz)
            break;

        qsid = pgm_read_word(&protos[i].qsid);
        if (qsid > qsid_gt) {
            memcpy((char*)buffer + buffer_offset, &qsid, sizeof(qsid));
            buffer_offset += sizeof(qsid);
        }
    }
}

static const qmk_settings_proto_t *find_setting(uint16_t qsid) {
    for (size_t i = 0; i < sizeof(protos)/sizeof(*protos); ++i)
        if (pgm_read_word(&protos[i].qsid) == qsid)
            return &protos[i];
    return NULL;
}

int qmk_settings_get(uint16_t qsid, void *setting, size_t maxsz) {
    const qmk_settings_proto_t *proto = find_setting(qsid);
    if (!proto)
        return -1;

    qmk_settings_get_t get = pgm_read_ptr(&proto->get);
    if (!get)
        return -1;

    return get(proto, setting, maxsz);
}

int qmk_settings_set(uint16_t qsid, const void *setting, size_t maxsz) {
    const qmk_settings_proto_t *proto = find_setting(qsid);
    if (!proto)
        return -1;

    qmk_settings_set_t set = pgm_read_ptr(&proto->set);
    if (!set)
        return -1;

    int ret = set(proto, setting, maxsz);
    if (ret != 0)
        return ret;

    qmk_settings_notify_t notify = pgm_read_ptr(&proto->notify);
    if (notify)
        notify();
    return 0;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping_term;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 1;
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 2;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 4;
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 8;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    return QS.combo_term;
}

bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AUTO_SHIFT_ALPHA:
            if (!QS_auto_shift_no_auto_shift_alpha) return true;
            break;
        case AUTO_SHIFT_NUMERIC:
            if (!QS_auto_shift_no_auto_shift_numeric) return true;
            break;
        case AUTO_SHIFT_SPECIAL:
            if (!QS_auto_shift_no_auto_shift_special) return true;
            break;
    }
    return false;
}

bool get_auto_shift_repeat(uint16_t keycode, keyrecord_t *record) {
    return QS_auto_shift_repeat;
}

bool get_auto_shift_no_auto_repeat(uint16_t keycode, keyrecord_t *record) {
    return QS_auto_shift_no_auto_repeat;
}
