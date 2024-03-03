# La Somme

![La Somme](https://i.imgur.com/E9JGFkX.jpg)

*A unibody-split col-stag 10u board by [rubybuilds](https://github.com/onisage) with the PCB designed by [NoahK](https://github.com/NCKiser)*
* Keyboard Maintainer: [NCKiser](https://github.com/NCKiser)
* Hardware Supported: La Somme PCB, rp2040
* Hardware Availability: shop.rubybuilds.com

Make example for this keyboard (after setting up your build environment):

    make kiserdesigns/la_somme:default

Flashing example for this keyboard:

    make kiserdesigns/la_somme:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key or "Q") and plug in the keyboard
* **Physical reset button(s)**: On the back of the PCB: tap the RESET button while holding the BOOT button, or double-tap the RESET button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
