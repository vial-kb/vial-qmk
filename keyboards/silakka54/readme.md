# Silakka54

![Silakka54](https://i.imgur.com/JrsS0kY.png)

Silakka54 is a RP2040 Zero based 54-key column staggered split keyboard. PCB uses hotswap sockets. Design is inspired from REVIUNG41 and Corne keyboards.

* Keyboard Maintainer: [Squalius-cephalus](https://github.com/Squalius-cephalus)
* Hardware Supported: Silakka54 PCB
* Hardware Availability: https://github.com/Squalius-cephalus/silakka54

Make example for this keyboard (after setting up your vial build environment):

    make silakka54:vial

Flashing example for this keyboard:

    make silakka54:vial:flash

## Bootloader

Enter the bootloader in 2 ways:

* **Physical boot button**: Hold BOOT button down and connect MCU to the PC
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
