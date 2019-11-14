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
* File Name    : hwsetup.c
* Device(s)    : RZ/A2M
* Tool-Chain   : e2Studio Ver 7.4.0
*              : GCC ARM Embedded 5.4.1.20160919
* OS           : None
* H/W Platform : RZ/A2M Evaluation Board
* Description  : RZ/A2M Sample Program - FIT function of Hardware Setup
* Operation    :
* Limitations  :
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_typedefs.h"
#include "iodefine.h"
#include "iobitmask.h"
#include "rza_io_regrw.h"
#include "r_startup_config.h"
#include "hwsetup.h"

/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: R_SC_HardwareSetup
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void R_SC_HardwareSetup(void)
{

    /* This code must to be run in internal RAM. */
    /* If the IOKEEP is 1, then clear to 0. */
    if( 1 == RZA_IO_RegRead_16(&PMG.DSFR.WORD, PMG_DSFR_IOKEEP_SHIFT,  PMG_DSFR_IOKEEP) )
    {
        /* Clear IOKEEP bit */
        RZA_IO_RegWrite_16(&PMG.DSFR.WORD, 0, PMG_DSFR_IOKEEP_SHIFT,  PMG_DSFR_IOKEEP);

        /* dummy read*/
        RZA_IO_RegRead_16(&PMG.DSFR.WORD, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    }

#if STARTUP_CFG_RETENTION_RAM_WRITE_ENABLE == 1

    /* Enable write access for the retention RAM (0x8000_0000 ~ 0x8001_FFFF) */
    RZA_IO_RegWrite_8 (&CPG.SYSCR3.BYTE, 0xf, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* dummy read*/
    RZA_IO_RegRead_8(&CPG.SYSCR3.BYTE, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

#endif

}
/*******************************************************************************
 End of function R_SC_HardwareSetup
 *******************************************************************************/

/* End of File */
