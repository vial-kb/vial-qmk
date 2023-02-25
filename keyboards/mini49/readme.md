# mini49  


![mini49](https://raw.githubusercontent.com/pcs3rd/qmk_firmware/master/keyboards/mini49/resources/keeb.jpg)

A sub-60% ortholinear keyboard powered by qmk.  
The VIA configuration can be found [here](https://github.com/pcs3rd/via-configurations/tree/main/keyboards/mini49)

* Keyboard Maintainer: [Raymond Dean][def]
* Hardware Supported: *RP2040*

Make example for this keyboard (after setting up your build environment):

    make mini49:vial

Flashing example for this keyboard:

    make mini49:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader (default keymap only)

Enter the bootloader in 3 ways:

Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
Physical reset button: Briefly press the button on the back of the PCB - some may have pads you must short instead
Keycode in layout: Press the key mapped to QK_BOOT if it is available

[def]: https://github.com/pcs3rd
