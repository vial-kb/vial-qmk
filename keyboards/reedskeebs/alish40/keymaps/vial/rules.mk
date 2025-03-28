ENCODER_MAP_ENABLE = yes
VIA_ENABLE = yes
VIAL_ENABLE = yes

ifeq ($(strip $(CONVERT_TO)), )
    GRAVE_ESC_ENABLE = no
    KEY_OVERRIDE_ENABLE = no
    LTO_ENABLE = yes
    MAGIC_ENABLE = no
    SPACE_CADET_ENABLE = no
endif
