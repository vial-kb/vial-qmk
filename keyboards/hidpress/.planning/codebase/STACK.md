# Technology Stack

**Analysis Date:** 2026-02-13

## Languages

**Primary:**
- C (C99/C11) - Core firmware implementation for keyboard logic, OLED rendering, and hardware drivers
- Python 3 - Utility scripts for image conversion and build tooling

## Runtime

**Environment:**
- Bare-metal ARM Cortex-M0+ (RP2040 microcontroller)
- No operating system - Direct hardware control via QMK firmware framework

**Build System:**
- QMK firmware build system (make-based)
- Compilation targets ARM binaries for RP2040 bootloader

## Frameworks

**Core:**
- QMK Firmware - Open-source keyboard firmware framework providing hardware abstraction, key handling, and feature modules
- Vial - QMK extension for runtime keymap configuration and remapping via GUI without recompilation

**Hardware Abstraction:**
- ChibiOS/RT - Real-time operating system layer providing HAL (Hardware Abstraction Layer) for RP2040
- RP2040 SDK - Raspberry Pi microcontroller SDK for low-level peripheral access

**Display:**
- SSD1306 OLED Driver - I2C-based monochrome OLED display controller (128x32 pixel displays)
- Custom OLED font system - Bitmap-based font rendering for layer indicators and status displays

**Peripheral Drivers:**
- WS2812 (NeoPixel/RGB LED) driver - SPI-based RGB LED control via vendor driver
- Analog Joystick driver - ADC-based analog input for pointing device
- Rotary Encoder driver - GPIO interrupt-based rotary encoder support
- I2C Master - Inter-integrated circuit for OLED and split keyboard communication
- USART/Serial - For split keyboard communication between left/right halves

## Key Dependencies

**Critical:**
- ChibiOS HAL - Provides `halconf.h` and `mcuconf.h` configuration headers for hardware setup
- QMK quantum.h - Core keyboard matrix processing, keycode definitions, and feature macros
- i2c_master - I2C communication library for OLED display and split keyboard sync

**Feature Modules:**
- oled_driver (ssd1306) - SSD1306 OLED display support
- rgblight - RGB LED animation and control
- pointing_device - Mouse/trackpad support via analog joystick
- split_common - Split keyboard synchronization (communication, layer sync, pointing device sync)
- extrakey - Extended key support (media keys, brightness, volume)
- encoder - Rotary encoder support with per-layer mappings
- joystick - Analog stick emulation for game-like control

## Configuration

**Microcontroller Configuration:**
- MCU: RP2040 (Raspberry Pi Pico processor)
- Bootloader: RP2040 native bootloader with double-tap reset support
- Crystal: Internal oscillator (no external crystal required)

**Hardware Pins (example - Bipedal65):**
- Matrix rows: GP9, GP10, GP11, GP8, GP5 (5 rows)
- Matrix cols: GP4, GP3, GP2, GP28, GP27, GP26, GP25, GP24, GP23, GP22, GP21, GP20, GP19, GP18, GP15, GP14 (16 cols)
- RGB LED: GP29 via WS2812 driver using PIO1
- Encoder pins: GP12/GP13, GP16/GP17, GP7/GP6 (3 encoders)
- OLED I2C: GP1 (SCL), GP0 (SDA) - I2C0 controller

**Build Configuration Files:**
- `rules.mk` - Feature enablement and driver selection per keyboard
- `info.json` - USB device info, processor, layout definitions, feature matrix
- `config.h` - Hardware-specific defines, display settings, timing parameters
- `halconf.h` - ChibiOS HAL feature configuration
- `mcuconf.h` - ChibiOS MCU-specific settings

## Platform Requirements

**Development:**
- QMK CLI or make with arm-gcc toolchain
- Python 3 (for build scripts and utilities like image conversion)
- Python PIL/Pillow library (for OLED image conversion script in `tools/convert_oled_image.py`)
- arm-none-eabi-gcc compiler
- OpenOCD (for debugging with RP2040 debug probe)

**Production (Flash):**
- RP2040 USB bootloader (accessible via double-tap reset)
- Vial GUI application (for runtime keymap configuration)
- QMK toolbox or equivalent USB flashing utility

**Hardware:**
- RP2040 microcontroller with ~260KB flash, ~264KB RAM
- USB micro-B connector for power and data
- I2C OLED display (SSD1306, 128x32)
- Optional: WS2812B/NeoPixel RGB LEDs
- Optional: Analog joystick input
- Optional: Rotary encoders

---

*Stack analysis: 2026-02-13*
