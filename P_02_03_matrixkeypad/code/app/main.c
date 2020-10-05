/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Project     : MC1 Lab Matrix-Keypad
 * -- Description : This code handles the reading of a 4x4
 * --               matrix-keypad (0..F)
 * --				The value of the pressed key will be displayed
 * --				on a 8-digit 7-segment-display.
 * --				For more information see description of the internship.
 * --
 * -- $Id: main.c 1539 2018-09-20 06:17:18Z kjaz $
 * ------------------------------------------------------------------------- */


#include <stdint.h>
#include "hal_gpio.h"
//#include "hal_rcc.h"
#include "keypad.h"
#include "display.h"
#include "inout.h"

#define DEBOUNCE_NR      50

typedef enum { MODE_HW_TEST = 0,
               MODE_NR_SEQUENCE = 1,
               MODE_COL_BY_COL = 2,
               MODE_FAST_SCAN = 3,
} t_keypad_output_conf;

/* ----------------------------------------------------------------------------
 * Main
 * ------------------------------------------------------------------------- */
int32_t main(void)
{
    uint8_t mode = 0;
    uint8_t prev_mode = 0;
    /// STUDENTS: To be programmed




    /// END: To be programmed

    /* enable clock on GPIOA and GPIOB */
    GPIOA_ENABLE();
    GPIOB_ENABLE();

    disp_init();
    inout_init_io();


    while (1) {
        mode = inout_switch_read();
        if (mode != prev_mode) {    // mode changed
            prev_mode = mode;
            disp_clear_buffer();
            disp_update();
            inout_led_write(mode);
        }
 
        /* Depending on the selected mode, display the following information
           on the 7-segment display:
        
           MODE_HW_TEST         --> All segments on
           MODE_NR_SEQUENCE     --> display 01234567
           MODE_COL_BY_COL      --> Read and display one key using Col by Col
                                    method. The new digit is shifted in from 
                                    the right.
           MODE_FAST_SCAN       --> Read and display one key using fast scan
                                    method. The new digit is shifted in from 
                                    the right.
         */
        /// STUDENTS: To be programmed        




        /// END: To be programmed        
    }

}
