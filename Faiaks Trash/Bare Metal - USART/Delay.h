
#ifndef __Delay_H
#define __Delay_H


#include <stdint.h>
#include "stm32f446xx.h"

#ifdef __cplusplus
extern "C" {
#endif



void TIM6Config(void);    //TIM6 & TIM7 are basic purpose timers
void delay_micro_s(uint16_t us);
void delay_ms(uint16_t ms);


#ifdef __cplusplus
}
#endif
#endif

