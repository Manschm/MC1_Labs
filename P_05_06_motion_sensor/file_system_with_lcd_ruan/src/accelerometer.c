/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Project     : MC1 lab - Motion Sensor
 * -- Description : This modul handles the commands of the Accelerometer
 *                  of the Type LSM6DSL. The access to the peripherals is
 *                  executed trough the file hal_acc.h
 * -- $Revision: 2067 $
 * -- $Id: accelerometer.c 2067 2020-10-05 11:23:44Z ruan $
 * --------------------------------------------------------------- */

/* includes ----------------------------------------------------------------- */
#include <stdint.h>
#include "accelerometer.h"
#include "spi.h"
#include "error.h"
#include "lsm6dsl_reg.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_dma.h"  // double include
#include "stm32f4xx_hal_gpio.h" // double include

/* -- defines-----------------------------------------------------------------*/
/* DMA defines */
#define NR_TRANSACTIONS_SINGLE   7
#define NR_TRANSACTIONS_FIFO     601

/* Correction factors for accelerometer */
#define         X_OFFSET 0
#define         Y_OFFSET 0
#define         Z_OFFSET 0

#define MAX_INTEGER_VAL  32767
#define MAX_G_FORCE      4000

/* -- module-local variables definitions -------------------------------------*/
static uint8_t tx_buffer[NR_TRANSACTIONS_FIFO]; // Transmit buffer for SPI
static uint8_t rx_buffer[NR_TRANSACTIONS_FIFO]; // Receive buffer for SPI

/* -- local function declarations --------------------------------------------*/
static void init_continous(void);
static void init_fifo(void);

static ACC_STATUS dma_read_write(uint16_t length, uint8_t *hal_tx_buffer, 
                           uint8_t *hal_rx_buffer);

static void calculate_gvalue_fifo(int16_t *result, uint8_t *raw_values);
static void calculate_gvalue(int16_t *result, uint8_t *raw_values);

static void write_reg(uint8_t address, uint8_t value);
static void wait_100_us(void);

/*
 * See header file
 */
void accelerometer_init(mode_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    
    /* Configure PE15 as input for External Interrupt from sensor */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    /* Enable EXTI15_10 interrupt using functions HAL_NVIC_SetPriority() and
     *  HAL_NVIC_EnableIRQ()
     *  Set priority level to '0' and subpriority level to '1'
     */
    /// STUDENTS: To be programmed
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    /// END: To be programmed    
    
    /* reset sensor */
    write_reg(CTRL3_C_ADD, 0x01);       // activate reset
    wait_100_us();
    
    // MOTION SENSOR I
    /* Sensor configuration independent of mode
     * according to datasheet                      
     * Program values of control registers from CTRL2_G through CTRL10_G to 
     * default values, except for
     *    - enable automatic register address
     *    - I2C disabled, SPI only enabled
     *
     * At the end:
     * Configure 208 Hz output data rate (ODR) and a full-scale of +/- 4g
     */
    
    /// STUDENTS: To be programmed




    /// END: To be programmed
    
    /* sensor configuration dependent on mode */
    
    switch (mode) {
        case SPI_SINGLE: case SPI_DMA:
            init_continous();
            break;

        case SPI_SINGLE_LSM_FIFO: case SPI_DMA_LSM_FIFO:
            init_fifo();
            break;

        default:
            break;
    }
}

/*
 * See header file
 */
uint16_t accelerometer_read_acceleration(int16_t *acceleration, mode_t mode)
{
    uint16_t nr_of_samples = 0;
    SPI_STATUS spi_status;
    ACC_STATUS acc_status;

    switch (mode) {
        case SPI_SINGLE:
            
            /* Read the acceleration output registers in x,y,z using automatic
             * register increment.
             *  - set tx_buffer[0] to address of low byte of x-axis
             *  - call hal_acc_spi_read_write() using tx_buffer and rx_buffer
             *    using NR_TRANSACTIONS_SINGLE as length
             *    I.e. address plus 3 times 2 bytes
             *  - call calculate_gvalue() with the raw values in rx_buffer and
             *    the result stored in the memory area indicated by pointer 
             *    acceleration.
             *  - set return value in length
             */
            /// STUDENTS: To be programmed




            /// END: To be programmed
            break;
        
        case SPI_DMA:
            
            /* The same as for case SPI_SINGLE but replace the call to
             * hal_acc_spi_read_write() by dma_read_write()
             */            
            /// STUDENTS: To be programmed




            /// END: To be programmed
            break;
        
        case SPI_SINGLE_LSM_FIFO:

            /* The same as for case SPI_SINGLE but with a different number of
             * transactions (here we use NR_TRANSACTIONS_FIFO)
             * Call calculate_gvalue_fifo() instead of calculate_gvalue()
             */          
            /// STUDENTS: To be programmed




            /// END: To be programmed
            break;
       
        case SPI_DMA_LSM_FIFO:
            /// STUDENTS: To be programmed




            /// END: To be programmed
            break;
        
        default: 
            break;
    }    
    
    return nr_of_samples;
}

