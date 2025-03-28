VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
KEY_OVERRIDE_ENABLE = no

ifeq ($(strip $(KEYBOARD)), lazydesigners/dimple/staggered/rev1)
   QMK_SETTINGS = no
endif
