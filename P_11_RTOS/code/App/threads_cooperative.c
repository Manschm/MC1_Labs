/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module threads_cooperative.
 * 
 *  $Id: threads_cooperative.c 1319 2017-12-08 10:20:00Z kjaz $
 * ------------------------------------------------------------------------- */


/* Standard includes */ 
#include <cmsis_os.h>
#include <hal_gpio.h>
#include <stdio.h>

/* User includes */
#include "threads.h"
#include "uart.h"


/* -- Macros
 * ------------------------------------------------------------------------- */

#define LED_GREEN           (0x1 << 13u)
#define LED_RED             (0x1 << 14u)
#define HALF_SECOND         (0x7fffff)


/* -- Variables with global scope
 * ------------------------------------------------------------------------- */


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

void led_green_job(void const *argument);
void led_red_job(void const *argument);

/// END: To be programmed
static void wait_blocking(uint32_t value);


/* -- Thread definition
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

osThreadDef(led_green_job, osPriorityNormal, 1, 0);
osThreadDef(led_red_job, osPriorityNormal, 1, 0);

/// END: To be programmed


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void threads_init(void)
{
    hal_gpio_output_t gpio;

    uart_init();
  
    GPIOG_ENABLE();
    
    gpio.pins = LED_GREEN | LED_RED;
    gpio.pupd = HAL_GPIO_PUPD_UP;
    gpio.out_speed = HAL_GPIO_OUT_SPEED_100MHZ;
    gpio.out_type = HAL_GPIO_OUT_TYPE_PP;
    
    hal_gpio_init_output(GPIOG, gpio);
    
    /// STUDENTS: To be programmed      
	
	// Thread that toggles the green LED once
	if (osThreadCreate(osThread(led_green_job), NULL) != NULL) {
		printf("Thread 1 created!\n");
	} else {
		printf("Thread 1 not created!\n");
	}
	
	// Thread that toggles the green LED once
	if (osThreadCreate(osThread(led_red_job), NULL) != NULL) {
		printf("Thread 2 created!\n");
	} else {
		printf("Thread 2 not created!\n");
	}
	
    /// END: To be programmed
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

// Turn green LED on and off for 500ms each
void led_green_job(void const *argument)
{
	hal_gpio_bit_set(GPIOG, LED_GREEN);
	wait_blocking(HALF_SECOND);
	hal_gpio_bit_reset(GPIOG, LED_GREEN);
	wait_blocking(HALF_SECOND);
}

// Turn red LED on and off for 500ms each
void led_red_job(void const *argument)
{
	hal_gpio_bit_set(GPIOG, LED_RED);
	wait_blocking(HALF_SECOND);
	hal_gpio_bit_reset(GPIOG, LED_RED);
	wait_blocking(HALF_SECOND);
}

/// END: To be programmed

/**
 *  \brief  Wait loop.
 *  \param  value : Iterations to wait. Blocks execution of other threads.
 */
static void wait_blocking(uint32_t value)
{
    for (; value > 0u; value--);
}
