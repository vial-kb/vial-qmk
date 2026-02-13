# Codebase Structure

**Analysis Date:** 2026-02-13

## Directory Layout

```
/Users/matthewthomas/dev/vial-qmk/keyboards/hidpress/
├── bipedal65/              # Single-unit 65-key keyboard
│   ├── config.h            # MCU, OLED, RGB configuration
│   ├── bipedal65.c         # OLED display logic, layer state rendering
│   ├── halconf.h           # ChibiOS HAL configuration
│   ├── mcuconf.h           # MCU-specific settings
│   ├── glcdfont.c          # Custom OLED font definitions
│   ├── rules.mk            # Build rules (MCU, bootloader, drivers)
│   └── keymaps/
│       ├── via/
│       │   ├── keymap.c    # Via-compliant keymap (65 keys)
│       │   └── rules.mk    # Via-specific build flags
│       └── vial/
│           ├── keymap.c    # Vial-compliant keymap (65 keys)
│           ├── config.h    # Vial UID, unlock combo, features
│           └── rules.mk    # Vial-specific build flags
│
├── bipedalsouthpaw/        # Split keyboard with southpaw layout
│   ├── config.h            # Common config (pins overridden per-keymap)
│   ├── bipedalsouthpaw.c   # OLED rendering, screensaver animation
│   ├── bipedalsouthpaw_shared.h  # Shared pointing device mode enum
│   ├── halconf.h           # ChibiOS HAL configuration
│   ├── mcuconf.h           # MCU-specific settings
│   ├── glcdfont.c          # Custom OLED font
│   ├── rules.mk            # Build rules
│   └── keymaps/
│       ├── via/
│       │   ├── keymap.c
│       │   └── rules.mk
│       └── vial/
│           ├── keymap.c
│           ├── config.h    # Vial UID, pin configuration
│           └── rules.mk
│
├── bipedalambi/            # Split ambidextrous with analog joystick
│   ├── config.h            # Common config (matrix, OLED, joystick, serial)
│   ├── bipedalambi.h       # LAYOUT macro, pointing mode enum, extern globals
│   ├── bipedalambi.c       # OLED rendering, startup animation, screensaver
│   ├── halconf.h           # ChibiOS HAL configuration
│   ├── mcuconf.h           # MCU-specific settings
│   ├── glcdfont.c          # Custom OLED font
│   ├── rules.mk            # Build rules (includes analog.c)
│   └── keymaps/
│       ├── default/
│       │   └── keymap.c    # Default 29-key left layout
│       ├── vial_left/
│       │   ├── keymap.c    # Left half (29 keys) - full logic
│       │   ├── config.h    # Left-specific pins, Vial UID, custom keycodes
│       │   └── rules.mk    # Left-specific build flags
│       └── vial_right/
│           ├── keymap.c    # Right half (29 keys) - mirror layout
│           ├── config.h    # Right-specific pins, Vial UID
│           └── rules.mk    # Right-specific build flags
│
└── .planning/              # GSD documentation (generated)
    └── codebase/
        ├── ARCHITECTURE.md
        ├── STRUCTURE.md
        └── (other analysis docs)
```

## Directory Purposes

**bipedal65:**
- Purpose: Production 65-key single PCB keyboard
- Contains: Monolithic firmware for wired keyboard
- Key files: `bipedal65.c` (OLED), `keymaps/vial/keymap.c` (inputs)
- Notes: No split communication, simpler pin mapping

**bipedalsouthpaw:**
- Purpose: Split keyboard with custom layout and southpaw support
- Contains: Split firmware with screensaver animation (warp particles)
- Key files: `bipedalsouthpaw.c` (warp animation), `bipedalsouthpaw_shared.h` (mode enum)
- Notes: More complex OLED animations than bipedal65

**bipedalambi:**
- Purpose: Split ambidextrous keyboard with analog joystick on both sides
- Contains: Most advanced firmware with custom joystick modes and global actuation
- Key files: `bipedalambi.c` (animation + joystick display), `keymap.c` (full logic)
- Notes: Joystick hysteresis, 3 pointing modes, dynamic keymap binding, persistent config

## Key File Locations

**Entry Points:**
- `bipedalambi/bipedalambi.c`: `keyboard_pre_init_user()` - early I2C init
- `bipedalambi/keymaps/vial_left/keymap.c`: `keyboard_post_init_user()` - EEPROM load
- `bipedalambi/bipedalambi.c`: `oled_init_user()` - display startup
- `bipedalambi/keymaps/vial_left/keymap.c`: `process_record_user()` - keycode handling
- `bipedalambi/keymaps/vial_left/keymap.c`: `matrix_scan_user()` - joystick polling
- `bipedalambi/keymaps/vial_left/keymap.c`: `pointing_device_task_user()` - axis transformation

**Configuration:**
- `bipedalambi/config.h`: Common MCU, OLED, joystick, serial config
- `bipedalambi/keymaps/vial_left/config.h`: Left-specific pins, Vial UID, I2C pins
- `bipedalambi/keymaps/vial_right/config.h`: Right-specific pins, Vial UID
- `bipedal65/config.h`: Standalone config (no split)

**Core Logic:**
- `bipedalambi/keymaps/vial_left/keymap.c`: Custom keycodes (TMB_MODE, ACT_UP, ACT_DOWN, SCROLL_DIR, CL_FWD, CL_BWD)
- `bipedalambi/keymaps/vial_left/keymap.c`: Joystick input reading (GP28/GP29 ADC pins)
- `bipedalambi/keymaps/vial_left/keymap.c`: EEPROM persistence functions (save_layer_config_to_eeprom, load_layer_config_from_eeprom)
- `bipedalambi/keymaps/vial_left/keymap.c`: Layer mode tracking and switching

