# Splinter

![Splinter](https://i.imgur.com/PylZQ3S.png)

*A split Minivan-esque board with encoder/macro columns and dropped spacebars envisioned by [Leviathan](https://leviathanmech.com) with a PCB by [Kiser Designs](https://kiserdesigns.com)*
* Keyboard Maintainer: [NCKiser](https://github.com/NCKiser)
* Hardware Supported: Splinter PCB, rp2040
* Hardware Availability: www.kiserdesigns.com

Make example for this keyboard (after setting up your build environment):

    make kiserdesigns/splinter:default

Flashing example for this keyboard:

    make kiserdesigns/splinter:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix ('T' on the left, 'Y' on the right) and plug in the keyboard
* **Physical reset button**: Briefly double-tap the RESET button on the back of the PCB, or hold BOOT then tap RESET
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
