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
/******************************************************************************
* File Name     : compiler_settings.h
* Device(s)     : RZ/A2M
* Tool-Chain    : GNUARM-NONE-EABI-v16.01
* H/W Platform  : Platform Independent
* Description   : Any compiler specific settings are stored here.
*               : Variants of this file must be created for each compiler
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 18.06.2013 1.00
*               : 21.03.2014 2.00
******************************************************************************/

#ifndef COMPILER_SETTINGS_H
#define COMPILER_SETTINGS_H

#include "r_compiler_abstraction_api.h"
#include "r_os_abstraction_api.h"
#include "r_typedefs.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/* CMSIS OPTIONS Required by ARM SMSYS module */
#define __FPU_PRESENT (1)


/******************************************************************************
Variable External definitions and Function External definitions
******************************************************************************/

extern void     __set_sctlr(uint32_t sctlr);
extern uint32_t __get_sctlr(void);
extern void     __set_cpsr(uint32_t cpsr);
extern uint32_t __get_cpsr(void);
extern void     __set_vbar(uint32_t vbar);
extern uint32_t __get_vbar(void);
extern void     __wfi(void);
extern void     __isb(void);
extern void     __dsb(void);
extern void     __dmb(void);

extern void R_SoftwareDelay( uint32_t delay );

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* COMPILER_SETTINGS_H */
#endif  

/* End of File */
