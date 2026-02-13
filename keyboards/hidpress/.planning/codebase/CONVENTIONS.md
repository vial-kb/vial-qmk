# Coding Conventions

**Analysis Date:** 2026-02-13

## Naming Patterns

**Files:**
- Keyboard implementation files: `{keyboard_name}.c` (e.g., `bipedalambi.c`, `bipedalsouthpaw.c`)
- Header files: `{keyboard_name}.h` (e.g., `bipedalambi.h`)
- Shared headers: `{keyboard_name}_shared.h` (e.g., `bipedalsouthpaw_shared.h`)
- Configuration: `config.h`, `halconf.h`, `mcuconf.h`
- Keymaps: `keymaps/{keymap_name}/keymap.c` (e.g., `keymaps/vial/keymap.c`, `keymaps/vial_left/keymap.c`)
- Font files: `glcdfont.c`
- Rules: `rules.mk`

**Functions:**
- snake_case: `render_layer_state()`, `init_warp_particle()`, `register_oled_activity()`, `update_warp()`
- Callback handlers use QMK naming: `oled_task_user()`, `keyboard_pre_init_user()`, `oled_init_user()`, `process_record_user()`
- Private static functions: `static void render_dissolve()`, `static void fill_noise()`, `static uint16_t simple_rand()`
- Helper functions prefix with action: `init_warp()`, `update_warp()`, `render_warp()`

**Variables:**
- Global state uses snake_case: `current_mode`, `actuation`, `showing_actuation`, `last_activity_time`, `screensaver_active`
- Static module variables are descriptive: `warp_particles`, `animation_timer`, `warp_initialized`, `screen_is_off`
- Boolean flags use `_is_` and `_active` suffixes: `oled_startup_complete`, `warp_initialized`, `screen_is_off`, `screensaver_active`
- Timers use `_timer` suffix: `animation_timer`, `actuation_display_timer`, `oled_startup_timer`, `last_activity_time`
- Array indices: `current_actuation_index`, `startup_phase`, `noise_frame`

**Types:**
- Enums: UPPER_CASE_SNAKE style: `MODE_MOUSE`, `MODE_SCROLLING`, `MODE_CUSTOM_KEYS`
- Typedef structs: snake_case_t suffix: `warp_particle_t`, `led_t` (from QMK)
- Defines: UPPER_CASE: `SCREEN_CENTER_X`, `FRAME_DELAY`, `NUM_PARTICLES`, `SCREENSAVER_TIMEOUT`, `SCREEN_OFF_TIMEOUT`

## Code Style

**Formatting:**
- No explicit linter or formatter configured; follows QMK conventions
- Brace style: Opening brace on same line for functions and control structures
- Indentation: 4 spaces (not tabs)
- Line length: No apparent limit enforced, but kept reasonable

**Examples from codebase:**
```c
void render_layer_state(void) {
    uint8_t layer = get_highest_layer(layer_state);

    switch(layer) {
        case 0:
            switch(current_mode) {
                case MODE_MOUSE:
                    oled_write_P(default_layer_on_mouse, false);
                    break;
            }
            break;
    }
}
```

**Spacing:**
- Operators have spaces around them: `p->x = (simple_rand() % 128) * 16`
- Function calls: no space before parentheses: `oled_write_P(...)`, `timer_read32()`
- Array indexing: no spaces: `warp_particles[i]`, `layer_modes[i]`

## Import Organization

**Order:**
1. QMK core header: `#include QMK_KEYBOARD_H`
2. Local headers: `#include "bipedalambi.h"`, `#include "quantum.h"`
3. Standard library/driver includes: `#include "i2c_master.h"`, `#include "analog.h"`
4. Configuration-dependent includes: `#include "dynamic_keymap.h"`

**Examples:**
```c
#include QMK_KEYBOARD_H
#include "bipedalambi.h"
#include "i2c_master.h"
```

```c
#include "quantum.h"
#include "bipedalsouthpaw_shared.h"
```

## Error Handling

