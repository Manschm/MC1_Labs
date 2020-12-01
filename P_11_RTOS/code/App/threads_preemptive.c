/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module threads_preemtive.
 * 
 *  $Id: threads_preemptive.c 1319 2017-12-08 10:20:00Z kjaz $
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
osThreadDef(led_red_job, osPriorityAboveNormal, 1, 0);

/// END: To be programmed


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void threads_init(void)
{
    hal_gpio_output_t gpio;
    
    GPIOG_ENABLE();
  
    uart_init();
    
    gpio.pins = LED_GREEN | LED_RED;
    gpio.pupd = HAL_GPIO_PUPD_UP;
    gpio.out_speed = HAL_GPIO_OUT_SPEED_100MHZ;
    gpio.out_type = HAL_GPIO_OUT_TYPE_PP;
    
    hal_gpio_init_output(GPIOG, gpio);
    
    /// STUDENTS: To be programmed    
	
	osThreadCreate(osThread(led_green_job), NULL);	// Toggle green LED once
	osThreadCreate(osThread(led_red_job), NULL);	// Toggle red LED once
	
    /// END: To be programmed
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

// Turn the green LED on and off for 500ms
void led_green_job(void const *argument)
{
	while (1) {
		hal_gpio_bit_set(GPIOG, LED_GREEN);
		wait_blocking(HALF_SECOND);
		hal_gpio_bit_set(GPIOG, LED_GREEN);
		wait_blocking(HALF_SECOND);
	}
}

// Turn the red LED on and off for 500ms with an 40ms delay at the end
void led_red_job(void const *argument)
{
	while (1) {
		hal_gpio_bit_set(GPIOG, LED_RED);
		wait_blocking(HALF_SECOND);
		hal_gpio_bit_reset(GPIOG, LED_RED);
		wait_blocking(HALF_SECOND);
		osDelay(40u);
	}
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
