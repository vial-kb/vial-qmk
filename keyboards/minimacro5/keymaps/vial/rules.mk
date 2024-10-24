VIA_ENABLE = yes
VIAL_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# Reduce size on atmega32u4
ifeq ($(strip $(CONVERT_TO)), )
    TAP_DANCE_ENABLE = no
    QMK_SETTINGS = no
    KEY_OVERRIDE_ENABLE = no
    COMBO_ENABLE = no
endif
