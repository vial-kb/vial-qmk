# TuStation TQ61

A 61-key ANSI staggered mechanical keyboard with in-switch backlight support, powered by STM32F103 - a lean TuStation DIY kit.

* Keyboard Maintainer: [TuStation Team](https://github.com/tustation)
* Hardware Supported: TQ61 PCB, STM32F103
* Hardware Availability: [TuStation Wiki](http://wiki.tustation.cn:100/)

## Features

- 61-key ANSI layout
- 5x14 matrix
- Per-key in-switch backlight (TIM4, PB4)
- Caps Lock indicator (B5)
- STM32F103 MCU, stm32duino bootloader
- Vial-compatible via vial keymap

## Bootloader

Enter the bootloader in any of the following ways:

* **Bootmagic reset**: Hold down the top-left key while plugging in the USB
* **Physical reset button**: Short press the RST button on the PCB
* **Keycode**: Press the key mapped to `QK_BOOT` on the function layer

## Making firmware

    make tustation/tq61:default
    make tustation/tq61:vial

## Flashing

    make tustation/tq61:default:flash
    make tustation/tq61:vial:flash

## QMK Build Environment

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).