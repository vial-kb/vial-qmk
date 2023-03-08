# MCU name
MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040

# Bootloader selection
ALLOW_WARNINGS = yes
PICO_INTRINSICS_ENABLED = no

# Build Options
#   change yes to no to disable
#
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
#RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = vendor
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

VIALRGB_ENABLE = yes
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
LTO_ENABLE = no
VIA_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
CAPS_WORD_ENABLE = yes
