PROTOCOL_DIR = protocol
PICO_DIR = $(PROTOCOL_DIR)/pico

SRC += $(KEYBOARD_OUTPUT)/src/bs2_default_padded_checksummed.S
LDSCRIPT := $(PICO_SDK_PATH)/src/rp2_common/pico_standard_link/memmap_default.ld

SRC += $(PICO_DIR)/pico.c
SRC += $(PICO_DIR)/usb_descriptors.c
SRC += $(PICO_DIR)/iusb.c
SRC += $(PICO_DIR)/pio_manager.c
SRC += $(PICO_DIR)/usb_util.c

VPATH += $(TMK_PATH)/$(PROTOCOL_DIR)
VPATH += $(TMK_PATH)/$(PICO_DIR)
VPATH += $(TMK_PATH)/$(PICO_DIR)/lufa_utils

CFLAGS += -DPROTOCOL_PICO
CFLAGS += -DGPIO_INPUT_PIN_DELAY=100
CFLAGS += -DDYNAMIC_KEYMAP_EEPROM_MAX_ADDR=4095
