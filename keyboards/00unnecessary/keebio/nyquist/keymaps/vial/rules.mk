VIA_ENABLE          = yes
VIAL_ENABLE         = yes
LTO_ENABLE          = yes

ENCODER_MAP_ENABLE  = yes
MOUSEKEY_ENABLE     = yes
MUSIC_ENABLE        = no

#REV1
ifeq ($(KEYBOARD), keebio/nyquist/rev1)
    OPT_DEFS += -DNYQUIST_REV1
    RGBLIGHT_ENABLE     = no
    RGB_MATRIX_ENABLE   = no
    VIALRGB_ENABLE      = no
    COMBO_ENABLE        = no
    QMK_SETTINGS        = no
    REPEAT_KEY_ENABLE   = no
endif

#REV2
ifeq ($(KEYBOARD), keebio/nyquist/rev2)
    OPT_DEFS += -DNYQUIST_REV2
    RGBLIGHT_ENABLE     = no
    RGB_MATRIX_ENABLE   = no
    VIALRGB_ENABLE      = no
    COMBO_ENABLE        = no
    QMK_SETTINGS        = no
    REPEAT_KEY_ENABLE   = no
endif

#REV3
ifeq ($(KEYBOARD), keebio/nyquist/rev3)
    OPT_DEFS += -DNYQUIST_REV3
    RGBLIGHT_ENABLE     = no
    RGB_MATRIX_ENABLE   = no
    VIALRGB_ENABLE      = no
    COMBO_ENABLE        = no
    QMK_SETTINGS        = no
    REPEAT_KEY_ENABLE   = no
endif

#REV4
ifeq ($(KEYBOARD), keebio/nyquist/rev4)
    OPT_DEFS += -DNYQUIST_REV4
    RGBLIGHT_ENABLE     = no
    RGB_MATRIX_ENABLE   = yes
    VIALRGB_ENABLE      = yes
    COMBO_ENABLE        = yes
    QMK_SETTINGS        = yes
    REPEAT_KEY_ENABLE   = yes
endif

#REV5
ifeq ($(KEYBOARD), keebio/nyquist/rev5)
    OPT_DEFS += -DNYQUIST_REV5
    RGBLIGHT_ENABLE     = no
    RGB_MATRIX_ENABLE   = yes
    VIALRGB_ENABLE      = yes
    COMBO_ENABLE        = yes
    QMK_SETTINGS        = yes
    REPEAT_KEY_ENABLE   = yes
endif

