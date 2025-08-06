# Gyrovan

![Gyrovan](https://i.imgur.com/2meFupl.jpg)

*A MiniVan/Vanagon/Embrace-compatible PCB powered by an STM32F072*
* Keyboard Maintainer: [NCKiser](https://github.com/NCKiser)
* Hardware Supported: Gyrovan PCB, STM32F072

Make example for this keyboard (after setting up your build environment):

    make kiserdesigns/gyrovan:default

Flashing example for this keyboard:

    make kiserdesigns/gyrovan:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (ESC key) and plug in the keyboard
* **Physical bootsel button**: Hold down the button on the back of the PCB while plugging into the computer
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
