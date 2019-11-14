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
 *
 * Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
 *******************************************************************************/
/*******************************************************************************
 * @file          r_rza2_scifa_lld.c
 * Device(s)      RZ/A2
 * Tool-Chain     GCC ARM Embedded 5.4 2016q3
 * H/W Platform   RZ/A2
 * @brief         SCIFA low level driver
 *******************************************************************************/
/*******************************************************************************
 * History       DD.MM.YYYY Version Description
 * @date         15.05.2018 1.00
 *******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_typedefs.h"
#include "iodefine.h"
#include "iobitmask.h"
#include "rza_io_regrw.h"              /* Low level register read/write header */

/* Driver Includes */
#include "driver.h"                    /* Device driver header */
#include "r_rza2_scifa_lld.h"          /* Low level Driver Header */
#include "r_rza2_scifa_lld_cfg.h"      /* Low level Driver Configuration Header */
#include "r_scifa_drv_sc_cfg.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/

#define R_PRV_TX_FIFO_LENGTH        (16)
#define R_PRV_RX_FIFO_EMPTY         (0)

#define R_PRV_TX_FIFO_MAX_TRG       (0x0Fu)
#define R_PRV_TX_FIFO_MIN_TRG       (0x00u)
#define R_PRV_RX_FIFO_MAX_TRG       (0x10u)
#define R_PRV_RX_FIFO_MIN_TRG       (0x01u)

/*******************************************************************************
 Typedefs
 *******************************************************************************/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
/**
 * @section st_scifa structure used for register access of SCIFA channels
 */
static volatile struct st_scifa *gsp_scifa[SCIFA_CFG_LLD_NUM_CHANNELS] =
{
    /* SCIFA Channels */
    &SCIFA0, &SCIFA1, &SCIFA2, &SCIFA3, &SCIFA4
};

/*******************************************************************************
 Prototypes
 *******************************************************************************/

/******************************************************************************
 Public Function Definitions
 ******************************************************************************/
 
/**
 * @brief Starts the SCIFA channel allowing reading/writing
 *
 * R_SCIFA_Start starts an SCIFA channel according to the
 * read_write variable, this determines whether Transmit
 * enable and Receive Enable are turned on. Or just one,
 * for read-only or write-only access.
 *
 * @param[in] channel SCIFA channel to be started.
 *
 * @param[in] read_write Read/Write permission setting.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_Start (int_t channel, int_t read_write)
{
    /* check arguments */
    if ((channel > SCIFA_CFG_LLD_NUM_CHANNELS) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    if ((read_write & __SWR) > 0)
    {
        /* Enable transmit */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 1, SCIFA_SCR_TE_SHIFT, SCIFA_SCR_TE);

        /* Disable transmit interrupt */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, SCIFA_SCR_TIE_SHIFT, SCIFA_SCR_TIE);
    }

    if ((read_write & __SRD) > 0)
    {
        /* Enable receive */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 1, SCIFA_SCR_RE_SHIFT, SCIFA_SCR_RE);

        /* Enable receive interrupt */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 1, SCIFA_SCR_RIE_SHIFT, SCIFA_SCR_RIE);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_Start
 ******************************************************************************/

/**
 * @brief Stops SCIFA channel operation
 *
 * R_SCIFA_Stop will turn off the Transmit/Receive enable for a given
 * channel, it also prevents the device from triggering TXI and RXI.
 *
 * @param[in] Channel The channel to stop operation for.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_Stop (int_t channel)
{
    /* check arguments */
    if ((channel > SCIFA_CFG_LLD_NUM_CHANNELS) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Disable transmit interrupt */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, SCIFA_SCR_TIE_SHIFT, SCIFA_SCR_TIE);

    /* Disable transmit */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, SCIFA_SCR_TE_SHIFT, SCIFA_SCR_TE);

    /* Disable receive interrupt */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, SCIFA_SCR_RIE_SHIFT, SCIFA_SCR_RIE);

    /* Disable receive */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, SCIFA_SCR_RE_SHIFT, SCIFA_SCR_RE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_Stop
 ******************************************************************************/


