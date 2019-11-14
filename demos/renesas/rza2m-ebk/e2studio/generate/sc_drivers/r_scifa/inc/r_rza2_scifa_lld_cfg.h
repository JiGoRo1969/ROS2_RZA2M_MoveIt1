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
 * Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
 *******************************************************************************/
/*******************************************************************************
 * @headerfile     r_rza2_scifa_lld_cfg.h
 * @brief          SCIFA low level driver cfg header
 * @version        1.00
 * @date           15.05.2018
 * H/W Platform    RZ/A2M
 *******************************************************************************/
/*******************************************************************************
 * History       : DD.MM.YYYY Version Description
 *               : 15.05.2018 1.00    Release
 *******************************************************************************/

#ifndef R_SCIFA_INC_R_RZA2_SCIFA_LLD_CFG_H_
#define R_SCIFA_INC_R_RZA2_SCIFA_LLD_CFG_H_

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

/******************************************************************************
 Macro Definitions
 ******************************************************************************/

/* This define specifies what channels are supported by this low level driver */
/* It is used to inform the high level driver the supported channels */
#define SCIFA_CFG_LLD_SUPPORTED_CHANNELS     (R_CH0 | R_CH1 | R_CH2 | R_CH3 | R_CH4)

/* The define specifies the total number of channels supported by this low level driver */
#define SCIFA_CFG_LLD_NUM_CHANNELS           (5)

#define R_PRV_SCIF_LAST_CHANNEL              (5)

/******************************************************************************
Typedef definitions
******************************************************************************/

#endif /* SRC_RENESAS_AUTOMATED_TEST_R_SCIFA_INC_R_RZA2_SCIFA_LLD_CFG_H_ */
