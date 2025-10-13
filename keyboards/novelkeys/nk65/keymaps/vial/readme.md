# Vial Support for NK65 Entry Edition

This keymap adds Vial support to the NK65 v1.0-v1.3 revision keyboard.

## Features

-   Full Vial support for dynamic keymap editing
-   Wilba.tech RGB backlight controls (brightness, effects, colors, speed)
-   VIA compatibility
-   4 configurable layers

## Default RGB Control Keys (Layer 1)

-   **Z/X**: Change effect (EF_DEC/EF_INC)
-   **C/V**: Adjust Color 1 Hue (H1_DEC/H1_INC)
-   **B/N**: Adjust Color 2 Hue (H2_DEC/H2_INC)
-   **M/,**: Adjust Brightness (BR_DEC/BR_INC)
-   **./Slash**: Adjust Effect Speed (ES_DEC/ES_INC)
-   **F/G**: Adjust Color 1 Saturation (S1_DEC/S1_INC)
-   **T/Y**: Adjust Color 2 Saturation (S2_DEC/S2_INC)

## Build

    make novelkeys/nk65:vial

## Flash

To flash the firmware:

1. Unplug the keyboard
2. Hold Escape
3. Plug in the keyboard (while still holding Escape)
4. The keyboard will enter bootloader mode
5. Flash using QMK Toolbox or: `make novelkeys/nk65:vial:flash`

## Notes

-   This keymap uses standard USB endpoints for optimal latency
-   For macOS Globe key support with shared USB endpoints, use the `vial_globe` keymap instead
-   RGB keycodes appear in the "User" section of the Vial configurator
