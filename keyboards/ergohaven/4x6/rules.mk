# MCU name
MCU = RP2040

BOARD = GENERIC_RP_RP2040

# Bootloader selection
BOOTLOADER = rp2040
ALLOW_WARNINGS = yes
PICO_INTRINSICS_ENABLED = no

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_DRIVER = WS2812

VIALRGB_ENABLE = no
WS2812_DRIVER = vendor
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
LTO_ENABLE = no
VIA_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
