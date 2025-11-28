
# Q6 Max Custom Keycodes

## Headers
0x5F80 = # Markdown H1
0x5F81 = ## Markdown H2  
0x5F82 = ### Markdown H3
0x5F92 = Google Docs H1
0x5F93 = Google Docs H2
0x5F94 = Google Docs H3

## Formatting
0x5F83 = Bold
0x5F84 = Italic
0x5F85 = Clear Format

## Editing  
0x5F86 = Cut to Line Start
0x5F87 = Cut to Line End
0x5F88 = Cut Previous Word
0x5F89 = Cut Next Word
0x5F8A = Cut Paragraph
0x5F8B = Cut to Para End

## Utility
0x5F8C = Paste
0x5F8D = Quote "
0x5F8E = Paren (
0x5F8F = Em Dash —
0x5F90 = Wrap in Quotes
0x5F91 = Wrap in Parens
0x5F95 = GDocs Clear Format

---

# D3lilahPad-18 Macro Reference

## Text Manipulation Macros

### Line Operations

- **M6**: Cut from cursor to start of line
- **M9**: Cut from cursor to end of line

### Word Operations

- **M7**: Select previous word and cut
- **M10**: Select next word and cut

### Paragraph Operations

- **M8**: Select current paragraph and cut
- **M11**: Select to end of paragraph and cut

### Cut and Wrap Operations

- **M16**: Cut selection and wrap in quotes ("selection")
- **M17**: Cut selection and wrap in parentheses (selection)

## Formatting Macros

### Markdown Headers (Obsidian)

- **M0**: Insert H1 header (# )
- **M1**: Insert H2 header (## )
- **M2**: Insert H3 header (### )

### Google Docs Headers

- **M18**: Apply Heading 1 style (Cmd+Alt+1)
- **M19**: Apply Heading 2 style (Cmd+Alt+2)
- **M20**: Apply Heading 3 style (Cmd+Alt+3)
- **M21**: Clear formatting/Normal text (Cmd+Alt+0)

### Text Formatting

- **M3**: Bold (Cmd+B)
- **M4**: Italic (Cmd+I)
- **M5**: Clear formatting (Obsidian) (Cmd+Shift+Ctrl+K)

## Utility Macros

### Basic Operations

- **M12**: Paste (Cmd+V)

### Text Insertion

- **M13**: Insert quotation mark (")
- **M14**: Insert opening parenthesis
- **M15**: Insert em dash with spaces ( — )

## Layer Design Philosophy

The macropad is designed with parallel functionality across layers:

- **OBSIDIAN layer**: Markdown-focused editing with direct text insertion
- **GDOCS layer**: Google Docs editing with style application via keyboard shortcuts
- Both layers share the same conceptual operations (H1, H2, H3) implemented differently for each environment

---

// Portable QMK Macro Library for Text Editing
// Compatible with VIA-enabled keyboards
// Author: joandelilah

#include QMK_KEYBOARD_H

// Custom keycodes starting at SAFE_RANGE to avoid conflicts
enum custom_keycodes {
    // === MARKDOWN HEADERS ===
    MC_MD_H1 = SAFE_RANGE,  // Markdown H1: Insert "# "
    MC_MD_H2,               // Markdown H2: Insert "## "
    MC_MD_H3,               // Markdown H3: Insert "### "
    
    // === TEXT FORMATTING ===
    MC_BOLD,                // Bold: Cmd+B
    MC_ITALIC,              // Italic: Cmd+I
    MC_CLEAR_FORMAT,        // Clear Formatting (Obsidian): Cmd+Shift+Ctrl+K
    
    // === LINE OPERATIONS ===
    MC_CUT_TO_START,        // Cut from cursor to start of line
    MC_CUT_TO_END,          // Cut from cursor to end of line
    
    // === WORD OPERATIONS ===
    MC_CUT_WORD_PREV,       // Select previous word and cut
    MC_CUT_WORD_NEXT,       // Select next word and cut
    
    // === PARAGRAPH OPERATIONS ===
    MC_CUT_PARA,            // Select current paragraph and cut
    MC_CUT_PARA_END,        // Select to end of paragraph and cut
    
    // === CLIPBOARD OPERATIONS ===
    MC_PASTE,               // Paste: Cmd+V
    
    // === TEXT INSERTION ===
    MC_QUOTE,               // Insert quotation mark
    MC_PAREN,               // Insert opening parenthesis
    MC_EM_DASH,             // Insert em dash with spaces
    
    // === CUT AND WRAP OPERATIONS ===
    MC_WRAP_QUOTE,          // Cut selection and wrap in quotes
    MC_WRAP_PAREN,          // Cut selection and wrap in parentheses
    
    // === GOOGLE DOCS FORMATTING ===
    MC_GDOC_H1,             // Google Docs H1: Cmd+Alt+1
    MC_GDOC_H2,             // Google Docs H2: Cmd+Alt+2
    MC_GDOC_H3,             // Google Docs H3: Cmd+Alt+3
    MC_GDOC_NORMAL,         // Google Docs Normal/Clear: Cmd+Alt+0
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Only process on key press, not release
    if (record->event.pressed) {
        switch (keycode) {
            
            // ========== MARKDOWN HEADERS ==========
            case MC_MD_H1:
                tap_code(KC_HOME);           // Move to start of line
                SEND_STRING("# ");           // Insert H1 marker
                return false;
                
            case MC_MD_H2:
                tap_code(KC_HOME);           // Move to start of line
                SEND_STRING("## ");          // Insert H2 marker
                return false;
                
            case MC_MD_H3:
                tap_code(KC_HOME);           // Move to start of line
                SEND_STRING("### ");         // Insert H3 marker
                return false;
            
            // ========== TEXT FORMATTING ==========
            case MC_BOLD:
                register_code(KC_LGUI);      // Hold Cmd
                tap_code(KC_B);              // Tap B
                unregister_code(KC_LGUI);    // Release Cmd
                return false;
                
            case MC_ITALIC:
                register_code(KC_LGUI);      // Hold Cmd
                tap_code(KC_I);              // Tap I
                unregister_code(KC_LGUI);    // Release Cmd
                return false;
                
            case MC_CLEAR_FORMAT:
                // Clear Formatting in Obsidian (Cmd+Shift+Ctrl+K)
                register_code(KC_LGUI);
                register_code(KC_LSHIFT);
                register_code(KC_LCTRL);
                tap_code(KC_K);
                unregister_code(KC_LCTRL);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LGUI);
                return false;
            
            // ========== LINE OPERATIONS ==========
            case MC_CUT_TO_START:
                // Select from cursor to start of line
                register_code(KC_LSHIFT);
                tap_code(KC_HOME);
                unregister_code(KC_LSHIFT);
                // Cut selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
                
            case MC_CUT_TO_END:
                // Select from cursor to end of line
                register_code(KC_LSHIFT);
                tap_code(KC_END);
                unregister_code(KC_LSHIFT);
                // Cut selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            
            // ========== WORD OPERATIONS ==========
            case MC_CUT_WORD_PREV:
                // Select previous word (Alt+Shift+Left)
                register_code(KC_LSHIFT);
                register_code(KC_LALT);
                tap_code(KC_UP);             // Note: Original uses UP for word selection
                unregister_code(KC_LALT);
                unregister_code(KC_LSHIFT);
                // Cut selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
                
            case MC_CUT_WORD_NEXT:
                // Select next word (Alt+Shift+Right)
                register_code(KC_LSHIFT);
                register_code(KC_LALT);
                tap_code(KC_DOWN);           // Note: Original uses DOWN for word selection
                unregister_code(KC_LALT);
                unregister_code(KC_LSHIFT);
                // Cut selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            
            // ========== PARAGRAPH OPERATIONS ==========
            case MC_CUT_PARA:
                // Move to start of paragraph
                register_code(KC_LALT);
                tap_code(KC_UP);
                unregister_code(KC_LALT);
                // Select to end of paragraph
                register_code(KC_LSHIFT);
                register_code(KC_LALT);
                tap_code(KC_DOWN);
                unregister_code(KC_LALT);
                unregister_code(KC_LSHIFT);
                // Cut selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
                
            case MC_CUT_PARA_END:
                // Select to end of paragraph (Cmd+Shift+Down)
                register_code(KC_LSHIFT);
                register_code(KC_LGUI);
                tap_code(KC_DOWN);
                unregister_code(KC_LSHIFT);
                tap_code(KC_X);              // Cut (X still held with Cmd)
                unregister_code(KC_LGUI);
                return false;
            
            // ========== CLIPBOARD OPERATIONS ==========
            case MC_PASTE:
                register_code(KC_LGUI);      // Hold Cmd
                tap_code(KC_V);              // Tap V
                unregister_code(KC_LGUI);    // Release Cmd
                return false;
            
            // ========== TEXT INSERTION ==========
            case MC_QUOTE:
                SEND_STRING("\"");           // Insert quotation mark
                return false;
                
            case MC_PAREN:
                SEND_STRING("(");            // Insert opening parenthesis
                return false;
                
            case MC_EM_DASH:
                SEND_STRING(" ");            // Space before
                // Em dash on macOS: Alt+Shift+Minus
                register_code(KC_LALT);
                register_code(KC_LSHIFT);
                tap_code(KC_MINUS);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LALT);
                SEND_STRING(" ");            // Space after
                return false;
            
            // ========== CUT AND WRAP OPERATIONS ==========
            case MC_WRAP_QUOTE:
                // Cut current selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                wait_ms(150);                // Wait for clipboard
                SEND_STRING("\"");           // Opening quote
                wait_ms(150);
                // Paste
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING("\" ");          // Closing quote + space
                return false;
                
            case MC_WRAP_PAREN:
                // Cut current selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                wait_ms(150);                // Wait for clipboard
                SEND_STRING("(");            // Opening paren
                wait_ms(150);
                // Paste
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING(") ");           // Closing paren + space
                return false;
            
            // ========== GOOGLE DOCS FORMATTING ==========
            case MC_GDOC_H1:
                // Apply Heading 1 style in Google Docs
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_1);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
                
            case MC_GDOC_H2:
                // Apply Heading 2 style in Google Docs
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_2);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
                
            case MC_GDOC_H3:
                // Apply Heading 3 style in Google Docs
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_3);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
                
            case MC_GDOC_NORMAL:
                // Apply Normal text style (clear formatting) in Google Docs
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_0);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
        }
    }
    return true;  // Process all other keycodes normally
}

