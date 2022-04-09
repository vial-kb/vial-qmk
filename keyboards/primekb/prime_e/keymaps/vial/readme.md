# The VIAL keymap for Prime_E
This keymap is for compatibility with the VIAL configurator.

## Default disabled features
Some features need to be disabled in the [`rules.mk`](./rules.mk) to fit EEPROM.

* `QMK_SETTINGS`
* `COMBO_ENABLE`

Likewise, `VIAL_TAP_DANCE_ENTRIES` is limited to 4 by default.

To free up the space to enable/expand these, reduce `DYNAMIC_KEYMAP_LAYER_COUNT`
in [`keyboards/primekb/prime_e/config.h`](../../config.h) down to 4.
