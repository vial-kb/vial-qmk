# Little Big Scroll 6

![littlebigscroll6](imgur.com image replace me!)

A simple, easy to build, low cost macro pad with 6 Cherry MX hot swap keys and a clickable encoder wheel


* Keyboard Maintainer: [Markus Knutsson](https://github.com/TweetyDaBird)
* Hardware Supported: [LittleBigScroll 6 PCB](https://github.com/TweetyDaBird/Little-Big-Scroll), Pro Micro or pin-compatible
* Hardware Availability: https://lectronz.com/stores/tweetys-wild-thinking

## Make example for this keyboard (after setting up your build environment):

    make tweetydabird\lbs6:vial

Flashing example for this keyboard:

    make tweetydabird\lbs6:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the bottom left key and plug in the keyboard
* **Physical reset button**: Briefly short the two pads on the top right of the PCB, next to the USB cable
* **Keycode**: Assign the keycode to a button