/* VIA KEYCODE REFERENCE
 * When compiled with VIA, these custom keycodes will appear as:
 * 
 * MC_MD_H1        = 0x5F80
 * MC_MD_H2        = 0x5F81
 * MC_MD_H3        = 0x5F82
 * MC_BOLD         = 0x5F83
 * MC_ITALIC       = 0x5F84
 * MC_CLEAR_FORMAT = 0x5F85
 * MC_CUT_TO_START = 0x5F86
 * MC_CUT_TO_END   = 0x5F87
 * MC_CUT_WORD_PREV= 0x5F88
 * MC_CUT_WORD_NEXT= 0x5F89
 * MC_CUT_PARA     = 0x5F8A
 * MC_CUT_PARA_END = 0x5F8B
 * MC_PASTE        = 0x5F8C
 * MC_QUOTE        = 0x5F8D
 * MC_PAREN        = 0x5F8E
 * MC_EM_DASH      = 0x5F8F
 * MC_WRAP_QUOTE   = 0x5F90
 * MC_WRAP_PAREN   = 0x5F91
 * MC_GDOC_H1      = 0x5F92
 * MC_GDOC_H2      = 0x5F93
 * MC_GDOC_H3      = 0x5F94
 * MC_GDOC_NORMAL  = 0x5F95
 *
 * To use in VIA: Select a key, go to "Custom" tab, enter the hex code
 */

