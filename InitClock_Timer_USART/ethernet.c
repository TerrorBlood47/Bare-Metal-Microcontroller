#include<stm32f446xx.h>
#include"USART.h"
#include"CLOCK.h"
#include"Timer.h"
#include"GPIO.h"



int main(void){
	
	initClock();
	TIM6_Config();
	UART2_Config();
	
	delay_ms(3000);
	
	UART_SendString(USART2, "Faiak, Roll: 01, Zisan, Roll: 23\n");
	delay_ms(2000);
	
	while(1){
		UART_SendString(USART2, "Hello World\n");
		delay_ms(1000);
	}

}

