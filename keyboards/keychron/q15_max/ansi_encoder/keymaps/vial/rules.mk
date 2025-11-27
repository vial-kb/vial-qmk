VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# Include Keychron common for wireless support
VPATH += keyboards/keychron/common
SRC += keychron_common.c

# Optional Vial features (can be disabled to save space if needed)
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = no
QMK_SETTINGS = no