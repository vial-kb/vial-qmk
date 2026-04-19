# YDKB Dusk67

![YDKB Dusk67](https://i.imgur.com/0NZo55x.jpeg)

A 67-key ANSI keyboard from KBDFans/YDKB using an STM32F103 and a custom serial shift-register matrix.

* Keyboard Maintainer: [Sarah Helmbrecht](https://github.com/skhelmbrecht)
* Hardware Supported: YDKB Dusk67 PCB
* Hardware Availability: [KBDFans](https://kbdfans.com/)

Make example for this keyboard (after setting up your build environment):

    make kbdfans/dusk67:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at matrix position (0,0), which is `Esc` in the default keymap, and plug in the keyboard
* **Physical reset button**: Press the reset button on the PCB, if present
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
