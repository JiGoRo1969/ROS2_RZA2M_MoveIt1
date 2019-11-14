/*******************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized. This
 * software is owned by Renesas Electronics Corporation and is protected under
 * all applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 * LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
 * ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
 * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software
 * and to discontinue the availability of this software. By using this software,
 * you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 * Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
 ******************************************************************************/
/*******************************************************************************
 * @headerfile     r_rza2_scifa_lld_api.h
 * @brief          SCIFA low level driver interface header
 * @version        1.00
 * @date           15.05.2018
 * H/W Platform    RZ/A2M
 *******************************************************************************/
/*******************************************************************************
 * History       : DD.MM.YYYY Version Description
 *               : 
 *******************************************************************************/

#ifndef R_SCIFA_INC_R_RZA2_SCIFA_LLD_API_H_
    #define R_SCIFA_INC_R_RZA2_SCIFA_LLD_API_H_
/*********************************************************************//**
 * @ingroup RENESAS_DRIVER_LIBRARY
 * @defgroup R_SCIFA_LLD_API_78 SCIFA RZA2 EBK_RZA2M Low Level Driver
 *
 * @section R_SCIFA_LLD_API_78_SUMMARY Summary
 * 
 * This SCIFA Low Level Driver is developed for the RZA2M EBK_RZA2M board.
 * 
 * The driver depends upon the common SSGSTARC-77 High Level Driver for SCIFA.
 *
 * This is a device and board specific component of an SCIFA driver, 
 * configured for the RZA2M EBK_RZA2M board. This interface is not intended to be
 * used directly without the associated High Level Driver.
 * 
 * @section R_SCIFA_LLD_API_78_INSTANCES Known Implementations:
 * This driver is used in the RZA2M Software Package.
 * @see TODO_PackageReference
 *
 * @section R_SCIFA_LLD_API_78_SEE_ALSO See Also:
 * @see RENESAS_SC_CFG Renesas Smart Configuration Settings
 * @see R_SCIFA_HLD_API_77 RZA2M SCIFA High Level Driver API
 * @see RENESAS_OS_ABSTRACTION  Renesas OS Abstraction interface
 * @{
 ************************************************************************/

/*******************************************************************************
 Includes
 *******************************************************************************/
    #include "driver.h"
    #include "r_scifa_drv_api.h"

/*******************************************************************************
 Macro definitions
 *******************************************************************************/

/** Version Number of API. */
    #define STDIO_SCIFA_RZ_LLD_DRV_NAME ("LLD EBK_RZA2M SCIFA")
/** Major Version Number of API. */
    #define STDIO_SCIFA_RZ_LLD_VERSION_MAJOR      (1)
/** Minor Version Number of API. */
    #define STDIO_SCIFA_RZ_LLD_VERSION_MINOR      (3)
/** Minor Version Number of API. */
    #define STDIO_SCIFA_RZ_LLD_BUILD_NUM          (0)
/** Unique ID. */
    #define STDIO_SCIFA_RZ_LLD_UID                (78)

/******************************************************************************
Typedef definitions
******************************************************************************/

/**
 * @typedef st_scifa_rx_error_t struct to hold RX error counts.
 */
typedef struct
{
    uint32_t cnt_overrun;  /*!< Counter for FIFO overruns */
    uint32_t cnt_framing;  /*!< Counter for data framing errors */
    uint32_t cnt_parity;   /*!< Counter for data parity errors */
    uint32_t cnt_break;    /*!< Counter for received breaks */
} st_scifa_rx_error_t;

/******************************************************************************
 Function Prototypes
 ******************************************************************************/
/* ==== Functional Methods ==== */

/**
 * @brief R_SCIFA_GetChannel Converts SC table index into SCIFA channel
 *
 * This function interrogates SC table to determine which
 * channel is described by sc_config
 *
 * @param[in] sc_config Configuration ID.
 *
 * @retval  =>0: Corresponding SCIFA channel
 * @retval  -1 DRV_ERROR
 */
int_t  R_SCIFA_GetChannel (int_t sc_config);

/**
 * @brief R_SCIFA_Init initialises a channel for set-up
 *
 * This function configures device registers in preparation for
 * configuration.
 *
 * @param[in] channel Channel to initialise.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t  R_SCIFA_Init (int_t channel);

/**
 * @brief R_SCIFA_StartTXI Starts TXI interrupt for a given channel.
 *
 * @param[in] channel Channel to start TXI for.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t  R_SCIFA_Start (int_t channel, int_t read_write);

/**
 * @brief Stops channel operation.
 * @param[in] channel  channel to stop.
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t  R_SCIFA_Stop (int_t channel);

/**
 * @brief R_SCIFA_PutByte puts a byte in a channels FIFO.
 *
 * This function will put a single byte into the FIFO of the
 * channel given.
 *
 * @param[in] channel Channel to put byte in FIFO.
 *
 * @param[in] data Byte to place in FIFO.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t  R_SCIFA_PutByte (int_t channel, uint8_t data);

/**
 * @brief R_SCIFA_GetByte get's 1 byte from a channels FIFO.
 *
 * This function retrieves a single byte from a channel's
 * transmit FIFO.
 *
 * @param[in] channel Channel to retrieve byte from FIFO.
 *
 * @param[out] p_data Location to place retrieved byte.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t  R_SCIFA_GetByte (int_t channel, uint8_t *p_data);

/**
 * @brief R_SCIFA_Close is to be called when closing a channel.
 *
 * This function is currently stubbed, in case a developer may wish
 * to implement it in a future driver update.
 *
 * @param[in] channel Channel to Close.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_Close (int_t channel);

/* ==== TXI Methods ==== */

