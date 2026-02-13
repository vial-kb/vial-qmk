# Testing Patterns

**Analysis Date:** 2026-02-13

## Test Framework

**Status:** No testing framework detected

**Finding:**
- No unit test files found (no `*.test.c`, `*.spec.c`, or test directories)
- No test runner configuration (no CMake, CTest, or unittest framework)
- No mock/stub libraries in use
- This is typical for QMK firmware projects, which are hardware-dependent embedded code

**Why No Tests:**
- QMK firmware requires hardware to validate behavior (matrix scanning, OLED output, USB communication)
- Testing would require:
  - Hardware simulation layer
  - QMK's embedded environment (ARM toolchain, ChibiOS)
  - Device-specific I/O simulation
- Development validation happens through:
  - Compilation against QMK (detects syntax/type errors)
  - Hardware testing and flashing
  - Manual testing with actual keyboard

## Build and Deployment

**Build Command:**
```bash
qmk compile -kb hidpress/bipedalambi -km vial_left
qmk compile -kb hidpress/bipedalambi -km vial_right
qmk compile -kb hidpress/bipedal65 -km vial
qmk compile -kb hidpress/bipedalsouthpaw -km vial
```

**Build Configuration:**
- Rules file: `/Users/matthewthomas/dev/vial-qmk/keyboards/hidpress/{keyboard}/rules.mk`
- Example from `bipedal65/rules.mk`:
  ```makefile
  VIA_ENABLE = yes
  LTO_ENABLE = yes
  ENCODER_MAP_ENABLE = yes
  OLED_DRIVER_ENABLE = yes
  MOUSEKEY_ENABLE = yes
  ```
- Hardware-specific config: `halconf.h`, `mcuconf.h` (ChibiOS hardware abstraction)

## Code Validation

**Compilation Validation:**
- QMK build system provides:
  - C compiler type checking (gcc/clang with strict flags)
  - Header dependency validation
  - Memory footprint analysis (firmware size constraints)
  - Link-time optimization checks (`LTO_ENABLE`)

**Example Compilation Check Pattern:**
From `bipedalambi.h`:
```c
#pragma once

#include "quantum.h"

enum pointing_device_mode {
    MODE_MOUSE,
    MODE_SCROLLING,
    MODE_CUSTOM_KEYS,
    MODE_COUNT
};

extern enum pointing_device_mode current_mode;  // Compile-time validation of extern linkage
extern int actuation;
extern bool showing_actuation;
extern uint32_t actuation_display_timer;
```

**Static Analysis:**
- No explicit linter (like cppcheck or clang-analyzer) configured
- QMK's build inherits gcc warnings; `-Wall` is typically enabled
- Developers rely on compiler warnings to catch issues

## Hardware Integration Patterns

**QMK Callbacks Used for Integration Testing:**
These are invoked by QMK framework at specific lifecycle points:

1. **`keyboard_pre_init_user()`** - Called before hardware initialization
   - Location: `bipedalambi/bipedalambi.c:5`
   - Validates early initialization (I2C, display pre-config)
   ```c
   void keyboard_pre_init_user(void) {
       i2c_init();
       uint8_t display_off_cmd[] = {0x00, 0xAE};
       i2c_transmit(0x3C << 1, display_off_cmd, 2, 100);
   }
   ```

2. **`oled_init_user()`** - Called when OLED initializes
   - Location: `bipedalambi/bipedalambi.c:409`
   - Tests startup animation state initialization
   ```c
   oled_rotation_t oled_init_user(oled_rotation_t rotation) {
       oled_startup_timer = timer_read32();
       oled_startup_complete = false;
       startup_phase = 0;
       return rotation;
   }
   ```

3. **`oled_task_user()`** - Called every OLED update cycle
   - Location: `bipedalambi/bipedalambi.c:432`
   - Tests animation state machines, rendering, timeout logic
   - Returns `false` to indicate no rendering needed

4. **`process_record_user()`** - Called on every keypress
   - Location: `bipedal65/keymaps/via/keymap.c:29`
   - Tests custom keycode behavior and layer cycling

## Integration Testing Strategy

**Manual Hardware Testing:**
Without formal test framework, validation happens through:

1. **Compilation verification**
   - All files must compile without errors
   - extern declarations must match definitions
   - Layout macros must map to actual matrix rows/cols

2. **Runtime behavior testing** (on hardware)
   - Flash firmware to keyboard
   - Test each keyboard variant:
     - `bipedal65` (single keyboard)
     - `bipedalsouthpaw` (single keyboard)
     - `bipedalambi` (split: vial_left and vial_right)
   - Verify OLED animation sequences
   - Verify layer switching
   - Verify pointing device modes (mouse/scroll/custom keys)
   - Verify actuation display

