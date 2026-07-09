# Model H - A USB capable PCB for the IBM Model M keyboard

![modelh](https://i.imgur.com/4ymGdkM.jpg)

This conversion kit allows you to replace your IBM Model M's original internal controller board with a modern USB board. This aims to match the footprint of the original controller and plugs into the original keyboard matrix, but exposes a USB port through the original SDL connector.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## SSK (Space-saving Keyboard) variant

SSK-specific features were copied and modified from those for the `teensypp_ssk` board.

LED features of the Model H are left enabled in case you want to modify your SSK to add lock-indicator LEDs.

I tested using the Model H sold by Keebd, with IBM part number 1397681 made in
1991.  This matrix appears to differ from the one in `teensypp_ssk`, and
matches the full-size matrix in the Model H definitions.

```bash
qmk compile -kb ibm/model_m_ssk/modelh_ssk -km vial

# DFU device ID 6b62:0000 for Keebd Model H doesn't match stm32duino 1eaf:0003, so using dfu-util directly
dfu-util -D ibm_model_m_ssk_modelh_ssk_vial.bin -R
```

* Keyboard Maintainer: [Mike Bourgeous](https://github.com/mike-bourgeous), based on work by [John Hawthorn](https://github.com/jhawthorn) and [tiltowait](https://github.com/tiltowait)
* Hardware Supported: Model H controller, IBM Model M Space-saving Keyboard
* Hardware Availability: [www.modelh.club](www.modelh.club)
* How to [build your own controller](https://github.com/jberclaz/modelh)
