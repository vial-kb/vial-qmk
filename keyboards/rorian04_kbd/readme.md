# rorian04_kbd
![1726747889080](https://github.com/user-attachments/assets/acade73f-5c4c-4c72-9565-6f4eeff3b5da)


A one hand keyboard with multiple layers (vial only)

* Keyboard Maintainer: [Rorian04](https://github.com/Rorian04)
* Hardware Supported: waveshare rp2040


Make example for this keyboard (after setting up your build environment):

    qmk compile -kb rorian04_kd -km vial

Flashing example for this keyboard:

Waveshare rp2040 has a inbuilt bootloader so you just copy paste the ".uf2" file into the keyboard drive while bootmode is active.
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Reset button in mcu**: Hold down both the buttons in the rp2040 mcu while plugging in
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
