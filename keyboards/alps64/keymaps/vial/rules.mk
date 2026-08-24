VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MIDI_ENABLE = no

# The atmega32u2 only has 1kB of SRAM. The Vial defaults (combos, key overrides,
# tap dance, QMK settings + auto shift) leave barely 100 bytes of stack, which the
# USB/keyboard call chain blows straight through into .bss. Keep them off.
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no
QMK_SETTINGS = no

CAPS_WORD_ENABLE = no
LAYER_LOCK_ENABLE = no
REPEAT_KEY_ENABLE = no
