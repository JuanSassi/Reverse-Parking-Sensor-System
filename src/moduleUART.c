#include "moduleUART.h"

volatile uint32_t (*table_uart[4])(void) = {(uint32_t(*)(void))send_adc_value, // Conversion to proper pointer
                                            send_status_leds,
                                            notify_interruption_status,
                                            send_system_status};

/**
 * @brief Configure the UART.
 *
 * Initialize the UART with default settings.
 */
void conf_UART(void)
{
    UART_CFG_Type uart_cfg;
    uart_cfg.Baud_rate = COMMUNICATION_SPEED; /*  This is the communication speed value in bits per second.
                                                  For example, if you want a speed of 9600 bps */
    uart_cfg.Parity = UART_PARITY_NONE;
    uart_cfg.Databits = UART_DATABIT_8;
    uart_cfg.Stopbits = UART_STOPBIT_1;
    UART_ConfigStructInit(&uart_cfg);

    UART_IntConfig(LPC_UART0, UART_INTCFG_THRE, ENABLE); /* UART_INTCFG_THRE Enables interrupting when the
 Transmit Holding Register (THR) is empty, indicating that the UART is ready to send new data. */
    UART_Init(LPC_UART0, &uart_cfg);

    UART_FIFO_CFG_Type UARTFIFOConfigStruct;
    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct); // FIFO configuration
    UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);

    UART_TxCmd(LPC_UART0, ENABLE); // Enable streaming
}

/**
 * @brief Configures the DAC and UART for data transfer using DMA.
 *
 * This function initializes the DMA and sets up a linked list item (LLI)
 * for continuous data transfer from a memory table to the UART transmit register.
 * The DMA channel is configured for memory-to-peripheral transfer.
 */
void configure_dac_uart(void)
{
    GPDMA_LLI_Type DMA_LLI_Struct; /**< DMA linked list element for continuous transfer */

    // Configure the DMA linked list for continuous transfer
    DMA_LLI_Struct.SrcAddr = (uint32_t)table_uart;          /**< Source address: wave table */
    DMA_LLI_Struct.DstAddr = (uint32_t) & (LPC_UART0->THR); /**< Destination address: UART transmit register */
    DMA_LLI_Struct.NextLLI = (uint32_t)&DMA_LLI_Struct;     /**< Link to same item for continuous transfer */
    DMA_LLI_Struct.Control = DMA_SIZE                       /**< Transfer size */
                             | (2 << 18)                    /**< Source width: 32 bits */
                             | (2 << 21)                    /**< Destination width: 32 bits */
                             | (1 << 26);                   /**< Increment source address */

    GPDMA_Init(); /**< Initialize the GPDMA controller */

    // DMA channel configuration structure
    GPDMA_Channel_CFG_Type dma_config;
    dma_config.ChannelNum = 2;                        /**< Use DMA channel 2 */
    dma_config.TransferSize = UART_BUFFER_SIZE;       /**< Size of the transfer */
    dma_config.TransferWidth = 0;                     /**< Not applicable for UART transfer */
    dma_config.SrcMemAddr = (uint32_t)table_uart;     /**< Source memory address: wave table */
    dma_config.DstMemAddr = 0;                        /**< Destination is a peripheral (UART) */
    dma_config.TransferType = GPDMA_TRANSFERTYPE_M2P; /**< Memory-to-peripheral transfer */
    dma_config.SrcConn = 0;                           /**< Source is memory */
    dma_config.DstConn = GPDMA_CONN_UART0_Tx;         /**< Destination is UART0 transmit */
    dma_config.DMALLI = 0;                            /**< No linked list */

    GPDMA_Setup(&dma_config);    /**< Configure the DMA channel */
    GPDMA_ChannelCmd(2, ENABLE); /**< Enable DMA channel 2 */
}

/**
 * @brief Sends the ADC value via UART.
 *
 * @return Buffer with the information to be transmitted.
 */
uint32_t send_adc_value(void)
{
    char buffer[100];
    sprintf(buffer, "ADC: %lu\n", adc_read_value);
    return UART_Send(LPC_UART0, (uint8_t*)buffer, strlen((const char*)buffer), BLOCKING);
}

/**
 * @brief Send the status of the LEDs via UART.
 *
 * Informs if the system is in reverse or normal mode.
 * @return Buffer with the information to be transmitted.
 */
uint32_t send_status_leds(void)
{
    char buffer[100];
    sprintf(buffer, "Reverse mode: %s\n", reverse_flag ? "Enable" : "Disabled");
    return UART_Send(LPC_UART0, (uint8_t*)buffer, strlen((const char*)buffer), BLOCKING);
}

/**
 * @brief Notify switch status via UART.
 *
 * Indicates whether the switch is enabled or disabled.
 * @return Buffer with the information to be transmitted.
 */
uint32_t notify_interruption_status(void)
{
    char buffer[100];
    sprintf(buffer, "Switch: %s\n", habilitar ? "Enable" : "Disabled");
    return UART_Send(LPC_UART0, (uint8_t*)buffer, strlen(buffer), BLOCKING);
}

/**
 * @brief Sends the general status of the system via UART.
 *
 * Provides information about the current operating mode.
 * @return Buffer with the information to be transmitted.
 */
uint32_t send_system_status(void)
{
    char buffer[100];
    sprintf(buffer, "System: %s\n", reverse_flag ? "Reverse" : "Moving forward");
    return UART_Send(LPC_UART0, (uint8_t*)buffer, strlen(buffer), BLOCKING);
}
