# Le Chiffre 32

32-bit version of the Le Chiffre originally designed by tominabox1

* Keyboard Maintainer: [sporkus](https://github.com/sporkus)
* Hardware Supported: APM32F072
* Hardware Availability: [](https://github.com/sporkus/le_chiffre_keyboard_stm32)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb sporkus/le_chiffre_stm32 -km default

Flashing example for this keyboard:

    qmk flash -kb sporkus/le_chiffre_stm32 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the DFU bootloader in 3 ways:

* **Physical DFU button**: hold the button while powering up the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
