# BigBAE

![BigBAE](https://i.imgur.com/RhkLArW.jpeg)

*A scaled-up Big Enter key macropad supporting ANSI, ISO, and BAE Enter*
* Keyboard Maintainer: [NCKiser](https://github.com/NCKiser)
* Hardware Supported: BigBAE and BigANSI, stm32f072
* Hardware Availability: kiserdesigns.com

Make example for this keyboard (after setting up your build environment):

    make kiserdesigns/bigbae:default

Flashing example for this keyboard:

    make kiserdesigns/bigbae:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the Caps Lock key on the left side) and plug in the keyboard
* **Physical reset button**: On the back of the PCB, Hold the BOOT1 button while plugging in, or tap RST1 while holding BOOT1
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
