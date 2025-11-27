VIA_ENABLE = yes
VIAL_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# Include Keychron common
VPATH += keyboards/keychron/common
SRC += keychron_common.c

# Explicitly disable RGB for basic build
RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = no

# Enable tap dance and combo features
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = no
QMK_SETTINGS = no

# RGB will be enabled once basic build works
# VIALRGB_ENABLE = yes