/**
 * @brief R_SCIFA_GetChannel COnverts SC table index into SCIFA channel
 *
 * This function interrogates SC table to determine which
 * channel is described by sc_config
 *
 * @param[in] sc_config Configuration ID.
 *
 * @retval  =>0: Corresponding SCIFA channel
 * @retval  -1 DRV_ERROR
 */
int_t  R_SCIFA_GetChannel (int_t sc_config)
{
    int_t ret = DRV_ERROR;
    int_t sc_table_size = (sizeof(SCIFA_SC_TABLE)) / sizeof(st_r_drv_scifa_sc_config_t);

    /* Perform range check of sc_config to determine if index is available in st_r_drv_scifa_sc_config_t */
    if ((sc_config >= 0) && (sc_config < sc_table_size))
    {
        ret = SCIFA_SC_TABLE[sc_config].channel;
    }

    return (ret);
}
/*******************************************************************************
 End of function R_SCIFA_GetChannel
 ******************************************************************************/


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
int_t R_SCIFA_Init (int_t channel)
{
    /* check arguments */
    if ((channel > SCIFA_CFG_LLD_NUM_CHANNELS) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Set SCR.TE and SCR.RE -> 0 */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* Reset TFRST */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FCR.WORD, (uint16_t) 1, SCIFA_FCR_TFRST_SHIFT, SCIFA_FCR_TFRST);

    /* Reset FRDR */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FCR.WORD, (uint16_t) 1, SCIFA_FCR_RFRST_SHIFT, SCIFA_FCR_RFRST);

    /* Read error flag first*/
    RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* Clear all error flags of FSR */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, (uint16_t) 0, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* Read error flag first */
    RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->LSR.WORD, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* clear error flag of LSR */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->LSR.WORD, (uint16_t) 0, SCIFA_LSR_ORER_SHIFT, SCIFA_LSR_ORER);

    /* set TXD output high */
    R_SCIFA_SetTXDOutput(channel, SCIFA_SPTR_INIT_HIGH);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_Init
 ******************************************************************************/

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
int_t R_SCIFA_SetParity (int_t channel, scifa_parity_t desired_parity)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    switch (desired_parity)
    {
        default:
        {
            /* invalid desired_parity value */
            return (DRV_ERROR);
        }

        case SCIFA_NONE_PARITY:
        {
            /* Parity enable bit */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 0, SCIFA_SMR_PE_SHIFT, SCIFA_SMR_PE);
            break;
        }

        case SCIFA_ODD_PARITY:
        {
            /* Parity enable bit */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 1, SCIFA_SMR_PE_SHIFT, SCIFA_SMR_PE);

            /* Parity mode bit */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 1, SCIFA_SMR_PM_SHIFT, SCIFA_SMR_PM);
            break;
        }

        case SCIFA_EVEN_PARITY:
        {
            /* Parity enable bit */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 1, SCIFA_SMR_PE_SHIFT, SCIFA_SMR_PE);

            /* Parity mode bit */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 0, SCIFA_SMR_PM_SHIFT, SCIFA_SMR_PM);
            break;
        }
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetParity
 ******************************************************************************/

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
int_t R_SICFA_SetTransmissionMode (int_t channel, scifa_sync_mode_t desired_mode)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    switch (desired_mode)
    {
        default:
        {
            /* invalid desired_mode value */
            return (DRV_ERROR);
        }

        case SCIFA_MODE_ASYNC:
        {
            /* Communication mode : Asynchronous */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 0, SCIFA_SMR_CM_SHIFT, SCIFA_SMR_CM);
            break;
        }

        case SCIFA_MODE_SYNC:
        {
            /* Communication mode : Synchronous */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 1, SCIFA_SMR_CM_SHIFT, SCIFA_SMR_CM);
            break;
        }
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SICFA_SetTransmissionMode
 ******************************************************************************/

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
int_t R_SCIFA_SetStopBits (int_t channel, scifa_stop_t desired_stop_bits)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    switch (desired_stop_bits)
    {
        default:
        {
            /* invalid desired_stop_bits value */
            return (DRV_ERROR);
        }

        case SCIFA_STOPBITS_1:
        {
            /* Stop bit length : 1 stop bit */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 0, SCIFA_SMR_STOP_SHIFT, SCIFA_SMR_STOP);
            break;
        }

        case SCIFA_STOPBITS_2:
        {
            /* Stop bit length : 2 stop bits */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 1, SCIFA_SMR_STOP_SHIFT, SCIFA_SMR_STOP);
            break;
        }
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetStopBits
 ******************************************************************************/

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
int_t R_SCIFA_SetDataBits (int_t channel, scifa_size_t desired_data_bits)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    switch (desired_data_bits)
    {
        default:
        {
            /* invalid desired_data_bits value */
            return (DRV_ERROR);
        }

        case SCIFA_DATA_7BIT:
        {
            /* Character length: 7-bit data */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 1, SCIFA_SMR_CHR_SHIFT, SCIFA_SMR_CHR);
            break;
        }

        case SCIFA_DATA_8BIT:
        {
            /* Character length: 8-bit data */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SMR.WORD, (uint16_t) 0, SCIFA_SMR_CHR_SHIFT, SCIFA_SMR_CHR);
            break;
        }
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetDataBits
 ******************************************************************************/

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
int_t R_SCIFA_SetLoopBack (int_t channel, scifa_loop_t loopback)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    switch (loopback)
    {
        default:
        {
            /* invalid loopback value */
            return (DRV_ERROR);
        }

        case SCIFA_LOOPBACK_DISABLE:
        {
            /* Loop back disabled */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FCR.WORD, 0u, SCIFA_FCR_LOOP_SHIFT, SCIFA_FCR_LOOP);
            break;
        }

        case SCIFA_LOOPBACK_ENABLE:
        {
            /* Loop back enabled */
            RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FCR.WORD, 1u, SCIFA_FCR_LOOP_SHIFT, SCIFA_FCR_LOOP);
            break;
        }
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetLoopBack
 ******************************************************************************/

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
int_t R_SCIFA_SetDataOrder (int_t channel, scifa_dir_t desired_data_order)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    switch (desired_data_order)
    {
        default:
        {
            /* invalid desired_data_order value */
            return (DRV_ERROR);
        }

        case SCIFA_LSB_FIRST:
        {
            /* LSB first */
            RZA_IO_RegWrite_8((volatile uint8_t *) &gsp_scifa[channel]->SEMR.BYTE, 0u, SCIFA_SEMR_DIR_SHIFT, SCIFA_SEMR_DIR);
            break;
        }

        case SCIFA_MSB_FIRST:
        {
            /* MSB first */
            RZA_IO_RegWrite_8((volatile uint8_t *) &gsp_scifa[channel]->SEMR.BYTE, 1u, SCIFA_SEMR_DIR_SHIFT, SCIFA_SEMR_DIR);
            break;
        }
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetDataOrder
 ******************************************************************************/

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
int_t R_SCIFA_Close (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_Close
 ******************************************************************************/

/**
 * @brief R_SCIFA_StopTransmit stops transmission at the end of a DMA transmit
 *
 * @param[in] channel Channel to stop
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StopTransmit (int_t channel)
{
    /* check arguments */
    if ((channel > SCIFA_CFG_LLD_NUM_CHANNELS) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Disable transmit interrupt */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, SCIFA_SCR_TIE_SHIFT, SCIFA_SCR_TIE);

    /* Disable transmit */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, (uint16_t) 0, SCIFA_SCR_TE_SHIFT, SCIFA_SCR_TE);

    /* disable transmit end interrupt enable */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 0, SCIFA_SCR_TEIE_SHIFT, SCIFA_SCR_TEIE);

    /* flush the transmit FIFO */
    gsp_scifa[channel]->FCR.BIT.TFRST = 1;
    gsp_scifa[channel]->FCR.BIT.TFRST = 0;

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_StopTransmit
 ******************************************************************************/

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
int_t R_SCIFA_GetTXEIState (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    volatile int_t txend_interrupt_state;

    /* Get transmit end interrupt state */
    txend_interrupt_state = gsp_scifa[channel]->FSR.BIT.TEND;

    return (txend_interrupt_state);
}
/******************************************************************************
 * End of Function R_SCIFA_GetTXEIState
 ******************************************************************************/

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
int_t R_SCIFA_GetTXIState (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    volatile int_t tx_interrupt_state;
    volatile int_t tx_interrupt_enable_state;

    /* Get FIFO empty status */
    tx_interrupt_state = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_TDFE_SHIFT, SCIFA_FSR_TDFE);

    /* Get interrupt enable status */
    tx_interrupt_enable_state = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, SCIFA_SCR_TIE_SHIFT, SCIFA_SCR_TIE);

    return (tx_interrupt_state && tx_interrupt_enable_state);
}
/******************************************************************************
 * End of Function R_SCIFA_GetTXIState
 ******************************************************************************/

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
int_t R_SCIFA_ClearTXIFlags (int_t channel)
{
    int_t dummy;

    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Dummy read */
    dummy = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_TDFE_SHIFT, SCIFA_FSR_TDFE);

    /* The TDFE flag can only be reset after a 1 is read from it */
    if (1 == dummy)
    {
        /* Reset the TDFE flag */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, 0, SCIFA_FSR_TDFE_SHIFT, SCIFA_FSR_TDFE);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_ClearTXIFlags
 ******************************************************************************/

