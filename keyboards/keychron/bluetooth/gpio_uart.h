#ifndef __GPIO_UART_H__
#define __GPIO_UART_H__


#include "stdarg.h"


#define UART_DEBUG_TRACE

#ifdef UART_DEBUG_TRACE
void gpiouart_init(void);
void log_uint8(unsigned char val);
void log_uint8_arrary(unsigned char *val ,unsigned char len);

void myxprintf (			/* Put a formatted string to the default device */
	const char*	fmt,	/* Pointer to the format string */
	...					/* Optional arguments */
);

	#define LOG_TRACE(format,...) myxprintf(format,##__VA_ARGS__)
	#define LOG_UINT8_ARRARY(val,len) log_uint8_arrary(val,len)
	#define LOG_UINT8(val) log_uint8(val)
#else
    #define gpiouart_init(void)
	#define LOG_TRACE(format,...)
	#define LOG_UINT8_ARRARY(val,len)
	#define LOG_UINT8(val)
#endif




#endif

