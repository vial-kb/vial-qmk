MCU = RP2040
BOOTLOADER = rp2040
SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
POINTING_DEVICE_DRIVER = analog_joystick
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
CONSOLE_ENABLE = yes

SRC += analog.c

# Build for right side: qmk compile ... -e SIDE=right
ifeq ($(SIDE),right)
    OPT_DEFS += -DRIGHT_SIDE
endif
