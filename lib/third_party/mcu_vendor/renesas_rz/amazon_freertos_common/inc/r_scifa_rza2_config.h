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
/******************************************************************************
* File Name    : r_scifa_rza2_config.h
* Description   : Configures the SCIFA driver
*******************************************************************************
* History : DD.MM.YYYY Version Description
*           12.12.2017 1.00    Initial Release
*******************************************************************************/
#ifndef SCIFA_CONFIG_ASYNC_H
#define SCIFA_CONFIG_ASYNC_H

/******************************************************************************
Configuration Options
*******************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
// Setting to STARTUP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
// Setting to 1 includes parameter checking; 0 compiles out parameter checking
#define SCIFA_CFG_PARAM_CHECKING_ENABLE   STARTUP_CFG_PARAM_CHECKING_ENABLE

/* SPECIFY TX BUFFER SIZE */
// The TX BUFFER SIZE indicates the size of TX BUFFER
// Setting value mult not be less than maximum length of 3rd argument of
// R_SCIFA_ASYNC_Send() function
// 
#define SCIFA_CFG_CH0_TX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH1_TX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH2_TX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH3_TX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH4_TX_BUFFER_SIZE (256)

/* SPECIFY RX BUFFER SIZE */
// The RX BUFFER SIZE indicates the size of RX BUFFER
// Setting value mult not be less than maximum length of 2nd argument of
// R_SCIFA_ASYNC_Receive() function
#define SCIFA_CFG_CH0_RX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH1_RX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH2_RX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH3_RX_BUFFER_SIZE (256)
#define SCIFA_CFG_CH4_RX_BUFFER_SIZE (256)

#endif /* SCIFA_CONFIG_ASYNC_H */
/* End of File */
