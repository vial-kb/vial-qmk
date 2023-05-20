# The Vial keymap for Zoom65 Lite

This is the Vial keymap for the Zoom65 Lite. 

Several (arbitrary) QMK features have been modified / disabled to reduce the size of the final firmware binary and make it fit in the (otherwise kind of limited) memory of the `atmega32u4` microcontroller.

These arbitrary configurations are:

- reduce the number predefined keyboard layouts to 3
- disable *key override* feature
- disable *combo* feature

If you any of the above configuration decisions conflicts with your needs, feel free to adjust the configuration as long as the final binary still fits in the microcontroller memory.
