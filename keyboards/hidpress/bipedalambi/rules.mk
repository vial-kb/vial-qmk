MCU = RP2040
BOOTLOADER = rp2040

# Drivers
SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor
OLED_DRIVER = ssd1306
POINTING_DEVICE_DRIVER = analog_joystick

# Features
# ENCODER_ENABLE = yes  # Disabled until encoder pins are configured per-side
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

# Source files
SRC += analog.c
