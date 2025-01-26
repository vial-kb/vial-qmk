# The Classic_TKL Vial default layout

To change the color of the Caps Lock indicator:

1. change this line with whatever RGB values you want

```c
rgb_matrix_set_color(i, 255, 86, 0);
```

2. rebuild the firmware using

```
make novelkeys/nk_classic_tkl:vial
```

3. reflash the firmware according to [README.md](../../readme.md#flash)