/**
 * @brief R_SCIFA_CheckRXIError Determines error status of the receive channel.
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
int_t R_SCIFA_CheckRXIError(int_t channel, st_scifa_rx_error_t *p_rx_err)
{
    int_t ret = DRV_SUCCESS;
    int_t framing_errors;
    int_t parity_errors;
    bool_t framing_errors_present;
    bool_t parity_errors_present;

    /* read the ER flag; this tells us if there were any framing or parity errors */
    if (1 == RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_ER_SHIFT, SCIFA_FSR_ER))
    {
        /* read the FER flag for framing errors */
        framing_errors_present = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_FER_SHIFT, SCIFA_FSR_FER);

        /* read the PER flag for parity errors */
        parity_errors_present = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_PER_SHIFT, SCIFA_FSR_PER);

        /* if there were any framing errors, then get the framing error count and update our total */
        if (framing_errors_present)
        {
            /* count framing errors */
            framing_errors = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->LSR.WORD, SCIFA_LSR_FER_SHIFT, SCIFA_LSR_FER);

            /* 0 actually means that there were 16 framing errors */
            if (0 == framing_errors)
            {
                framing_errors = 16;
            }

            p_rx_err->cnt_framing += (uint32_t) framing_errors;
        }

        /* if there were any parity errors, then get the parity error count and update our total */
        if (parity_errors_present)
        {
            /* count parity errors */
            parity_errors = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->LSR.WORD, SCIFA_LSR_PER_SHIFT, SCIFA_LSR_PER);

            /* 0 actually means that there were 16 parity errors */
            if (0 == parity_errors)
            {
                parity_errors = 16;
            }

            p_rx_err->cnt_parity += (uint32_t) parity_errors;
        }

        /* clear the ER flag */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, 0, SCIFA_FSR_ER_SHIFT, SCIFA_FSR_ER);
    }

    /* Count break errors */
    if (1 == RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_BRK_SHIFT, SCIFA_FSR_BRK))
    {
        p_rx_err->cnt_break++;
    }

    /* Count overrun errors */
    if (1 == RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->LSR.WORD, SCIFA_LSR_ORER_SHIFT, SCIFA_LSR_ORER))
    {
        p_rx_err->cnt_overrun++;

        /* clear the overrun flag */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->LSR.WORD, 0, SCIFA_LSR_ORER_SHIFT, SCIFA_LSR_ORER);
    }

    /* Is data ready? */
    if (1 == RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_DR_SHIFT, SCIFA_FSR_DR))
    {
        ret = DRV_ERROR;
    }

    return (ret);
}
/******************************************************************************
 * End of Function R_SCIFA_CheckRXIError
 ******************************************************************************/

