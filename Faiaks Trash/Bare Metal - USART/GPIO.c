#include "stm32f446xx.h"
#include "GPIO.h"
#include "CLOCK.h"

//rm0390 - 7.4
void GPIOA_config(void){
	//1. Enable the GPIO CLOCK
	RCC->AHB1ENR |= (1<<0);
	
	//2. Set the PIN as Output
	GPIOA->MODER |= (0<<11) | (1<<10);    //PIN pa5(bits 11:10) as OUTPUT MODE(01) //PIN selection
	
	//3. Configure the Output Mode
	GPIOA->OTYPER |=  (0<<5); // 0 =  Output push-pull (reset state)
	GPIOA->OSPEEDR |= (1<<11) | (0<<10); // 00 = low speed, 10 = Fast Speed
	
	GPIOA->PUPDR &= (0<<11) | (0<<10); //PIN P5 (bits 11:10) are 0:0 --> No Pull Up or Pull Down

}
