/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module threads_roundrobin.
 * 
 *  $Id: threads_roundrobin.c 1319 2017-12-08 10:20:00Z kjaz $
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
#define HALF_SECOND         (0x7fffff)


/* -- Variables with global scope
 * ------------------------------------------------------------------------- */


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

void led_on_job(void const *argument);
void led_off_job(void const *argument);

/// END: To be programmed
static void wait_blocking(uint32_t value);


/* -- Thread definition
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

osThreadDef(led_on_job, osPriorityNormal, 1, 0);
osThreadDef(led_off_job, osPriorityNormal, 1, 0);

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
    
    gpio.pins = LED_GREEN;
    gpio.pupd = HAL_GPIO_PUPD_UP;
    gpio.out_speed = HAL_GPIO_OUT_SPEED_100MHZ;
    gpio.out_type = HAL_GPIO_OUT_TYPE_PP;
    
    hal_gpio_init_output(GPIOG, gpio);
    
    /// STUDENTS: To be programmed    
	
	osThreadCreate(osThread(led_on_job), NULL);		// Turn green LED on
	osThreadCreate(osThread(led_off_job), NULL);	// Turn green LED off
	
    /// END: To be programmed
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

// Turn green LED on and wait for 500ms
void led_on_job(void const *argument)
{
	hal_gpio_bit_set(GPIOG, LED_GREEN);
	wait_blocking(HALF_SECOND);
}

// Turn green LED off and wait for 500ms
void led_off_job(void const *argument)
{
	hal_gpio_bit_reset(GPIOG, LED_GREEN);
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
