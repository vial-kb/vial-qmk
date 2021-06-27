# rp2040_split

* Sample implementation for RP2040.

* Keyboard Maintainer: [sekigon-gonnoc](https://github.com/sekigon-gonnoc)

Since RP2040 does not have VBUS detect ports, `SPLIT_USB_DETECT` is enabled automatically.

Make split for this keyboard (after setting up your build environment):

    make rp2040_split:default

Flashing split for this keyboard by `picotool`:

    make rp2040_split:default:flash

Convert firmware into uf2 format:

    make rp2040_split:default:uf2

To replace Pro Micro to Pico Micro, use `CTPIM=yes` (`CONVERT_TO_PICO_MICRO=yes`):

    make <your_keyboard>:<your_keyamp>:<output option> CTPIM=yes


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
