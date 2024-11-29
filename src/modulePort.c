#include "modulePort.h"

/**
 * @file modulePort.c
 * @brief Implementation of GPIO pin and port configuration.
 * This file contains the logic to initialize and configure the system's GPIO pins and ports.
 * The functionality of the pins is configured for various peripherals such as external interrupts,
 * LEDs, UART, ADC and DAC.
 *
 */

/**
 * @brief Configure system pins.
 *
 * Configure the GPIO pins necessary for various peripherals, including:
 * - External switch (EINT0)
 * - LEDs (green y red)
 * - UART (TX y RX)
 * - ADC (Analog to Digital Conversion Input)
 * - DAC (Digital to Analog Conversion Output)
 *
 * Configure the pins with the corresponding functions, as well as resistance modes (pull-up, pull-down, etc.)
 * and input/output addresses.
 *
 */
void configure_port(void)
{
    PINSEL_CFG_Type pin_cfg;
    // Pin configuration for EINT0 (External Interrupt 0)
    pin_cfg.Portnum = PINSEL_PORT_2;           /**< Port where the pin is configured */
    pin_cfg.Pinnum = PINSEL_PIN_10;            /**< EINT0 pin */
    pin_cfg.Funcnum = PINSEL_FUNC_1;           /**< Alternative function 1 for EINT0 */
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN; /**< Pull-down resistance */
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL; /**< Normal mode */
    PINSEL_ConfigPin(&pin_cfg);                /**< Set the pin based on the provided settings */

    // Pin configuration for LEDs (green and red)
    pin_cfg.Portnum = PINSEL_PORT_0;                   /**< Port where the pin is configured */
    pin_cfg.Pinnum = PINSEL_PIN_4;                     /**< Green LED pin */
    pin_cfg.Funcnum = PINSEL_FUNC_0;                   /**< GPIO function */
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN;         /**< Pull-down resistance */
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;         /**< Normal mode */
    PINSEL_ConfigPin(&pin_cfg);                        /**< Set the configuration for green LED pin */
    pin_cfg.Pinnum = PINSEL_PIN_5;                     /**< Red LED pin */
    PINSEL_ConfigPin(&pin_cfg);                        /**< Set the configuration for red LED pin */
    GPIO_SetDir(PINSEL_PORT_0, GREEN_LED_PIN, OUTPUT); /**< Set the green LED pin as output */
    GPIO_SetDir(PINSEL_PORT_0, RED_LED_PIN, OUTPUT);   /**< Set the red LED pin as output */

    // UART0 TX pin configuration (P0.2)
    pin_cfg.Pinnum = PINSEL_PIN_2;             /**< UART TX pin */
    pin_cfg.Funcnum = PINSEL_FUNC_1;           /**< UART TX function */
    pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE; /**< Tristate mode */
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL; /**< Normal mode */
    PINSEL_ConfigPin(&pin_cfg);                /**< Set the configuration for UART TX pin */

    // UART0 RX pin configuration (P0.3)
    pin_cfg.Pinnum = PINSEL_PIN_3;   /**< UART RX pin */
    pin_cfg.Funcnum = PINSEL_FUNC_1; /**< UART RX function */
    PINSEL_ConfigPin(&pin_cfg);      /**< Set the configuration for UART RX */

    // ADC pin configuration (P0.23)
    pin_cfg.Pinnum = PINSEL_PIN_23;  /**< ADC pin */
    pin_cfg.Funcnum = PINSEL_FUNC_1; /**< ADC function */
    PINSEL_ConfigPin(&pin_cfg);      /**< Set the configuration for ADC */

    // DAC pin configuration (P0.26)
    pin_cfg.Pinnum = PINSEL_PIN_26;  /**< DAC pin */
    pin_cfg.Funcnum = PINSEL_FUNC_2; /**< DAC function */
    PINSEL_ConfigPin(&pin_cfg);      /**< Set the configuration for DAC */
}