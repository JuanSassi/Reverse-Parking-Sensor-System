#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#ifdef __USE_MCUEXPRESSO
#include <cr_section_macros.h> /* MCUXpresso toolchain-specific macros */
#endif

#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_uart.h"
#include <string.h>

#include "moduleADC.h"
#include "moduleDAC.h"
#include "moduleEINT.h"
#include "modulePort.h"
#include "moduleSystick.h"
#include "moduleUART.h"

/**
 * @brief Main function of the system.
 * Configure the peripherals and enter an infinite loop using DMA and low power.
 */
int main(void)
{
    SystemInit(); /*!< Initialize the system clock */

    configure_port(); /*!< Configure the board pins */

    configure_adc();             /*!< Configure the ADC */
    configure_timer_and_match(); /*!< Configure Timer0 and its matches */
    start_timer();               /*!< Start Timer0 */

    configure_systick();    /*!< Set the SysTick timer */
    SYSTICK_IntCmd(ENABLE); /*!< Enable SysTick interrupt */
    SYSTICK_Cmd(ENABLE);    /*!< Enable the SysTick counter */

    configure_external_interrupt(); /*!< Configure external interrupt */
    NVIC_EnableIRQ(EINT0_IRQn);     /*!< Enable interrupt EINT0 */

    configure_dac();                           /*!< Set up the DAC */
    configure_dma_for_dac(dac_value);          /*!< Configure the DMA for continuous wave output */
    GPDMA_ChannelCmd(CHANNEL_DMA_DAC, ENABLE); /*!< Enable the DMA channel for the DAC */

    conf_UART();          /*!< Configure UART communication over DMA */
    configure_dac_uart(); /*!< Configure DMA for UART */

    NVIC_SetPriority(EINT0_IRQn, 0);   /*!< Set priority for interrupt EINT0 */
    NVIC_SetPriority(TIMER0_IRQn, 1);  /*!< Set priority for Timer0 interrupt */
    NVIC_SetPriority(ADC_IRQn, 2);     /*!< Set priority for ADC interrupt */
    NVIC_SetPriority(SysTick_IRQn, 3); /*!< Set priority for SysTick interrupt */

    /**
     * @brief Infinite loop.
     * The system operates using DMA and enters low power mode while waiting for interruptions.
     */
    while (TRUE)
    {
        __WFI(); /*!< Wait for an interruption (reduce energy consumption) */
    }

    return 0;
}