/****************************************************************************
 * Project: Reverse Parking Sensor System
 * File:    moduleEINT.c
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
#include "moduleEINT.h"

/**
 * @file moduleEINT.c
 * @brief Implementing configuration and handling external interrupts.
 *
 * This file contains the functions necessary to initialize and handle the external interrupt EINT0.
 */

// Global variables for system enablement and control
volatile uint8_t habilitar = 1; ///< Indicates whether the system is enabled (1) or disabled (0).

/**
 * @brief Configure external interrupt EINT0.
 *
 * This function initializes the external interrupt EINT0, configuring it to trigger on the falling edge or when active
 * on low.
 */
void configure_external_interrupt(void)
{
    EXTI_InitTypeDef exti_cfg;                     /**< Configuration structure for external interrupt */
    exti_cfg.EXTI_Line = EXTI_EINT0;               /**< External interrupt line EINT0 */
    exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE; /**< Edge sensitivity mode */
    exti_cfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE; /**< Rising edge polarity */
    EXTI_Config(&exti_cfg); /**< Configure the external interrupt with the specified parameters */

    // Enable interrupt on the NVIC
    NVIC_EnableIRQ(EINT0_IRQn);
}

/**
 * @brief External interrupt handler EINT0.
 *
 * Toggles between enabling and disabling the system when the interrupt is triggered.
 * It also controls the status of the LEDs and the DAC.
 */

void EINT0_IRQHandler(void)
{
    EXTI_ClearEXTIFlag(EXTI_EINT0);
    if (habilitar == TRUE)
    {
        habilitar = FALSE;
        SYSTICK_IntCmd(DISABLE);
        GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN);
        GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN);
        DAC_UpdateValue(LPC_DAC, 0);
    }
    else
    {
        habilitar = TRUE;
        SYSTICK_IntCmd(ENABLE);
    }
}