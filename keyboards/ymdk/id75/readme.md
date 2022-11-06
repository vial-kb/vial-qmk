- First of all: **YMDK** has an existing 10-layer **Vial** firmware available for their ID75 keyboard, (but with only 15 Macros, and too many unused layers).
- You may just ask them to email a copy to you and skip the needs to compile the firmware yourself.
-
- This code is for for **Idobao/YMDK** version of **id75** keyboard which runs on the **STM32F103C8T6** chip/MCU (a.k.a. the **Blue pills**).  It is not compatible with the **Idobao's** other id75 keyboard which uses **ATmega32** chips.
-
- This code is original from **YMDK** service representative, with minor configuration fix and changes to to port it to be **vial-qmk** ready.
- **YMDK** service representative refused to show you how to setup and compile the uf2 for the id75 keyboards, which make is a huge barriers for inexperience users to make modification on this keyboard.
-
- This firmware is both **via** and **vial** compatible, you may use either configurator tool to configure the keyboard.  But the **vial** is noticeably better and provides a whole lot extra features, like tap dance, combos, key override, etc.
-
- **WARNING**: the code is compliable and lightly tested. you will fix any issue you may encounter.
- Rarely, you may see error when use this firmware with the **vial** configurator tool, but it won't affect the usage of the keyboard in any ways, you may dismiss the error by just close (kill) and reopen the **vial** configurator tool.
-
- You need a working environment to be able to compile the code, for Windows, it is **MSYS**.
  Follow the steps in below location to setup your **Vial-Qmk** environment:
  https://get.vial.today/docs/porting-to-vial.html
  (you may need to follow the link inside above link if you also need to set up the **QMK** development environment, **MSYS**)
-
- Steps to to pull and compile  the source code from https://github.com/fghxu/vial-qmk.git
  (suppose you will check out the **vial-qmk** repo at : d:/qmk/)
  
  Below steps are performed within the **MSYS** 
  ``` sh
  
  cd /d/qmk
  git clone https://github.com/fghxu/vial-qmk.git
  cd /d/qmk/vial-qmk 
  make git-submodule
  
  ```
  
  Optional: (between compilations), delete the .build folder under /d/qmk/vial-qmk/  (just in case it caches the old definitions)
  
  To compile the firmware:
  ``` sh
  
  make ymdk/id75:vial
  
  ```
-
- You will have the firmware named **ymdk_id75_vial.uf2** created and placed under d:/qmk/vial-qmk/.
- Please follow the YMDK id75's instruction to reset the keyboard and copy the above **.uf2** file under the USB drive.   i.e.:
	- 1) if you already have configured the QMK Reset key in your current keyboard, you don't need to open the keyboard to press the hardware reset key.  just press the key to reset the keyboard to BootLoader mode.
	  
	  2) otherwise, double push the hardware reset button in the back of the PCB .
	  
	  3) there will be a USB drive appears in Windows My Computer, drag the .uf2 to the USB drive. the you are all set.
	  
	  4) open the **vial** configurator tool and start configure the keyboard your own way.