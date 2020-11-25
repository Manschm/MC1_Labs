/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/** 
 *  \brief  Implementation of module button_count.
 * 
 *  $Id: button_count.c 1064 2016-11-18 06:12:26Z feur $
 * ------------------------------------------------------------------------- */
 

/* User includes */
#include "button_count.h"
#include "queue.h"
#include "lcd.h"
#include "reg_ctboard.h"

/* -- Macros
 * ------------------------------------------------------------------------- */

//                           "                    "
#define TEXT_LINE_1         ("BUTTONS       0>MODE")
#define TEXT_LINE_2_T0      ("              1>T0  ")
#define TEXT_LINE_2_T1      ("              1>T1  ")
#define TEXT_LINE_2_T2      ("              1>T2  ")
#define TEXT_LINE_2_T3      ("              1>T3  ")

/// STUDENTS: To be programmed

/* -- Local type definitions
 * ------------------------------------------------------------------------- */

/* enumerate the states */
typedef enum {
    T0,
    T1,
    T2,
	T3
} button_count_state_t;


/* -- Variables with module-wide scope
 * ------------------------------------------------------------------------- */

/* event queue for this FSM */
static queue_t button_count_queue;

/* current state of the FSM */
static button_count_state_t state = T0;

// Counts the buttons
static uint16_t button_counts[4] = {0};

/* -- Local function declarations
 * ------------------------------------------------------------------------- */

static void button_counter(uint32_t button) {
	switch(button) {
		case 0x1: button_counts[0]++; break;
		case 0x2: button_counts[1]++; break;
		case 0x3: button_counts[2]++; break;
		case 0x4: button_counts[3]++; break;
	}
}

/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/**
 *  see header file
 */
void button_count_init(void) {
	buttons_register_observer(button_counter);
}


/**
 *  see header file
 */
void button_count_get_output(seg7_output_t *output) {
	uint16_t output_value = (button_counts[state] & 0x0FFF);
	uint16_t temp = output_value;
	uint16_t result = 0;
	uint8_t i;
	
	for (i = 0; i < 3; i++) {
		result += (temp % 10) << (4 * i);
		temp /= 10;
	}
	
	result |= state << 12u;
	
	output->value = result;
    output->dots = (0x1 << 3u);     // Set dot on DS3
}


/**
 *  see header file
 */
void button_count_put_queue(button_count_events_t event)
{
    queue_enqueue(&button_count_queue, event);
}


/*
 *  See header file
 */
void button_count_handle_event(void)
{
    uint32_t event;

    event = queue_dequeue(&button_count_queue);

    switch (state) {
        case T0:
            switch (event) {
                case BCC_BUTTON_T1_EVENT:
                    state = T1;
                    break;

                default:
                    ;// no change
            }
            break;

        case T1:
            switch (event) {
                case BCC_BUTTON_T1_EVENT:
                    state = T2;
                    break;

                default:
                    ;// no change
            }
            break;

        case T2:
            switch (event) {
                case BCC_BUTTON_T1_EVENT:
                    state = T3;
                    break;

                default:
                    ;// no change
            }
            break;
			
		case T3:
            switch (event) {
                case BCC_BUTTON_T1_EVENT:
                    state = T0;
                    break;

                default:
                    ;// no change
            }
            break;
        default:
            ;// no change
    }
	
    /* Update outputs */
    if (event != BCC_NO_EVENT) {
        seg7_output_update();   
        lcd_output_update();        
    }
}


/*
 *  See header file
 */
void button_count_update_display(void)
{
    lcd_write(LCD_LINE_1, TEXT_LINE_1);
    
    switch (state) {
        case T0:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_T0);
            break;
		
		case T1:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_T1);
            break;
		
		case T2:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_T2);
            break;
		
		case T3:
            lcd_write(LCD_LINE_2, TEXT_LINE_2_T3);
            break;
    }
}

/// END: To be programmed
