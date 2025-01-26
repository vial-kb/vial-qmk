# The Classic_TKL Vial default layout

To change the color of the Caps Lock indicator:

1. Uncomment line 11 in `config.h` and change the RGB values:

```c
// Uncomment to customize the color of the caps lock indicator
// #define CAPS_LOCK_COLORS {0, 255, 0}
```

2. rebuild the firmware using

```
make novelkeys/nk_classic_tkl:vial
```

3. reflash the firmware according to [README.md](../../readme.md#flash)