/**
 * @brief R_SCIFA_GetRXIState Determines the current RXI state for a channel.
 *
 * This function will determine whether a channel has recently triggered
 * a RXI interrupt event.
 *
 * @param[in] channel Channel to check RXI state for.
 *
 * @retval  N Where N is the receive interrupt state: 0 or 1 (interrupting).
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_GetRXIState (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    volatile int_t rx_interrupt_state; // RDF
    volatile int_t rx_enable_state;    // RE
    volatile int_t rx_interrupt_enable_state; // RIE

    /* Get FIFO full status */
    rx_interrupt_state = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_RDF_SHIFT, SCIFA_FSR_RDF);

    /* Get receive enable status */
    rx_enable_state = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, SCIFA_SCR_RE_SHIFT, SCIFA_SCR_RE);

    /* Get interrupt enable status */
    rx_interrupt_enable_state = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, SCIFA_SCR_RIE_SHIFT, SCIFA_SCR_RIE);

    return (rx_interrupt_state && rx_enable_state && rx_interrupt_enable_state);
}
/******************************************************************************
 * End of Function R_SCIFA_GetRXIState
 ******************************************************************************/

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
int_t R_SCIFA_ClearRXIFlags (int_t channel)
{
    uint16_t dummy;

    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Clear receive data ready */
    dummy = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, SCIFA_FSR_DR_SHIFT, SCIFA_FSR_DR);


    if (1 == dummy)
    {
        /* Clear DR only if 1 read */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FSR.WORD, 0, SCIFA_FSR_DR_SHIFT, SCIFA_FSR_DR);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_ClearRXIFlags
 ******************************************************************************/

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
int_t R_SCIFA_IsRxFifoEmpty(int_t channel, int_t *p_fifo_empty)
{
    int_t fifo_bytes;

    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* get the number of bytes in the FIFO */
    fifo_bytes = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FDR.WORD, SCIFA_FDR_R_SHIFT, SCIFA_FDR_R);

    if (R_PRV_RX_FIFO_EMPTY == fifo_bytes)
    {
        *p_fifo_empty = 1;
    }
    else
    {
        *p_fifo_empty = 0;
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_IsRxFifoEmpty
 ******************************************************************************/

/**
 * @brief R_SCIFA_StopTXI stops TXI for a given channel.
 *
 * @param[in] channel Channel to disable TXI for.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StopTXI (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* disable transmit interrupt enable */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 0, SCIFA_SCR_TIE_SHIFT, SCIFA_SCR_TIE);

    /* disable transmit end interrupt enable */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 0, SCIFA_SCR_TEIE_SHIFT, SCIFA_SCR_TEIE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_StopTXI
 ******************************************************************************/

