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
*******************************************************************************/
/*******************************************************************************
* File Name    : r_ostm_lld_rza2m.c
* Device(s)    : RZ/A2M
* Tool-Chain   : e2Studio Ver 7.4.0
*              : GCC ARM Embedded 5.4.1.20160919
* OS           : None
* H/W Platform : RZ/A2M Evaluation Board
* Description  : RZ/A2M Sample Program - LowLevel function of OSTM Module
* Operation    :
* Limitations  :
*******************************************************************************/
/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <string.h>
#include <ctype.h>
#include "r_typedefs.h"
#include "r_ostm_drv_link.h"
#include "r_ostm_drv_api.h"
#include "r_intc_drv_api.h"
#include "iodefine.h"
#include "iobitmask.h"
#include "rza_io_regrw.h"
#include "r_cpg_drv_api.h"
#include "r_stb_drv_api.h"

/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/
/*! Version Information */
static const st_drv_info_t gs_lld_info =
{
    {
        ((STDIO_OSTM_RZ_LLD_VERSION_MAJOR << 16) + STDIO_OSTM_RZ_LLD_VERSION_MINOR)
    },
    STDIO_OSTM_RZ_LLD_BUILD_NUM,
    STDIO_OSTM_RZ_LLD_DRV_NAME
};

static volatile struct st_ostm * const gsp_ostm_reg[OSTM_CH_MAX] =
{
    &OSTM0, &OSTM1, &OSTM2
};
static const e_stb_module_t gs_ostm_module[] =
{
    MODULE_OSTM0,MODULE_OSTM1,MODULE_OSTM2
};
static const e_r_drv_intc_intid_t gs_intid[OSTM_CH_MAX] =
{
    INTC_ID_OSTM_OSTMI0, INTC_ID_OSTM_OSTMI1, INTC_ID_OSTM_OSTMI2
};

/**
 * @brief          is_valid_mode
 *                 Check if desired OSTM mode is valid or not
 * @param[in]      mode: desired mode
 * @retval         true  valid mode
 * @retval         false invalid mode
 */
static bool_t is_valid_mode(e_r_drv_ostm_mode_t mode)
{
    bool_t result;

    result = false;
    
    switch ( mode )
    {
        case OSTM_MODE_INTERVAL:
        {
            /* OK */
            result = true;
            break;
        }
        case OSTM_MODE_FREERUN:
        {
            /* OK */
            result = true;
            break;
        }
        default:
        {
            /* NG */
            result = false;
        }
    }
    return result;
}
/******************************************************************************
 * End of function is_valid_mode
 ******************************************************************************/

/**
 * @brief          is_valid_counter_format
 *                 Check if desired counter format is valid or not
 * @param[in]      format: desired format
 * @retval         true  valid counter format
 * @retval         false invalid counter format
 */
static bool_t is_valid_counter_format(e_r_drv_ostm_counter_format_t format)
{
    bool_t result;

    result = false;
    
    switch ( format )
    {
        case OSTM_TIME_MS:
        {
            /* OK */
            result = true;
            break;
        }
        case OSTM_TIME_COUNT:
        {
            /* OK */
            result = true;
            break;
        }
        default:
        {
            /* NG */
            result = false;
        }
    }

    return result;
}
/******************************************************************************
 * End of function is_valid_counter_format
 ******************************************************************************/

/**
 * @brief          is_valid_start_interrupt
 *                 Check if desired start_interrupt parameter is valid or not
 * @param[in]      start_interrupt: desired start_interrupt parameter
 * @retval         true  valid start_interrupt parameter
 * @retval         false invalid start_interrupt parameter
 */
