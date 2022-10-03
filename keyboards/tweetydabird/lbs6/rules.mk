# MCU type and Bootloader
MCU = atmega32u4
BOOTLOADER = caterina 		# Bootloader for ProMicro
#BOOTLOADER = qmk-dfu		# Bootloader for Elite

# Build Options
BOOTMAGIC_ENABLE = yes		# Bootmagic Lite allows reset from key on plug-in
ENCODER_ENABLE = yes		# Rotary encoder
EXTRAKEY_ENABLE = yes		# Audio and System control
TAP_DANCE_ENABLE = yes		# Allows assigning multiple keycodes to the same key

# RGB and Backlight
BACKLIGHT_ENABLE = no		# No backlight functionality
RGBLIGHT_ENABLE = yes		# Enable keyboard RGB underglow

SLEEP_LED_ENABLE = no		# Breathing sleep LED during USB suspend

# Debug otions
CONSOLE_ENABLE = no			# Console for debug
COMMAND_ENABLE = no			# Commands for debug and configuration

# Disabled to save space 
MOUSEKEY_ENABLE = no        # Mouse keys
AUDIO_ENABLE = no           # Audio output
SPACE_CADET_ENABLE = no		# Use left/right shift for opening and closing parantesis
GRAVE_ESC_ENABLE = no		# Allow Esc to act as ~ when needed
MAGIC_ENABLE = no			# Allow remapping of modifiers for Win/iOS etc
NKRO_ENABLE = no            # Allow more than 6 keys to be used at once



