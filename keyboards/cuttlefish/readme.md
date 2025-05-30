# Sepia officinalis

![Sepia officinalis](https://github.com/tapioki/cephalopoda/raw/main/Images/sepia_officinalis.png)

AKA S. officinalis, S.O., "The first one", "Cuttlefish"

34 keys, aggressive pinky stagger with top pinky key omitted.

## Keyboard Info

* Keyboard Maintainer: [@tapioki](https://github.com/tapioki)
* Hardware Supported: Sepia officinalis
* Hardware Availability: Order PCBs with gerber files from the [repository](https://github.com/tapioki/cephalopoda/tree/main/Sepia%20officinalis)

Make example for this keyboard (after setting up your build environment):

    make cuttlefish:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Setting Handedness

Firmware uses [handedness by EEPROM](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) as default and it must be *configured once* on each side. The make commands are:

    make cuttlefish:default:dfu-split-left
    make cuttlefish:default:dfu-split-right

[QMK Toolbox](http://qmk.fm/toolbox) can also be used to set EEPROM handedness. Place the controller in bootloader mode and select menu option Tools -> EEPROM -> Set Left/Right Hand

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key on the left half (or the top right right key on the right half) and plug in the controller on that side.
* **Physical reset pins**: Briefly short the RST and GND pins on the microcontroller using tweezers, a paperclip, or any other conductive material.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
