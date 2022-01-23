
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar
NM = arm-none-eabi-nm
HEX = $(OBJCOPY) -O $(FORMAT)
EEP =
BIN = $(OBJCOPY) -O binary

ALLOW_WARNINGS := yes
OPT_DEFS += -DPROTOCOL_PICO
OPT_DEFS += -DSPLIT_USB_DETECT
PICOTOOL ?= picotool
RP2BOOT_ID ?= "2e8a:0003"
LSUSB ?= lsusb

PICO_SDK_PATH = lib/pico-sdk

PICO_SDK_EXIST = $(shell test -d $(PICO_SDK_PATH)/src && echo true)
ifneq ($(PICO_SDK_EXIST),true)
$(error pico-sdk does not found at PICO_SDK_PATH. Please setup pico-sdk.)
endif

GIT_DESCRIBE = $(shell git describe --tags --long --dirty="\\*")

ifneq ($(PICO_FLASH_SPI_CLKDIV),)
	CFLAGS += -DPICO_FLASH_SPI_CLKDIV=$(PICO_FLASH_SPI_CLKDIV)
else
	CFLAGS += -DPICO_FLASH_SPI_CLKDIV=4
endif

CFLAGS += -DCFG_TUSB_DEBUG=0
CFLAGS += -DCFG_TUSB_MCU=OPT_MCU_RP2040
CFLAGS += -DCFG_TUSB_OS=OPT_OS_PICO
CFLAGS += -DLIB_PICO_BIT_OPS=1
CFLAGS += -DLIB_PICO_BIT_OPS_PICO=1
CFLAGS += -DLIB_PICO_BOOTSEL_VIA_DOUBLE_RESET=1
CFLAGS += -DLIB_PICO_DIVIDER=1
CFLAGS += -DLIB_PICO_DIVIDER_HARDWARE=1
CFLAGS += -DLIB_PICO_DOUBLE=1
CFLAGS += -DLIB_PICO_DOUBLE_PICO=1
CFLAGS += -DLIB_PICO_FIX_RP2040_USB_DEVICE_ENUMERATION=1
CFLAGS += -DLIB_PICO_FLOAT=1
CFLAGS += -DLIB_PICO_FLOAT_PICO=1
CFLAGS += -DLIB_PICO_INT64_OPS=1
CFLAGS += -DLIB_PICO_INT64_OPS_PICO=1
CFLAGS += -DLIB_PICO_MALLOC=1
CFLAGS += -DLIB_PICO_MEM_OPS=1
CFLAGS += -DLIB_PICO_MEM_OPS_PICO=1
CFLAGS += -DLIB_PICO_PLATFORM=1
CFLAGS += -DLIB_PICO_PRINTF=1
CFLAGS += -DLIB_PICO_PRINTF_PICO=1
CFLAGS += -DLIB_PICO_RUNTIME=1
CFLAGS += -DLIB_PICO_STANDARD_LINK=1
CFLAGS += -DLIB_PICO_STDIO=1
CFLAGS += -DLIB_PICO_STDIO_UART=1
CFLAGS += -DLIB_PICO_STDLIB=1
CFLAGS += -DLIB_PICO_SYNC=1
CFLAGS += -DLIB_PICO_SYNC_CORE=1
CFLAGS += -DLIB_PICO_SYNC_CRITICAL_SECTION=1
CFLAGS += -DLIB_PICO_SYNC_MUTEX=1
CFLAGS += -DLIB_PICO_SYNC_SEM=1
CFLAGS += -DLIB_PICO_TIME=1
CFLAGS += -DLIB_PICO_UTIL=1
CFLAGS += -DLIB_TINYUSB_BOARD=1
CFLAGS += -DLIB_TINYUSB_DEVICE=1
CFLAGS += -DPICO_BOARD=\"pico\"
CFLAGS += -DPICO_BUILD=1
CFLAGS += -DPICO_COPY_TO_RAM=0
CFLAGS += -DPICO_CXX_ENABLE_EXCEPTIONS=0
CFLAGS += -DPICO_NO_FLASH=0
CFLAGS += -DPICO_NO_HARDWARE=0
CFLAGS += -DPICO_ON_DEVICE=1
CFLAGS += -DPICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1
CFLAGS += -DPICO_TARGET_NAME=\"$(TARGET)\"
CFLAGS += -DPICO_PROGRAM_VERSION_STRING=\"$(GIT_DESCRIBE)\"
CFLAGS += -DPICO_USE_BLOCKED_RAM=0
CFLAGS += -I$(PICO_SDK_PATH)
CFLAGS += -I$(PICO_SDK_PATH)/src
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_stdlib/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_flash/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_gpio/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_base/include
CFLAGS += -I$(PICO_SDK_PATH)/src/boards/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_platform/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2040/hardware_regs/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_base/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2040/hardware_structs/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_adc/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_claim/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_dma/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_sync/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_uart/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_i2c/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_spi/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_pio/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_pwm/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_divider/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_time/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_timer/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_sync/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_util/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_runtime/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_clocks/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_irq/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_resets/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_pll/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_vreg/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_watchdog/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_xosc/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_printf/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_bootrom/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_bit_ops/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_divider/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_double/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_int64_ops/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_float/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_malloc/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/boot_stage2/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_binary_info/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_stdio/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_stdio_uart/include
CFLAGS += -I$(PICO_SDK_PATH)/lib/tinyusb/src
CFLAGS += -I$(PICO_SDK_PATH)/lib/tinyusb/src/common
CFLAGS += -I$(PICO_SDK_PATH)/lib/tinyusb/hw
CFLAGS += -I$(PICO_SDK_PATH)/lib/tinyusb/src/class/hid
CFLAGS += -I$(PICO_SDK_PATH)/lib/tinyusb/src/class/cdc
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include
CFLAGS += -mcpu=cortex-m0plus
CFLAGS += -mthumb
CFLAGS += -O0 -g3
# CFLAGS += -DNDEBUG
CFLAGS += -Wall
CFLAGS += -Wno-format
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-maybe-uninitialized
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -std=gnu11

