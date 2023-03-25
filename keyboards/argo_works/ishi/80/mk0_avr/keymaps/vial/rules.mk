VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes

ifeq ($(strip $(MCU)), atmega32u4)
    MAGIC_ENABLE = no
    SPACE_CADET_ENABLE = no
    COMBO_ENABLE = no
    CONSOLE_ENABLE = no
    COMMAND_ENABLE = no
    MOUSEKEY_ENABLE = no
    TAP_DANCE_ENABLE = no
endif