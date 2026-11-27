# BFS9000

![BFS9000](https://raw.githubusercontent.com/jguillen-lab/BFS9000/main/media/kbpic/000_no1.jpg)

BFS9000 is a split keyboard based on Sofle-Pico, designed by Jesús Guillén. Each half uses an RP2040 controller (YD-RP2040-style board) and has an SSD1306 OLED and a rotary encoder. It supports RGB Matrix lighting, combos, tap dance and an optional Azoteq TPS65 (IQS5xx) trackpad on the right half.

* Keyboard Maintainer: [jguillen-lab](https://github.com/jguillen-lab)
* Hardware Supported: BFS9000 PCB
* Hardware Availability: [BFS9000 repository](https://github.com/jguillen-lab/BFS9000)

Make example for this keyboard, after setting up your build environment:

```
make jguillen_lab/bfs9000:default
```

Flashing example for this keyboard:

```
make jguillen_lab/bfs9000:default:flash
```

Vial keymap build example:

```
make jguillen_lab/bfs9000:vial
```

Vial keymap flashing example:

```
make jguillen_lab/bfs9000:vial:flash
```

See the [build environment setup](https://docs.qmk.fm/newbs_getting_started) and the [make instructions](https://docs.qmk.fm/newbs_building_firmware) for more information.

## Bootloader

Enter the bootloader in one of these ways:

* **Bootmagic reset** (left half): hold the top-left key (Print Screen in the default keymap) and plug in the USB cable.
* **USR button** (`vial` keymap only): press the USR button on the RP2040 controller of that half.
* **BOOT button**: hold BOOT on the RP2040 controller while plugging it in or pressing RESET.
