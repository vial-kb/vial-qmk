# Suffer (SVFFER)

![Suffer Layouts](https://i.imgur.com/fPsC2Uj.jpeg)

*Suffer is a 12-18 key macropad inspired by the [masochist16 by Zicodia](https://github.com/Z1codia/masochist16), with a case designed by seirin_blu*
* Keyboard Maintainer: [NCKiser](https://github.com/NCKiser)
* Hardware Supported: Suffer PCB (V1: 32u4, V2: STM32)
* Hardware Availability: kiserdesigns.com

Make example for this keyboard (after setting up your build environment):

    make kiserdesigns/suffer/v2:default

Flashing example for this keyboard:

    make kiserdesigns/suffer/v2:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly double-tap the reset button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