3. **State machine validation** (code review)
   - `render_layer_state()` - Verify all 4 layers render correctly
   - `oled_task_user()` startup phases - Verify: noise -> dissolve -> GUI
   - `register_oled_activity()` - Verify screensaver activation and deactivation
   - Animation timers - Verify timeouts and resets

## Test Coverage Analysis

**High Confidence Areas (code review-validated):**

**Rendering Functions:**
- `render_layer_state()` - `bipedalambi/bipedalambi.c:129` (70 lines)
  - Tests 4 layers × 3 modes = 12 code paths
  - All paths render OLED arrays based on current state

- `render_actuation_state()` - `bipedalambi/bipedalambi.c:203` (20 lines)
  - Tests 5 actuation levels
  - Each case displays specific PROGMEM array

**Animation/Screensaver:**
- `init_warp()` - `bipedalambi/bipedalambi.c:289` (3 lines)
  - Initializes 50 particles with random starting positions

- `update_warp()` - `bipedalambi/bipedalambi.c:294` (20 lines)
  - Updates particle positions toward center
  - Tests respawn vs freeze behavior

- `render_warp()` - `bipedalambi/bipedalambi.c:315` (35 lines)
  - Renders particles with trail effect
  - Tests boundary conditions (0 >= x < 128, 0 >= y < 32)

**Startup Animation:**
- `oled_task_user()` phases 0-2 - `bipedalambi/bipedalambi.c:437-482`
  - Phase 0: Noise animation for 1 second
  - Phase 1: Dissolve fade (2.5 seconds)
  - Phase 2: Transition to GUI
  - Tests timing calculations, frame updates, noise generation

**Medium Confidence Areas (compile-validated only):**

**Keymap Processing:**
- `process_record_user()` - `bipedal65/keymaps/via/keymap.c:29` (28 lines)
  - Layer cycling logic
  - Custom keycode dispatch
  - Only validated by compilation; runtime behavior requires hardware

**EEPROM Persistence:**
- `save_layer_config_to_eeprom()` - `bipedalambi/keymaps/vial_left/keymap.c:64`
- `load_layer_config_from_eeprom()` - `bipedalambi/keymaps/vial_left/keymap.c:77`
- Bitpacking logic for modes and actuation index
- Compile-validated for syntax; runtime requires hardware EEPROM access

**Low/Untested Areas:**

**Pointing Device Modes:**
- Mode switching and joystick input handling
- Scroll accumulation and divisor calculations
- Custom key state management
- These require analog joystick hardware and USB HID reporting to fully validate

**Split Keyboard Synchronization:**
- `bipedalambi` uses split keyboard with serial communication
- Left/right side coordination requires both halves running and communicating
- Cannot be validated without hardware or QMK's software simulation environment

## Validation Checklist

When adding or modifying code, validate:

**Compilation:**
- [ ] `qmk compile -kb hidpress/bipedalambi -km vial_left` succeeds
- [ ] `qmk compile -kb hidpress/bipedalambi -km vial_right` succeeds
- [ ] `qmk compile -kb hidpress/bipedal65 -km vial` succeeds
- [ ] `qmk compile -kb hidpress/bipedalsouthpaw -km vial` succeeds
- [ ] No compiler warnings (use `qmk compile -kb ... --verbose` to inspect)

**Code Structure:**
- [ ] Extern declarations in header match definitions in `.c`
- [ ] Static variables initialized at file scope
- [ ] Private helpers marked `static`
- [ ] PROGMEM arrays marked with `static const char PROGMEM`
- [ ] Macro definitions don't conflict with QMK names

**Runtime Behavior (Hardware Required):**
- [ ] OLED displays correctly for each layer
- [ ] Layer switching works smoothly
- [ ] Pointing device mode changes work
- [ ] Screensaver activates after timeout
- [ ] Screen turns off after extended inactivity
- [ ] Activity (keypress) resets screensaver

## Adding Tests

**If unit testing were added,** recommended approach:

1. **Create hardware abstraction layer** to mock:
   - `oled_write_P()` calls
   - `timer_read32()` and `timer_elapsed32()` calls
   - `layer_state_is()` queries

2. **Test rendering logic** independently:
   ```c
   // Pseudo-test
   void test_render_layer_state_mouse_mode(void) {
       current_mode = MODE_MOUSE;
       layer_state = 0;
       render_layer_state();
       assert_oled_write_called_with(default_layer_on_mouse);
   }
   ```

3. **Test state machines** with mock timers:
   ```c
   // Pseudo-test for startup animation
   void test_oled_startup_noise_phase(void) {
       oled_startup_timer = 0;
       timer_mock_set_elapsed(500);
       oled_task_user();
       assert(startup_phase == 0);  // Still in noise phase
   }
   ```

4. **Use QMK's unit test framework** if available (requires qmk_firmware checkout)

---

*Testing analysis: 2026-02-13*