ASFLAGS += $(CFLAGS)

LDFLAGS += -Wl,--build-id=none
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,--wrap=sprintf
LDFLAGS += -Wl,--wrap=snprintf
LDFLAGS += -Wl,--wrap=vsnprintf
LDFLAGS += -Wl,--wrap=__clzsi2
LDFLAGS += -Wl,--wrap=__clzdi2
LDFLAGS += -Wl,--wrap=__ctzsi2
LDFLAGS += -Wl,--wrap=__ctzdi2
LDFLAGS += -Wl,--wrap=__popcountsi2
LDFLAGS += -Wl,--wrap=__popcountdi2
LDFLAGS += -Wl,--wrap=__clz
LDFLAGS += -Wl,--wrap=__clzl
LDFLAGS += -Wl,--wrap=__clzll
LDFLAGS += -Wl,--wrap=__aeabi_idiv
LDFLAGS += -Wl,--wrap=__aeabi_idivmod
LDFLAGS += -Wl,--wrap=__aeabi_ldivmod
LDFLAGS += -Wl,--wrap=__aeabi_uidiv
LDFLAGS += -Wl,--wrap=__aeabi_uidivmod
LDFLAGS += -Wl,--wrap=__aeabi_uldivmod
LDFLAGS += -Wl,--wrap=__aeabi_dadd
LDFLAGS += -Wl,--wrap=__aeabi_ddiv
LDFLAGS += -Wl,--wrap=__aeabi_dmul
LDFLAGS += -Wl,--wrap=__aeabi_drsub
LDFLAGS += -Wl,--wrap=__aeabi_dsub
LDFLAGS += -Wl,--wrap=__aeabi_cdcmpeq
LDFLAGS += -Wl,--wrap=__aeabi_cdrcmple
LDFLAGS += -Wl,--wrap=__aeabi_cdcmple
LDFLAGS += -Wl,--wrap=__aeabi_dcmpeq
LDFLAGS += -Wl,--wrap=__aeabi_dcmplt
LDFLAGS += -Wl,--wrap=__aeabi_dcmple
LDFLAGS += -Wl,--wrap=__aeabi_dcmpge
LDFLAGS += -Wl,--wrap=__aeabi_dcmpgt
LDFLAGS += -Wl,--wrap=__aeabi_dcmpun
LDFLAGS += -Wl,--wrap=__aeabi_i2d
LDFLAGS += -Wl,--wrap=__aeabi_l2d
LDFLAGS += -Wl,--wrap=__aeabi_ui2d
LDFLAGS += -Wl,--wrap=__aeabi_ul2d
LDFLAGS += -Wl,--wrap=__aeabi_d2iz
LDFLAGS += -Wl,--wrap=__aeabi_d2lz
LDFLAGS += -Wl,--wrap=__aeabi_d2uiz
LDFLAGS += -Wl,--wrap=__aeabi_d2ulz
LDFLAGS += -Wl,--wrap=__aeabi_d2f
LDFLAGS += -Wl,--wrap=sqrt
LDFLAGS += -Wl,--wrap=cos
LDFLAGS += -Wl,--wrap=sin
LDFLAGS += -Wl,--wrap=tan
LDFLAGS += -Wl,--wrap=atan2
LDFLAGS += -Wl,--wrap=exp
LDFLAGS += -Wl,--wrap=log
LDFLAGS += -Wl,--wrap=ldexp
LDFLAGS += -Wl,--wrap=copysign
LDFLAGS += -Wl,--wrap=trunc
LDFLAGS += -Wl,--wrap=floor
LDFLAGS += -Wl,--wrap=ceil
LDFLAGS += -Wl,--wrap=round
LDFLAGS += -Wl,--wrap=sincos
LDFLAGS += -Wl,--wrap=asin
LDFLAGS += -Wl,--wrap=acos
LDFLAGS += -Wl,--wrap=atan
LDFLAGS += -Wl,--wrap=sinh
LDFLAGS += -Wl,--wrap=cosh
LDFLAGS += -Wl,--wrap=tanh
LDFLAGS += -Wl,--wrap=asinh
LDFLAGS += -Wl,--wrap=acosh
LDFLAGS += -Wl,--wrap=atanh
LDFLAGS += -Wl,--wrap=exp2
LDFLAGS += -Wl,--wrap=log2
LDFLAGS += -Wl,--wrap=exp10
LDFLAGS += -Wl,--wrap=log10
LDFLAGS += -Wl,--wrap=pow
LDFLAGS += -Wl,--wrap=powint
LDFLAGS += -Wl,--wrap=hypot
LDFLAGS += -Wl,--wrap=cbrt
LDFLAGS += -Wl,--wrap=fmod
LDFLAGS += -Wl,--wrap=drem
LDFLAGS += -Wl,--wrap=remainder
LDFLAGS += -Wl,--wrap=remquo
LDFLAGS += -Wl,--wrap=expm1
LDFLAGS += -Wl,--wrap=log1p
LDFLAGS += -Wl,--wrap=fma
LDFLAGS += -Wl,--wrap=__aeabi_lmul
LDFLAGS += -Wl,--wrap=__aeabi_fadd
LDFLAGS += -Wl,--wrap=__aeabi_fdiv
LDFLAGS += -Wl,--wrap=__aeabi_fmul
LDFLAGS += -Wl,--wrap=__aeabi_frsub
LDFLAGS += -Wl,--wrap=__aeabi_fsub
LDFLAGS += -Wl,--wrap=__aeabi_cfcmpeq
LDFLAGS += -Wl,--wrap=__aeabi_cfrcmple
LDFLAGS += -Wl,--wrap=__aeabi_cfcmple
LDFLAGS += -Wl,--wrap=__aeabi_fcmpeq
LDFLAGS += -Wl,--wrap=__aeabi_fcmplt
LDFLAGS += -Wl,--wrap=__aeabi_fcmple
LDFLAGS += -Wl,--wrap=__aeabi_fcmpge
LDFLAGS += -Wl,--wrap=__aeabi_fcmpgt
LDFLAGS += -Wl,--wrap=__aeabi_fcmpun
LDFLAGS += -Wl,--wrap=__aeabi_i2f
LDFLAGS += -Wl,--wrap=__aeabi_l2f
LDFLAGS += -Wl,--wrap=__aeabi_ui2f
LDFLAGS += -Wl,--wrap=__aeabi_ul2f
LDFLAGS += -Wl,--wrap=__aeabi_f2iz
LDFLAGS += -Wl,--wrap=__aeabi_f2lz
LDFLAGS += -Wl,--wrap=__aeabi_f2uiz
LDFLAGS += -Wl,--wrap=__aeabi_f2ulz
LDFLAGS += -Wl,--wrap=__aeabi_f2d
LDFLAGS += -Wl,--wrap=sqrtf
LDFLAGS += -Wl,--wrap=cosf
LDFLAGS += -Wl,--wrap=sinf
LDFLAGS += -Wl,--wrap=tanf
LDFLAGS += -Wl,--wrap=atan2f
LDFLAGS += -Wl,--wrap=expf
LDFLAGS += -Wl,--wrap=logf
LDFLAGS += -Wl,--wrap=ldexpf
LDFLAGS += -Wl,--wrap=copysignf
LDFLAGS += -Wl,--wrap=truncf
LDFLAGS += -Wl,--wrap=floorf
LDFLAGS += -Wl,--wrap=ceilf
LDFLAGS += -Wl,--wrap=roundf
LDFLAGS += -Wl,--wrap=sincosf
LDFLAGS += -Wl,--wrap=asinf
LDFLAGS += -Wl,--wrap=acosf
LDFLAGS += -Wl,--wrap=atanf
LDFLAGS += -Wl,--wrap=sinhf
LDFLAGS += -Wl,--wrap=coshf
LDFLAGS += -Wl,--wrap=tanhf
LDFLAGS += -Wl,--wrap=asinhf
LDFLAGS += -Wl,--wrap=acoshf
LDFLAGS += -Wl,--wrap=atanhf
LDFLAGS += -Wl,--wrap=exp2f
LDFLAGS += -Wl,--wrap=log2f
LDFLAGS += -Wl,--wrap=exp10f
LDFLAGS += -Wl,--wrap=log10f
LDFLAGS += -Wl,--wrap=powf
LDFLAGS += -Wl,--wrap=powintf
LDFLAGS += -Wl,--wrap=hypotf
LDFLAGS += -Wl,--wrap=cbrtf
LDFLAGS += -Wl,--wrap=fmodf
LDFLAGS += -Wl,--wrap=dremf
LDFLAGS += -Wl,--wrap=remainderf
LDFLAGS += -Wl,--wrap=remquof
LDFLAGS += -Wl,--wrap=expm1f
LDFLAGS += -Wl,--wrap=log1pf
LDFLAGS += -Wl,--wrap=fmaf
LDFLAGS += -Wl,--wrap=malloc
LDFLAGS += -Wl,--wrap=calloc
LDFLAGS += -Wl,--wrap=free
LDFLAGS += -Wl,--wrap=memcpy
LDFLAGS += -Wl,--wrap=memset
LDFLAGS += -Wl,--wrap=__aeabi_memcpy
LDFLAGS += -Wl,--wrap=__aeabi_memset
LDFLAGS += -Wl,--wrap=__aeabi_memcpy4
LDFLAGS += -Wl,--wrap=__aeabi_memset4
LDFLAGS += -Wl,--wrap=__aeabi_memcpy8
LDFLAGS += -Wl,--wrap=__aeabi_memset8
LDFLAGS += -Wl,-Map=$(TARGET).elf.map
LDFLAGS += -Wl,--script=$(LDSCRIPT)
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--wrap=printf
LDFLAGS += -Wl,--wrap=vprintf
LDFLAGS += -Wl,--wrap=puts
LDFLAGS += -Wl,--wrap=putchar
LDFLAGS += -Wl,--wrap=getchar
LDFLAGS += -Wl,--print-memory-usage

SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_stdlib/stdlib.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_adc/adc.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_sync/sync.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_flash/flash.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_gpio/gpio.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_claim/claim.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_dma/dma.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_platform/platform.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_sync/sync.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_uart/uart.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_i2c/i2c.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_spi/spi.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_pio/pio.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_divider/divider.S
SRC += $(PICO_SDK_PATH)/src/common/pico_time/time.c
SRC += $(PICO_SDK_PATH)/src/common/pico_time/timeout_helper.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_timer/timer.c
SRC += $(PICO_SDK_PATH)/src/common/pico_sync/sem.c
SRC += $(PICO_SDK_PATH)/src/common/pico_sync/lock_core.c
SRC += $(PICO_SDK_PATH)/src/common/pico_sync/mutex.c
SRC += $(PICO_SDK_PATH)/src/common/pico_sync/critical_section.c
SRC += $(PICO_SDK_PATH)/src/common/pico_util/datetime.c
SRC += $(PICO_SDK_PATH)/src/common/pico_util/pheap.c
SRC += $(PICO_SDK_PATH)/src/common/pico_util/queue.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_runtime/runtime.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_clocks/clocks.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_irq/irq.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_irq/irq_handler_chain.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_pll/pll.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_vreg/vreg.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_watchdog/watchdog.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_xosc/xosc.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_printf/printf.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_bit_ops/bit_ops_aeabi.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_bootrom/bootrom.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_divider/divider.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_double/double_aeabi.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_double/double_init_rom.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_double/double_math.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_double/double_v1_rom_shim.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_int64_ops/pico_int64_ops_aeabi.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_float/float_aeabi.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_float/float_init_rom.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_float/float_math.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_float/float_v1_rom_shim.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_malloc/pico_malloc.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_mem_ops/mem_ops_aeabi.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_standard_link/crt0.S
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_standard_link/new_delete.cpp
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_standard_link/binary_info.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_stdio/stdio.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_stdio_uart/stdio_uart.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_bootsel_via_double_reset/pico_bootsel_via_double_reset.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/hw/bsp/rp2040/family.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/device/usbd.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/device/usbd_control.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/audio/audio_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/cdc/cdc_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/dfu/dfu_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/dfu/dfu_rt_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/hid/hid_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/midi/midi_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/msc/msc_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/usbtmc/usbtmc_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/class/vendor/vendor_device.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/tusb.c
SRC += $(PICO_SDK_PATH)/lib/tinyusb/src/common/tusb_fifo.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/rp2040_usb_device_enumeration.c

