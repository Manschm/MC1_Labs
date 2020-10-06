/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Project     : CT2 Lab Matrix-Keypad
 * -- Description : Modul handles the reading of the keypad
 * --
 * -- $Id: keypad.c 1539 2018-09-20 06:17:18Z kjaz $
 * ------------------------------------------------------------------------- */

#include "keypad.h"
#include "hal_gpio.h"

/* -- Macros, type definitions and function prototypes
 * --------------------------------------------------------------------------*/
 
/// STUDENTS: To be programmed
#define PAD_PORT   GPIOB
#define ROW_MASK	0xF0
#define COL_MASK	0x0F


/// END: To be programmed

/* internal variable definitions ------------------------------------------- */

static const int key_array [4][4] = { { 0x1, 0x2, 0x3, 0xF },
                                      { 0x4, 0x5, 0x6, 0xE },
                                      { 0x7, 0x8, 0x9, 0xD },
                                      { 0xA, 0x0, 0xB, 0xC } };

void init_poll_mode(void);

/* public function definitions --------------------------------------------- */
                                      
/*
 * See header file
 */
uint8_t scan_keypad_cbc(void)
{
    uint8_t ret_val = NOKEY_PRESSED;
    /// STUDENTS: To be programmed
	uint8_t i, j;				// For loop counter variables
	uint16_t column;				// Current row
	uint8_t pad_data;		// Returned data from row
	
	// Initialize GPIO for polling
	hal_gpio_input_t rows = {
		ROW_MASK,
		HAL_GPIO_PUPD_UP
	};
	
	hal_gpio_output_t columns = {
		COL_MASK,
		HAL_GPIO_PUPD_UP,
		HAL_GPIO_OUT_SPEED_2MHZ,
		HAL_GPIO_OUT_TYPE_PP
	};
	
	hal_gpio_init_input(PAD_PORT, rows);
	hal_gpio_init_output(PAD_PORT, columns);
	
	column = 1;
	for (i=0; i<4; i++) {
		hal_gpio_output_write(PAD_PORT, COL_MASK);
		hal_gpio_output_write(PAD_PORT, ~column);
		
		pad_data = (~hal_gpio_input_read(PAD_PORT) & 0xF0) >> 4;
			
		if (pad_data != 0) {
			for (j = 0; j < 4; j++) {
				if (pad_data & 1) {
					ret_val = key_array[j][i];
					break;
				}
				pad_data >>= 1;
			}
		}
		
		if (ret_val != NOKEY_PRESSED) {
			break;
		}
		
		column <<= 1;
	}


    /// END: To be programmed
    return ret_val;
}

/*
 * See header file
 */
uint8_t scan_keypad_fast(void)
{
    uint8_t ret_val = NOKEY_PRESSED;
    /// STUDENTS: To be programmed
	uint8_t i, j;
	uint8_t data_row;
	uint8_t data_col;
	
	hal_gpio_input_t columnsA = {
		COL_MASK,
		HAL_GPIO_PUPD_UP
	};
	
	hal_gpio_output_t rowsA = {
		ROW_MASK,
		HAL_GPIO_PUPD_UP,
		HAL_GPIO_OUT_SPEED_2MHZ,
		HAL_GPIO_OUT_TYPE_PP
	};
	
	hal_gpio_input_t rowsB = {
		COL_MASK,
		HAL_GPIO_PUPD_UP
	};
	
	hal_gpio_output_t columnsB = {
		ROW_MASK,
		HAL_GPIO_PUPD_UP,
		HAL_GPIO_OUT_SPEED_2MHZ,
		HAL_GPIO_OUT_TYPE_PP
	};
	
	hal_gpio_init_input(PAD_PORT, columnsA);
	hal_gpio_init_output(PAD_PORT, rowsA);
	
	data_col = hal_gpio_input_read(PAD_PORT) & 0xF;
	
	
	hal_gpio_init_input(PAD_PORT, rowsB);
	hal_gpio_init_output(PAD_PORT, columnsB);
															
	data_row = (hal_gpio_input_read(PAD_PORT) & 0xF0) >> 4;
	
	
	for (i=0; i<4; i++) {
		if ((data_col >> i) & 1) {
			for (j=0; j<4; j++) {
				if ((data_row >> j) & 1) {
					ret_val = key_array[i][j];
					break;
				}
			}
			break;
		}
	}

    /// END: To be programmed
    return ret_val;
}

/* internal functions definitions ------------------------------------------ */
/// STUDENTS: To be programmed


/// END: To be programmed

