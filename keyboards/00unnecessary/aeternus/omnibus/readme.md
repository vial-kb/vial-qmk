# Omnibus

![Omnibus](https://cdn.shopify.com/s/files/1/0501/5080/1588/products/IMG_9986_1024x1024@2x.jpg?v=1629070461)

A drop-in replacement PCB for most Minivan cases. Also supports every known bottom row layout.

* Keyboard Maintainer: [Aeternus](https://github.com/AeternusCo)
* Hardware Supported: Most Minivan cases
* Hardware Availability: https://store.aeternus.co/products/omnibus-pcb

Make example for this keyboard (after setting up your build environment):

    make aeternus/omnibus:default

Flashing example for this keyboard:

    make aeternus/omnibus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available