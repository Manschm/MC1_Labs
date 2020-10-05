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




/// END: To be programmed

/* internal variable definitions ------------------------------------------- */

static const int key_array [4][4] = { { 0x1, 0x2, 0x3, 0xF },
                                      { 0x4, 0x5, 0x6, 0xE },
                                      { 0x7, 0x8, 0x9, 0xD },
                                      { 0xA, 0x0, 0xB, 0xC } };


/* public function definitions --------------------------------------------- */
                                      
/*
 * See header file
 */
uint8_t scan_keypad_cbc(void)
{
    uint8_t ret_val = NOKEY_PRESSED;
    /// STUDENTS: To be programmed




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




    /// END: To be programmed
    return ret_val;
}

/* internal functions definitions ------------------------------------------ */
/// STUDENTS: To be programmed




/// END: To be programmed

