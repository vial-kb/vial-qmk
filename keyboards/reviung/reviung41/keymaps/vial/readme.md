# Vial Keymap for Reviung41

[Vial] settings for the [Reviung41] by [gtips].

The Keyboard Layout Editor source for the visual layout can be found [here][kle].

**NOTE**: The following functions will be disabled to reduce firmware size when using a ProMicro MCU:

  * QMK Settings
  * Mouse Keys

If an alternate MCU is used and a [converter] is specified, these features will be enabled.
For example:
```
qmk compile -kb reviung/reviung41 -km vial -e CONVERT_TO=kb2040
```

![Reviung41](https://github.com/gtips/reviung/blob/master/reviung41/image/REVIUNG41B-1.jpg?raw=true)

[Vial]: https://get.vial.today
[Reviung41]: https://github.com/gtips/reviung/tree/master/reviung41
[gtips]: https://reviung.com
[kle]: http://www.keyboard-layout-editor.com/#/gists/e7b3db0ccb704e9b38cefa526ca950b2
[converter]: https://docs.qmk.fm/#/feature_converters?id=supported-converters
