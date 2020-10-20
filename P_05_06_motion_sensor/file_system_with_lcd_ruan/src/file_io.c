/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Project     : MC1 lab - Motion sensor
 * -- Description : This module handles the io operations on the file
 * --               system. It creates files on the SD card and writes
 * --               the data to it and reads from it.
 * --
 * -- $Revision: 2067 $
 * -- $Id: file_io.c 2067 2020-10-05 11:23:44Z ruan $
 * --------------------------------------------------------------- */

#include "file_io.h"
#include "ff.h"
#include "ff_gen_drv.h" // FATFS_LinkDriver
#include "sd_diskio.h"  // defines SD_Driver as external */
#include <string.h>
#include <stdio.h>

static char SDPath[4];   /* SD logical drive path */
static FATFS SDFatFS;    /* File system object for SD logical drive */
static const char avg_path[] = "average_values.csv\0";
static const char raw_path[] = "raw_values.csv\0";

/**
 * see header file
 */
void MX_FATFS_Init(void)
{
    /* Link the SD driver */
    //retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
    FATFS_LinkDriver(&SD_Driver, SDPath);
}

/**
 * see header file
 */
FILE_IO_STATUS file_io_register_filesystem(void)
{
    /* Exercise 4.1: Register filesystem object to the fatfs module */
    /* Use the predefined module-wide variables SDFatFS and SDPath */
    /// STUDENTS: To be programmed




    /// END: To be programmed
    /* End of Exercise 4.1 */
}

/**
 * see header file
 */
FILE_IO_STATUS file_io_unregister_filesystem(void)
{
    /* Exercise 4.1: Unregister filesystem object to the fatfs module */
    /// STUDENTS: To be programmed




    /// END: To be programmed
    /* End of Exercise 4.1 */
}

/**
 * see header file
 */
FILE_IO_STATUS file_io_create(FILE_IO_FILE_TYPE type)
{
    /* Exercise 4.2: Create file object and write header */
    
    /* Use the following steps
     *      - f_open() with predefined paths -->  error handling
     *      - write header to file with f_write() --> error handling
     *      - close file with f_close()  --> error handling
     */
    
    /// STUDENTS: To be programmed




    /// END: To be programmed
    /* End of Exercise 4.2 */
}

/**
 * see header file
 */
FILE_IO_STATUS file_io_write_avg_to_sd_card(int16_t *acceleration)
{
    /* Exercise 4.3: Write average acceleration */
    
    /* Use the following steps (all with appropriate error handling)
     *      - open file
     *      - append line to file containing average acceleration
     *      - close file
     */
    
    /// STUDENTS: To be programmed




    /// END: To be programmed
    /* End of Exercise 4.3 */
}

/**
 * see header file
 */
FILE_IO_STATUS file_io_write_raw_to_sd_card(int16_t *acceleration,
                                            uint16_t nr_of_samples)
{
    /* Exercise 4.4: Write raw acceleration*/
    
    /* Use the following steps (all with appropriate error handling)
     *      - open file
     *      - a for loop (based on nr_of_samples) appending lines with the raw
     *        acceleration values to the file
     *      - close file
     */
    
    /// STUDENTS: To be programmed




    /// END: To be programmed
    /* End of Exercise 4.4 */
}
