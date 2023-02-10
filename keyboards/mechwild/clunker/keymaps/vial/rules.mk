VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
ENCODER_MAP_ENABLE = yes

ifeq ($(strip $(MCU)), atmega32u4)
    MAGIC_ENABLE = no
    SPACE_CADET_ENABLE = no
    #TAP_DANCE_ENABLE = no    # if space becomes an issue, uncomment
endif
