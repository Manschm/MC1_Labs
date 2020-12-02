/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module threads_uart.
 * 
 *  $Id: threads_uart.c 1319 2017-12-08 10:20:00Z kjaz $
 * ------------------------------------------------------------------------- */


/* Standard includes */ 
#include <cmsis_os.h>
#include <stdio.h>

/* User includes */
#include "threads.h"
#include "uart.h"

/* -- Macros
 * ------------------------------------------------------------------------- */

//#define MUTEX_ENABLE        (1)
#define HALF_SECOND         (0x7fffff)


/* -- Variables with global scope
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

osMutexId count_id;

/// END: To be programmed


/* -- Variables with module wide scope
 * ------------------------------------------------------------------------- */

static uint32_t count = 0u;


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

void thread_1(void const *argument);
void thread_2(void const *argument);

/// END: To be programmed
static void wait_blocking(uint32_t value);


/* -- Thread / mutex definition
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

osThreadDef(thread_1, osPriorityNormal, 1, 0);
osThreadDef(thread_2, osPriorityNormal, 1, 0);

#ifdef MUTEX_ENABLE
osMutexDef(count);
osMutexId(count_id);
#endif

/// END: To be programmed


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void threads_init(void)
{
    uart_init();
    
    /// STUDENTS: To be programmed    
	
	osThreadCreate(osThread(thread_2), NULL);
	osThreadCreate(osThread(thread_1), NULL);
	
	#ifdef MUTEX_ENABLE
	count_id = osMutexCreate(osMutex(count));
	#endif
	
    /// END: To be programmed
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

// Sends a signal if the user button is pressed (falling edge)
void thread_1(void const *argument)
{
	while (1) {
		#ifdef MUTEX_ENABLE
		osMutexWait(count_id, osWaitForever);
		#endif
		
		count++;
		printf("Thread 1 incremented count. Current value is %d\r\n", count);
		
		#ifdef MUTEX_ENABLE
		osMutexRelease(count_id);
		#endif
		
		wait_blocking(HALF_SECOND);
	}
}

// Toggles the green LED when a signal is received
void thread_2(void const *argument)
{
	while (1) {
		#ifdef MUTEX_ENABLE
		osMutexWait(count_id, osWaitForever);
		#endif
		
		count++;
		printf("Thread 2 incremented count. Current value is %d\r\n", count);
		
		#ifdef MUTEX_ENABLE
		osMutexRelease(count_id);
		#endif
		
		wait_blocking(HALF_SECOND);
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

