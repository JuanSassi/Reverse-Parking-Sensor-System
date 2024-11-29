/****************************************************************************
 * Project: Reverse Parking Sensor System
 * File:    moduleDAC.h
 * Author:  Juan Ignacio Sassi
 * Date:    29/11/2024
 * Description:
 *    This project implements a proximity sensor to assist when reversing a car. The system is developed 
 *    on the LPC1769 (Rev C) board and uses multiple modules and peripherals to ensure efficient control 
 *    and monitoring, providing real-time interaction with the user.
 *
 * This file is part of a project developed for the course Digital Electronics III at FCEFYN, 
 * National University of Córdoba (UNC). 
 * All rights reserved.
 ****************************************************************************/
#ifndef MODULE_DAC_H
#define MODULE_DAC_H

#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"
#include "moduleSystick.h"

/** @defgroup DAC and DMA configuration
 *  Constants and definitions related to DAC and DMA configuration.
 *
 */
#define DMA_SIZE       60 /**< DMA transfer size in samples */
#define NUM_SAMPLES    4  /**< Total samples for full wave */
#define WAVE_FREQUENCY 60 /**< Sine wave frequency: 60 Hz */
#define CLOCK_DAC_MHZ  25 /**< DAC clock frequency: 25 MHz (CCLK divided by 4) */

/**
 * @brief Values ​​for DAC per DMA.
 *
 */
extern volatile uint32_t dac_value[NUM_SAMPLES];

/**
 * @brief Values ​​for dac by DMA if reverse_flag = TRUE.
 *
 */
extern volatile uint32_t dac_value1[NUM_SAMPLES];

/**
 * @brief Values ​​for the dac by DMA if reverse_flag = FALSE.
 *
 */
extern volatile uint32_t dac_value2[NUM_SAMPLES];

#define CHANNEL_DMA_DAC 0 /**< DMA channel used for the DAC */

/**
 * @brief Set the DAC to generate a periodic wave.
 *
 * Initializes the DAC and sets its refresh interval based on the desired wave frequency.
 */
void configure_dac(void);

/**
 * @brief Set the DMA to transfer data to the DAC.
 *
 * Configures the DMA to perform continuous transfers from a data table
 * containing wave samples to the DAC register.
 *
 * @param table Pointer to the wave sample table.
 */
void configure_dma_for_dac(volatile uint32_t* table);

/**
 * @brief Updates the data to be converted by the DAC.
 *
 */
void update_dac(void);

#endif