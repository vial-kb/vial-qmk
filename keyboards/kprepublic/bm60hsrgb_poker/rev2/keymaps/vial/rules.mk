# Build Options
#   change yes to no to disable
#
LTO_ENABLE = yes
VIA_ENABLE = yes
VIAL_ENABLE = yes

LINK_TIME_OPTIMIZATION_ENABLE = yes

COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
QMK_SETTINGS = yes
KEY_OVERRIDE_ENABLE = yes

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes       # Audio control and System control
MOUSEKEY_ENABLE = no       # Mouse keys
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = no           # Audio output

EXTRAFLAGS += -flto

# RGB Matrix is required to support per-key LEDs connected to IS31FL3733.
RGB_MATRIX_ENABLE = yes
VIALRGB_ENABLE = yes        # Enable Vial GUI
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality


# The custom RGB Matrix driver combines IS31FL3733 and WS2812; things that are
# normally done by common_features.mk for both of these drivers need to be done
# here manually.
COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3733.c
QUANTUM_LIB_SRC += i2c_master.c
WS2812_DRIVER_REQUIRED = yes
