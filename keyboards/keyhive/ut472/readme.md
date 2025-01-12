# ut47.2

Somewhere between ortholinear and standard offset. Created to have all the same functions on a Planck in a keyboard but with a more conventional keyboard row stagger.

Keyboard Maintainer: [filoxo](https://github.com/filoxo), [network_operations](https://www.keyhive.xyz)

The keyboard files can be found here: https://github.com/ai03-2725/UT47.2
or purchased at keyhive.xyz

## Instructions

To create a hex file for the UT47.2, run:

    make keyhive/ut472:default

## Layout

Go to the [default layout README](keymaps/default/readme.md) for more information.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## RGB Memory Usage
If you are having unusual issues such as keys sticking (such as ctrl) then you may need to disable RGB animations to save on memory in [keyboard.json](keyboard.json).
Setting rainbow_mood and rainbow_swirl to false for example allows for the keyboard to work well.
See [Example Usage to Reduce Memory Footprint](https://docs.qmk.fm/features/rgblight#example-usage-to-reduce-memory-footprint) for more information.
