First of all: YMDK has an existing 10-layer Vial firmware available for their ID75 keyboard, (with only 15 Macros)
You may just ask them to email a copy to you and skip the need to compile the firmware yourself.


This code is for for idobao/ymdk id75 keyboard which runs on the STM32F103C8T6 chip/MCU
This original code is from YMDK service representative, with minor bug fix  and changes to to port it to be vial-qmk ready
YMDK service representative refused to show you how to setup and compile the uf2 for the id75 keyboard.

This firmware is both VIA and VIAL compatable, you may use eiter tool to configure the keyboard. 
But the vial is noticeably provide a whole lot extra features, like tap dance, combos, key override, etc.


WARNING: the code is compilable and lightly tested. you will fix any issue you may encounter.
Rarely, you may see error when use the firmware with the Vial Tool, 
just close and reopen the Vial tool to dismiss the error, it won't affect the usage of the keyboard in any ways

You need a working environment to be able to compile the code, for windows, it is MSYS
follow the steps in below location to setup your Vial-QMK environment
https://get.vial.today/docs/porting-to-vial.html
(you may need to follow the link inside above link if you also need to set up the QMK development environment)



Steps to to pull the source code from https://github.com/fghxu/vial-qmk.git
(suppost you will check out the vial-qmk repo at : d:/qmk/)

below steps are performed within the MSYS 
``` sh

cd /d/qmk
git clone https://github.com/fghxu/vial-qmk.git
cd /d/qmk/vial-qmk 
make git-submodule

```

#optional : delete the .build folder under /d/qmk/vial-qmk/  (just in case it has old definitions)

#to compile the firmware:
``` sh

make ymdk/id75:vial

```

you will have the firmware named "ymdk_id75_vial.uf2" placed under d:/qmk/vial-qmk/
follow the YMDK id75 instruction to reset the keyboard and copy the above .uf2 file under the  USB drive
i.e. 
1) if you already have configured the QMK Reset key in your current keyboard, you don't need to open the keyboard to press the hardware reset key.  just press the key to reset the keyboard to BootLoader mode
2) otherwise, double push the hardware reset button in the back of the PCB 

3) there will be a USB drive appears in Windows My Computer, drag the .uf2 to the USB drive. the you are all set
4) open the vial tool and start configure your own way


