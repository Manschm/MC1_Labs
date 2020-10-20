/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module wakeup timer.
 *
 *  $Id: wakeup_timer.c 1804 2019-09-13 15:52:32Z kjaz $
 * ------------------------------------------------------------------------- */


/* Standard includes */
#include <reg_stm32f4xx.h>

/* User includes */
#include "wakeup_timer.h"


/* -- Macros
 * ------------------------------------------------------------------------- */

#define TIME_OUT 0x1000
#define LSION    (0x01 << 0u)
#define LSIRDY   (0x01 << 1u)
#define WUTWF    (0x01 << 2u)


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void wakeup_init(void)
{
    uint32_t reg = 0;
    uint32_t count = 0;

    /* In LP mode the clocks might be disabled.
     * Enable LSI and wait till its ready */
    RCC->CSR |= LSION;
    do {
        reg = RCC->CSR & LSIRDY;
        count++;
    } while ((reg == 0) && (count != TIME_OUT));

    /*
     * There is no wakeup timer hal, please read/write
     * directly to the registers.
     */

    /// STUDENTS: To be programmed
	PWR->CR |= 1<<8;					// Unlock backup domain
	RTC->WPR = 0xCA;					// Write unlock key
	RTC->WPR = 0x53;
	RCC->BDCR |= (1<<15) | (0x10<<8);	// Set clock source of RTC
	
	RTC->CR &= ~(1<<10);				// Disable wakeup timer
	while (~(RTC->ISR & (1<<2)));		// Wait until register access is garanteed
	RTC->CR &= ~(0x3);					// Select prescaler 16
	RTC->WUTR = 2048-1;					// Set auto-reload value
	RTC->CR |= (1<<14);					// Enable wakeup interrupt
	
	RTC->ISR &= ~(1<<2);				// Clear any pending interrupt flags
	EXTI->IMR |= (1<<22);				// Interrupt lines mask
	EXTI->RTSR |= (1<<22);				// Trigger on rising edge
	NVIC->ISER0 |= (1<<19);				// ENABLE RTC wakeup interrupt in the NVIC
	
	RTC->CR |= (1<<10);					// Enable wakeup timer
	RTC->WPR = 0xFF;					// Enable RTC write protection
	
	
    /// END: To be programmed
}

/* -- Interrupt function definitions
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed
void RTC_WKUP_IRQHandler()
{
	RTC->ISR &= ~(1<<10);	// Clear WUTF (wakeup timer flag)
	EXTI->PR &= ~(1<<22);	// Clear EXTI interrupt flag
	// NVIC flag?
}



/// END: To be programmed
