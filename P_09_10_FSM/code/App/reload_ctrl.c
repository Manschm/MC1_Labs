/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/** 
 *  \brief  Implementation of module reload_ctrl.
 * 
 *  $Id: reload_ctrl.c 1064 2016-11-18 06:12:26Z feur $
 * ------------------------------------------------------------------------- */
 

/* User includes */
#include "reload_ctrl.h"
#include "reload.h"
#include "queue.h"
#include "seg7_display.h"
#include "lcd.h"
#include "egg_timer.h"


/* -- Macros
 * ------------------------------------------------------------------------- */

//                           "                    "
#define TEXT_LINE_1         ("RELOAD        0>MODE")
#define TEXT_LINE_2_SEC     ("3>SEC- 2>SEC+ 1>MIN ")
#define TEXT_LINE_2_MIN     ("3>MIN- 2>MIN+ 1>SEC ")

/// STUDENTS: To be programmed

/*
typedef enum {
    RLC_NO_EVENT,
    RLC_DISPLAY_UPDATE_EVENT,   // just update the display
    RLC_BUTTON_SELECT_EVENT,    // change between seconds and minutes
    RLC_BUTTON_UP_EVENT,        // increment the selected reload value
    RLC_BUTTON_DOWN_EVENT       // decrement the selected reload value
} reload_ctrl_events_t;
*/

/* -- Variables with module-wide scope
 * ------------------------------------------------------------------------- */

/* event queue for this FSM */
static queue_t rl_ctrl_queue;

/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/**
 *  Put new event in this FSMs queue.
 *  event : Event for the FSM to process.
 */
void rl_ctrl_put_queue(reload_ctrl_events_t event)
{
	queue_enqueue(&rl_ctrl_queue, event);
}

/**
 *  Handle events in queue of this FSM.
 */
void rl_ctrl_handle_event(void)
{
	uint32_t event;

    event = queue_dequeue(&rl_ctrl_queue);

    // FSM here
	
    /* Update outputs */
    if (event != RLC_NO_EVENT) {
        seg7_output_update();   
        lcd_output_update();        
    }
}

/**
 *  Update content for display for this FSM.
 */
void rl_ctrl_update_display(void)
{
	lcd_write(LCD_LINE_1, TEXT_LINE_1);
}

/// END: To be programmed
