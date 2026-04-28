MCU_LDSCRIPT = STM32F103xB_uf2boot
DFU_SUFFIX_ARGS = -p FFFF -v FFFF

# UniCore-F1 UF2 bootloader uses a custom family ID (not the standard STM32F1 0x5EE21072).
UF2_FAMILY = 0x9D5BCF10

# Use custom bootloader type so we can provide our own bootloader_jump() with the correct
# magic value for the UniCore-F1 bootloader. Still output UF2 format.
FIRMWARE_FORMAT = uf2

CUSTOM_MATRIX = lite
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = custom
SRC += matrix.c
