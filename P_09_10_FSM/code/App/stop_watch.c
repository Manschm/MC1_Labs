/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/** 
 *  \brief  Implementation of module stop_watch.
 * 
 *  $Id: stop_watch.c 1064 2016-11-18 06:12:26Z feur $
 * ------------------------------------------------------------------------- */
 

/* User includes */
#include "stop_watch.h"
#include "scheduler.h"

/// STUDENTS: To be programmed


/* -- Variables with module-wide scope
 * ------------------------------------------------------------------------- */

static scheduler_task_t task_increment;
static uint16_t stop_watch_time = 0;		// 1 = 100ms


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

static void stop_watch_increment(void);


/**
 *  \brief  Start stop watch.
 */
void stop_watch_start(void) {
	stop_watch_time = 0;
    seg7_output_update();
    scheduler_register_task(&task_increment, stop_watch_increment, HUNDRED_MILLISECONDS);
}

/**
 *  \brief  Stop stop watch.
 */
void stop_watch_stop(void) {
	// stop the timer
    scheduler_unregister_task(&task_increment);
}

/**
 *  \brief  Reset stop watch.
 */
void stop_watch_reset(void) {
	// resume the timer
    stop_watch_time = 0;
}

/**
 *  \brief  Returns 7 segment output data.
 *  \param  output : Pointer to struct to store output data.
 */
void stop_watch_get_output(seg7_output_t *output) {
	output->value = stop_watch_time;
    output->dots = (0x1 << 1u);     // Set dot on DS1
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/**
 *  \brief  Decrement timer variable.
 */
static void stop_watch_increment(void)
{
	stop_watch_time++;
	if ((stop_watch_time & 0xF) >= 0x9) {
		stop_watch_time &= 0xFFF0;
		stop_watch_time += 0x10;
	}
	if ((stop_watch_time & 0xF0) >= 0x90) {
		stop_watch_time &= 0xFF00;
		stop_watch_time += 0x100;
	}
	if ((stop_watch_time & 0xF00) >= 0x900) {
		stop_watch_time &= 0xF000;
		stop_watch_time += 0x1000;
	}
	if ((stop_watch_time & 0xF000) >= 0x9000) {
		stop_watch_time = 0;
	}

    // output data
    seg7_output_update();
}

/// END: To be programmed
