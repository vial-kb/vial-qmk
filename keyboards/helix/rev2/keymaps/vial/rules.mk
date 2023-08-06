VIA_ENABLE = yes
VIAL_ENABLE = yes
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
COMBO_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

COMMAND_ENABLE = no
CONSOLE_ENABLE = no

LTO_ENABLE = yes

KEY_OVERRIDE_ENABLE = no

ifneq ($(strip $(KEYBOARD)), helix/rev2)
   TAP_DANCE_ENABLE = no
endif
ifeq ($(strip $(KEYBOARD)), helix/rev2/qmk_conf)
   QMK_SETTINGS = no
endif
