# Q15 Max Autocorrect Implementation

## Overview
This keymap includes QMK's autocorrect feature with a 400-word dictionary, automatically correcting common typos as you type.

## Features
- **400-word autocorrect dictionary** from D_38 keyboard implementation
- **Starts enabled by default** when keyboard powers on
- **Toggle with Fn2 + A** to enable/disable on the fly
- **6KB compiled dictionary** (increases firmware size by ~5KB)

## Key Mapping
- **AC_TOGG** (0x7C76): Located at **Fn2 + A**
  - Press to toggle autocorrect on/off
  - Can be remapped in VIA using hex code 0x7C76

## Files
- `autocorrect_dictionary.txt`: 400-word source dictionary
- `autocorrect_data.h`: Generated binary data (6KB)
- `rules.mk`: Contains `AUTOCORRECT_ENABLE = yes`
- `keymap.c`:
  - AC_TOGG mapped to Layer 2, position (2,1) - the 'A' key
  - `keyboard_post_init_user()` enables autocorrect on startup

## Dictionary Format
The dictionary uses special prefixes:
- `:word` - Only corrects at word boundaries
- `word` - Corrects anywhere it appears

Examples from dictionary:
- `:thier → their` (word boundary)
- `becuase → because` (anywhere)
- `effeceincy → efficiency` (anywhere)

## Building
1. Generate autocorrect data:
   ```bash
   qmk generate-autocorrect-data -kb keychron/q15_max/ansi_encoder -km delilah \
     keyboards/keychron/q15_max/ansi_encoder/keymaps/delilah/autocorrect_dictionary.txt
   ```

2. Compile firmware:
   ```bash
   qmk compile -kb keychron/q15_max/ansi_encoder -km delilah
   ```

## Customization
To modify the dictionary:
1. Edit `autocorrect_dictionary.txt`
2. Regenerate `autocorrect_data.h` using the command above
3. Recompile firmware

## VIA Configuration
The keymap includes:
- 8 layers
- 32 custom macros
- Full RGB Matrix effects (47 total)
- Autocorrect support

Load `q15_max_delilah.json` in VIA for full functionality.