---

// Portable Tap Dance Layer Switching
// Can be combined with macro library for Q6 Max, Nuphy Halo96, etc.
// Author: joandelilah

#include QMK_KEYBOARD_H

// ========== TAP DANCE CONFIGURATION ==========

// Tap Dance keycodes - these will appear as TD(0), TD(1) in VIA
enum tap_dances {
    TD_LAYERS_LOW = 0,   // Layers 0-3 switcher
    TD_LAYERS_HIGH = 1,  // Layers 4-7 switcher
};

// ========== TAP DANCE HANDLERS ==========

// Handler for TD(0) - Switches between layers 0-3
void td_layers_low_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            layer_move(0);      // Single tap: Go to layer 0 (base layer)
            break;
        case 2:
            layer_invert(2);    // Double tap: Toggle layer 2
            break;
        case 3:
            layer_invert(1);    // Triple tap: Toggle layer 1
            break;
        case 4:
            layer_invert(3);    // Quad tap: Toggle layer 3
            break;
    }
}

// Handler for TD(1) - Switches between layers 4-7
void td_layers_high_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            layer_invert(4);    // Single tap: Toggle layer 4
            break;
        case 2:
            layer_invert(6);    // Double tap: Toggle layer 6
            break;
        case 3:
            layer_invert(5);    // Triple tap: Toggle layer 5
            break;
        case 4:
            layer_invert(7);    // Quad tap: Toggle layer 7
            break;
    }
}

