# MCU name
MCU = STM32F401
BOARD = BLACKPILL_STM32_F401

# Via/VIAL
VIA_ENABLE = yes
VIAL_ENABLE = yes

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#

BOOTMAGIC_ENABLE = yes # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no  # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = no    # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes      # Enable N-Key Rollover
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no  # Enable keyboard RGB underglow
AUDIO_ENABLE = no      # Audio output
ENCODER_ENABLE = no   # Enable encoder