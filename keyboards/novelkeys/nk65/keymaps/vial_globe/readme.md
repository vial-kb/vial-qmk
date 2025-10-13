# Vial Support for NK65 Entry Edition (with macOS Globe Key)

This keymap adds Vial support with macOS Globe key functionality to the NK65 v1.0-v1.3 keyboard.

## Features

-   Full Vial support for dynamic keymap editing
-   Wilba.tech RGB backlight controls (brightness, effects, colors, speed)
-   VIA compatibility
-   4 configurable layers
-   **macOS Globe key support** - assignable custom keycode for Globe/Fn functionality

## macOS Globe Key

This keymap includes a custom "Globe" keycode that can be assigned to any key through the Vial configurator. The Globe key enables macOS-specific shortcuts such as:

-   **Globe + E**: Emoji picker
-   **Globe + C**: Control Center
-   **Globe + N**: Opens Notifications
-   **Globe + H**: Shows/Hides Desktop
-   **Globe + M**: Navigate menu bar with arrow keys
-   **Globe + A**: Navigate dock with arrow keys
-   Others, but likely not all.

The Globe keycode appears in the "User" section of the Vial configurator.

## Default RGB Control Keys (Layer 1)

-   **Z/X**: Change effect (EF_DEC/EF_INC)
-   **C/V**: Adjust Color 1 Hue (H1_DEC/H1_INC)
-   **B/N**: Adjust Color 2 Hue (H2_DEC/H2_INC)
-   **M/,**: Adjust Brightness (BR_DEC/BR_INC)
-   **./Slash**: Adjust Effect Speed (ES_DEC/ES_INC)
-   **F/G**: Adjust Color 1 Saturation (S1_DEC/S1_INC)
-   **T/Y**: Adjust Color 2 Saturation (S2_DEC/S2_INC)

## Build

    make novelkeys/nk65:vial_globe

## Flash

To flash the firmware:

1. Unplug the keyboard
2. Hold Escape
3. Plug in the keyboard (while still holding Escape)
4. The keyboard will enter bootloader mode
5. Flash using QMK Toolbox or: `make novelkeys/nk65:vial_globe:flash`

## Notes

-   This keymap uses shared USB endpoints (`KEYBOARD_SHARED_EP = yes`) to enable Globe key functionality
-   Shared endpoints allow both regular keypresses and consumer control codes (like Globe key) to be sent together
-   In case of unexpected behavior, use the vial keymap instead for standard Vial support without Globe key or shared mode
-   RGB keycodes and Globe keycode appear in the "User" section of the Vial configurator
