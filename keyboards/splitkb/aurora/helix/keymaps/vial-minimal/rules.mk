VIA_ENABLE = yes
VIAL_ENABLE = yes

ENCODER_MAP_ENABLE = yes

# A default 32u4 build is more than 8k oversized,
# so we have to disable some less-common / expert-level features.
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no
KEY_OVERRIDE_ENABLE = no
MOUSEKEY_ENABLE = no
COMBO_ENABLE = no
QMK_SETTINGS = no

SRC+=oneshot_shim.c
