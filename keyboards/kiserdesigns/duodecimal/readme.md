# Duodecimal

![Duodecimal](https://i.imgur.com/XNVNMgZ.jpg)

*A Base-Kit compatible, 12u, 5-row, WKL, 50% keyboard conceptualized by SwearWolf, with the PCB designed by Noah Kiser*
* Keyboard Maintainer: [NCKiser](https://github.com/NCKiser)
* Hardware Supported: Duodecimal PCB, STM32F072

Make example for this keyboard (after setting up your build environment):

    make kiserdesigns/duodecimal:default

Flashing example for this keyboard:

    make kiserdesigns/duodecimal:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical bootsel button**: Hold down the button on the back of the PCB while plugging into the computer
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
