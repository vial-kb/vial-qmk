This is a place for me to put my various QMK firmware profiles and compiled .hex files, plus a few .uf2 files for using RP2040-based boards. (It's weird that people hardly ever make the compiled firmware files available for download, right?) Also check out [this repo](https://github.com/Xelus22/QMK-VIA-Hex) for pre-compiled VIA firmware for tons of keyboards and [this page](https://keyboard.gay/) for pre-compiled VIAL firmware! Thanks to XDeckerX for creating compiled KLOR firmware!

The easiest way to flash firmware (that has already been compiled) is with the [QMK Toolbox](github.com/qmk/qmk_toolbox).

Install the Toolbox application, then open the .hex file. Check the "Auto-Flash" option, plug your controller in, and then when you bridge the GND and RST pins it should put the controller in bootloader mode and flash automatically. If your keyboard has a reset switch you can press that instead, while for an Elite-C you should press its built-in reset switch.

![A screenshot of QMK Toolbox with the Open and Auto-Flash controls circled in red](https://github.com/nekoewen/ewen-qmk/blob/main/qmk%20toolbox%20example.png)

For those RP2040-based boards, you just put the board into bootloader mode and drop the file into the drive that appear.
