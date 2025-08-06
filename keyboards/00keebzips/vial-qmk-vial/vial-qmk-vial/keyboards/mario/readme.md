# mario

![mario](https://github.com/YkieWang/images/blob/main/DSC01937.JPG)
![mario](https://github.com/YkieWang/images/blob/main/DSC01938.JPG)
![mario](https://github.com/YkieWang/images/blob/main/DSC01940.JPG)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Yuting Wang](https://github.com/YkieWang)
* Hardware Supported: *coming soon*
* Hardware Availability: *coming soon*
* I designed this keyboard based on crkbd, thanks the maintainers of crkbd! And I added a encoder in the left and a joystick in the right. The encoder could help me with scrolling, while the joystick can control the cursor, which makes things easier when I code, because I don't need to move my hand to reach the mouse.

Make example for this keyboard (after setting up your build environment):

    make mario:vial

Flashing example for this keyboard:

    make mario:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
