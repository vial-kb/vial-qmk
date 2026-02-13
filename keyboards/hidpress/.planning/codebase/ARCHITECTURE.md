# Architecture

**Analysis Date:** 2026-02-13

## Pattern Overview

**Overall:** Modular QMK firmware with per-keyboard customization and dynamic feature binding via Vial

**Key Characteristics:**
- Split keyboard support (left/right halves communicate via USART serial)
- Multi-layered keymap system (4 layers per keyboard)
- Dynamic pointing device mode switching (mouse, scrolling, custom keys)
- Persistent configuration via EEPROM
- Vial protocol support for runtime keyboard remapping
- Global state management for joystick actuation and display modes

## Layers

**Hardware Abstraction:**
- Purpose: Encapsulate MCU-specific configuration (pins, drivers, peripherals)
- Location: `*/config.h` files (keyboard root and per-keymap)
- Contains: Pin definitions, driver setup, feature flags, MCU selection
- Depends on: QMK core framework
- Used by: Keyboard firmware compilation

**Keyboard Logic:**
- Purpose: Implement keymap processing, custom keycodes, mode switching
- Location: `*/keymaps/[keymap_name]/keymap.c`
- Contains: Keymaps, custom keycode handlers, layer management, joystick reading
- Depends on: Hardware abstraction layer, QMK core
- Used by: Entry point during key press/joystick activity

**OLED Display:**
- Purpose: Render layer state, mode indicators, actuation levels, animations
- Location: `*/[keyboard_name].c` (OLED functions in `#ifdef OLED_ENABLE`)
- Contains: Layer state graphics, actuation visualization, screensaver/startup animation
- Depends on: Global state variables (current_mode, actuation, layer_state)
- Used by: oled_task_user() called by QMK main loop

**Pointing Device:**
- Purpose: Handle joystick input and transform to mouse/scroll/custom key output
- Location: `*/keymaps/[keymap_name]/keymap.c` (pointing_device_task_user)
- Contains: Axis reading, mode-based transformation logic, scroll accumulation
- Depends on: ADC input, current_mode global
- Used by: QMK pointing device system on axis change

## Data Flow

**Key Press Flow:**

1. Matrix scan triggers key press event
2. QMK calls `process_record_user()` in `keymap.c`
3. Custom keycode check (ACT_UP, ACT_DOWN, SCROLL_DIR, TMB_MODE, CL_FWD, CL_BWD)
4. Register OLED activity and update state if needed
5. Save updated state to EEPROM
6. Return false to stop propagation or true to allow default processing

**Joystick Flow (Custom Keys Mode):**

1. ADC reads analog pins (GP28/GP29 for left side joystick)
2. `matrix_scan_user()` compares against actuation threshold
3. Reads keycode from dynamic keymap at joystick matrix position (rows 0-3, col 7)
4. Calls `handle_joystick_keycode()` which processes through `process_record_user()`
5. State change triggers EEPROM save and OLED update

**Pointing Device Flow:**

1. Joystick analog axes read continuously
2. `pointing_device_task_user()` receives raw mouse_report
3. Based on `current_mode` (MODE_MOUSE/MODE_SCROLLING/MODE_CUSTOM_KEYS):
   - MODE_MOUSE: pass through unchanged
   - MODE_SCROLLING: accumulate fractional deltas and convert to scroll reports
   - MODE_CUSTOM_KEYS: zero out movement (handled in matrix_scan_user instead)
4. Return modified report to QMK

**Display Update Flow:**

1. OLED task runs on timer
2. Check for inactivity (screensaver timeout: 60000ms, screen off: 300000ms)
3. If screensaver active: render warp particle animation
4. Else if showing_actuation flag set: render actuation level display
5. Else: render normal layer state based on `get_highest_layer()` and `current_mode`
6. All renders use layer-specific PROGMEM arrays (mouse/scroll/keycodes modes)

**State Management:**

- `current_mode`: Global enum tracking which pointing device mode is active
- `actuation`: Global int (values 64, 128, 256, 320, 352) for joystick sensitivity
- `layer_modes[4]`: Per-layer mode storage (MODE_MOUSE default)
- `current_actuation_index`: Index into actuation_values array (0-4)
- Persistent storage: EEPROM address via `eeconfig_update_user()`/`eeconfig_read_user()`

