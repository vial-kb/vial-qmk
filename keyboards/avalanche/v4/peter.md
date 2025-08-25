# How to build using vial-qmk

I use vial-qmk instead of qmk-firmware for one reason: The VIA web keyboard configurator does not support Avalanche keyboard yet.
Web configurator is the gem of QMK based keyboard. VIAL is the one supporting it.

To build:
``` bash
git clone https://github.com/peterliu-tw/vial-qmk.git
cd ./vial-qmk
qmk compile -kb avalanche/v4 -km vial
```
The downside of VIAL-QMK is it use a lot of EEPROM size. In the future:
# switch back to qmk-firmware when VIA supports Avalanche.
# Change the microcontroller from ProMicro to RP2040



# How to flash
Get QMK Toolbox and google on how to use it.



# How to Configure keymap
https://vial.rocks/
