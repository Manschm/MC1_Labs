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
	
	if (f_mount(&SDFatFS, SDPath, 1)) {
		return FILE_IO_MOUNT_ERROR;	// Non 0 returns are errors
	} else {
		return FILE_IO_OK;
	}
	
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
	
	if (f_mount(0, SDPath, 0)) {
		return FILE_IO_MOUNT_ERROR;	// Non 0 returns are errors
	} else {
		return FILE_IO_OK;
	}
	
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
	
	FIL fil;        	// File object
    FRESULT fr;     	// FatFs return code
	UINT bw;			// File write count
	char header_avg[] = "Average Sample Nr.;Acceleration X;Acceleration Y;Acceleration Z";
	char header_raw[] = "Raw Sample Nr.;Acceleration X;Acceleration Y;Acceleration Z";
	
	// Open/Create file and set write mode
	if (type == FILE_IO_AVERAGE) {
		if (f_open(&fil, avg_path, FA_WRITE | FA_CREATE_ALWAYS) != FR_OK) {
			return FILE_IO_OPEN_ERROR;
		}
	} else {
		if (f_open(&fil, raw_path, FA_WRITE | FA_CREATE_ALWAYS) != FR_OK) {
			return FILE_IO_OPEN_ERROR;
		}
	}
	
	// Write header
	if (type == FILE_IO_AVERAGE) {
		if (f_write(&fil, header_avg, strlen(header_avg), &bw) != FR_OK){
			return FILE_IO_WRITE_ERROR;
		}
	} else {
		if (f_write(&fil, header_raw, strlen(header_raw), &bw) != FR_OK){
			return FILE_IO_WRITE_ERROR;
		}
	}
	
	// Close file
	if (f_close(&fil) != FR_OK){
		return FILE_IO_CLOSE_ERROR;
	}
	
	return FILE_IO_OK;
	
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
	
	FIL fil;        	// File object
    FRESULT fr;     	// FatFs return code
	UINT bw;			// File write count
	static uint32_t sample_count = 1;	// Sample number
	char buffer[100];	// String buffer
	uint16_t buf_len;	// Effective string length
	
	// Open file and set write mode
	if (f_open(&fil, avg_path, FA_WRITE | FA_OPEN_APPEND) != FR_OK) {
		return FILE_IO_OPEN_ERROR;
	}
	
	// Fill buffer
	buf_len = snprintf(buffer, 100, "\n%u;%d;%d;%d", sample_count,
													acceleration[0],
													acceleration[1],
													acceleration[2]);
	sample_count++;

	// Write data
	if (f_write(&fil, buffer, buf_len, &bw) != FR_OK){
		return FILE_IO_WRITE_ERROR;
	}
	
	// Close file
	if (f_close(&fil) != FR_OK){
		return FILE_IO_CLOSE_ERROR;
	}
	
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
	
	FIL fil;        	// File object
    FRESULT fr;     	// FatFs return code
	UINT bw;			// File write count
	static uint32_t sample_count = 1;	// Sample number
	char buffer[100];	// String buffer
	uint16_t buf_len;	// Effective string length
	uint16_t i;			// Loop variable
	
	// Open file and set write mode
	if (f_open(&fil, raw_path, FA_WRITE | FA_OPEN_APPEND) != FR_OK) {
		return FILE_IO_OPEN_ERROR;
	}
	
	for (i = 0; i < nr_of_samples; i++) {
	// Fill buffer
		buf_len = snprintf(buffer, 100, "\n%u;%d;%d;%d", sample_count,
													acceleration[3 * i],
													acceleration[3 * i + 1],
													acceleration[3 * i + 2]);
		sample_count++;

		// Write data
		if (f_write(&fil, buffer, buf_len, &bw) != FR_OK){
			return FILE_IO_WRITE_ERROR;
		}
	}
	
	// Close file
	if (f_close(&fil) != FR_OK){
		return FILE_IO_CLOSE_ERROR;
	}
	
    /// END: To be programmed
    /* End of Exercise 4.4 */
}
