
# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
NKRO_ENABLE = yes           # Enable N-Key Rollover
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
KEY_LOCK_ENABLE = no
KEY_OVERRIDE_ENABLE = no
SECURE_ENABLE = no
SEQUENCER_ENABLE = no
AUTO_SHIFT_ENABLE = no
CAPS_WORD_ENABLE = no
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

# media
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
# RGB Matrix enabled
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = pwm

# Additional thing to reduce compiled size
LTO_ENABLE = yes


# Enter lower-power sleep mode when on the ChibiOS idle thread
# OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