**Pattern:**
- Limited explicit error handling due to embedded firmware constraints
- Function return values used sparingly; mostly void functions
- Boolean returns indicate success/failure: `bool oled_task_user()` returns `false` to skip redrawing
- Validation uses early returns and checks: `if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) { return false; }`

**Example from `bipedal65/keymaps/via/keymap.c`:**
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CYCLE_LAYERS:
            if (!record->event.pressed) {
                return false;  // Handle release silently
            }
            uint8_t current_layer = get_highest_layer(layer_state);
            if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
                return false;  // Out of range - silently ignore
            }
            // Process normally
            return false;
        default:
            return true;  // Let QMK handle other keycodes
    }
}
```

## Logging

**Framework:** None - uses QMK's debug functions if needed

**Pattern:**
- Comments indicate intent and important state changes
- Console output not used in normal operation (embedded firmware)
- Example comments: `// Send SSD1306 display off command (0xAE) directly`, `// Fill screen with sparse random static (~10% pixels lit)`

## Comments

**When to Comment:**
- Complex algorithms: Documented in `bipedalambi.c` warp particle animation
- Bitwise operations: `// Bits 0-7: Layer modes (2 bits per layer * 4 layers)`
- Register/hardware operations: `// OLED address is typically 0x3C (or 0x3D)`
- Layer/mode transitions: `// Phase 0: Animated static noise for 1 second`
- Configuration notes: `// Rename to LAYOUT_bipedalambi to avoid QMK data-driven conflict`

**JSDoc/TSDoc:**
- Not used in this C firmware codebase
- Instead, inline comments explain intent and parameters

## Function Design

**Size:** Functions range 5-150 lines; typically focused on single responsibility
- Simple rendering: `render_layer_state()` - ~70 lines (switch-based dispatch)
- Complex animation: `oled_task_user()` - ~120 lines (state machine with phases)
- Utility functions: `simple_rand()` - 5 lines

**Parameters:**
- Minimal parameters; use static/global state when appropriate
- Pointers for struct modification: `void init_warp_particle(warp_particle_t *p)`
- Boolean flags for behavioral control: `update_warp(bool respawn)`

**Return Values:**
- Boolean for QMK handlers: `bool oled_task_user()`, `bool process_record_user()`
- Void for side-effect functions: `void register_oled_activity()`, `void render_layer_state()`
- Unsigned integers for calculations: `uint16_t simple_rand()`, `uint8_t fast_rand()`

## Module Design

**Exports:**
- Global variables declared in `.h` files with `extern` keyword:
  - `extern enum pointing_device_mode current_mode;`
  - `extern int actuation;`
  - `extern bool showing_actuation;`
  - `extern uint32_t actuation_display_timer;`
- Functions used across modules declared in header: `void register_oled_activity(void);`

**Static Encapsulation:**
- Module-private data is `static` at file scope:
  - `static warp_particle_t warp_particles[NUM_PARTICLES];`
  - `static uint32_t animation_timer = 0;`
  - `static uint16_t rng_state = 12345;`
- Private helper functions are `static`: `static void fill_noise()`, `static void render_dissolve()`

**Barrel Files:**
- Not applicable to C firmware; headers expose what's needed for cross-module use

## Macro Patterns

**Layout Macros:**
Used to define keyboard matrix layouts from KLE raw data:
```c
#define LAYOUT_bipedalambi( \
    k03, \
    k02, k04, \
    k00, k01, k05, \
    // ... more keys \
) { \
    { k00, k01, k02, k03, k04, k05, KC_NO, k07 }, \
    { k10, k11, k12, k13, k14, k15, KC_NO, k17 }, \
    // ... matrix mapping \
}
```

**Configuration Macros:**
Simple #define for constants:
```c
#define SCREEN_CENTER_X 64
#define FRAME_DELAY 40
#define NUM_PARTICLES 50
#define SCREENSAVER_TIMEOUT 60000
#define ACTUATION_DISPLAY_DURATION 1000
```

---

*Convention analysis: 2026-02-13*
