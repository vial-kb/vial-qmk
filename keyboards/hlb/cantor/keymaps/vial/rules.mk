VIA_ENABLE  = yes    # Enable VIA
VIAL_ENABLE = yes    # Enable VIAL

#We need to specify bootloader and MCU for F411 8Mhz version of BlackPillS
BOOTLOADER = stm32-dfu
MCU = STM32F411

#We are in split keyboard mode
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart
