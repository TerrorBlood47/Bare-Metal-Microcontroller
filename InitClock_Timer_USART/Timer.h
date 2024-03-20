#include <stdint.h>
#include "stm32f446xx.h"

void TIM6_Config(void);

void delay_us(uint16_t us);

void delay_ms(uint16_t ms);

void ARR_Interrupt_Call(uint16_t s);
	