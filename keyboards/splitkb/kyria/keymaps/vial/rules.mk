# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no          # Audio output
SPLIT_KEYBOARD = yes       # Split common
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes

DEFAULT_FOLDER = splitkb/kyria/rev2


AUTO_SHIFT_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = no

VIA_ENABLE = yes
VIAL_ENABLE = yes

LTO_ENABLE = yes
QMK_SETTINGS = yes
KEY_OVERRIDE_ENABLE = no
DEFERRED_EXEC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
AVR_USE_MINIMAL_PRINTF = yes
DYNAMIC_MACRO_ENABLE = no
MUSIC_ENABLE = no
SWAP_HANDS_ENABLE= no

