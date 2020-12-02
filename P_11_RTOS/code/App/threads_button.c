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

#define DEBOUNCE_LEN		10

/// END: To be programmed


/* -- Variables with global scope
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

osThreadId tid_thread_2;

/// END: To be programmed


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

void thread_1(void const *argument);
void thread_2(void const *argument);

/// END: To be programmed


/* -- Thread definition
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

osThreadDef(thread_1, osPriorityNormal, 1, 0);
osThreadDef(thread_2, osPriorityNormal, 1, 0);

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
	
	tid_thread_2 = osThreadCreate(osThread(thread_2), NULL);
	osThreadCreate(osThread(thread_1), NULL);
	
    /// END: To be programmed
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

// Sends a signal if the user button is pressed (falling edge)
void thread_1(void const *argument)
{
	static uint16_t input_buffer[DEBOUNCE_LEN] = {0};
	static uint16_t idx_ctr = 0;
	static uint8_t	signal_sent = 0;
	
	while (1) {
		uint8_t btn_pressed = 1;
		uint16_t i;
		
		// Read button
		input_buffer[idx_ctr] = hal_gpio_input_read(GPIOA) & USER_BUTTON;
		printf("Input is: %x\n", input_buffer[idx_ctr]);
		idx_ctr++;
		
		if (idx_ctr >= DEBOUNCE_LEN) {	// Check if end of buffer was reached
			idx_ctr = 0;
			printf("Reseting index pointer.\n");
		}
		
		for (i = 0; i < DEBOUNCE_LEN; i++) {	// Do some debouncing
			if (input_buffer[i] == 0) {
				btn_pressed = 0;
				signal_sent = 0;
				printf("Button isn't pressed.\n");
				break;
			}
		}
		
		// Check if button was pressed and if a message hasn't already been sent
		if (!signal_sent && btn_pressed) {
			printf("Button is pressed. Signal sent.\n");
			signal_sent = 1;
			osSignalSet(tid_thread_2, 0x1);
		}
		osDelay(5u);
	}
}

// Toggles the green LED when a signal is received
void thread_2(void const *argument)
{
	osEvent evt;
	
	while (1) {
		evt = osSignalWait(0x1, osWaitForever);	// Wait for event
		
		if (evt.status == osEventSignal) {		// Toggle LED
			hal_gpio_bit_toggle(GPIOG, LED_GREEN);
			printf("Signal received.\n");
		}
	}
}

/// END: To be programmed

