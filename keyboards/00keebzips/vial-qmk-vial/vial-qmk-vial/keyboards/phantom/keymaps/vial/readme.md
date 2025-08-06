# Keymap for a standard ANSI configuration of the Phantom

Keymap for Phantom keyboard with Vial support. Standard TKL ANSI layout with the following options:

- split backspace
- ISO Enter
- split left shift
- split right shift
- 7U spacebar with symmetrical modifiers, 1.5U - 1U - 1.5U
- 7U spacebar with _winkeyless_ 1.5U modifiers

Most options have been disabled in rules.mk to reduce the size of the firmware and make it fit in the Phantom MCU.

## Layers

The keymap have two layers. To access the functions on the second layer, hold down `Fn` and press the corresponding key.

### Layer 1: Default Layer

     ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     `---'   `---------------' `---------------' `---------------' `-----------'
     ,-----------------------------------------------------------. ,-----------.
     |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |Ins|Hom|PgU|
     |-----------------------------------------------------------| |-----------|
     |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
     |-----------------------------------------------------------| '-----------'
     |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     |-----------------------------------------------------------|     ,---.
     |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |
     |-----------------------------------------------------------| ,-----------.
     |Ctl|Gui|Alt|             Space             |Alt|Gui|Fn |Ctl| |Lef|Dow|Rig|
     `-----------------------------------------------------------' `-----------'

### Layer 2: Function Layer

     ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     |RST|   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |
     `---'   `---------------' `---------------' `---------------' `-----------'
     ,-----------------------------------------------------------. ,-----------.
     |   |   |   |   |   |   |   |   |   |   |   |   |   |       | |   |   |   |
     |-----------------------------------------------------------| |-----------|
     |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   |
     |-----------------------------------------------------------| '-----------'
     |      |   |   |   |   |   |   |   |   |   |   |   |        |
     |-----------------------------------------------------------|     ,---.
     |        |   |   |   |   |   |   |   |   |   |   |          |     |   |
     |-----------------------------------------------------------| ,-----------.
     |   |   |   |                               |   |   |   |   | |   |   |   |
     `-----------------------------------------------------------' `-----------'

## Building

```
qmk compile -kb phantom -km vial
qmk flash -kb phantom -km vial
```