// Optional reset functions (cleanup if needed)
void td_layers_low_reset(tap_dance_state_t *state, void *user_data) {
    // Add any cleanup code here if needed
}

void td_layers_high_reset(tap_dance_state_t *state, void *user_data) {
    // Add any cleanup code here if needed
}

// ========== TAP DANCE DEFINITIONS ==========
// This array defines all tap dances
tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYERS_LOW]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layers_low_finished, td_layers_low_reset),
    [TD_LAYERS_HIGH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layers_high_finished, td_layers_high_reset),
};

// ========== OPTIONAL: RULES.MK ADDITIONS ==========
/* 
 * Add this line to your rules.mk to enable tap dance:
 * TAP_DANCE_ENABLE = yes
 */

// ========== USAGE IN KEYMAP ==========
/*
 * In your keymap, use TD(TD_LAYERS_LOW) and TD(TD_LAYERS_HIGH)
 * or the shorter forms TD(0) and TD(1)
 * 
 * Example keymap usage:
 * 
 * const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 *     [0] = LAYOUT(
 *         KC_ESC,  KC_1,    KC_2,    KC_3,    TD(0),   TD(1),
 *         // ... rest of layout
 *     ),
 * };
 * 
 * In VIA, these will appear as:
 * - TD(0) for the low layers switcher
 * - TD(1) for the high layers switcher
 * 
 * You can place these tap dances on any key through VIA's interface.
 */

// ========== LAYER REFERENCE ==========
/*
 * Layer switching logic:
 * 
 * TD(0) - Low Layers:
 *   1 tap  = Go to layer 0 (base/default)
 *   2 taps = Toggle layer 2
 *   3 taps = Toggle layer 1  
 *   4 taps = Toggle layer 3
 * 
 * TD(1) - High Layers:
 *   1 tap  = Toggle layer 4
 *   2 taps = Toggle layer 6
 *   3 taps = Toggle layer 5
 *   4 taps = Toggle layer 7
 * 
 * Note: layer_move(0) sets layer 0 as the only active layer
 *       layer_invert(n) toggles layer n on/off
 */

// ========== CUSTOMIZATION NOTES ==========
/*
 * To adjust tap dance timing, add to config.h:
 * 
 * #define TAPPING_TERM 200     // Default is 200ms
 * #define TAPPING_TERM_PER_KEY // If you want different terms per key
 * 
 * For your setup, you used 250ms timeout in VIAL, so you might want:
 * #define TAPPING_TERM 250
 */

---

// Complete Portable Macro and Tap Dance Library
// For Q6 Max, Nuphy Halo96, and other QMK/VIA keyboards
// Author: joandelilah

#include QMK_KEYBOARD_H

// ========== CUSTOM KEYCODES ==========
enum custom_keycodes {
    // === MARKDOWN HEADERS ===
    MC_MD_H1 = SAFE_RANGE,  // Markdown H1: Insert "# "
    MC_MD_H2,               // Markdown H2: Insert "## "
    MC_MD_H3,               // Markdown H3: Insert "### "
    
    // === TEXT FORMATTING ===
    MC_BOLD,                // Bold: Cmd+B
    MC_ITALIC,              // Italic: Cmd+I
    MC_CLEAR_FORMAT,        // Clear Formatting (Obsidian): Cmd+Shift+Ctrl+K
    
