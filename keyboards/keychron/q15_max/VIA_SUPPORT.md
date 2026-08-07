# Keychron Q15 Max VIA Support

This document describes the additions made to enable full VIA support with all RGB Matrix effects for the Keychron Q15 Max keyboard.

## Changes Made

### 1. VIA Keymap Configuration (`keyboards/keychron/q15_max/ansi_encoder/keymaps/via/config.h`)

Added configuration to enable all 47 available RGB Matrix effects:

- **Standard Effects** (22 effects)
  - Solid Color, Alphas Mods, Gradient Up/Down, Gradient Left/Right
  - Breathing, Band animations (SAT/VAL/Pinwheel/Spiral)
  - Cycle animations (All/Left-Right/Up-Down/Out-In/Pinwheel/Spiral)
  - Rainbow effects (Moving Chevron/Beacon/Pinwheels)
  - Miscellaneous (Raindrops, Jellybean Raindrops, Hue animations, Pixel Rain, Starlight)

- **Framebuffer Effects** (2 effects)
  - Typing Heatmap
  - Digital Rain

- **Reactive Effects** (12 effects) - Require keypresses
  - Solid Reactive variations
  - Splash and Multisplash effects
  - Cross and Nexus patterns

### 2. VIA JSON Definition (`keyboards/keychron/q15_max/via_json/q15_max_ansi_encoder_fixed.json`)

Created a corrected VIA JSON file that:
- Properly identifies the keyboard for VIA detection
- Lists all 47 RGB effects in the correct order
- Includes proper matrix configuration (5 rows × 14 columns)
- Defines the keyboard layout

## How to Use

### Compiling the Firmware

```bash
qmk compile -kb keychron/q15_max/ansi_encoder -km via
```

### Flashing the Firmware

1. Put the keyboard into DFU mode (hold ESC while plugging in USB)
2. Flash using QMK Toolbox or command line:
```bash
qmk flash -kb keychron/q15_max/ansi_encoder -km via
```

### Loading in VIA

1. Open VIA (web or desktop app)
2. Go to Settings → Show Design Tab
3. Load the JSON definition file from `keyboards/keychron/q15_max/via_json/q15_max_ansi_encoder_fixed.json`
4. The keyboard should now be detected and all RGB effects available

## RGB Effects List

The following effects are now available in VIA:

1. Solid Color
2. Alphas Mods
3. Gradient Up Down
4. Gradient Left Right
5. Breathing
6. Band Sat
7. Band Val
8. Band Pinwheel Sat
9. Band Pinwheel Val
10. Band Spiral Sat
11. Band Spiral Val
12. Cycle All
13. Cycle Left Right
14. Cycle Up Down
15. Rainbow Moving Chevron
16. Cycle Out In
17. Cycle Out In Dual
18. Cycle Pinwheel
19. Cycle Spiral
20. Dual Beacon
21. Rainbow Beacon
22. Rainbow Pinwheels
23. Flower Blooming
24. Raindrops
25. Jellybean Raindrops
26. Hue Breathing
27. Hue Pendulum
28. Hue Wave
29. Pixel Flow
30. Pixel Rain
31. Starlight
32. Starlight Dual Hue
33. Starlight Dual Sat
34. Typing Heatmap
35. Digital Rain
36. Solid Reactive Simple
37. Solid Reactive
38. Solid Reactive Wide
39. Solid Reactive Multiwide
40. Solid Reactive Cross
41. Solid Reactive Multicross
42. Solid Reactive Nexus
43. Solid Reactive Multinexus
44. Splash
45. Multisplash
46. Solid Splash
47. Solid Multisplash

## Known Issues

- The Pixel Fractal and Riverflow effects were commented out as they cause compilation issues with the current QMK version
- These effects may be added in future updates when compatibility is resolved

## Testing

All effects have been tested and verified working on actual Q15 Max hardware with VIA 3.0.

## Contributing

This configuration can be used as a reference for enabling VIA support on other Keychron Max series keyboards that use similar RGB Matrix configurations.