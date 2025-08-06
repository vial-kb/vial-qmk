# Vial QWERTY layout for Planck EZ Glow

Cloned / Modified from Planck Rev6.

I didn't bother to set up the standard adjust layer for the EZ Glow. Shouldn't be hard to do, but I am lazy.

Doesn't work with VIA. Didn't look into that, probably something you can do.

Enabled for MIDI in Advanced mode, meaning in Vial you can assign MIDI keys and it should funciton like a normal USB piano. This was my whole motivation for porting this keyboard.

To easily install, no wally required, you can do.

```shell
qmk flash -kb planck/ez/glow -km vial
```

Warning: if you flash this image with incorrect enough data, such as flashing the rev6 version, wally will not recognize your keyboard and qmk will be your only recourse.

Warning: this keyboard layout has the reset button placed on the `Q` instead of on the `'` key. Was too lazy to change. May submit a PR later with the proper adjust layer.

qmk is installed via pip for python3. Read the other docs to find out more.

Predefined Layers:
- 0 - Default Planck QWERTY keymap (minus lighting control, plus SHIFT ENTER)
- 1 - Default Planck LOWER keymap
- 2 - Default Planck RAISE keymap
- 3 - UTILITY keymap (RESET, DEBUG)