    // === LINE OPERATIONS ===
    MC_CUT_TO_START,        // Cut from cursor to start of line
    MC_CUT_TO_END,          // Cut from cursor to end of line
    
    // === WORD OPERATIONS ===
    MC_CUT_WORD_PREV,       // Select previous word and cut
    MC_CUT_WORD_NEXT,       // Select next word and cut
    
    // === PARAGRAPH OPERATIONS ===
    MC_CUT_PARA,            // Select current paragraph and cut
    MC_CUT_PARA_END,        // Select to end of paragraph and cut
    
    // === CLIPBOARD OPERATIONS ===
    MC_PASTE,               // Paste: Cmd+V
    
    // === TEXT INSERTION ===
    MC_QUOTE,               // Insert quotation mark
    MC_PAREN,               // Insert opening parenthesis
    MC_EM_DASH,             // Insert em dash with spaces
    
    // === CUT AND WRAP OPERATIONS ===
    MC_WRAP_QUOTE,          // Cut selection and wrap in quotes
    MC_WRAP_PAREN,          // Cut selection and wrap in parentheses
    
    // === GOOGLE DOCS FORMATTING ===
    MC_GDOC_H1,             // Google Docs H1: Cmd+Alt+1
    MC_GDOC_H2,             // Google Docs H2: Cmd+Alt+2
    MC_GDOC_H3,             // Google Docs H3: Cmd+Alt+3
    MC_GDOC_NORMAL,         // Google Docs Normal/Clear: Cmd+Alt+0
};

// ========== TAP DANCE DECLARATIONS ==========
enum tap_dances {
    TD_LAYERS_LOW = 0,   // Layers 0-3 switcher - shows as TD(0) in VIA
    TD_LAYERS_HIGH = 1,  // Layers 4-7 switcher - shows as TD(1) in VIA
};

// ========== TAP DANCE HANDLERS ==========
void td_layers_low_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            layer_move(0);      // Single tap: Go to layer 0
            break;
        case 2:
            layer_invert(2);    // Double tap: Toggle layer 2
            break;
        case 3:
            layer_invert(1);    // Triple tap: Toggle layer 1
            break;
        case 4:
            layer_invert(3);    // Quad tap: Toggle layer 3
            break;
    }
}

void td_layers_high_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            layer_invert(4);    // Single tap: Toggle layer 4
            break;
        case 2:
            layer_invert(6);    // Double tap: Toggle layer 6
            break;
        case 3:
            layer_invert(5);    // Triple tap: Toggle layer 5
            break;
        case 4:
            layer_invert(7);    // Quad tap: Toggle layer 7
            break;
    }
}

void td_layers_low_reset(tap_dance_state_t *state, void *user_data) {
    // Cleanup if needed
}

void td_layers_high_reset(tap_dance_state_t *state, void *user_data) {
    // Cleanup if needed
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYERS_LOW]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layers_low_finished, td_layers_low_reset),
    [TD_LAYERS_HIGH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layers_high_finished, td_layers_high_reset),
};

