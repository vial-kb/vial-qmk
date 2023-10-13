# Herringbone Pro

![Herringbone Pro](https://i.imgur.com/cewklY5l.png)

A through-hole 75% keyboard with a rotary encoder and OLED display!

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Vial port: [Yak](https://github.com/yakMM)
* Hardware Supported: ATmega32A
* Hardware Availability: [Herringbone](https://github.com/ramonimbao/Herringbone)

NOTE: Oled is not enabled on the vial port, due to firmware size constraints.

To get to the bootloader,

1. Press and hold the BOOT button

2. Press the RESET button

3. Release the BOOT button

Make vial for this keyboard (after setting up your build environment):

    make rmi_kb/herringbone/pro:vial

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
