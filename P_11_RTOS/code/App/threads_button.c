/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module threads_button.
 * 
 *  $Id: threads_button.c 1319 2017-12-08 10:20:00Z kjaz $
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
#define USER_BUTTON         (0x1 << 0u)
/// STUDENTS: To be programmed




/// END: To be programmed


/* -- Variables with global scope
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed




/// END: To be programmed


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed




/// END: To be programmed


/* -- Thread definition
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed




/// END: To be programmed


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void threads_init(void)
{
    hal_gpio_input_t gpio_in;
    hal_gpio_output_t gpio_out;
    
    GPIOA_ENABLE();
    GPIOG_ENABLE();
  
    uart_init();
    
    gpio_in.pins = USER_BUTTON;
    gpio_in.pupd = HAL_GPIO_PUPD_NOPULL;
    
    hal_gpio_init_input(GPIOA, gpio_in);
    
    gpio_out.pins = LED_GREEN;
    gpio_out.pupd = HAL_GPIO_PUPD_UP;
    gpio_out.out_speed = HAL_GPIO_OUT_SPEED_100MHZ;
    gpio_out.out_type = HAL_GPIO_OUT_TYPE_PP;
    
    hal_gpio_init_output(GPIOG, gpio_out);
    
    /// STUDENTS: To be programmed    




    /// END: To be programmed
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed




/// END: To be programmed

