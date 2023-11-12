LTO_ENABLE = yes
VIA_ENABLE = yes
VIAL_ENABLE = yes

LINK_TIME_OPTIMIZATION_ENABLE = yes

COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
QMK_SETTINGS = yes
KEY_OVERRIDE_ENABLE = yes
MAGIC_ENABLE = yes

CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no




EXTRAFLAGS += -flto

# RGB Matrix is required to support per-key LEDs connected to IS31FL3733.
RGB_MATRIX_ENABLE = yes
VIALRGB_ENABLE = yes
BACKLIGHT_ENABLE = no


# The custom RGB Matrix driver combines IS31FL3733 and WS2812; things that are
# normally done by common_features.mk for both of these drivers need to be done
# here manually.
COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3733.c
QUANTUM_LIB_SRC += i2c_master.c
WS2812_DRIVER_REQUIRED = yes
