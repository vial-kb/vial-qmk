VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes

# EEPROM usage and firmware size are too high with default options, so some optional features had to be disabled.
# If you need some of these, try disabling some others, YMMV. Refer to https://get.vial.today/docs/firmware-size.html

QMK_SETTINGS = no
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no
