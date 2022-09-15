VIA_ENABLE           = yes
LTO_ENABLE           = yes
VIAL_ENABLE          = yes

ifeq ($(strip $(MCU)), atmega32u4)
    QMK_SETTINGS         = no

    COMBO_ENABLE         = no
    KEY_OVERRIDE_ENABLE  = no
    TAP_DANCE_ENABLE     = no
endif