/*
 * See header file
 */
uint8_t accelerometer_who_am_i(void)
{
    // MOTION SENSOR I
    /* See lecture slide on how to implement a read access to sensor 
       Use function hal_acc_spi_read_write() from module spi
     */
    /// STUDENTS: To be programmed
	tx_buffer[0] = WHO_AM_I_ADD | 0x80;	// WHO_AM_I register and read
	tx_buffer[1] = 0;
	
	hal_acc_spi_read_write(2, tx_buffer, rx_buffer);
	
	return rx_buffer[1];
    /// END: To be programmed
}

/**
 * \brief Initialize the sensor with continuous-mode
 */
static void init_continous(void)
{
    /* interrupt on INT1 if data ready */
    // MOTION SENSOR I
    /// STUDENTS: To be programmed
	// Enable accelerometer data ready on INT1
	write_reg(INT1_CTRL_ADD, (0x1 << 0));
	
	// Set accelerometer data rate to 104 Hz
	write_reg(CTRL1_XL_ADD, (0x4 << 4));
	
	// Set ODR to 104 Hz and select conitnuous mode with overwrite
	write_reg(FIFO_CTRL5_ADD, (0x4 << 3) | 0x6);	
    /// END: To be programmed
}

/**
 * \brief Initialize the Sensor with FIFO-mode
 */
static void init_fifo(void)
{
    /* configure sensor registers for FIFO 
     *  - Nr. of data (FTH) -> 0x12C = 300 samples --> 100 samples with 3 values
     *                                                 of 2 bytes each
     *  - Accelerometer in FIFO, No decimation
     *  - Gyro Data not in FIFO
     *  - FIFO ODR 208 Hz
     *  - STOP_ON_FTH: FIFO depth is not limited
     *  - FIFO mode: Stop when FIFO full
     *  - Interrupt on INT1: FIFO Threshold
     */
    // MOTION SENSOR II
    /// STUDENTS: To be programmed




    /// END: To be programmed
}

/**
 * \brief calculate the FIFO values into accelerations
 * \param result: pointer to array with acceleration values in mg.
 * \param raw_values: pointer to array with raw-values of acceleration.
                      contains alternately high- and low-register values.
 */
static void calculate_gvalue_fifo(int16_t *result, uint8_t *raw_values)
{
    uint16_t i;

    for (i = 0; i < NR_TRANSACTIONS_FIFO; i = i + 3) {
        calculate_gvalue(result + i, raw_values + (1 + (2 * i)));
    }
}

/**
 * \brief calculate the continous values into accelerations
 * \param result: pointer to array with acceleration values in mg.
 * \param raw_values: pointer to array with raw-values of acceleration.
                      contains alternately high- and low-register values.
 */
static void calculate_gvalue(int16_t *result, uint8_t *raw_values)
{
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;

    /* connect two uint8 to int16 */
    x = (int16_t)((raw_values[1] << 8) + raw_values[0]);
    y = (int16_t)((raw_values[3] << 8) + raw_values[2]);
    z = (int16_t)((raw_values[5] << 8) + raw_values[4]);

    /* calculate acceleration in mg */
    result[0] = (x * MAX_G_FORCE / MAX_INTEGER_VAL) + X_OFFSET;
    result[1] = (y * MAX_G_FORCE / MAX_INTEGER_VAL) + Y_OFFSET;
    result[2] = (z * MAX_G_FORCE / MAX_INTEGER_VAL) + Z_OFFSET;
}

/**
 *  \brief  Writes LSM6DSL register
 */
static void write_reg(uint8_t address, uint8_t value)
{
    /// STUDENTS: To be programmed
	tx_buffer[0] = address;
	tx_buffer[1] = value;
	
	hal_acc_spi_read_write(2, tx_buffer, rx_buffer);
    /// END: To be programmed
}

/**
 * \brief Generate a delay
 */
static void wait_100_us(void)
{
    uint16_t counter = 0;
    while (counter < 1600) {
        counter++;
    }
}

/**
 * \brief setup SPI TX and RX DMA, start a transfer and poll until transfer is
 *        complete
 * \param length: the number of bytes to be transmitted/received
 * \param hal_tx_buffer: pointer to an array with the byte sequence to be sent
 * \param hal_rx_buffer: pointer to an array where the received bytes will be 
 *                       stored
 * \return accelerometer status code
 */
static ACC_STATUS dma_read_write(uint16_t length, uint8_t *hal_tx_buffer, 
                           uint8_t *hal_rx_buffer)
{   
    /* Implement the following steps
     *      - Enable DMA Clock
     *      - Configure and initialize DMA for SPI TX
     *      - Configure and initialize DMA for SPI RX
     *      - Set SS pin low
     *      - Start SPI TX DMA
     *      - Start SPI RX DMA
     *      - Generate SPI DMA requests
     *      - Poll for transfer on SPI TX DMA
     *      - Poll for transfer on SPI TX DMA
     *      - Set SS pin high
     */
    /// STUDENTS: To be programmed




    /// END: To be programmed
}