/**
 * @brief R_SCIFA_StartRX enable receive and receive interrupts
 *
 * @param[in] channel to start receive
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StartRX (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* receive enable */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 1, SCIFA_SCR_RE_SHIFT, SCIFA_SCR_RE);

    /* enable interrupts to trigger DMA */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 1, SCIFA_SCR_RIE_SHIFT, SCIFA_SCR_RIE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_StartRX
 ******************************************************************************/

/**
 * @brief R_SCIFA_StopRX disable receive
 *
 * @param[in] channel to stop receive
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StopRX (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 0, SCIFA_SCR_RE_SHIFT, SCIFA_SCR_RE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_StopRX
 ******************************************************************************/

/**
 * @brief R_SCIFA_GetReadDataRegisterAddress return the read data register address
 *
 * @param[in] channel to get the FRDR register address for
 *
 * @retval the address of the FRDR register
 * @retval NULL error
 */
void * R_SCIFA_GetReadDataRegisterAddress (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (NULL);
    }

    return (void *) &gsp_scifa[channel]->FRDR.BYTE;
}
/******************************************************************************
 * End of Function R_SCIFA_GetReadDataRegisterAddress
 ******************************************************************************/

/**
 * @brief R_SCIFA_StartTX enable transmit and transmit interrupts
 *
 * @param[in] channel to start transmit
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StartTX (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 1, SCIFA_SCR_TE_SHIFT, SCIFA_SCR_TE);

    /* enable interrupts to trigger DMA */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 1, SCIFA_SCR_TIE_SHIFT, SCIFA_SCR_TIE);

    /* enable transmit end interrupt */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 1, SCIFA_SCR_TEIE_SHIFT, SCIFA_SCR_TEIE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_StartTX
 ******************************************************************************/