static bool_t is_valid_start_interrupt(e_r_drv_start_interrupt_t start_interrupt)
{
    bool_t result;

    result = false;
    
    switch ( start_interrupt )
    {
        case OSTM_START_INTERRUPT_OFF:
        {
            /* OK */
            result = true;
            break;
        }
        case OSTM_START_INTERRUPT_ON:
        {
            /* OK */
            result = true;
            break;
        }
        default:
        {
            /* NG */
            result = false;
        }
    }

    return result;
}
/******************************************************************************
 * End of function is_valid_start_interrupt
 ******************************************************************************/

/**
 * @brief          is_valid_interrupt
 *                 Check if desired interrupt parameter is valid or not
 * @param[in]      interrupt: desired interrupt parameter
 * @retval         true  valid interrupt parameter
 * @retval         false invalid interrupt parameter
 */
static bool_t is_valid_interrupt(e_r_drv_intc_enable_t interrupt)
{
    bool_t result;

    result = false;
    
    switch ( interrupt )
    {
        case INTC_ENABLE:
        {
            /* OK */
            result = true;
            break;
        }
        case INTC_DISABLE:
        {
            /* OK */
            result = true;
            break;
        }
        default:
        {
            /* NG */
            result = false;
        }
    }

    return result;
}
/******************************************************************************
 * End of function is_valid_interrupt
 ******************************************************************************/

/**
 * @brief          calc_interval
 *                 Calculate compare match counter for using interval timer mode
 * @param[in]      msec:      timer duration
 * @param[out]     p_compare: compare value
 * @retval         true  result fits in 32bit unsigned value
 * @retval         false result overs out of 32bit unsigned value
 */
static int_t calc_interval( uint32_t msec, uint32_t *p_compare )
{
    int_t err;
    float64_t p1clk;
    uint64_t count;

    err = DRV_SUCCESS;

    /* get current P1CLK frequency */
    R_CPG_GetClock(CPG_FREQ_P1CLK, &p1clk);

    /* calculate compare register value for interval timer mode
     * (P1CLK(KHz) * [interval duration]) - 1
     * to keeping the accuracy, keep in 64bit float while multiply.
     */
    count = (uint64_t)((float64_t)msec * p1clk);
    count--;

    /* check whether the result overflow or not */
    if( count > UINT32_MAX )
    {
        err = DRV_ERROR;
    }
    else
    {
        /* only if result is fit in 32-bit unsigned value */
        *p_compare = (uint32_t)count;
    }

    return err;
}
/******************************************************************************
 * End of function calc_interval
 ******************************************************************************/

/**
 * @brief          calc_compare
 *                 Calculate compare match counter for using free-run compare mode
 * @param[in]      msec:      timer duration
 * @param[out]     p_compare: compare value
 * @retval         true  result fits in 32bit unsigned value
 * @retval         false result overs out of 32bit unsigned value
 */
static int_t calc_compare( uint32_t msec, uint32_t *p_compare )
{
    int_t err;
    float64_t p1clk;
    uint64_t count;

    err = DRV_SUCCESS;

    /* get current P1CLK frequency */
    R_CPG_GetClock(CPG_FREQ_P1CLK, &p1clk);

    /* calculate compare register value for free-run compare mode
     * (P1CLK(KHz) * [interval duration]) - 1
     * to keeping the accuracy, keep in 64bit float while multiply.
     */
    count = (uint64_t)((float64_t)msec * p1clk);
    count--;

    /* check whether the result overflow or not */
    if( count > UINT32_MAX )
    {
        err = DRV_ERROR;
    }
    else
    {
        /* only if result is fit in 32-bit unsigned value */
        *p_compare = (uint32_t)count;
    }

    return err;
}
/******************************************************************************
 * End of function calc_compare
 ******************************************************************************/

/**
 * @brief      ostm_init_internal
 *             Configure the channel (internal)
 * @param[in]  channel:     desired channel
 * @param[in]  p_config:    configuration for the channel
 * @retval     DRV_SUCCESS  Successful operation
 * @retval     DRV_ERROR    Failure operation
 */
