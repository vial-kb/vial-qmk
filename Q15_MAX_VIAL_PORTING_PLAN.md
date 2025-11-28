# Keychron Q15 Max Vial Porting Plan

## Executive Summary

This document outlines a comprehensive plan to port the Keychron Q15 Max from QMK/VIA to Vial firmware. The Q15 Max is a wireless numpad with special considerations due to its STM32F401 MCU and SNLED27351 SPI LED driver. The plan follows the established pattern from the Keychron Q3 Vial implementation.

## Current State Analysis

### Repository Context
- **Current Branch**: vial
- **Source Implementation**: q15-max-via-clean branch (Keychron's wireless_playground fork)
- **Reference Implementation**: Keychron Q3 (already has Vial support)

### Q15 Max Hardware Specifications
- **MCU**: STM32F401 (wireless-capable)
- **LED Driver**: SNLED27351 (SPI interface)
- **Form Factor**: Numpad with knob/encoder
- **Wireless**: Bluetooth support required

## Vial Implementation Structure (Based on Q3 Analysis)

### Required File Structure
```
keyboards/keychron/q15_max/
├── config.h                    # Base configuration
├── halconf.h                   # HAL configuration
├── mcuconf.h                   # MCU-specific configuration
├── matrix.c                    # Matrix implementation
├── q15_max.c                   # Keyboard-specific code
├── info.json                   # QMK info file
├── readme.md                   # Documentation
└── ansi_encoder/              # Variant folder
    ├── ansi_encoder.c         # Variant-specific code
    ├── config.h               # Variant configuration
    ├── keyboard.json          # Keyboard definition
    ├── readme.md              # Variant documentation
    └── keymaps/
        ├── default/           # DEFAULT keymap (required first)
        │   ├── keymap.c       # Default keymap implementation
        │   └── rules.mk       # Default rules
        └── vial/              # VIAL keymap
            ├── config.h       # Vial-specific configuration
            ├── keymap.c       # Vial keymap implementation
            ├── rules.mk       # Vial build rules
            └── vial.json      # Vial layout definition
```

### Key Vial Configuration Elements

#### 1. Vial UID Generation (config.h)
```c
#define VIAL_KEYBOARD_UID {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }  // Adjust for Q15 Max matrix
#define VIAL_UNLOCK_COMBO_COLS { 0, 4 }  // Adjust for Q15 Max matrix
```

#### 2. Build Rules (rules.mk)
```makefile
VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes

VPATH += keyboards/keychron/common
SRC += keychron_common.c
```

#### 3. Vial JSON Structure
- Vendor ID: 0x3434 (Keychron standard)
- Product ID: (needs to be determined from Q15 Max)
- Matrix size configuration
- Custom keycodes for Mac/Windows features
- Visual layout representation

## Step-by-Step Porting Plan

### Phase 1: Preparation and Setup

1. **Checkout and Merge Base Code**
   - Create a new branch from vial: `q15-max-vial-port`
   - Cherry-pick or merge Q15 Max implementation from q15-max-via-clean branch
   - Resolve any merge conflicts

2. **Verify Base Functionality**
   - Ensure Q15 Max builds successfully with VIA support
   - Test basic keyboard functionality
   - Document the existing file structure

### Phase 2: Create DEFAULT Keymap

3. **Implement Default Keymap**
   - Copy VIA keymap as starting point
   - Remove VIA-specific features
   - Simplify to basic QMK functionality
   - Structure:
     ```c
     // keymap.c
     enum layers {
         BASE,
         FN
     };

     const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
         [BASE] = LAYOUT_numpad_6x5(
             // Define base layer
         ),
         [FN] = LAYOUT_numpad_6x5(
             // Define function layer
         )
     };
     ```

4. **Test Default Keymap**
   - Build: `qmk compile -kb keychron/q15_max/ansi_encoder -km default`
   - Flash and verify functionality
   - Document any issues

### Phase 3: Implement Vial Support

5. **Create Vial Keymap Directory**
   ```bash
   mkdir -p keyboards/keychron/q15_max/ansi_encoder/keymaps/vial
   ```

6. **Generate Vial UID**
   - Use Python script or online generator
   - Ensure unique UID across Vial ecosystem
   - Example: `python3 util/vial_generate_keyboard_uid.py`

7. **Create Vial Configuration (config.h)**
   ```c
   #pragma once

   // Vial Keyboard UID
   #define VIAL_KEYBOARD_UID {generated_uid_here}

   // Unlock combo (adjust for Q15 Max matrix)
   #define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
   #define VIAL_UNLOCK_COMBO_COLS { 0, 4 }

   // Optional: Increase dynamic keymap layers if needed
   #define DYNAMIC_KEYMAP_LAYER_COUNT 4
   ```

8. **Create Build Rules (rules.mk)**
   ```makefile
   VIA_ENABLE = yes
   VIAL_ENABLE = yes
   VIALRGB_ENABLE = yes

   # Include Keychron common functionality
   VPATH += keyboards/keychron/common
   SRC += keychron_common.c

   # Reduce firmware size if needed
   LTO_ENABLE = yes
   ```

9. **Implement Vial Keymap (keymap.c)**
   ```c
   #include QMK_KEYBOARD_H
   #include "keychron_common.h"

   enum layers {
       BASE,
       FN,
       L2,
       L3
   };

   const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
       // Copy from default but use Keychron custom keycodes
       // Include all 4 layers for Vial configurability
   };

   void housekeeping_task_user(void) {
       housekeeping_task_keychron();
   }

   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
       if (!process_record_keychron(keycode, record)) {
           return false;
       }
       return true;
   }
   ```

10. **Create Vial JSON Layout**
    - Use Vial's KLE converter or manual creation
    - Include:
      - Matrix positions
      - Visual layout
      - Custom keycodes definitions
      - Encoder support (if applicable)

### Phase 4: Wireless Considerations

11. **Validate Wireless Compatibility**
    - STM32F401 is supported by both QMK and Vial
    - Bluetooth functionality should work through QMK's bluetooth driver
    - No known incompatibilities with Vial

12. **Configure Wireless Features**
    - Ensure bluetooth keycodes are properly mapped
    - Test power management features
    - Verify RGB behavior over bluetooth

### Phase 5: Testing and Validation

13. **Build Verification**
    ```bash
    qmk compile -kb keychron/q15_max/ansi_encoder -km vial
    ```

14. **Functional Testing**
    - Flash firmware
    - Connect to Vial GUI
    - Test all keys and layers
    - Verify encoder functionality
    - Test RGB controls
    - Validate wireless features

15. **Memory Optimization** (if needed)
    - Enable LTO
    - Reduce DYNAMIC_KEYMAP_LAYER_COUNT
    - Disable unused features
    - Consider VIAL_COMBO_ENTRIES reduction

## Potential Challenges and Solutions

### Challenge 1: Memory Constraints
**Issue**: STM32F401 has limited flash (256KB)
**Solution**:
- Enable LTO_ENABLE = yes
- Reduce layer count if necessary
- Disable unused RGB effects
- Use CONSOLE_ENABLE = no

### Challenge 2: Wireless Integration
**Issue**: Bluetooth stack might conflict with Vial
**Solution**:
- Vial is VIA-compatible, so wireless should work
- Test thoroughly with both USB and Bluetooth
- May need to adjust VIAL_KEYBOARD_UID for wireless variant

### Challenge 3: SNLED27351 Driver Compatibility
**Issue**: SPI LED driver might have Vial-specific issues
**Solution**:
- VIALRGB_ENABLE should handle this
- Reference other Keychron boards with similar drivers
- May need custom RGB implementation in keymap

### Challenge 4: Encoder Support
**Issue**: Rotary encoder mapping in Vial
**Solution**:
- Include encoder definitions in vial.json
- Map encoder to proper matrix positions
- Test with Vial GUI encoder configuration

## Implementation Timeline

1. **Day 1-2**: Setup and DEFAULT keymap creation
2. **Day 3-4**: Vial implementation and configuration
3. **Day 5-6**: Testing and debugging
4. **Day 7**: Documentation and cleanup

## Success Criteria

- [ ] Q15 Max builds successfully with Vial support
- [ ] All keys register correctly in Vial GUI
- [ ] RGB lighting works through Vial
- [ ] Encoder functions properly
- [ ] Wireless functionality maintained
- [ ] Firmware size within limits
- [ ] Custom Keychron keycodes work

## Testing Checklist

### Basic Functionality
- [ ] All keys register
- [ ] Layers switch properly
- [ ] Encoder rotates and clicks
- [ ] RGB modes cycle

### Vial-Specific
- [ ] Vial GUI detects keyboard
- [ ] Key remapping works
- [ ] Macro recording functions
- [ ] RGB configuration saves
- [ ] Layer tap/hold works

### Wireless Testing
- [ ] Bluetooth pairing works
- [ ] Keys register over Bluetooth
- [ ] Power management functions
- [ ] USB/Bluetooth switching works

## Files to Create/Modify

1. **New Files**:
   - `/keyboards/keychron/q15_max/ansi_encoder/keymaps/default/keymap.c`
   - `/keyboards/keychron/q15_max/ansi_encoder/keymaps/default/rules.mk`
   - `/keyboards/keychron/q15_max/ansi_encoder/keymaps/vial/config.h`
   - `/keyboards/keychron/q15_max/ansi_encoder/keymaps/vial/keymap.c`
   - `/keyboards/keychron/q15_max/ansi_encoder/keymaps/vial/rules.mk`
   - `/keyboards/keychron/q15_max/ansi_encoder/keymaps/vial/vial.json`

2. **Modified Files** (if needed):
   - `/keyboards/keychron/q15_max/config.h` (add Vial-compatible defines)
   - `/keyboards/keychron/q15_max/ansi_encoder/keyboard.json` (ensure VIA/Vial compatibility)

## Resources and References

- Vial Documentation: https://get.vial.today/docs/
- QMK Documentation: https://docs.qmk.fm/
- Keychron Q3 Reference: `/keyboards/keychron/q3/ansi/keymaps/vial/`
- Vial UID Generator: `python3 util/vial_generate_keyboard_uid.py`

## Notes

- The Q15 Max uses Keychron's custom keycodes (KC_LOPTN, KC_ROPTN, etc.)
- Must include keychron_common.c for proper functionality
- Vial is backward compatible with VIA, so existing VIA keymaps provide good base
- Consider creating a vial-wireless variant if Bluetooth requires different configuration

## Conclusion

This porting plan provides a systematic approach to adding Vial support to the Keychron Q15 Max. The wireless nature of the keyboard (STM32F401) should not pose significant challenges as Vial fully supports this MCU. The main considerations are memory optimization and ensuring all Keychron-specific features work correctly with Vial.