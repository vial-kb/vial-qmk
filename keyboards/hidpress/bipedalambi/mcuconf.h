#pragma once

#include_next <mcuconf.h>

// I2C0 for LEFT side OLED (GP12 SDA, GP13 SCL)
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

// I2C1 for RIGHT side OLED (GP18 SDA, GP19 SCL)
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE

// ADC for joystick (LEFT) and encoder might use analog
#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE

// Enable UART0 for serial (LEFT side uses GP0/GP1)
#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0 TRUE

// Enable UART1 for serial (RIGHT side uses GP16/GP17)
#undef RP_SIO_USE_UART1
#define RP_SIO_USE_UART1 TRUE
