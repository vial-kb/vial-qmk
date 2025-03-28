VIA_ENABLE           = yes
LTO_ENABLE           = yes
VIAL_ENABLE          = yes

ENCODER_MAP_ENABLE   = yes

ifeq ($(strip $(CONVERT_TO)), )
    QMK_SETTINGS         = no

	MAGIC_ENABLE         = no
    COMBO_ENABLE         = no
    KEY_OVERRIDE_ENABLE  = no
    TAP_DANCE_ENABLE     = no
endif
