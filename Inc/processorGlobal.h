#ifndef PROCESSORGLOBAL_H_
#define PROCESSORGLOBAL_H_

#ifdef __cplusplus
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L // takes care of ensuring AC6 builds use extensions like strtok_r
#endif
#endif

#include "stm32l0xx_hal.h"

#ifdef __cplusplus
extern "C" void fatalERROR(const char* file, unsigned line);
#else
void fatalERROR(const char* file, unsigned line);
#endif


// SERIAL Port Definitions
#ifdef __cplusplus
extern "C" UART_HandleTypeDef *usartHandler(uint8_t num);
#else
UART_HandleTypeDef *usartHandler(uint8_t num);
#endif

#define ENABLE_SERIAL2

// TIMER Port Definitions
#ifdef __cplusplus
extern "C" TIM_HandleTypeDef *timHandler(uint8_t num);
#else
TIM_HandleTypeDef *timHandler(uint8_t num);
#endif


// General Definitions
#define ArraySizeof( X) (sizeof(X)/sizeof(X[0]))

#endif /* PROCESSORGLOBAL_H_ */
