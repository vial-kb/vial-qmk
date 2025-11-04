# Cantordeon

Inspired by [El Cantor HS](https://github.com/azhizhinov/ELCANTORHS)

![Cantordeon](https://cornedeon.ru/img/cantordeon_1_over.jpg)

This keyboard a mod of El Cantor HS with rp2040 MCU and diode matrix, optimized for handwired.

* Keyboard Maintainer: [alko](https://github.com/alko-kbd/)
* Gallery: [Cornedeon](https://cornedeon.ru)
* Case 3D Model: [Thingiverse](https://www.thingiverse.com/thing:7161522)
* Hardware Supported: rp2040-zero

## Build firmware

qmk compile -kb alko/cantordeon -km vial

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the two top left keys (top right for right side) and plug in the keyboard.
* **Physical reset button**: 
  * Press and hold the BOOT button.
  * Press and release the RESET button.
  * Release the BOOT button.

