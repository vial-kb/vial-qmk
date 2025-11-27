# Delilah's Custom Q15 Max Keymap

A comprehensive QMK/VIA implementation featuring 32 custom macros, 8 layers, and full RGB support for the Keychron Q15 Max.

## Key Features

### Macro System
- **32 Custom Macros** organized into categories:
  - Markdown/Writing tools (headers, formatting, todo)
  - Text editing operations (cut, wrap, select)
  - Application shortcuts (Obsidian, Google Docs, Logic Pro)
  - Utility functions (date, time)
- Full VIA support with descriptive names for all macros
- Modular architecture for easy maintenance

### Keyboard Configuration
- **8 Layers** for maximum customization flexibility
- **All 47 RGB Matrix effects** enabled
- **Custom base layout** with specialized keys
- **Encoder support** with per-layer functionality

## Layout Details

### Base Layer (Layer 0)
- Custom arrow key placement (Up on row 4, Left/Down/Right on row 5)
- Paste macro (Cmd+V) on first key of bottom row
- Double shift keys on right side of row 4
- Layer switching: MO(1) and MO(2) for function layers

### Function Layers
- **Layer 1 (MAC_FN1)**: Function keys, media controls, RGB controls
- **Layer 2 (MAC_FN2)**: Secondary functions, system controls
- **Layers 3-7**: Available for VIA customization

## Custom Macros

All macros accessible through VIA's CUSTOM tab:

### Writing & Markdown
- `MD H1`, `MD H2`, `MD H3` - Markdown headers
- `Bold`, `Italic` - Text formatting
- `TODO` - Todo checkbox
- `EmDash` - Em dash with spaces

### Text Editing
- `Cut←`, `Cut→` - Cut to line start/end
- `CutW←`, `CutW→` - Cut previous/next word
- `Cut¶` - Cut paragraph
- `Wrap"`, `Wrap()`, `Wrap[]` - Wrap selections

### Applications
- `Daily`, `Search`, `Graph` - Obsidian shortcuts
- `GD H1`, `GD H2`, `GD H3` - Google Docs headers
- `Split`, `Join`, `XFade` - Logic Pro operations

## Installation

### Compiling
```bash
qmk compile -kb keychron/q15_max/ansi_encoder -km delilah
```

### Flashing
1. Put keyboard in DFU mode (hold ESC while plugging in)
2. Run:
```bash
qmk flash -kb keychron/q15_max/ansi_encoder -km delilah
```

## VIA Configuration

### Loading Custom Definitions
1. Open VIA (web or desktop)
2. Settings → Show Design tab
3. Design → Load Draft Definition
4. Load: `via_custom_keycodes.json`

### Using Custom Macros
1. After loading the JSON, go to the CUSTOM tab in keycode picker
2. All 32 macros will appear with descriptive names
3. Drag and drop macros to any key position
4. Configure up to 8 layers

## Files Included

- `keymap.c` - Main keymap with 8 layers
- `config.h` - Configuration for layers and macros
- `rules.mk` - Build rules and user integration
- `via_custom_keycodes.json` - VIA definition with all macros
- `README.md` - This documentation

## Technical Architecture

This keymap integrates with the `d3lilah_qmk` user directory, providing:
- Modular macro organization
- Reusable across multiple keyboards
- Clean separation of concerns
- VIA-compatible custom keycodes (QK_KB_0 - QK_KB_31)

## Customization

To modify macros:
1. Edit files in `users/d3lilah_qmk/macros/`
2. Recompile firmware
3. Flash to keyboard

To change layout:
1. Edit layer definitions in `keymap.c`
2. Use VIA for dynamic remapping

## Reference Implementation

This keymap serves as a reference for:
- Porting Vial macros to QMK
- Implementing VIA custom keycodes
- Creating modular macro systems
- Maximum layer and macro utilization

## Author

Created by d3lilah (2024) as a reference implementation for advanced QMK/VIA integration.