# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Build Commands

### Compile Firmware
```fish
# Basic compilation for a specific keyboard and keymap
qmk compile -kb <keyboard_name> -km <keymap_name>

# Example: compile default keymap for a keyboard
qmk compile -kb planck/rev6 -km default

# Compile from JSON configurator export
qmk compile <configuratorExport.json>

# Parallel compilation for faster builds
qmk compile -j 0 -kb <keyboard_name> -km <keymap_name>
```

### Flash Firmware
```fish
# Flash to keyboard (automatically detects bootloader)
qmk flash -kb <keyboard_name> -km <keymap_name>

# Flash pre-compiled firmware
qmk flash <keyboard_name>_<keymap_name>.hex
```

### Make-based Build (Alternative)
```fish
# Format: make <keyboard>:<keymap>:<target>
make planck/rev6:default
make planck/rev6:default:flash
```

## Development Commands

### Code Formatting
```fish
# Format C code using clang-format
# Configuration in .clang-format (Google style with custom settings)
clang-format -i <file.c>
```

### Python Linting
```fish
# Install dev requirements first
pip install -r requirements-dev.txt

# Run Python tests
nose2

# Python linting
flake8 <file.py>
```

### Testing
```fish
# Tests are located in tests/ directory
# Use keyboard-specific test commands as defined in their rules.mk

# Run QMK doctor for environment validation
qmk doctor
```

## Project Structure

### High-Level Architecture

**vial-qmk** is a fork of QMK firmware with Vial integration for on-the-fly keyboard configuration without reflashing.

#### Core Directories
- **`keyboards/`** - Hardware-specific implementations for 1100+ keyboards. Each keyboard has subdirectories for revisions and keymaps
- **`quantum/`** - Core QMK framework including keycodes, processes, and Vial integration
  - `vial.c/vial.h` - Vial protocol implementation for dynamic configuration
  - `vialrgb.c` - RGB configuration through Vial
  - `qmk_settings.c` - Runtime settings management
- **`builddefs/`** - Build system makefiles
  - `build_vial.mk` - Vial-specific build configuration that enables tap dance, combos, key overrides, and QMK settings by default
- **`tmk_core/`** - Low-level keyboard matrix scanning and USB protocol
- **`platforms/`** - Platform-specific code for AVR, ARM, and other MCU families
- **`drivers/`** - Hardware drivers for displays, sensors, RGB controllers
- **`lib/`** - External dependencies and submodules

#### Build System
The build system uses GNU Make with Python-based QMK CLI:
- Entry point: `Makefile` - Parses rules in format `<keyboard>:<keymap>:<target>`
- Python CLI: `lib/python/qmk/cli/` - Modern interface wrapping make commands
- Build definitions: `builddefs/*.mk` - Feature configuration and compilation rules

#### Vial Architecture
Vial extends QMK with dynamic configuration:
- **Protocol**: Binary protocol over raw HID endpoint (32-byte packets)
- **Definition Generation**: `util/vial_generate_definition.py` converts `vial.json` to compressed C header at compile time
- **Dynamic Features**: Tap dance, combos, key overrides configurable at runtime without reflashing
- **Storage**: EEPROM-backed configuration with entry counts scaled by available memory

### Keyboard Implementation Pattern
Each keyboard follows this structure:
```
keyboards/<manufacturer>/<model>/
  ├── config.h          # Hardware configuration
  ├── rules.mk          # Build options and features
  ├── <model>.c/h       # Keyboard-specific code
  ├── info.json         # Metadata and layout definitions
  └── keymaps/
      ├── default/      # Stock keymap
      └── vial/         # Vial-enabled keymap with vial.json
```

## Important Notes

### Vial-Specific Development
- Vial keymaps require a `vial.json` file defining the keyboard layout for the configurator
- Build automatically generates `vial_generated_keyboard_definition.h` from `vial.json`
- Set `VIAL_INSECURE=yes` in rules.mk during development to skip unlock sequence
- Dynamic features (tap dance, combos, key overrides) have configurable entry limits based on EEPROM size

### Build System Behavior
- The build system is directory-aware: running `qmk compile` in a keyboard directory auto-detects keyboard name
- Bootloader type is usually auto-detected; only specify manually if flashing fails
- Parallel compilation (`-j 0`) significantly speeds up builds but may hide some build warnings

### Code Style
- C code follows modified Google style (see `.clang-format`)
- 4-space indentation, no tabs
- Column limit: 1000 characters (effectively no wrapping for firmware code)
- Align consecutive assignments and declarations for readability

### Platform Considerations
- AVR platforms have strict memory constraints - monitor firmware size
- ARM platforms (STM32, RP2040) have more resources for features
- RP2040 uses UF2 bootloader (drag-and-drop flashing), others use various bootloaders
