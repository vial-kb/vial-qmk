# mini49  


![mini49](https://cloud.stickpile.net/apps/files_sharing/publicpreview/YkYfcoeLRmHpfy2?file=/&fileId=225288&x=1080&y=1920&a=true)

A sub-60% ortholinear keyboard powered by vial-qmk.  

* Keyboard Maintainer: [Raymond Dean][def]
* Hardware Supported: *RP2040*

Make example for this keyboard (after setting up your build environment):

    make mini49:vial

Flashing example for this keyboard:

    make mini49:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard. Bootmagic is not enabled in the vial layout.
- Physical reset: Hold the BOOT button down while pressing the RESET button.  
- Keycode in layout: Press the key mapped to QK_BOOT if it is available

[def]: https://github.com/pcs3rd
