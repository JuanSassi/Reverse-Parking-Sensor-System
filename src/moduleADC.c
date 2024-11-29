#include "moduleADC.h"

/**
 * @brief Set the timer and its match.
 *
 * This function initializes the TIMER0 timer with a 100 µs prescaler and sets the match register
 * to generate an interrupt every 60 seconds.
 *
 */
void configure_timer_and_match(void)
{
    TIM_TIMERCFG_Type timer_cfg_struct; /**< Structure to store timer settings. */

    timer_cfg_struct.PrescaleOption = TIM_PRESCALE_USVAL; /**< Prescaler in microseconds. */
    timer_cfg_struct.PrescaleValue = 100;                 /**< Prescaler value, time resolution ~100 µs. */

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer_cfg_struct); /**< Initialize timer TIMER0. */

    TIM_MATCHCFG_Type match_cfg_struct; /**< Structure to store match configuration. */

    match_cfg_struct.MatchChannel = 0;                          /**< Matching channel 0. */
    match_cfg_struct.IntOnMatch = ENABLE;                       /**< Enable break on match. */
    match_cfg_struct.StopOnMatch = DISABLE;                     /**< Does not stop timer on match. */
    match_cfg_struct.ResetOnMatch = ENABLE;                     /**< Reset timer on match. */
    match_cfg_struct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; /**< No external match output. */
    match_cfg_struct.MatchValue = (uint32_t)(SECOND);           /**< Match value for 1 second. */

    TIM_ConfigMatch(LPC_TIM0, &match_cfg_struct); /**< Set up the match. */
}

/**
 * @brief Start the timer.
 *
 * Activate timer TIMER0 and enable its interruption.
 */
void start_timer(void)
{
    TIM_Cmd(LPC_TIM0, ENABLE);   /**< Enable the timer. */
    NVIC_EnableIRQ(TIMER0_IRQn); /**< Enable interrupt for TIMER0. */
}

/**
 * @brief Set the ADC to perform periodic conversions.
 *
 * Initializes the ADC with a sample rate of 100 kHz and enables ADC channel 0 with interrupt.
 */
void configure_adc(void)
{
    ADC_Init(LPC_ADC, ADC_FREQ);                    /**< 100 kHz frequency. */
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE); /**< Activate channel 0. */
    ADC_BurstCmd(LPC_ADC, DISABLE);                 /**< Disable burst mode. */
    ADC_IntConfig(LPC_ADC, ADC_CHANNEL_0, ENABLE);  /**< Interruption on channel 0. */
    NVIC_EnableIRQ(ADC_IRQn);                       /**< Enable ADC Interrupt. */
}

/**
 * @brief Interrupt handler for TIMER0.
 *
 * This function is executed when an interrupt occurs at TIMER0.
 * Clears the interrupt flag and begins a conversion in the ADC.
 */
void TIMER0_IRQHandler(void)
{
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); /**< Clear the interrupt flag. */
    ADC_StartCmd(LPC_ADC, ADC_START_NOW);       /**< Start ADC conversion. */
}

/**
 * @brief Interrupt handler for the ADC.
 *
 * This function is executed when a conversion is completed in the ADC.
 * Reads the conversion value and calls the @ref continue_reverse function.
 */
void ADC_IRQHandler(void)
{
    NVIC_DisableIRQ(ADC_IRQn);                                   /**< Temporarily disables ADC interrupt. */
    adc_read_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0); /**< Read the ADC conversion value. */
    continue_reverse();       /**< Control the reverse flag depending on the adc value */
    NVIC_EnableIRQ(ADC_IRQn); /**< Enable ADC interrupt again. */
}

/**
 * @brief Control the reverse flag depending on the adc value.
 *
 * This function evaluates the value of `adc_read_value` and adjusts
 * `reverse_flag` based on whether it meets the allowed limits.
 */
void continue_reverse(void)
{
    if (adc_read_value < MAX_VALUE_ALLOWED)
    {
        reverse_flag = TRUE;
    }
    else
    {
        reverse_flag = FALSE;
    }
}