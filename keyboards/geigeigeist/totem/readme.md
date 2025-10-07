# TOTEM

TOTEM is a 38-key column-staggered split keyboard by GEIGEIGEIST designed for Seeed XIAO RP2040 or XIAO nRF52840 BLE. This port targets the wired RP2040 variant.

-   Repository: https://github.com/GEIGEIGEIST/TOTEM
-   Controller: Seeed Studio XIAO RP2040
-   Split transport: vendor serial (RP2040) on GP0/GP1
-   Matrix: 8 rows x 5 columns
-   Diodes: COL2ROW

Build

-   Default keymap:
    qmk compile -kb geigeigeist/totem -km default

-   Vial keymap:
    qmk compile -kb geigeigeist/totem -km vial

Notes

-   The JSON-driven keyboard definition is in keyboard.json (QMK data-driven format).
-   For Vial, the UID and unlock combo are defined in keymaps/vial/config.h, with VIAL_ENABLE in keymaps/vial/rules.mk.
-   If using XIAO RP2040 bootloader, double-tap reset is enabled (500ms timeout).