// ========== MACRO PROCESSING ==========
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // === MARKDOWN HEADERS ===
            case MC_MD_H1:
                tap_code(KC_HOME);
                SEND_STRING("# ");
                return false;
            case MC_MD_H2:
                tap_code(KC_HOME);
                SEND_STRING("## ");
                return false;
            case MC_MD_H3:
                tap_code(KC_HOME);
                SEND_STRING("### ");
                return false;
            
            // === TEXT FORMATTING ===
            case MC_BOLD:
                register_code(KC_LGUI);
                tap_code(KC_B);
                unregister_code(KC_LGUI);
                return false;
            case MC_ITALIC:
                register_code(KC_LGUI);
                tap_code(KC_I);
                unregister_code(KC_LGUI);
                return false;
            case MC_CLEAR_FORMAT:
                register_code(KC_LGUI);
                register_code(KC_LSHIFT);
                register_code(KC_LCTRL);
                tap_code(KC_K);
                unregister_code(KC_LCTRL);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LGUI);
                return false;
            
            // === LINE OPERATIONS ===
            case MC_CUT_TO_START:
                register_code(KC_LSHIFT);
                tap_code(KC_HOME);
                unregister_code(KC_LSHIFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            case MC_CUT_TO_END:
                register_code(KC_LSHIFT);
                tap_code(KC_END);
                unregister_code(KC_LSHIFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            
            // === WORD OPERATIONS ===
            case MC_CUT_WORD_PREV:
                register_code(KC_LSHIFT);
                register_code(KC_LALT);
                tap_code(KC_UP);
                unregister_code(KC_LALT);
                unregister_code(KC_LSHIFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            case MC_CUT_WORD_NEXT:
                register_code(KC_LSHIFT);
                register_code(KC_LALT);
                tap_code(KC_DOWN);
                unregister_code(KC_LALT);
                unregister_code(KC_LSHIFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            
            // === PARAGRAPH OPERATIONS ===
            case MC_CUT_PARA:
                register_code(KC_LALT);
                tap_code(KC_UP);
                unregister_code(KC_LALT);
                register_code(KC_LSHIFT);
                register_code(KC_LALT);
                tap_code(KC_DOWN);
                unregister_code(KC_LALT);
                unregister_code(KC_LSHIFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            case MC_CUT_PARA_END:
                register_code(KC_LSHIFT);
                register_code(KC_LGUI);
                tap_code(KC_DOWN);
                unregister_code(KC_LSHIFT);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;
            
            // === BASIC OPERATIONS ===
            case MC_PASTE:
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                return false;
            case MC_QUOTE:
                SEND_STRING("\"");
                return false;
            case MC_PAREN:
                SEND_STRING("(");
                return false;
            case MC_EM_DASH:
                SEND_STRING(" ");
                register_code(KC_LALT);
                register_code(KC_LSHIFT);
                tap_code(KC_MINUS);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LALT);
                SEND_STRING(" ");
                return false;
            
            // === CUT AND WRAP ===
            case MC_WRAP_QUOTE:
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
            case MC_WRAP_PAREN:
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
            
            // === GOOGLE DOCS ===
            case MC_GDOC_H1:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_1);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
            case MC_GDOC_H2:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_2);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
            case MC_GDOC_H3:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_3);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
            case MC_GDOC_NORMAL:
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

/* ========== VIA REFERENCE GUIDE ==========
 * 
 * IN VIA, CUSTOM KEYCODES APPEAR AS HEX VALUES:
 * 
 * Headers:
 * 0x5F80 = MC_MD_H1      (Markdown H1)
 * 0x5F81 = MC_MD_H2      (Markdown H2)
 * 0x5F82 = MC_MD_H3      (Markdown H3)
 * 
 * Formatting:
 * 0x5F83 = MC_BOLD       (Bold)
 * 0x5F84 = MC_ITALIC     (Italic)
 * 0x5F85 = MC_CLEAR_FORMAT (Clear)
 * 
 * Line Operations:
 * 0x5F86 = MC_CUT_TO_START
 * 0x5F87 = MC_CUT_TO_END
 * 
 * Word Operations:
 * 0x5F88 = MC_CUT_WORD_PREV
 * 0x5F89 = MC_CUT_WORD_NEXT
 * 
 * Paragraph Operations:
 * 0x5F8A = MC_CUT_PARA
 * 0x5F8B = MC_CUT_PARA_END
 * 
 * Basic:
 * 0x5F8C = MC_PASTE
 * 0x5F8D = MC_QUOTE
 * 0x5F8E = MC_PAREN
 * 0x5F8F = MC_EM_DASH
 * 
 * Wrap Operations:
 * 0x5F90 = MC_WRAP_QUOTE
 * 0x5F91 = MC_WRAP_PAREN
 * 
 * Google Docs:
 * 0x5F92 = MC_GDOC_H1
 * 0x5F93 = MC_GDOC_H2
 * 0x5F94 = MC_GDOC_H3
 * 0x5F95 = MC_GDOC_NORMAL
 * 
 * TAP DANCES APPEAR AS NAMED ENTRIES:
 * TD(0) = Layer switcher 0-3
 * TD(1) = Layer switcher 4-7
 * 
 * ========== REQUIRED IN rules.mk ==========
 * VIA_ENABLE = yes
 * TAP_DANCE_ENABLE = yes
 * 
 * ========== OPTIONAL IN config.h ==========
 * #define TAPPING_TERM 250  // Match your preference
 */
