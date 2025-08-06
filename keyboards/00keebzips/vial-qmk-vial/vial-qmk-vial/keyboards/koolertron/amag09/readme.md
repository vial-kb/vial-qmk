# AMAG09 (Koolertron)

![Koolertron AMAG09](https://i.imgur.com/mepvkTe.jpg)

One Handed Macro Mechanical Keyboard, 9 Key with optional RGB backlighting.

- Keyboard Maintainer: [al177](https://github.com/al177)
- Hardware Supported: AMAG09 (ATmega32A)
- Hardware Availability:
    - [Amazon](https://www.amazon.com/Koolertron-Mechanical-Keyboard-One-Handed-Programmable/dp/B0998QM9L2)

Make example for this keyboard (after setting up your build environment):

    make koolertron/amag09:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make amag09:default:flash
    make amag09:vial:flash

**Reset Key**: Hold down the *upper left* key while plugging in the keyboard.

**Tips**:
- The keyboard comes with bootloadHID installed from factory.
- The configuration here is for the single color LED keyboard. RGB versions are presumed to be i2c like the amag23

Based on keyboards/amag23 by ianmclinden

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
