#pragma once

#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN GP1
#define I2C1_SDA_PIN GP0

//Disable unused functionality
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifdef COMBO_ENABLE
#    define COMBO_COUNT 9
#    define COMBO_TERM 200
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 30
