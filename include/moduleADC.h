#ifndef MODULEADC_H
#define MODULEADC_H

#include "lpc17xx_adc.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_timer.h"
#include "moduleDAC.h"
#include "moduleSystick.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @file moduleADC.h
 * @brief Configuring and managing the ADC for the system.
 *
 * This module configures the ADC (Analog-Digital Converter) and its interaction with a timer 
 * to perform periodic readings.
 */

/**
 * @defgroup ADC module constants
 * @brief Constants and definitions related to ADC configuration.
 * 
 */
#define SECOND                     10000  ///< Number of cycles for one second in the timer.
#define ADC_FREQ                   100000 ///< ADC sampling rate in Hz.
#define MAX_VALUE_ALLOWED          2048   ///< Maximum value allowed in the ADC for system logic.
#define NUM_SAMPLES                4      ///< Number of samples used in the table.

/// Last value read from ADC.
extern volatile uint32_t adc_read_value;

/**
 * @brief Set the timer and matching system for the ADC.
 *
 * Initializes the timer that controls the ADC sample rate.
 */
void configure_timer_and_match(void);

/**
 * @brief Start ADC timer.
 *
 * Activates the timer that generates the signals for the ADC conversions.
 */
void start_timer(void);

/**
 * @brief Configure the system ADC.
 *
 * Initializes the ADC with the settings necessary to convert on a specific channel.
 * 
 */
void configure_adc(void);

/**
 * @brief Timer interrupt handler (TIMER0).
 *
 * Starts an ADC conversion when the timer generates an interrupt.
 */
void TIMER0_IRQHandler(void);

/**
 * @brief ADC Interrupt Handler.
 *
 * Processes the data converted by the ADC and updates the system status.
 */
void ADC_IRQHandler(void);

/**
 * @brief System status management based on ADC value continues.
 *
 * Determines whether the system should operate in normal or reverse mode based on the ADC value read.
 * 
 */
void continue_reverse(void);

#endif // MODULEADC_H
