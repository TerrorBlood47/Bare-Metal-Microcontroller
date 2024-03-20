#include "stm32f446xx.h"
#include "CLOCK.h"
#include "GPIO.h"
#include "Delay.h"
#include "USART.h"

int main(void){
	
	initClock();
	TIM6Config();
	//GPIOA_config();
	
	
/*	
	//LED Blinking on the MC Board
	while(47){
		GPIOA->BSRR |= (1<<5); //set the PA5 pin
		
		delay_ms(100); 
		
		GPIOA->BSRR |= ((1<<5)<<16); //reset the PA5 pin
		
		delay_ms(100);
		
	}
	
*/	
	
	//
	
	UART2_Config();
	delay_ms(2000);
	
	while(1){
		
		UART_SendChar(USART2, 'C');
		delay_ms(1000);
		
	}
	
}

