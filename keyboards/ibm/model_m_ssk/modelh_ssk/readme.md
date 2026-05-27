# Model H - A USB capable PCB for the IBM Model M keyboard

![modelh](https://i.imgur.com/4ymGdkM.jpg)

This conversion kit allows you to replace your IBM Model M's original internal controller board with a modern USB board. This aims to match the footprint of the original controller and plugs into the original keyboard matrix, but exposes a USB port through the original SDL connector.

Make example for this keyboard (after setting up your build environment):

    make ibm/model_m_ssk/modelh:vial

Flashing example for this keyboard:

    make ibm/model_m_ssk/modelh:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## SSK (Space-saving Keyboard) variant

SSK-specific features were copied and modified from those for the `teensypp_ssk` board.

LED features of the Model H are left enabled in case you want to modify your SSK to add lock-indicator LEDs.

* Keyboard Maintainer: [Mike Bourgeous](https://github.com/mike-bourgeous), based on work by [John Hawthorn](https://github.com/jhawthorn) and [tiltowait](https://github.com/tiltowait)
* Hardware Supported: Model H controller, IBM Model M Space-saving Keyboard
* Hardware Availability: [www.modelh.club](www.modelh.club)
* How to [build your own controller](https://github.com/jberclaz/modelh)
