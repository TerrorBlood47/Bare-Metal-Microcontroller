#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include<stdint.h>
#include "stm32f446xx.h"

void UART2_Config(void);
void UART2_SendChar(uint8_t c);


#ifdef __cplusplus
}
#endif
#endif