/**
 * @brief R_SCIFA_GetTXIState Determines the current TXI state for a channel.

 * This function will determine whether a channel has recently triggered
 * a TXI interrupt event.
 *
 * @param[in] channel  Channel to check TXI status for.
 *
 * @retval  N Where N is the transmit interrupt state: 0 or 1 (interrupting).
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_GetTXIState (int_t channel);

/**
 * @brief R_SCIFA_ClearTXIFlags removes TXI flags on a channel
 *
 * This function is called at the end of an TXI handler routine
 * it will clear necessary TXI flag to mark TXI as handled.
 *
 * @param[in] channel Channel to clear TXI flags for.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_ClearTXIFlags (int_t channel);

/**
 * @brief R_SCIFA_StartTXI Starts TXI interrupt for a given channel.
 *
 * @param[in] channel Channel to start TXI for.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StartTXI (int_t channel);

/**
 * @brief R_SCIFA_StopTXI stops TXI for a given channel.
 *
 * @param[in] channel Channel to disable TXI for.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StopTXI (int_t channel);

/**
 * @brief R_SCIFA_IsTxFifoFull Checks for space in the TX FIFO.
 *
 * This function checks the current amount of bytes in the TX FIFO
 * it will then return 0 if space in the FIFO, 1 if it's full.
 *
 * @param[in] channel Channel to check TX FIFO for.
 *
 * @param[out] p_fifo_full 0 if space in the FIFO, 1 if it's full.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_IsTxFifoFull (int_t channel, int_t *p_fifo_full);

/**
  * @brief R_SCIFA_StopTransmit stops transmission at the end of a DMA transmit
  *
  * @param[in] channel Channel to stop
  *
  * @retval  0 DRV_SUCCESS
  * @retval -1 DRV_ERROR
  */
int_t R_SCIFA_StopTransmit (int_t channel);

/**
 * @brief R_SCIFA_GetTXEIState Determines the current TXEI state for a channel
 *
 * This function will determine whether a channel has recently triggered
 * a TXEI interrupt event.
 *
 * @param[in] channel  Channel to check TXEI status for
 *
 * @retval  N Where N is the transmit end interrupt state: 0 or 1 (interrupting)
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_GetTXEIState (int_t channel);

/* ==== RXI Methods ==== */

/**
 * @brief R_SCIFA_GetRXIState Determines the current RXI state for a channel.
 *
 * This function will determine whether a channel has recently triggered
 * a RXI interrupt event.
 *
 * @param[in] channel Channel to check RXI state for.
 *
 * @retval  N Where N is the Receive interrupt state: 0 or 1 (interrupting).
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_GetRXIState (int_t channel);

/**
 * @brief R_SCIFA_ClearRXIFlags removes RXI flags on a channel
 *
 * This function is called at the end of an RXI handler routine
 * it will clear necessary RXI flag to mark RXI as handled.
 *
 * @param[in] channel Channel to clear RXI flags for.
 *
 * @retval  0  DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_ClearRXIFlags (int_t channel);

/**
 * @brief R_SCIFA_CheckRXIError Determines error status of Receipt channel.
 *
 * This function will determine whether a channel has recently experienced
 * any overflow/parity/framing errors when receiving data.
 * It returns this information in a error data structure.
 *
 * @param[in] channel Channel to check RXI error status for.
 *
 * @param[out] p_rx_err Error info struct to populate with any error details.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_CheckRXIError (int_t channel, st_scifa_rx_error_t *p_rx_err);

/**
 * @brief R_SCIFA_IsRxFifoEmpty checks if RX FIFO is empty.
 *
 * This function checks the current amount of bytes in the RX FIFO
 * it will then return 0 if data is in the FIFO, or 1 if it's empty.
 *
 * @param[in] channel Channel to check FIFO.
 *
 * @param[out] p_fifo_empty 0 if data in the FIFO, 1 if it's empty.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_IsRxFifoEmpty (int_t channel, int_t *p_fifo_empty);

/* ==== Set-up configuration Methods ==== */

