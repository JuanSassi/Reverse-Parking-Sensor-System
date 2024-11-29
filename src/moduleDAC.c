#include "moduleDAC.h"

volatile uint32_t dac_value[NUM_SAMPLES] = {1000, 700, 400, 0};
volatile uint32_t dac_value1[NUM_SAMPLES] = {1000, 700, 400, 0};
volatile uint32_t dac_value2[NUM_SAMPLES] = {800, 800, 800, 800};

/**
 * @brief Set the DAC.
 *
 * Configures the DAC to operate in counter mode with DMA enabled, using a calculated interval to
 * generate a desired frequency signal.
 */
void configure_dac(void)
{
    DAC_CONVERTER_CFG_Type DAC_Struct; /**< DAC configuration structure */
    uint32_t update_interval;          /**< Update interval between samples */

    // DAC Setup
    DAC_Struct.DBLBUF_ENA = RESET; /**< Disable double buffering */
    DAC_Struct.CNT_ENA = SET;      /**< Enable DAC counter mode (timeout mode) */
    DAC_Struct.DMA_ENA = SET;      /**< Enable DAC DMA mode */
    DAC_Init(LPC_DAC);             /**< Initialize the DAC */

    // Calculate the update interval for the desired wave frequency
    update_interval = (CLOCK_DAC_MHZ * 1000000) / (WAVE_FREQUENCY * NUM_SAMPLES);
    DAC_SetDMATimeOut(LPC_DAC, update_interval); /**< Set the timeout interval between samples */

    // Apply DAC settings
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_Struct);
}

/**
 * @brief Set the DMA to transfer data to the DAC.
 *
 * Configures the DMA to perform continuous transfers from a data table over the DAC channel,
 * using a linked list structure for continuous transfer.
 *
 */
void configure_dma_for_dac(volatile uint32_t* table)
{
    GPDMA_LLI_Type DMA_LLI_Struct; /**< DMA linked list element for continuous transfer */

    // Configure the DMA linked list for continuous transfer
    DMA_LLI_Struct.SrcAddr = (uint32_t)table;              /**< Source address: wave table */
    DMA_LLI_Struct.DstAddr = (uint32_t) & (LPC_DAC->DACR); /**< Destination address: DAC register */
    DMA_LLI_Struct.NextLLI = (uint32_t)&DMA_LLI_Struct;    /**< Link to same item for continuous transfer */
    DMA_LLI_Struct.Control = DMA_SIZE                      /**< Transfer size */
                             | (2 << 18)                   /**< Source width: 32 bits */
                             | (2 << 21)                   /**< Target width: 32 bits */
                             | (1 << 26);                  /**< Increment source address */

    // Initialize the DMA module
    GPDMA_Init();

    GPDMA_Channel_CFG_Type GPDMACfg; /**< DMA channel configuration structure */

    // Configuration of the DMA channel for memory transfer to peripheral
    GPDMACfg.ChannelNum = CHANNEL_DMA_DAC;          /**< Channel 0 */
    GPDMACfg.SrcMemAddr = (uint32_t)table;          /**< Source address: wave table */
    GPDMACfg.DstMemAddr = 0;                        /**< Without destination address in memory (peripheral) */
    GPDMACfg.TransferSize = DMA_SIZE;               /**< Transfer size */
    GPDMACfg.TransferWidth = 0;                     /**< Not used */
    GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P; /**< Memory transfer to peripheral */
    GPDMACfg.SrcConn = 0;                           /**< Source is memory */
    GPDMACfg.DstConn = GPDMA_CONN_DAC;              /**< Destination: DAC connection */
    GPDMACfg.DMALLI = (uint32_t)&DMA_LLI_Struct;    /**< Linked list for continuous transfer */

    // Apply DMA settings
    GPDMA_Setup(&GPDMACfg);
}

/**
 * @brief Updates the data to be converted by the DAC.
 *
 */
void actualizar_dac(volatile uint32_t* dac_value)
{
    if (reverse_flag == TRUE)
    {
        dac_value = dac_value1;
    }
    else
    {
        dac_value = dac_value2;
    }
}