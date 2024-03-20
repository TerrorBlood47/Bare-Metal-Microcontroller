#include "Delay.h"
#include "stm32f446xx.h"


void TIM6Config(void){
	
	/********************>>>>Steps Followed <<<<***********************
	
	1.Enable Timer Clock
	2.Set the Prescalar & the ARR
	3.Enable the timer, wait for the update flag to set

	********************************************************************/

	// 1.Enable Timer Clock
	RCC->APB1ENR |= (1<<4);
	
	//2.Set the Prescalar & the ARR
	TIM6->PSC = (60 - 1); //90 MHz / 90 = 1 MHz ~~ 1 uS delay for 1 clock cycle
	
	TIM6->ARR = 0xffff; // max ARR value
	
	/*
	The Auto-Reload Register (ARR) in microcontroller timers like those found in STM32 devices determines 
	when the timer resets after counting to a certain value. Think of it like setting a timer for a specific 
	duration: once the timer reaches the value set in the ARR register, it triggers an action (like an interrupt) 
	and starts counting again from zero. Adjusting the ARR register lets you control the timing of events in your 
	microcontroller application, whether it's generating precise intervals for tasks or coordinating actions with 
	external devices.
	*/
	
	//3.Enable the timer, wait for the update flag to set
	TIM6->CR1 |= (1<<0); //CEN(Counter ENable) bit enabled
	
	while(!(TIM6->SR & (1<<0)));//SR = Status Register || set when CR reg is updated

}

void delay_micro_s(uint16_t us){
/*
1. Reset the Clock
2. Wait for the counter to reach the input value. As each CNT takes 1 uS, the total 
   waiting time will be required uS delay	
*/
	
	TIM6->CNT = 0; //CLOCK COUNTER value is stored here, allocating 0 to it effectively resets the CLOCK
	
	while((TIM6->CNT) < us);
	
}

void delay_ms(uint16_t ms){
	
	for(uint16_t i=0; i<ms; i++){
		delay_micro_s(1000);
	}
	
	//while(ms--);
}

