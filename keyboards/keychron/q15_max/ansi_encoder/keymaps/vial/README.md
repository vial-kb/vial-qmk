# Keychron Q15 Max ANSI Encoder - Vial Support

This is a wired-only Vial implementation for the Keychron Q15 Max ANSI variant with dual rotary encoders.

## Features

- **Full Vial GUI support** with proper visual layout
- **Dual rotary encoders** with configurable actions per layer
- **RGB Matrix** with 64 LEDs and all QMK RGB effects
- **Vial configuration**:
  - 16 Macros
  - 8 Tap Dance keys
  - 8 Combos
  - 5 Layers
- **No wireless dependencies** - pure USB/wired implementation

## Technical Details

### RGB Implementation
The RGB Matrix uses the SNLED27351 LED driver in SPI mode. The SPI driver implementation was ported from Tymon3310's Keychron wireless branch, adapted for the official Vial QMK fork.

### Encoder Support
- Two rotary encoders at positions (0,0) and (0,13)
- Default mapping:
  - Base layers: Volume control
  - Function layers: Brightness control
- Fully configurable through Vial GUI

### Key Differences from Stock Firmware
- Removed all wireless/Bluetooth functionality
- Simplified initialization for wired-only operation
- Added Vial-specific features (macros, tap dance, combos)

## Building

```bash
qmk compile -kb keychron/q15_max/ansi_encoder -km vial
```

## Flashing

1. Put the keyboard into bootloader mode (hold ESC while plugging in, or press the reset button)
2. Flash the firmware:
```bash
qmk flash -kb keychron/q15_max/ansi_encoder -km vial
```

## Credits

- **LED Driver (SNLED27351 SPI)**: Ported from Tymon3310's implementation in the Keychron wireless branch
- **Vial Integration**: d3lilah
- **Original Hardware Support**: Keychron

## License

GPL v2 or later, matching QMK's license.