BOOT2INC_DIR += -I$(TMK_PATH)/$(PICO_DIR)
BOOT2INC_DIR += -I$(PICO_SDK_PATH)/src/rp2_common/boot_stage2/include
BOOT2INC_DIR += -I$(PICO_SDK_PATH)/src/rp2_common/boot_stage2/asminclude

$(KEYBOARD_OUTPUT)/src/bs2_default.o: $(PICO_SDK_PATH)/src/rp2_common/boot_stage2/compile_time_choice.S $(KEYBOARD_OUTPUT)/cflags.txt
	@mkdir -p $(KEYBOARD_OUTPUT)/src
	$(CC) $(CFLAGS) $(BOOT2INC_DIR) -c -o $@ $^

$(KEYBOARD_OUTPUT)/src/bs2_default.elf: $(KEYBOARD_OUTPUT)/src/bs2_default.o
	$(CC) $(CFLAGS) -Wl,--build-id=none -nostartfiles -Wl,--script=$(PICO_SDK_PATH)/src/rp2_common/boot_stage2/boot_stage2.ld $^ -o $@


$(KEYBOARD_OUTPUT)/src/bs2_default.bin: $(KEYBOARD_OUTPUT)/src/bs2_default.elf
	$(OBJCOPY) -Obinary $^ $@

$(KEYBOARD_OUTPUT)/src/bs2_default_padded_checksummed.S: $(KEYBOARD_OUTPUT)/src/bs2_default.bin
	$(PICO_SDK_PATH)/src/rp2_common/boot_stage2/pad_checksum -s 0xffffffff $^ $@


flash: $(BUILD_DIR)/$(TRAGET).elf cpfirmware sizeafter
	until $(LSUSB) | grep -q $(RP2BOOT_ID); do\
		printf "$(MSG_BOOTLOADER_NOT_FOUND)" ;\
		sleep 5 ;\
	done
	$(PICOTOOL) load $(BUILD_DIR)/$(TARGET).elf && $(PICOTOOL) reboot

uf2: $(BUILD_DIR)/$(TARGET).bin
	./util/uf2conv.py -f 0xe48bff56 -b 0x10000000 -o $(TARGET).uf2 $^
