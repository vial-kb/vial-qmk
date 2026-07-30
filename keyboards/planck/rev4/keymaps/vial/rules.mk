# Vial support
VIA_ENABLE = yes
VIAL_ENABLE = yes

# The ATmega32u4 has ~28KB of usable flash (32KB minus the 4KB atmel-dfu
# bootloader). Audio is the largest single flash consumer in QMK and must
# be disabled here for Vial to fit.
AUDIO_ENABLE = no
MIDI_ENABLE = no

# Frees a USB endpoint and saves flash.
CONSOLE_ENABLE = no

# Magic keycodes (AG_SWAP, NK_TOGG, CG_TOGG, etc.) — disabled to fit Vial
# into flash. None of them are used in this default keymap. Re-enable if you
# want them, but be prepared to disable another feature to make room.
MAGIC_ENABLE = no

# Required to keep the firmware within the flash budget. Without LTO the
# build will not fit.
LTO_ENABLE = yes

# Backlight is OFF by default to keep flash headroom on the 28KB chip — most
# rev4s in the wild don't have LEDs installed. If your board does, just add
#
#   BACKLIGHT_ENABLE = yes
#
# locally. Costs ~1KB of flash; you may then also need to disable a Vial
# feature to fit.
