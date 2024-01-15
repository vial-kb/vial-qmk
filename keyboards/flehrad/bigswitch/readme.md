Big Switch PCB by flehrad
=========================

Designed by Don of the Board Podcast and sold as a kit by [keeb.io](https://keeb.io/collections/frontpage/products/big-switch-pcb?variant=7507922845726)

### PCB Files

https://github.com/flehrad/Big-Switch-PCB

### Building Firmware

* Via: `make flehrad/bigswitch:default` 
* Vial: `make flehrad/bigswitch:vial` 

### Flashing Firmware
Flash with `qmk flash -kb flehrad/bigswitch -mk <vial or default>` or flash hex file to board with QMK Toolbox+Auto Flash.
Quickly short GND and RST (2 pins right below TX) to get Pro Micro into bootloader mode. 
Note that resetting the microcontroller may take a couple of tries.

### Technical Specifications

 * Uses a atmega32u4 pro micro or pin compatible MCU
 * Pins B5 and B6 connect to the pins on the Big Switch
 * Optionally you may add a RGB strip to pin D3 for data and take power from VCC and GND