/**
 * @brief R_SCIFA_StopTX disable transmit
 *
 * @param[in] channel to stop transmit
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StopTX (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 0, SCIFA_SCR_TE_SHIFT, SCIFA_SCR_TE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_StopTX
 ******************************************************************************/

/**
 * @brief R_SCIFA_GetWriteDataRegisterAddress return the read data register address
 *
 * @param[in] channel to get the FTDR register address for
 *
 * @retval the address of the FTDR register
 * @retval NULL error
 */
void * R_SCIFA_GetWriteDataRegisterAddress (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (NULL);
    }

    return (void *) &gsp_scifa[channel]->FTDR.BYTE;
}
/******************************************************************************
 * End of Function R_SCIFA_GetWriteDataRegisterAddress
 ******************************************************************************/

/**
 * @brief R_SCIFA_StartTXI Starts TXI interrupt for a given channel.
 *
 * @param[in] channel Channel to start TXI for.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_StartTXI (int_t channel)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* enable transmit interrupt enable */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, 1, SCIFA_SCR_TIE_SHIFT, SCIFA_SCR_TIE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_StartTXI
 ******************************************************************************/

/**
 * @brief R_SCIFA_PutByte puts a byte in a channel's FIFO.
 *
 * This function will put a single byte into the FIFO of the
 * channel given.
 *
 * @param[in] channel Channel to put byte in FIFO.
 *
 * @param[in] data byte to place in FIFO.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_PutByte (int_t channel, uint8_t data)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Put byte in FIFO */
    RZA_IO_RegWrite_8((volatile uint8_t *) &gsp_scifa[channel]->FTDR.BYTE, data, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_PutByte
 ******************************************************************************/

 /**
  * @brief R_SCIFA_GetByte gets 1 byte from a channel's FIFO.
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
int_t R_SCIFA_GetByte (int_t channel, uint8_t *p_data)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* get byte from FIFO */
    *p_data = RZA_IO_RegRead_8((volatile uint8_t *) &gsp_scifa[channel]->FRDR.BYTE, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_GetByte
 ******************************************************************************/

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
int_t R_SCIFA_IsTxFifoFull(int_t channel, int_t *p_fifo_full)
{
    int_t fifo_bytes;

    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* get the number of bytes in the FIFO */
    fifo_bytes = RZA_IO_RegRead_16((volatile uint16_t *) &gsp_scifa[channel]->FDR.WORD, SCIFA_FDR_T_SHIFT, SCIFA_FDR_T);

    if (R_PRV_TX_FIFO_LENGTH == fifo_bytes)
    {
        *p_fifo_full = 1;
    }
    else
    {
        *p_fifo_full = 0;
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_IsTxFifoFull
 ******************************************************************************/

/**
 * @brief R_SCIFA_SetExtendedCfg sets extended device settings.
 *
 * This function sets the extended device settings defined in
 * st_scifa_extended_t struct, these settings are usually device
 * specific or not considered commonly used.
 *
 * @param[in] channel Channel to set extended settings for
 *
 * @param[in] p_ext_cfg Extended Settings to be set.
 *
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetExtendedCfg(int_t channel, const scifa_config_t *p_ext_cfg)
{
    int_t ret = DRV_SUCCESS;

    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        ret = DRV_ERROR;
    }

    /* Set clock */
    if (DRV_SUCCESS == ret)
    {
        ret = R_SCIFA_SetClock(channel, p_ext_cfg->clk_enable );
    }

    if (DRV_SUCCESS == ret)
    {
        /* Set noise cancellation */
        ret = R_SCIFA_SetNoiseCanceller(channel, p_ext_cfg->noise_canceller);
    }

    /* Set modem */
    if (DRV_SUCCESS == ret)
    {
        ret = R_SCIFA_SetModemControl(channel, p_ext_cfg->modem_control);
    }

    /* Set FIFO */
    if (DRV_SUCCESS == ret)
    {
        ret = R_SCIFA_SetFIFOThreshold(channel, p_ext_cfg->tftc, p_ext_cfg->rftc);
    }

    return(ret);
}
/******************************************************************************
 * End of Function R_SCIFA_SetExtendedCfg
******************************************************************************/

/**
 * @brief Sets up modem settings for a channel
 * @param[in] modem modem setting for the channel
 * @param[in] channel  channel to configure modem settings for
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetModemControl(int_t channel, scifa_mce_t modem)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Modem Control (RTS/CTS) enable/disable */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FCR.WORD, modem, SCIFA_FCR_MCE_SHIFT, SCIFA_FCR_MCE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetModemControl
 ******************************************************************************/

/**
 * @brief Sets Noise cancellation
 * @param[in] noise_cancellation noise cancellation setting
 * @param[in] channel channel to set the noise cancellation for
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetNoiseCanceller(int_t channel, scifa_nfen_t noise_cancellation)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Noise canceller enable/disable */
    RZA_IO_RegWrite_8((volatile uint8_t *) &gsp_scifa[channel]->SEMR.BYTE, noise_cancellation, SCIFA_SEMR_NFEN_SHIFT, SCIFA_SEMR_NFEN);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetNoiseCanceller
 ******************************************************************************/

/**
 * @brief Sets the clock source for a channel
 * @param[in] desired_clock Clock setting for channel.
 * @param[in] channel Channel to set clock source for.
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetClock(int_t channel, scifa_clk_enable_t desired_clock)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Clock enable mode */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SCR.WORD, desired_clock, SCIFA_SCR_CKE_SHIFT, SCIFA_SCR_CKE);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetClock
 ******************************************************************************/

/**
 * @brief sets up FIFO control
 * @param[in] tx_trg   TX FIFO Trigger setting
 * @param[in] rx_trg   RX FIFO Trigger setting
 * @param[in] channel  channel to set FIFO for
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR 
 */
int_t R_SCIFA_SetFIFOThreshold(int_t channel, uint8_t tx_trg, uint8_t rx_trg)
{
    if ((channel > R_PRV_SCIF_LAST_CHANNEL) || (channel < 0))
    {
        return (DRV_ERROR);
    }

    /* Check TX FIFO Threshold is correct */
    if ((tx_trg > R_PRV_TX_FIFO_MAX_TRG) /* || (tx_trg < R_PRV_TX_FIFO_MIN_TRG) */)
    {
        return (DRV_ERROR);
    }

    /* Check RX FIFO Threshold is correct */
    if ((rx_trg > R_PRV_RX_FIFO_MAX_TRG) || (rx_trg < R_PRV_RX_FIFO_MIN_TRG))
    {
        return (DRV_ERROR);
    }

    /* Set TX Threshold */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FTCR.WORD, tx_trg, SCIFA_FTCR_TFTC_SHIFT, SCIFA_FTCR_TFTC);

    /* Set RX Threshold */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FTCR.WORD, rx_trg, SCIFA_FTCR_RFTC_SHIFT, SCIFA_FTCR_RFTC);

    /* TX - Use the FTCR Trigger settings instead of FCR - giving user more control */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FTCR.WORD, 1u, SCIFA_FTCR_TTRGS_SHIFT, SCIFA_FTCR_TTRGS);

    /* RX - Use the FTCR Trigger settings instead of FCR - giving user more control */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FTCR.WORD, 1u, SCIFA_FTCR_RTRGS_SHIFT, SCIFA_FTCR_RTRGS);

    /* TX - Reset suspended FIFO */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FCR.WORD, (uint16_t) 0, SCIFA_FCR_TFRST_SHIFT, SCIFA_FCR_TFRST);

    /* TX - Reset suspended FIFO */
    RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->FCR.WORD, (uint16_t) 0, SCIFA_FCR_RFRST_SHIFT, SCIFA_FCR_RFRST);

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetFIFOThreshold
 ******************************************************************************/