/**
 * @brief R_SICFA_SetTransmissionMode sets the transmission mode for a channel
 *
 * This function configures the channel parity to a setting
 * specified in e_scifa_mode_t.
 *
 * @param[in] channel Channel to set transmission mode for.
 * @param[in] desired_mode The desired transmission mode for the channel
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SICFA_SetTransmissionMode (int_t channel, scifa_sync_mode_t desired_mode);

/**
 * @brief Sets the device baud rate within 1% of value desired.
 *
 * This function determines the best possible settings for the
 * baud rate registers for the specified peripheral clock speed
 * and baud rate. Note that this does not guarantee a low bit
 * error rate, just the best possible one. The bit rate error is
 * returned in .1% increments. If the hardware cannot support
 * the specified combination, DEV_ERROR is returned.
 *
 * NOTE: The transmitter and receiver (TE and RE bits in SCR) must be disabled
 *       prior to calling this function.
 *
 *       The application must pause for 1 bit time after the BRR register
 *       is loaded before transmitting/receiving to allow time for the clock
 *       to settle.
 * @param[in]  channel: Channel number of SCIFA(0-4)
 * @param[in]  desired_baud_rate: Baud rate; 19200, 57600, 115200, etc.
 * @param[in]  clock_freq: Peripheral clock speed; e.g. 24000000 for 24MHz
 * @param[in]  mode: asynchronous or synchronous
 * @param[out] p_achieved_baud_rate - Pointer to achieved Baud rate
 *
 * @retval  0 DRV_SUCCESS - If a Baud rate within 1% of the desired value was
 *                          achieved.
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetBaud (int_t channel, uint32_t desired_baud_rate, uint32_t clock_freq, scifa_sync_mode_t mode, uint32_t *p_achieved_baud_rate);

/**
 * @brief R_SCIFA_SetDataBits sets the number of data bits for a channel
 *
 * This function configures the channel data bits to a value defined in
 * e_scifa_data_bits_t.
 *
 * @param[in] channel Channel to set data bits for.
 *
 * @param[in] desired_data_bits Number of data bits to set for channel.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetDataBits (int_t channel, scifa_size_t desired_data_bits);

/**
 * @brief R_SCIFA_SetStopBits Sets the number of stop bits for a channel
 *
 * This function configures the channel stop bits to a setting
 * specified in e_scifa_stop_bits_t.
 *
 * @param[in] channel Channel to set stop bits for.
 *
 * @param[in] desired_stop_bits Number of Stop bits to set for channel.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetStopBits (int_t channel, scifa_stop_t desired_stop_bits);

/**
 * @brief R_SCIFA_SetParity Sets the channel parity
 *
 * This function configures the channel parity to a setting
 * specified in e_scifa_parity_t.
 *
 * @param[in] channel Channel to configure parity for.
 *
 * @param[in] desired_parity Parity to configure channel with.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetParity (int_t channel, scifa_parity_t desired_parity);

/**
 * @brief R_SCIFA_SetDataOrder Sets the data order for a given channel
 *
 * This function sets the data order for a given channel,
 * this is either MSB or LSB first as defined in e_scifa_data_order_t.
 *
 * @param[in] channel Channel to set data order for.
 *
 * @param[in] desired_data_order Data order setting for channel.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetDataOrder (int_t channel, scifa_dir_t desired_data_order);

/**
 * @brief R_SCIFA_SetLoopBack enables loopback mode on a channel
 *
 * This function enables loopback mode on a channel,
 * loopback, connects TX to RX for a given channel,
 * this can be useful for testing whether a channel is
 * sending/receiving correctly.
 *
 * @param[in] channel Channel to enable loopback for.
 *
 * @param[in] loopback Setting for channel loopback.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetLoopBack (int_t channel, scifa_loop_t loopback);

/**
 * @brief Function to configure the extended SCIFA peripheral settings.
 * @param[in] channel Channel to set the extended settings for.
 * @param[in] p_ext_cfg Extended Config settings.
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetExtendedCfg (int_t channel, const scifa_config_t *p_ext_cfg);

/**
 * @brief Sets the TXD output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetTXDOutput (int_t channel, scifa_sptr_init_t level);

/**
 * @brief Sets the SCK output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetSCKOutput(int_t channel, scifa_sptr_init_t level);

/**
 * @brief Sets the CTS output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetCTSOutput (int_t channel, scifa_sptr_init_t level);

/**
 * @brief Sets the RTS output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetRTSOutput(int_t channel, scifa_sptr_init_t level);

/*==== Extended Config Functions - defined here for LLD test purposes only, not to be used in HLD ====*/
int_t R_SCIFA_SetModemControl(int_t channel, scifa_mce_t modem);
int_t R_SCIFA_SetNoiseCanceller(int_t channel, scifa_nfen_t noise_cancellation);
int_t R_SCIFA_SetClock(int_t channel, scifa_clk_enable_t desired_clock);
int_t R_SCIFA_SetFIFOThreshold(int_t channel, uint8_t tx_trg, uint8_t rx_trg);

int_t R_SCIFA_StartRX (int_t channel);
int_t R_SCIFA_StopRX (int_t channel);
void * R_SCIFA_GetReadDataRegisterAddress (int_t channel);
int_t R_SCIFA_StartTX (int_t channel);
int_t R_SCIFA_StopTX (int_t channel);
void * R_SCIFA_GetWriteDataRegisterAddress (int_t channel);

int_t R_SCIFA_GetVersion(st_ver_info_t *pVerInfo);
#endif /* SRC_RENESAS_AUTOMATED_TEST_R_SCIFA_INC_R_RZA2_SCIFA_LLD_API_H_ */
