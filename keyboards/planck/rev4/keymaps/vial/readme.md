# Vial keymap for Planck rev4

Adds [Vial](https://get.vial.today) support to the OLKB Planck rev4 (ATmega32u4 + atmel-dfu bootloader, 4×12 ortholinear). Base layer is the standard Planck QWERTY layout; everything is remappable in the Vial app after flashing.

## Build

```
make planck/rev4:vial
```

## Flash

Enter bootloader (hold the top-left key while plugging in USB, **or** press the reset button on the PCB), then flash the resulting `planck_rev4_vial.hex` via `dfu-programmer` or QMK Toolbox:

```
dfu-programmer atmega32u4 erase --force
dfu-programmer atmega32u4 flash planck_rev4_vial.hex
dfu-programmer atmega32u4 reset
```

## Notes

- **Flash budget is tight.** The ATmega32u4 has only ~28 KB of usable flash (32 KB minus the 4 KB atmel-dfu bootloader). To make Vial fit, the following are disabled in `rules.mk`:
  - `AUDIO_ENABLE`, `MIDI_ENABLE` — audio is the largest single flash consumer in QMK
  - `CONSOLE_ENABLE` — saves flash + a USB endpoint
  - `MAGIC_ENABLE` — magic keycodes (`AG_SWAP`, `NK_TOGG`, `CG_TOGG`, etc.) are not used by this default keymap
  - `BACKLIGHT_ENABLE` — most rev4s in the wild don't have LEDs installed
- **Enabling backlight (~1 KB flash):** if your board has LEDs, add `BACKLIGHT_ENABLE = yes` to `rules.mk` and rebuild. You will need to disable a Vial-pulled feature to make room (e.g., raise `DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE` constraints or trim layers).
- **Enabling magic keycodes (~500 B flash):** add `MAGIC_ENABLE = yes` to `rules.mk` and rebuild. Same flash caveat as above.
- **Vial unlock combo:** hold Esc (top-left) + Space for 5 seconds the first time you make a change in the Vial app.
- **Bootloader recovery:** hold the top-left key (matrix `(0,0)`) while plugging in USB to enter the bootloader at any time (Bootmagic Lite).
