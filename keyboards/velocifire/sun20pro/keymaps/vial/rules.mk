# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

VIA_ENABLE = yes
VIAL_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes

LTO_ENABLE = yes

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
VIALRGB_ENABLE = yes

COMBO_ENABLE = no
COMMAND_ENABLE = no         # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug
EXTRAKEY_ENABLE = yes       # Audio control and System control
MUSIC_ENABLE = no
QMK_SETTINGS = no
TAP_DANCE_ENABLE = yes
