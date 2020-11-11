/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module mode_control.
 * 
 *  $Id: mode_control.c 1071 2016-11-18 12:38:50Z ruan $
 * ------------------------------------------------------------------------- */

 
/* User includes */
#include "mode_control.h"
#include "queue.h"
#include "buttons.h"
#include "egg_timer_ctrl.h"
#include "egg_timer.h"
#include "reload_ctrl.h"
#include "reload.h"
#include "stop_watch_ctrl.h"
#include "stop_watch.h"
#include "button_count.h"
#include "lcd.h"
#include "seg7_display.h"


/* -- Type definitions
 * ------------------------------------------------------------------------- */

/* enumerate the states */
typedef enum {
    STATE_EGG_TIMER,
    STATE_RELOAD_CTRL,
    STATE_STOP_WATCH,
    STATE_BUTTON_COUNT
} mode_ctrl_state_t;


/* -- Variables with module-wide scope
 * ------------------------------------------------------------------------- */

static queue_t mode_control_queue;

/* current state of the FSM */
static mode_ctrl_state_t state = STATE_EGG_TIMER;


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

static void mode_control_enqueue_buttons(uint32_t action);


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/**
 * See header file
 */
void mode_control_init(void)
{
    buttons_register_observer(mode_control_enqueue_buttons);
    
    // call button_count_init();
    /// STUDENTS: To be programmed




    /// END: To be programmed
    
    /* Register initial callback function */
    seg7_register_get_output_callback(egg_timer_get_output);
    lcd_register_get_output_callback(et_ctrl_update_display);
    et_ctrl_put_queue(ETC_DISPLAY_UPDATE_EVENT);
}

/*
 * See header file
 */
void mode_control_handle_event(void)
{
    uint32_t event;

    event = queue_dequeue(&mode_control_queue);

    switch (state) {
        case STATE_EGG_TIMER:
            switch (event) {
                case T0_PRESSED:
                    /// STUDENTS: To be programmed




                    /// END: To be programmed
                    break;
                
                case T1_PRESSED:
                    state = STATE_EGG_TIMER;
                    et_ctrl_put_queue(ETC_BUTTON_EVENT);
                    break;
                
                default:
                    ;// no change
            }
            break;
        
        /// STUDENTS: To be programmed    




        /// END: To be programmed
            
        default:
            ;// no change
    }
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/**
 *  \brief  Call-back function in case a button has been pressed
 */
static void mode_control_enqueue_buttons(uint32_t action)
{
    queue_enqueue(&mode_control_queue, action);
}
