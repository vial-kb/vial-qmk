
#pragma once

void pico_cdc_enable_printf(void);
void pico_cdc_disable_printf(void);

// weak functions
void pico_cdc_change_baudrate_cb(uint32_t baudrate);
void pico_cdc_receive_cb(uint8_t const* buf, uint32_t cnt);
