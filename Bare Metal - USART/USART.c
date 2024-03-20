#include "stm32f446xx.h"
#include "USART.h"

void UART2_Config(void){
	
/**********************>>>>>> Steps Followed<<<<<<***********
	1. Enable UART clock and GPIO clock
	2. Configure UART pin for Alternate function
	3. Enable UART on USART_CR1 rgister
	4. Program M bit in USART CR1 to define the word length
	5. Select the baud rate using the USART_BRR register
	6. Enable transmission TE and recieption bits in USART_CR1 register

***********************************************************/

	//1. Enable UART clock and GPIO clock
	RCC->APB1ENR |= (1<<17); //Enable UART2 CLOCK
	RCC->AHB1ENR |= (1<<0);  //Enable GPIOA CLOCK
	
	//2. Configure UART pin for Alternate function
	GPIOA->MODER |= (2<<4); //Bits 5:4 = 1:0 ---> Alternate function for PIN PA2
	GPIOA->MODER |= (2<<6) ;//Bits 7:6 = 1:0 ---> Alternate function for PIN PA3
	
	GPIOA->OSPEEDR |= (3<<4); //Bits 5:4 = 1:1 ---> HIGH SPEED for PIN PA2
	GPIOA->OSPEEDR |= (3<<6) ;//Bits 7:6 = 1:1 ---> HIGH SPEED for PIN PA3
	
	GPIOA->AFR[0] |= (7<<8); //Bytes (11:10:09:08) = 0:1:1:1 --> AF7 Alternate function for USART2 at pin PA2
	GPIOA->AFR[0] |= (7<<12); //Bytes (15:14:13:12) = 0:1:1:1 --> AF7 Alternate function for USART2 at pin PA3
	
	//GPIO->AFR[0]-->ALTERNATE FUNVTION LOW REGISTER
	//GPIO->AFR[1]-->ALTERNATE FUNVTION HIGH REGISTER
	
	/*
	In simpler terms, when you put a GPIO pin in alternate function mode, you're telling it to do something different
	from its usual job of just sending or receiving digital signals. Instead, it could be used for tasks like communicating
	with other devices, generating specific timing signals, or controlling special hardware features. It's like giving the pin
	a new job to do, expanding its capabilities beyond basic input and output.
	*/

	//3. Enable UART on USART_CR1 rgister
	USART2->CR1 = 0x00; //clear USART
	USART2->CR1 |= (1<<13); //USART2 BIT ENABLE 
	
	//4. Program M bit in USART CR1 to define the word length
	USART2->CR1 &= ~(1u<<12); //M=0 --> 8 bit word length
	
	//5. Select the baud rate using the USART_BRR register
	USART2->BRR |= (7<<0) | (24<<4); //Baud Rate of 115200, PCLK1 at 45 MHz
	
	//6. Enable transmission TE and recieption bits in USART_CR1 register
	USART2->CR1 |= (1<<2); //RECEIVER Enabled
	USART2->CR1 |= (1<<3); //TRANSMITTER Enabled
	
}






void UART2_SendChar(uint8_t c){

/**********************>>>>>> Steps Followed<<<<<<***********
	1.Write the data to send in the USART_DR register(this Clears the TXE bit).Repeat this for each data to be transmitted
		in case of single buffer.
	2.After writing the last data into the USART_DR register,wait until TC=1. This indicates that the transmission of the last
	  frame is complete. This is required for instances when USART is disabled or enters the Halt mode to avoid corrupting the 
		last transmission.

***********************************************************/
	
	//c = c - 189;
	
	USART2->DR = c;  //load data into the DR register
	while(!(USART2->SR & (1<<7))); //wait for TC to set....this indicates that the transmission is completed
	
}



