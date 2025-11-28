#include QMK_KEYBOARD_H

// Custom keycodes for pre-compiled macros
// Using QK_KB_0 (USER00) as base for VIAL compatibility
enum custom_keycodes {
    MD_H1 = QK_KB_0,
    MD_H2,
    MD_H3,
    BOLD,
    ITALIC,
    CLR_FMT,
    CUT_LINE_START,
    CUT_LINE_END,
    CUT_WORD_PREV,
    CUT_WORD_NEXT,
    CUT_PARA,
    CUT_PARA_END,
    PASTE,
    OBS_QUOTE,
    OBS_PAREN,
    OBS_EMDASH,
    WRAP_QUOTE,
    WRAP_PAREN,
    GDOC_H1,
    GDOC_H2,
    GDOC_H3,
    GDOC_NORMAL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,            KC_PDOT, KC_PENT
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______,          _______, _______
    ),

    [2] = LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD,
        RGB_SAI, RGB_SAD, RGB_VAI,
        RGB_VAD, RGB_SPI, RGB_SPD, _______,
        _______, _______, _______,
        _______,          _______, QK_BOOT
    ),

    [3] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______,          _______, _______
    ),

    [4] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______,          _______, _______
    ),

    [5] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______,          _______, _______
    ),

    [6] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______,          _______, _______
    ),

    [7] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______,          _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {

            // ========== MARKDOWN HEADERS ==========
            case MD_H1:
                tap_code(KC_HOME);
                SEND_STRING("# ");
                return false;

            case MD_H2:
                tap_code(KC_HOME);
                SEND_STRING("## ");
                return false;

            case MD_H3:
                tap_code(KC_HOME);
                SEND_STRING("### ");
                return false;

            // ========== TEXT FORMATTING ==========
            case BOLD:
                register_code(KC_LGUI);
                tap_code(KC_B);
                unregister_code(KC_LGUI);
                return false;

            case ITALIC:
                register_code(KC_LGUI);
                tap_code(KC_I);
                unregister_code(KC_LGUI);
                return false;

            case CLR_FMT:
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_LCTL);
                tap_code(KC_K);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
                return false;

            // ========== LINE OPERATIONS ==========
            case CUT_LINE_START:
                register_code(KC_LSFT);
                tap_code(KC_HOME);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            case CUT_LINE_END:
                register_code(KC_LSFT);
                tap_code(KC_END);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            // ========== WORD OPERATIONS ==========
            case CUT_WORD_PREV:
                register_code(KC_LSFT);
                register_code(KC_LALT);
                tap_code(KC_UP);
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            case CUT_WORD_NEXT:
                register_code(KC_LSFT);
                register_code(KC_LALT);
                tap_code(KC_DOWN);
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            // ========== PARAGRAPH OPERATIONS ==========
            case CUT_PARA:
                register_code(KC_LALT);
                tap_code(KC_UP);
                unregister_code(KC_LALT);
                register_code(KC_LSFT);
                register_code(KC_LALT);
                tap_code(KC_DOWN);
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            case CUT_PARA_END:
                register_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_DOWN);
                unregister_code(KC_LSFT);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            // ========== CLIPBOARD OPERATIONS ==========
            case PASTE:
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                return false;

            // ========== OBSIDIAN WRAP OPERATIONS ==========
            case OBS_QUOTE:
                SEND_STRING("\"");
                return false;

            case OBS_PAREN:
                SEND_STRING("(");
                return false;

            case OBS_EMDASH:
                SEND_STRING(" ");
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_MINUS);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                SEND_STRING(" ");
                return false;

            // ========== CUT AND WRAP OPERATIONS NON-OBSIDIAN ==========
            case WRAP_QUOTE:
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING("\"");
                wait_ms(150);
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING("\" ");
                return false;

            case WRAP_PAREN:
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING("(");
                wait_ms(150);
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING(") ");
                return false;

            // ========== GOOGLE DOCS FORMATTING ==========
            case GDOC_H1:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_1);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;

            case GDOC_H2:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_2);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;

            case GDOC_H3:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_3);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;

            case GDOC_NORMAL:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_0);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
        }
    }
    return true;
}