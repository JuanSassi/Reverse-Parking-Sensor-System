/****************************************************************************
 * Project: Reverse Parking Sensor System
 * File:    moduleSystick.c
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
#include "moduleSystick.h"

/**
 * @file moduleSystick.c
 * @brief Implementation of SysTick configuration and management.
 *
 * This file contains the SysTick timer configuration and interrupt handler that performs periodic system tasks.
 */

// Global variables
volatile uint16_t red_led_counter = MAX_RED_LED_COUNTER;     ///< Red LED change counter
volatile uint16_t green_led_counter = MAX_GREEN_LED_COUNTER; ///< Green LED change counter
volatile uint8_t toggle = MAX_TOGGLE;                        ///< Toggle state variable
volatile uint8_t reverse_flag = 1;                           ///< Reverse mode flag (TRUE by default)

/**
 * @brief Set the SysTick timer.
 *
 * Sets the SysTick timer to generate an interrupt at a fixed interval defined by `SYSTICK_TIME`.
 * Enable the timer and its interruptions.
 *
 */
void configure_systick(void)
{
    SYSTICK_InternalInit(SYSTICK_TIME); // Initializes the SysTick with the specified time
    SYSTICK_IntCmd(ENABLE);             // Enable SysTick interrupts
    SYSTICK_Cmd(ENABLE);                // Enable SysTick timer
}

/**
 * @brief SysTick Interrupt Handler.
 *
 * This handler performs the following tasks:
 * - Change the state of the LEDs according to the state of `reverse_flag`.
 * - Reset the SysTick interrupt flag.
 */
void SysTick_Handler(void)
{
    // Toggle LEDs based on reverse_flag status
    if (reverse_flag == TRUE)
    {
        green_led(); // Green LED for reverse mode
    }
    else
    {
        red_led(); // Red LED for reverse mode
    }

    // Clear SysTick flag
    SYSTICK_ClearCounterFlag();
}

/**
 * @brief Change the state of the green LED.
 *
 * This function changes the state of the green LED, alternating between on and off based on the toggle counter.
 */
void green_led(void)
{
    GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN);

    if (green_led_counter > 0)
    {
        green_led_counter--;
    }

    if (green_led_counter == 0)
    {
        if (GPIO_ReadValue(PINSEL_PORT_0) & GREEN_LED_PIN)
        {
            GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN);
        }
        else
        {
            GPIO_SetValue(PINSEL_PORT_0, GREEN_LED_PIN);
        }
        green_led_counter = MAX_GREEN_LED_COUNTER;
        update_dac();
        toggle--;
    }

    if (toggle == 0)
    {
        toggle = MAX_TOGGLE;
    }
}

/**
 * @brief Change the state of the red LED.
 *
 * This feature changes the state of the red LED, alternating between on and off based on the toggle counter.
 */
void red_led(void)
{
    GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN);

    if (red_led_counter > 0)
    {
        red_led_counter--;
    }

    if (red_led_counter == 0)
    {
        if (GPIO_ReadValue(PINSEL_PORT_0) & RED_LED_PIN)
        {
            GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN);
        }
        else
        {
            GPIO_SetValue(PINSEL_PORT_0, RED_LED_PIN);
        }
        red_led_counter = MAX_RED_LED_COUNTER;
        update_dac();
        toggle--;
    }

    if (toggle == 0)
    {
        toggle = MAX_TOGGLE;
    }
}