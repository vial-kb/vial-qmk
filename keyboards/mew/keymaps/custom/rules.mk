# qmk compile -e MASTER=left -e CONVERT_TO=kb2040 --keyboard crkbd --keymap vial
VIA_ENABLE          = yes
VIAL_ENABLE         = yes
LTO_ENABLE          = yes
QMK_SETTINGS        = yes
SPLIT_KEYBOARD      = yes

RGBLIGHT_ENABLE     = no
RGB_MATRIX_ENABLE   = no # Can't have RGBLIGHT and RGB_MATRIX at the same time.
SLEEP_LED_ENABLE	= no

OLED_ENABLE         = yes
COMBO_ENABLE        = yes
WPM_ENABLE          = yes


# MOUSEKEY_ENABLE 	= no     # Mouse keys
# EXTRAKEY_ENABLE     = no
# KEY_OVERRIDE_ENABLED = no
# AUDIO_ENABLE 		= no
# COMMAND_ENABLE 		= no
# LEADER_ENABLE 		= no
# BLUETOOTH_ENABLE 	= no
# MIDI_ENABLE 		= no
# UNICODE_ENABLE 		= no
# BOOTMAGIC_ENABLE 	= no
# CONSOLE_ENABLE 		= no

# MCU = kb2040
# BOOTLOADER = rp2040