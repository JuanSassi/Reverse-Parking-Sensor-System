/****************************************************************************
 * Project: Reverse Parking Sensor System
 * File:    moduleSystick.h
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
#ifndef SYSTICK_H
#define SYSTICK_H

#include "lpc17xx_dac.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_systick.h"
#include "moduleDAC.h"
#include "modulePort.h"
#include "moduleUART.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @file moduleSystick.h
 * @brief Header file for the configuration and management of SysTick.
 *
 * This module provides functionality to configure and manage the SysTick timer to perform periodic
 * tasks such as changing the state of the LEDs.
 */

/** SysTick period in milliseconds */
#define SYSTICK_TIME 50

/** Maximum value for green LED counter */
#define MAX_GREEN_LED_COUNTER 10

/** Maximum value for red LED counter */
#define MAX_RED_LED_COUNTER 10

/** Maximum amount of toggle */
#define MAX_TOGGLE 1

/** GPIO pin definitions */
#define GREEN_LED_PIN ((uint32_t)(1 << 4))

/** GPIO pin definitions */
#define RED_LED_PIN ((uint32_t)(1 << 5))

/** SysTick global variables */
extern volatile uint16_t red_led_counter;   ///< Counter for changing the red LED
extern volatile uint16_t green_led_counter; ///< Green LED change counter
extern volatile uint8_t toggle;             ///< Toggle state variable
extern volatile uint8_t reverse_flag;       ///< Reverse mode flag

/**
 * @brief Set the SysTick timer.
 *
 * This function initializes the SysTick timer with the specified period and enables its interrupts.
 */
void configure_systick(void);

/**
 * @brief SysTick Interrupt Handler.
 *
 * Handles periodic tasks, such as changing the state of LEDs.
 * Clear SysTick interrupt flag on completion.
 */
void SysTick_Handler(void);

/**
 * @brief Change the state of the green LED.
 *
 * This function changes the state of the green LED, alternating between on and off based on the toggle counter.
 */
void green_led(void);

/**
 * @brief Change the state of the red LED.
 *
 * This feature changes the state of the red LED, alternating between on and off based on the toggle counter.
 */
void red_led(void);

#endif // SYSTICK_H
