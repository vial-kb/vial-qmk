#pragma once

#include_next <mcuconf.h>

// I2C0 for LEFT side OLED (GP12 SDA, GP13 SCL)
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

// ADC for joystick
#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE

// Hardware UART for split serial
#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0 TRUE
