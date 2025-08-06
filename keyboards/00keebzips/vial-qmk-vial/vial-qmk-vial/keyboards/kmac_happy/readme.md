KMAC Happy keyboard firmware
======================

The KMAC Happy is a HHKB layout 60% keyboard. It is programmed with the 'KMAC KEY MAP' original.

## Hardware
Columns 7-14 and rows 0-4 are wired directly to the ATmega32U4, and columns 0-7 are wired to the [74HC237D demultiplexer](https://www.mouser.de/datasheet/2/916/74HC237-1319445.pdf). Capslock is on E2 and also triggers a reset if held when plugging the cable in.

There is only one individually controllable led, which is the Capslock key.

The ATmega32U4 runs on an external crystal on 8mhz, so you'll have to change the bitclock on the ISP programmer if you're unable to read or write the chip.

## How to build

```
make kmac_happy:default
or
make kmac_happy:vial
```

## How to flash
Hold the capslock key while plugging in the USB and flash the .hex file using QMK Toolbox or Atmel FLIP.

## **IMPORTANT**

The backlight feature does not work in current version, I still does not figure out a way to add backlight function without breaking the firmware size limitation.

May be fixed in future release.

```bash
 * The firmware is too large! 29052/28672 (380 bytes over)
```

## Thanks

Thanks to Evy Dekkers for his great contribution, which makes the porting much easily.
