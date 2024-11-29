#ifndef MODULEUART_H
#define MODULEUART_H

#include "lpc17xx_uart.h"
#include "moduleEINT.h"
#include "moduleSystick.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * @file moduleUART.h
 * @brief Configuration and functions for UART communication.
 *
 * This module allows you to configure and manage UART communication, 
 * as well as send system-specific data and notifications..
 */

/**
 * @def COMMUNICATION_SPEED
 * @brief Defines the communication speed for UART.
 * 
 * This macro sets the UART communication speed to 9600 baud.
 */
#define COMMUNICATION_SPEED 9600

/**
 * @def UART_BUFFER_SIZE
 * @brief Defines the size of the UART buffer.
 * 
 * This macro sets the size of the buffer used for UART communication to 10 characters.
 */
#define UART_BUFFER_SIZE 10

/**
 * @def DMA_SIZE
 * @brief Defines the DMA transfer size.
 * 
 * This macro specifies the number of samples to be transferred in each DMA operation.
 */
#define DMA_SIZE 60 /**< DMA transfer size in samples */


/** 
 * @brief Holds the latest ADC conversion result.
 * 
 * This variable is updated by the ADC interrupt or DMA process. 
 * It is declared as volatile to prevent compiler optimizations, 
 * ensuring that its value is always read from memory.
 */
extern volatile uint32_t adc_read_value;

/** 
 * @brief Pointer to a volatile 8-bit unsigned data buffer.
 * 
 * This pointer may be used for accessing or transferring data 
 * in memory-mapped peripherals or other volatile contexts.
 */
volatile uint8_t* data;

/** 
 * @brief Character buffer for storing up to 100 characters.
 * 
 * Declared as volatile to handle asynchronous modifications, 
 * such as updates in an interrupt routine.
 */
volatile char buffer[100];

/**
 * @brief Configure the UART.
 *
 * Initialize the UART with default settings.
 */
void conf_UART(void);

/**
 * @brief Sends the ADC value via UART.
 *
 * @return Buffer with the information to be transmitted.
 */
uint32_t send_adc_value(void);

/**
 * @brief Send the status of the LEDs via UART.
 *
 * Informs if the system is in reverse or normal mode.
 * @return Buffer with the information to be transmitted.
 */
uint32_t send_status_leds(void);

/**
 * @brief Notify switch status via UART.
 *
 * Indicates whether the switch is enabled or disabled.
 * @return Buffer with the information to be transmitted.
 */
uint32_t notify_interruption_status(void);

/**
 * @brief Sends the general status of the system via UART.
 *
 * Provides information about the current operating mode.
 * @return Buffer with the information to be transmitted.
 */
uint32_t send_system_status(void);

/* Declaring array of function pointers */
uint32_t (*table_uart[4])(void) = {
    (uint32_t (*)(void))send_adc_value,  // Conversion to proper pointer
    send_status_leds,
    notify_interruption_status,
    send_system_status
};

#endif // MODULEUART_H
