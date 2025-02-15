/****************************************************************************
 * Project: Reverse Parking Sensor System
 * File:    modulePort.h
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
#ifndef MODULE_PORT_H
#define MODULE_PORT_H

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include <stddef.h>
#include <stdint.h>

#define INPUT  0
#define OUTPUT 1

#define MANUAL_MODO_PIN   ((uint32_t)(1 << 10)) /**< EINT0 on pin 2.10, input - function 1 */
#define MOTION_SENSOR_PIN ((uint32_t)(1 << 23)) /**< ADC on pin 0.23, input - function 1 */
#define GREEN_LED_PIN     ((uint32_t)(1 << 4))  /**< Green LED controlled by Systick, pin 0.4, output - function 0 */
#define RED_LED_PIN       ((uint32_t)(1 << 5))  /**< Red LED controlled by Systick, pin 0.5, output - function 0 */
#define BUZZER_PIN        ((uint32_t)(1 << 26)) /**< DAC for buzzer, pin 0.26, output - function 2 */
#define TX_PIN            ((uint32_t)(1 << 2))  /**< UART transmit pin at 0.2, output - function 1 */
#define RX_PIN            ((uint32_t)(1 << 3))  /**< UART receive pin at 0.3, input - function 1 */

/**
 * @brief Configure the ports necessary for system operation.
 * This function initializes the pins used in the project, setting the address of each pin (input or output)
 * and configuring specific functions according to the needs of the system, such as LEDs, sensors, and UART
 * communication.
 *
 * @param None
 */
void configure_port(void);

#endif
