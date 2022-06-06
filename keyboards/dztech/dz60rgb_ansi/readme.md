# DZ60RGB-ANSI

![dz60rgb](https://cdn.shopify.com/s/files/1/0043/9140/3591/products/TIM_20190130170231_grande.jpg?v=1548839053)

A hotswap 60% RGB keyboard.

* Keyboard Maintainer: [moyi4681](https://github.com/moyi4681)
* Vial Support: [dc959](https://github.com/dc959)
    > Vial support currently only tested and working on DZ60RGB_ansi v2
* Hardware Supported: DZtech DZ60RGB-ANSI V1 and V2
* Hardware Availability: [KBDfans](https://kbdfans.com/)

There are three versions of the DZ60RGB-ANSI. Please use the appropriate firmware for your board.

* V1: STM32F303 (Arm), takes .bin files
* V2: ATmega32U4 (AVR), takes .hex files
* V2.1: ATmega32U4 (AVR), takes .bin files

Make example for this keyboard (after setting up your build environment):

    make dztech/dz60rgb_ansi/v1:default # Arm (STM32F303)
    make dztech/dz60rgb_ansi/v2:vial # AVR (ATmega32U4)
    make dztech/dz60rgb_ansi/v2_1:default # AVR (ATmega32U4)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Vial Notes
```
Vial support for other revisions may be possible by changing vial.json under keymaps/vial.
Vial RGB control is enabled.
Combo, tap dance, qmk settings and key override are disabled.
Firmware is utilizing 97.7% when I built it, if it fails to build delete the build files and try build again, LTO can cause builds to vary in size.
```
