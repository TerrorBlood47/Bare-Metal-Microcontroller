#include "Timer.h"
#include "USART.h"

void TIM6_Config(void) {
  
  /*  Timer configuration steps:
      1. Enable Timer clock
      2. Set the prescalar and the ARR
      3. Enable the Timer, and wait for the update 
         Flag to set
  */
  
  
  // Step 1: enable clock for TIM6EN = 1
  RCC->APB1ENR |= (1<<4); 
  
  // Step 2: Set Prescalar and ARR
  
  // APB1 bus is set to 50MHz, Timer is set to 30Mhz/ 30 = 1 MHz, So delay is 10^(-6) second
  TIM6->PSC = 30-1; // prescalar value
  TIM6->ARR = 0xffff; // Maximum ARR value
  
  // Step 3: ENABLE the TIMER and wait for CONFIRMATION
  
  // Enable CEN (Counter)
  TIM6->CR1 |= (1<<0);
  
  // Check if timer is ready
  while(!(TIM6->SR & (1<<0)));
}


void delay_us(uint16_t us) {
  
  /*
    1. RESET the Counter
    2. Wait for the Counter to reach the entered value.
        As each count will take 10^(-6) s, the total waiting time will be the required delay us
  */
    
  TIM6->CNT = 0;
  while (TIM6->CNT < us);
  
}

void delay_ms(uint16_t ms) {
  
  for (uint16_t i=0; i<ms; i++)
  {
    delay_us(1000); // delay of 1 ms
  }
  
}

void ARR_Interrupt_Call(uint16_t s){
 
 TIM6->DIER |= TIM_DIER_UIE;//UIE Enabled
 
 TIM6->CNT = 0;
 
 TIM6->ARR = s;
 
 TIM6->SR = ~TIM_SR_UIF;
 
 volatile unsigned int x = TIM6->ARR;
 
 char c = (char)x;
 
 UART_SendChar(USART2,c);
 
 while(!(TIM6->SR & TIM_SR_UIF)){
  UART_SendChar(USART2, 'E');
 }
 UART_SendString(USART2," FINISHED ");
}

