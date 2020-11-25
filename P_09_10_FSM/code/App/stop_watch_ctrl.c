/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/** 
 *  \brief  Implementation of module stop_watch_ctrl.
 * 
 *  $Id: stop_watch_ctrl.c 1064 2016-11-18 06:12:26Z feur $
 * ------------------------------------------------------------------------- */
 

/* User includes */
#include "stop_watch_ctrl.h"
#include "stop_watch.h"
#include "queue.h"
#include "lcd.h"

/* -- Macros
 * ------------------------------------------------------------------------- */

//                           "                    "
#define TEXT_LINE_1         ("STOP WATCH    0>MODE")
#define TEXT_LINE_2_START   ("              1>GO  ")
#define TEXT_LINE_2_RESET   ("              1>RST ")
#define TEXT_LINE_2_STOP    ("              1>STOP")

/// STUDENTS: To be programmed

/* -- Local type definitions
 * ------------------------------------------------------------------------- */

/* enumerate the states */
typedef enum {
    START,
	STOP,
	RESET
} stop_watch_ctrl_state_t;

/* -- Variables with module-wide scope
 * ------------------------------------------------------------------------- */

/* event queue for this FSM */
static queue_t rl_ctrl_queue;

/* current state of the FSM */
static stop_watch_ctrl_state_t state = START;


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/**
 *  Put new event in this FSMs queue.
 *  event : Event for the FSM to process.
 */
void sw_ctrl_put_queue(stop_watch_ctrl_events_t event)
{
	queue_enqueue(&rl_ctrl_queue, event);
}

/**
 *  Handle events in queue of this FSM.
 */
void sw_ctrl_handle_event(void)
{
	uint32_t event;

    event = queue_dequeue(&rl_ctrl_queue);

    switch (state) {
        case START:
            switch (event) {
                case SWC_BUTTON_EVENT:
					stop_watch_start();
                    state = STOP;
                    break;
				
                default:
                    ;// no change
            }
            break;

        case STOP:
            switch (event) {
                case SWC_BUTTON_EVENT:
					stop_watch_stop();
                    state = RESET;
				
                default:
                    ;// no change
            }
            break;
			
		case RESET:
            switch (event) {
                case SWC_BUTTON_EVENT:
					stop_watch_reset();
                    state = START;
				
                default:
                    ;// no change
            }
            break;
        default:
            ;// no change
    }
	
    /* Update outputs */
    if (event != SWC_NO_EVENT) {
        seg7_output_update();   
        lcd_output_update();        
    }
}

/**
 *  Update content for display for this FSM.
 */
void sw_ctrl_update_display(void)
{
	lcd_write(LCD_LINE_1, TEXT_LINE_1);
	
	switch (state) {
        case START:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_START);
            break;
        
        case RESET:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_RESET);
            break;
		
		case STOP:
			lcd_write(LCD_LINE_2, TEXT_LINE_2_STOP);
            break;
    }
}

/// END: To be programmed