static int_t ostm_init_internal(e_r_drv_ostm_channel_t channel, const st_r_drv_ostm_config_t *p_config)
{
    int_t err;
    e_stb_err_t error_stb;
    e_r_drv_intc_err_t error_intc;
    uint32_t cmp_reg;

    err = DRV_SUCCESS;
    error_stb = STB_SUCCESS;
    error_intc = INTC_SUCCESS;

    /* Calculate OSTMnCMP register */
    if ( DRV_SUCCESS == err )
    {
        if ( OSTM_TIME_MS == p_config->counter_format )
        {
            if ( OSTM_MODE_INTERVAL == p_config->mode )
            {
                err = calc_interval( p_config->time, &cmp_reg );
            }
            else /* OSTM_MODE_FREERUN */
            {
                err = calc_compare( p_config->time, &cmp_reg );
            }
        }
        else /* OSTM_TIME_COUNT */
        {
            cmp_reg = p_config->time;
        }
    }

    /* Start module */
    if ( DRV_SUCCESS == err )
    {
        error_stb = R_STB_StartModule(gs_ostm_module[channel]);
        if(error_stb != STB_SUCCESS)
        {
            err = DRV_ERROR;
        }
    }

    /* Setting OSTMnCTL (control) register */
    if ( DRV_SUCCESS == err )
    {
        /* Setting OSTMnCTL.OSTMnMD1 bit
         * 1 for free-run mode or 0 for not */
        if( OSTM_MODE_FREERUN == p_config->mode )
        {
            RZA_IO_RegWrite_8(&gsp_ostm_reg[channel]->OSTMnCTL.BYTE, 1, OSTM_OSTMnCTL_OSTMnMD1_SHIFT, OSTM_OSTMnCTL_OSTMnMD1);
        }
        else /* OSTM_MODE_INTERVAL */
        {
            RZA_IO_RegWrite_8(&gsp_ostm_reg[channel]->OSTMnCTL.BYTE, 0, OSTM_OSTMnCTL_OSTMnMD1_SHIFT, OSTM_OSTMnCTL_OSTMnMD1);
        }

        /* Setting OSTMnCTL.OSTMnMD0 bit
         * 1 for generates interruption if timer started or not */
        if( OSTM_START_INTERRUPT_ON == p_config->start_generates_interruption )
        {
            RZA_IO_RegWrite_8(&gsp_ostm_reg[channel]->OSTMnCTL.BYTE, 1, OSTM_OSTMnCTL_OSTMnMD0_SHIFT, OSTM_OSTMnCTL_OSTMnMD0);
        }
        else /* OSTM_START_INTERRUPT_OFF */
        {
            RZA_IO_RegWrite_8(&gsp_ostm_reg[channel]->OSTMnCTL.BYTE, 0, OSTM_OSTMnCTL_OSTMnMD0_SHIFT, OSTM_OSTMnCTL_OSTMnMD0);
        }

        /* Setting OSTMnCMP register */
        RZA_IO_RegWrite_32(&gsp_ostm_reg[channel]->OSTMnCMP.LONG, cmp_reg, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

        /* Interrupt controller setup */
        if ( INTC_ENABLE == p_config->int_enable )
        {
            /* Setting gsp_ostm_reg interrupt priority level */
            error_intc = R_INTC_SetPriority( gs_intid[channel], p_config->int_priority );

            /* Check parameter (interrupt function) */
            if ( (void*)NULL == p_config->int_function )
            {
                /* can not register driver function */
                error_intc = INTC_ERR_INVALID;
            }

            /* Registering interrupt handler */
            if ( INTC_SUCCESS == error_intc )
            {
                error_intc = R_INTC_RegistIntFunc( gs_intid[channel], p_config->int_function );
            }

            /* Enable gsp_ostm_reg interrupt */
            if ( INTC_SUCCESS == error_intc )
            {
                error_intc = R_INTC_Enable( gs_intid[channel] );
            }

        }
        else /* INTC_DISABLE */
        {
            /* Disable OSTM interrupt */
            error_intc = R_INTC_Disable( gs_intid[channel] );
        }

        /* Follow the INTC error state */
        if ( INTC_SUCCESS != error_intc )
        {
            err = DRV_ERROR;
        }
    }

    return err;
}
/******************************************************************************
 * End of function ostm_init_internal
 ******************************************************************************/

/**
 * @brief          R_OSTM_Init
 *                 Configure the channel
 * @param[in]      channel:     desired channel
 * @param[in/out]  p_config:    configuration for the channel
 * @retval         DRV_SUCCESS  Successful operation
 * @retval         DRV_ERROR    Failure operation
 */
int_t R_OSTM_Init(e_r_drv_ostm_channel_t channel, const st_r_drv_ostm_config_t *p_config)
{
    int_t err;

    err = DRV_SUCCESS;

    /* Check parameter (channel) */
    if ( channel >= OSTM_CH_MAX )
    {
        err = DRV_ERROR;
    }

    /* Check parameter (counter format) */
    if ( !is_valid_counter_format(p_config->counter_format) )
    {
        err = DRV_ERROR;
    }

    /* Check parameter (mode) */
    if ( !is_valid_mode(p_config->mode) )
    {
        err = DRV_ERROR;
    }

    /* Check parameter (start_interrupt) */
    if ( !is_valid_start_interrupt(p_config->start_generates_interruption) )
    {
        err = DRV_ERROR;
    }

    /* Check parameter (interrupt) */
    if ( !is_valid_interrupt(p_config->int_enable) )
    {
        err = DRV_ERROR;
    }

    /* Calling internally defined initialissing function */
    if ( DRV_SUCCESS == err )
    {
        err = ostm_init_internal(channel, p_config);
    }

    return err;
}
/******************************************************************************
 * End of function R_OSTM_Init
 ******************************************************************************/

/**
 * @brief          R_OSTM_Close
 *                 Close the OSTM channel
 * @param[in]      channel:     desired channel
 * @retval         DRV_SUCCESS  Successful operation
 * @retval         DRV_ERROR    Failure operation
 */
int_t R_OSTM_Close(e_r_drv_ostm_channel_t channel)
{
    int_t err;
    e_stb_err_t error_stb;
    e_r_drv_intc_err_t error_intc;

    err = DRV_SUCCESS;

    /* Check parameter (channel) */
    if ( channel >= OSTM_CH_MAX )
    {
        err = DRV_ERROR;
    }

    /* Stop the OSTM */
    if ( DRV_SUCCESS == err )
    {
        err = R_OSTM_Stop( channel );
    }

    /* Disable interrupt of the OSTM */
    if ( DRV_SUCCESS == err )
    {
        error_intc = R_INTC_Disable( gs_intid[channel] );

        /* Follow the INTC error state */
        if( INTC_SUCCESS != error_intc )
        {
            err = DRV_ERROR;
        }
    }

    /* Set module standby */
    if ( DRV_SUCCESS == err )
    {
        error_stb = R_STB_StopModule(gs_ostm_module[channel]);
        if ( STB_SUCCESS != error_stb )
        {
            err = DRV_ERROR;
        }
    }

    return err;
}
/******************************************************************************
 * End of function R_OSTM_Close
 ******************************************************************************/

/**
 * @brief          R_OSTM_GetVersion
 *                 Obtains driver specific version information which is used for
 *                 reporting
 * @param[out]     drv_info_ptr: driver version information is populated into
 *                               this structure
 *                               @note the structure resources are created by
 *                                     the application not this function.
 * @retval         DRV_SUCCESS  Successful operation (always)
 */
int_t R_OSTM_GetVersion(st_ver_info_t *pVerInfo)
{
    pVerInfo->lld.p_szdriver_name = gs_lld_info.p_szdriver_name;
    pVerInfo->lld.version.sub.major = gs_lld_info.version.sub.major;
    pVerInfo->lld.version.sub.minor = gs_lld_info.version.sub.minor;
    pVerInfo->lld.build = gs_lld_info.build;

    return DRV_SUCCESS;
}
/******************************************************************************
 * End of function R_OSTM_GetVersion
 ******************************************************************************/

/**
 * @brief          R_OSTM_GetCount
 *                 Gets the count value for the specified OSTM channel
 *                 @note does not stop the channel from running.
 * @param[in]      channel:     desired channel
 * @param[out]     p_data:      count value
 * @retval         DRV_SUCCESS  Successful operation
 * @retval         DRV_ERROR    Failure operation
 */
int_t R_OSTM_GetCount(e_r_drv_ostm_channel_t channel, uint32_t * p_data)
{
    int_t err;

    err = DRV_SUCCESS;

    /* Check parameter (channel) */
    if ( channel >= OSTM_CH_MAX )
    {
        err = DRV_ERROR;
    }

    /* Get current counter */
    if ( DRV_SUCCESS == err )
    {
        *p_data = RZA_IO_RegRead_32(&gsp_ostm_reg[channel]->OSTMnCNT.LONG, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

        /* As this is a read32 the size will be 4 bytes */
        err = 4;
    }

    return err;
}
/******************************************************************************
 * End of function R_OSTM_GetCount
 ******************************************************************************/

/**
 * @brief          R_OSTM_Start
 *                 Starts timer for specified channel
 * @param[in]      channel:     desired channel
 * @retval         DRV_SUCCESS  Successful operation
 * @retval         DRV_ERROR    Failure operation
 */
int_t R_OSTM_Start(e_r_drv_ostm_channel_t channel)
{
    uint8_t dummy8;

    RZA_IO_RegWrite_8(&gsp_ostm_reg[channel]->OSTMnTS.BYTE, 1, OSTM_OSTMnTS_OSTMnTS_SHIFT, OSTM_OSTMnTS_OSTMnTS);
    RZA_IO_RegRead_8(&gsp_ostm_reg[channel]->OSTMnTS.BYTE, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* wait until OSTMn.OSTMnTE.BIT.OSTMnTE becomes "1" */
    do
    {
        dummy8 = RZA_IO_RegRead_8(&gsp_ostm_reg[channel]->OSTMnTE.BYTE, OSTM_OSTMnTE_OSTMnTE_SHIFT, OSTM_OSTMnTE_OSTMnTE);
    }while( 0 == dummy8 );

    return DRV_SUCCESS;
}
/******************************************************************************
 * End of function R_OSTM_Start
 ******************************************************************************/

/**
 * @brief          R_OSTM_Stop
 *                 Stops timer for specified channel
 * @param[in]      channel:     desired channel
 * @retval         DRV_SUCCESS  Successful operation
 * @retval         DRV_ERROR    Failure operation
 */
int_t R_OSTM_Stop(e_r_drv_ostm_channel_t channel)
{
    uint8_t dummy8;

    RZA_IO_RegWrite_8(&gsp_ostm_reg[channel]->OSTMnTT.BYTE, 1, OSTM_OSTMnTT_OSTMnTT_SHIFT, OSTM_OSTMnTT_OSTMnTT);
    RZA_IO_RegRead_8(&gsp_ostm_reg[channel]->OSTMnTT.BYTE, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* wait until OSTMn.OSTMnTE.BIT.OSTMnTE becomes "0" */
    do
    {
        dummy8 = RZA_IO_RegRead_8(&gsp_ostm_reg[channel]->OSTMnTE.BYTE, OSTM_OSTMnTE_OSTMnTE_SHIFT, OSTM_OSTMnTE_OSTMnTE);
    }while( 1 == dummy8 );

    return DRV_SUCCESS;
}
/******************************************************************************
 * End of function R_OSTM_Stop
 ******************************************************************************/

/* End of File */
