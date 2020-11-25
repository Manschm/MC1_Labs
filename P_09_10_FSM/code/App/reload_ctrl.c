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

/* -- Local type definitions
 * ------------------------------------------------------------------------- */

/* enumerate the states */
typedef enum {
    SEC,
    MIN
} reload_ctrl_state_t;

/* -- Variables with module-wide scope
 * ------------------------------------------------------------------------- */

/* event queue for this FSM */
static queue_t rl_ctrl_queue;

/* current state of the FSM */
static reload_ctrl_state_t state = SEC;


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

    switch (state) {
        case SEC:
            switch (event) {
                case RLC_BUTTON_SELECT_EVENT:
                    state = MIN;
                    break;
				
                case RLC_BUTTON_UP_EVENT:
					reload_inc_seconds();
                    break;
				
                case RLC_BUTTON_DOWN_EVENT:
					reload_dec_seconds();
                    break;
				
                default:
                    ;// no change
            }
            break;

        case MIN:
            switch (event) {
                case RLC_BUTTON_SELECT_EVENT:
                    state = SEC;

                    break;
				
                case RLC_BUTTON_UP_EVENT:
					reload_inc_minutes();
                    break;
				
                case RLC_BUTTON_DOWN_EVENT:
					reload_dec_minutes();
                    break;
				
                default:
                    ;// no change
            }
            break;
			
        default:
            ;// no change
    }
	
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
	
	switch (state) {
        case SEC:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_SEC);
            break;
        
        case MIN:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_MIN);
            break;
    }
}

/// END: To be programmed
