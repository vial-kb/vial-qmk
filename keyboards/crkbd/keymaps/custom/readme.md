# Custom Corne v4.1 Keymap with Vial

This keymap was created from a Vial configuration file (Vial.vil) for the Corne (crkbd) v4.1 keyboard.

## Features

- **8 layers**: Base layer plus 7 additional layers for numbers, function keys, navigation, macros, and special functions
- **Tap Dance**: Double-tap escape functionality
- **Combos**: 3 key combos for quick access to special functions
- **Macros**: Custom text macros and shortcut sequences
- **Home Row Mods**: Modifiers on home row keys for ergonomic typing
- **Caps Word**: Toggle for all-caps word typing
- **One Shot Modifiers**: Hyper and Meh key modifiers

## Building

To compile this keymap:

```bash
# From the vial-qmk directory
make crkbd/rev4_1/standard:custom

# Or to flash directly
make crkbd/rev4_1/standard:custom:flash
```

## Using with Vial

After flashing, open the Vial GUI application to further customize your keymap dynamically without recompiling.

## Layout Highlights

### Layer 0 (Base)
- QWERTY-like layout with Colemak-DH modifications
- Home row mods (Ctrl, Alt, Gui, Shift on A, S, R, T and O, I, E, N)
- Layer-tap thumb keys

### Layer 1 (Numbers)
- Number row
- Brackets and mathematical operators

### Layer 2 (Function Keys)
- F1-F10
- Media controls
- Navigation arrows

### Layer 3 (Special)
- Screenshot shortcuts
- Window management

### Layer 4 (Macros)
- Custom text macros
- Command shortcuts

### Layer 7 (Bootloader)
- QK_BOOT for entering bootloader mode
