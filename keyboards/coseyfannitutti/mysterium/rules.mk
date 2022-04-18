# MCU name
MCU = atmega32a

# Processor frequency
F_CPU = 16000000

# Bootloader selection
BOOTLOADER = usbasploader

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes       # Audio control and System control
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
WPM_ENABLE = yes
RGBLIGHT_ENABLE = yes

LAYOUTS = tkl_ansi
EXTRAFLAGS += -flto
