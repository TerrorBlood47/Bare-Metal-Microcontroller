#include "CLOCK.h"
#include "GPIO.h"
#include "USART.h"
#include "SYS_INIT.h"
#include "Timer.h"

#include "stm32f446xx.h"

int main(void) {
	initClock();
	TIM6_Config();
	
	UART2_Config();
	while(1){
		
		UART2_SendChar('C');
		delay_ms(1000);
		
	}
	
	
}
