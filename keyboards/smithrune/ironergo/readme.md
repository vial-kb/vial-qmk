# Smith and Rune Iron Ergo QMK folder

## Introduction

This is the QMK Firmware repository for the Iron Ergo PCB, a keyboard designed by [Smith and Rune](https://smithrune.com/) and PCB designed by [Gondolindrim](http://github.com/Gondolindrim).

The Iron Ergo is an Alice-layout PCB designed for the Iron Ergo keyboardt. It supports in-switch single-color LEDs.

As of June 2023, the Iron Ergo has not entered public sale.

## How to compile

After setting up your build environment, you can compile the Iron180 default keymap by using:

    make smithrune/ironergo:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (ESC key in the default layout) and plug in the keyboard
* **Physical reset button**: press and hold the button on the back of the PCB for at least 5 seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (ESC key at layer 1 in the default layout)
