#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /* The cr_section_macros is specific to the MCUXpresso delivered toolchain */
#endif

#ifndef MODULE_EINT_H
#define MODULE_EINT_H

#include "lpc17xx_dac.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_timer.h"
#include "modulePort.h"
#include <stddef.h>
#include <stdint.h>

extern volatile uint8_t habilitar;

/**
 * @brief Set the external interrupt to EINT0.
 *
 * This function initializes and enables the external interrupt (EINT0) on the LPC1769, 
 * setting the necessary parameters to activate an interrupt when the state of the specified pin changes. 
 * EINT0 is typically used to handle external events such as button presses.
 *
 * @param None
 */
void configure_external_interrupt(void);

/**
 * @brief External interrupt handler for EINT0.
 *
 * This function handles the EINT0 interrupt when it is activated. Contains the code to handle the 
 * response to the external event associated with EINT0. In the handler, actions such as toggling an 
 * LED or starting a process in response to the external signal can be implemented.
 *
 * @param None
 */
void EINT0_IRQHandler(void);

#endif // MODULE_EINT_H