## Key Abstractions

**Pointing Device Mode Enumeration:**
- Purpose: Abstract hardware input (joystick axes) into semantic behavior
- Examples: `MODE_MOUSE` (direct axis->movement), `MODE_SCROLLING` (axis->scroll), `MODE_CUSTOM_KEYS` (axis->keycode)
- Pattern: Runtime-switchable via TMB_MODE keycode, persisted per-layer

**Custom Keycode Handler:**
- Purpose: Unify custom keycode processing for both matrix switches and joystick
- Examples: `ACT_UP`, `ACT_DOWN`, `SCROLL_DIR`, `TMB_MODE`
- Pattern: Routed through `process_record_user()` with synthetic keyrecord construction

**Layer State Arrays (PROGMEM):**
- Purpose: Store pre-rendered OLED graphics per layer and mode combination
- Examples: `default_layer_on_mouse[]`, `one_layer_on_scroll[]`, `three_layer_on_keycodes[]`
- Pattern: Hardware-compressed font indices stored in flash, selected at runtime

**Joystick Custom Keys:**
- Purpose: Map arbitrary joystick positions (up/down/left/right) to configurable keycodes
- Pattern: Hysteresis comparison against actuation threshold, state tracking in `customkeys[4]` array
- Dynamic binding: Reads from dynamic_keymap at fixed matrix positions (rows 0-3, col 7)

## Entry Points

**Keyboard Startup:**
- Location: `keyboard_pre_init_user()` in `bipedalambi.c`
- Triggers: MCU power-on before OLED driver initialization
- Responsibilities: Initialize I2C, send display-off command to prevent uninitialized state

**Configuration Load:**
- Location: `keyboard_post_init_user()` in `keymap.c`
- Triggers: QMK initialization after hardware setup
- Responsibilities: Load layer modes and actuation from EEPROM into globals

**OLED Initialization:**
- Location: `oled_init_user()` in `bipedalambi.c`
- Triggers: OLED driver initialization
- Responsibilities: Setup startup animation timers and state

**Main Event Loop:**
- OLED task: `oled_task_user()` - called by QMK tick, handles display rendering
- Matrix scan: `matrix_scan_user()` - polled every scan cycle for joystick input
- Key processing: `process_record_user()` - event-driven on key press/release
- Layer change: `layer_state_set_user()` - event-driven on layer change
- Pointing device: `pointing_device_task_user()` - event-driven on joystick axis change

## Error Handling

**Strategy:** Defensive defaults with fallback to safe state

**Patterns:**
- Invalid layer read: `get_highest_layer()` bounds checked, defaults to layer 0
- EEPROM load failure: Mode defaults to MODE_MOUSE, actuation_index defaults to 2 (256)
- Joystick hysteresis: Requires actuation threshold hysteresis to prevent chatter
- ADC read: Direct analog reads with 10-bit range (0-1023), centered at 512
- Display update: All OLED writes check pointer validity before rendering

## Cross-Cutting Concerns

**Logging:** None - no debug output configured (pure firmware)

**Validation:**
- Layer mode: Clamped to MODE_COUNT via conditional `(mode < MODE_COUNT) ? mode : MODE_MOUSE`
- Actuation index: Clamped to 0-4 range via `(act_idx <= 4) ? act_idx : 2`
- Keycode reading: Only when MODE_CUSTOM_KEYS active, joystick threshold exceeded

**Authentication:** Vial unlock combo configured per-keyboard via VIAL_UNLOCK_COMBO_ROWS/COLS

**Split Keyboard Communication:**
- Left/right halves communicate layer state and joystick data via SERIAL_USART (full-duplex)
- Configuration: `SERIAL_USART_FULL_DUPLEX`, `SPLIT_USB_DETECT`, `SPLIT_LAYER_STATE_ENABLE`
- Pins vary per keymap: bipedalambi_left uses GP0/GP1, bipedalambi_right uses different pins

---

*Architecture analysis: 2026-02-13*