**Testing:**
- No formal test files - QMK firmware testing done via `make` build validation

**Display/UI:**
- `bipedalambi/bipedalambi.c`: OLED layers (render_layer_state, render_actuation_state)
- `bipedalambi/bipedalambi.c`: Startup animation (animated noise fade)
- `bipedalambi/bipedalambi.c`: Screensaver animation (warp particles to center)
- `bipedalambi/glcdfont.c`: Font data (custom character set for layer/mode graphics)

## Naming Conventions

**Files:**
- Keyboard name: lowercase with no spaces (e.g., `bipedalambi`, `bipedalsouthpaw`)
- Keymap directories: lowercase descriptive (e.g., `vial_left`, `vial_right`, `default`)
- Header files: `.h` extension, lowercase name matching source
- Implementation files: `.c` extension
- Configuration: `config.h` (QMK convention)
- Build rules: `rules.mk` (QMK convention)
- Bootloader: `halconf.h`, `mcuconf.h` (ChibiOS convention)

**Functions:**
- User-defined entry points: snake_case suffix with `_user` (e.g., `process_record_user`, `oled_task_user`)
- Helper functions: snake_case (e.g., `render_layer_state`, `init_warp_particle`, `handle_joystick_keycode`)
- Static helpers: prefixed with `static` (e.g., `static void render_dissolve()`)
- Animation helpers: descriptive action prefix (e.g., `init_warp`, `update_warp`, `render_warp`)

**Variables:**
- Global state: camelCase (e.g., `current_mode`, `showing_actuation`, `warp_particles`)
- Constants: UPPERCASE_SNAKE_CASE (e.g., `SCREENSAVER_TIMEOUT`, `FRAME_DELAY`, `NUM_PARTICLES`)
- Array suffixes: plural lowercase (e.g., `customkeys[4]`, `layer_modes[4]`)
- PROGMEM strings: descriptive with layer/state info (e.g., `default_layer_on_mouse[]`, `actuation_level_3[]`)

**Enums:**
- Enum name: CamelCase (e.g., `pointing_device_mode`, `layers`)
- Enum values: UPPERCASE_SNAKE_CASE (e.g., `MODE_MOUSE`, `MODE_SCROLLING`, `MODE_CUSTOM_KEYS`)

**Macros:**
- Feature flags: UPPERCASE (e.g., `OLED_ENABLE`, `JOYSTICK_ENABLE`)
- Pin definitions: all caps with prefix (e.g., `GP28`, `GP29`, `WS2812_DI_PIN`)
- Layout macros: keyboard-specific name (e.g., `LAYOUT_bipedalambi`, `LAYOUT_left`)

## Where to Add New Code

**New Feature (Keyboard-Wide):**
- Primary code: `bipedalambi/keymaps/vial_left/keymap.c`
- Configuration: `bipedalambi/keymaps/vial_left/config.h`
- If OLED display needed: `bipedalambi/bipedalambi.c`
- If new custom keycode: add to enum in `keymap.c`, implement in `process_record_user()`
- If new pointing mode: add to `pointing_device_mode` enum in `bipedalambi.h`, implement in `pointing_device_task_user()`

**New Keyboard Variant:**
- Create directory: `/keyboards/hidpress/[new_name]/`
- Copy structure from existing keyboard (e.g., `bipedalambi/`)
- Key files to create: `config.h`, `[keyboard].h`, `[keyboard].c`, `rules.mk`, `keymaps/vial_{left,right}/`
- For split keyboards: define left/right-specific pins in `keymaps/vial_left/config.h` and `keymaps/vial_right/config.h`
- For joystick: add ADC pin configuration in per-keymap config.h

**Custom Keymap:**
- Create directory: `keymaps/[keymap_name]/`
- Required files: `keymap.c`, `config.h` (with Vial UID), `rules.mk`
- In `keymap.c`: define LAYOUT macro matching keyboard layout, define keymaps array, implement custom handlers
- Custom keycodes: use `QK_KB_0+` range for Vial compatibility (defined in enum custom_keycodes)

**Utilities/Helpers:**
- Shared across keyboards: create new `.c`/`.h` file in keyboard root (e.g., `common_animation.c`)
- Include in `rules.mk`: `SRC += common_animation.c`
- Export declarations in shared `.h` file

**Animation/Graphics:**
- OLED graphics: add PROGMEM arrays in main `.c` file (e.g., `bipedalambi.c`)
- Layer state graphics: follow naming pattern `[layer_name]_layer_on_[mode][]` and `[layer_name]_layer_off_[mode][]`
- Actuation displays: `actuation_level_[1-5][]`
- Font data: `glcdfont.c` (pre-existing, update only if new characters needed)

## Special Directories

**keymaps/vial_left and vial_right:**
- Purpose: Vial firmware split into left and right half binaries
- Generated: No, manually maintained
- Committed: Yes, separate config.h per side with pin mappings
- Notes: Each side is flashed independently; left side typically contains full logic, right side mirrors

**glcdfont.c:**
- Purpose: Custom OLED font with game-like characters
- Generated: No, hand-crafted for aesthetic display
- Committed: Yes
- Notes: Indexed by byte values (0x00-0xFF) in PROGMEM arrays; new characters require font editor

**halconf.h, mcuconf.h:**
- Purpose: ChibiOS HAL and MCU configuration (inherited from QMK)
- Generated: No, customized per keyboard
- Committed: Yes
- Notes: Define hardware features (SERIAL, I2C, ADC), clock speeds, driver settings

---

*Structure analysis: 2026-02-13*
