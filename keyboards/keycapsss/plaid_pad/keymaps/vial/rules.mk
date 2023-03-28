VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
ENCODER_MAP_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), keycapsss/plaid_pad/rev3)
   KEY_OVERRIDE_ENABLE = no
   MAGIC_ENABLE = no
endif