/**
 * @brief Sets the TXD output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetTXDOutput (int_t channel, scifa_sptr_init_t level)
{
    if (SCIFA_SPTR_INIT_HIGH == level)
    {
        /* set both SPB2DT and SPB2IO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_SPB2IO | SCIFA_SPTR_SPB2DT, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_SPB2IO | SCIFA_SPTR_SPB2DT);
    }
    else
    {
        /* set SPB2DT low and SPB2IO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_SPB2IO, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_SPB2IO | SCIFA_SPTR_SPB2DT);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetTXDOutput
 ******************************************************************************/

/**
 * @brief Sets the SCK output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetSCKOutput (int_t channel, scifa_sptr_init_t level)
{
    if (SCIFA_SPTR_INIT_HIGH == level)
    {
        /* set both SCKDT and SCKIO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_SCKIO | SCIFA_SPTR_SCKDT, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_SCKIO | SCIFA_SPTR_SCKDT);
    }
    else
    {
        /* set SCKDT low and SCKIO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_SCKIO, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_SCKIO | SCIFA_SPTR_SCKDT);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetSCKOutput
 ******************************************************************************/

/**
 * @brief Sets the CTS output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetCTSOutput (int_t channel, scifa_sptr_init_t level)
{
    /* not supported on channel 3 or 4 */
    if ((3 == channel) || (4 == channel))
    {
        return (DRV_ERROR);
    }

    if (SCIFA_SPTR_INIT_HIGH == level)
    {
        /* set both CTS2DT and CTS2IO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_CTS2IO | SCIFA_SPTR_CTS2DT, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_CTS2IO | SCIFA_SPTR_CTS2DT);
    }
    else
    {
        /* set CTS2DT low and CTS2IO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_CTS2IO, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_CTS2IO | SCIFA_SPTR_CTS2DT);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetCTSOutput
 ******************************************************************************/

/**
 * @brief Sets the RTS output level
 * @param[in] channel: the channel to set
 * @param[in] level: the level (low or high)
 * @retval  0 DRV_SUCCESS
 * @retval -1 DRV_ERROR
 */
int_t R_SCIFA_SetRTSOutput (int_t channel, scifa_sptr_init_t level)
{
    /* not supported on channel 3 or 4 */
    if ((3 == channel) || (4 == channel))
    {
        return (DRV_ERROR);
    }

    if (SCIFA_SPTR_INIT_HIGH == level)
    {
        /* set both RTS2DT and RTS2IO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_RTS2IO | SCIFA_SPTR_RTS2DT, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_RTS2IO | SCIFA_SPTR_RTS2DT);
    }
    else
    {
        /* set RTS2DT low and RTS2IO high */
        RZA_IO_RegWrite_16((volatile uint16_t *) &gsp_scifa[channel]->SPTR.WORD, SCIFA_SPTR_RTS2IO, IOREG_NONSHIFT_ACCESS, SCIFA_SPTR_RTS2IO | SCIFA_SPTR_RTS2DT);
    }

    return (DRV_SUCCESS);
}
/******************************************************************************
 * End of Function R_SCIFA_SetRTSOutput
 ******************************************************************************/


/**
 * @brief Get version information
 * @param[out] pVerInfo: version info
 * @retval DRV_SUCCESS   Success(always)
 */
int_t R_SCIFA_GetVersion(st_ver_info_t *pVerInfo)
{
    pVerInfo->lld.p_szdriver_name = STDIO_SCIFA_RZ_LLD_DRV_NAME;
    pVerInfo->lld.version.sub.major = STDIO_SCIFA_RZ_LLD_VERSION_MAJOR;
    pVerInfo->lld.version.sub.minor = STDIO_SCIFA_RZ_LLD_VERSION_MINOR;
    pVerInfo->lld.build = STDIO_SCIFA_RZ_LLD_BUILD_NUM;

    return DRV_SUCCESS;
}
/******************************************************************************
 * End of Function R_SCIFA_GetVersion
 ******************************************************************************/

/* End of File */
