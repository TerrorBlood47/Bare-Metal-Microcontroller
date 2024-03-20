
#include "stm32f446xx.h"
#include "CLOCK.h"

//rm0390 - 6
void initClock(void)
{
	
/***************>>>>>>>>> Steps Followed<<<<<**********************
	1. Enable HSE & wait for HSE to become Ready
	2. Set the POWER ENABLE CLOCK & VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH & Latency related settings
	4. Configure the PRESCALARS HCLK, PCLK1 and PCLK2
  5. Configure the MAIN PLL
  6. Enable the PLL & wait for it to become Ready
  7. Select the Clock Source and wait for it to become set
********************************************************************/

	//1. Enable HSE & wait for HSE to become Ready
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	//2. Set the POWER ENABLE CLOCK & VOLTAGE REGULATOR
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS; //ALWAYS RESET MODE (11)
	
	//3. Configure the FLASH PREFETCH & Latency related settings
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	//ICEN -- instruction cache, DCEN -- Data Cache, PRFTEN -- prefetch , LAtency;
	/*
	Wait states are introduced to ensure that the data read from Flash memory is stable and reliable. 
	Each wait state represents a delay (usually in terms of clock cycles) inserted between the processor's 
	request for data and the availability of that data. The more wait states, the longer the delay.
	*/
	
	
	//4. Configure the PRESCALARS HCLK, PCLK1 and PCLK2
	
	//AHB PreScalar
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	
	//APB1 PreScalar
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	
	//APB2 PreScalar
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	
	

	//5. Configure the MAIN PLL
	
	/*
	
	1. What is a PLL?
	A PLL is a circuit that generates an output signal whose phase is related to the phase of an input signal. 
	It's commonly used to generate stable clock signals with precise frequencies.

  2. Role in STM32F446RE:
	The STM32F446RE microcontroller has an internal PLL that allows you to generate clock signals with frequencies
	higher than the external oscillator or crystal connected to the microcontroller.

	3.Clock Sources:
	The STM32F446RE typically has multiple clock sources available, such as an external crystal oscillator (HSE), an 
	internal RC oscillator (HSI), and an external clock signal (HSE bypass mode). These clock sources provide the base 
	frequency for the PLL.

	4. PLL Configuration:
	You can configure the PLL to multiply the frequency of one of these clock sources to generate a higher-frequency output. 
	This multiplication factor is determined by the PLL configuration settings, including the PLL input clock source, 
	multiplication factor (N), and division factors for the PLL output clocks.

	5. Example:
	For example, if you have a 8 MHz external crystal oscillator connected to the HSE input, you can configure the PLL to 
	multiply this frequency by, say, 9, resulting in a 72 MHz output frequency. This high-frequency output can then be used 
	to drive the CPU, peripherals, and other modules within the microcontroller.

	6. Stability and Precision:
	PLLs are designed to provide stable and precise clock signals, which are essential for the correct operation of the 
	microcontroller and any connected peripherals. By using a PLL, you can ensure that your system operates at the desired 
	frequency with minimal jitter and drift.
	
	*/
	
	/*
	formula: SystemCoreClock =((INPUT_CLOCK(HSE OR HSI IN HZ)/PLL_M) * PLL_N)/PLL_P
	*/
	
	RCC->PLLCFGR |= (PLL_M<<0) | (PLL_N<<6) | (PLL_P<<16) | (RCC_PLLCFGR_PLLSRC_HSE);
	
	// 6. Enable the PLL & wait for it to become Ready
	
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	
	// 7. Select the Clock Source and wait for it to become set
	
	RCC->CFGR |= RCC_CFGR_SW_PLL;  //SW = SWITCH , S = STATUS
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

}
