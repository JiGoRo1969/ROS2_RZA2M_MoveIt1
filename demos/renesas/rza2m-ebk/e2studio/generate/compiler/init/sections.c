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
* File Name : sections.c
* Description :
******************************************************************************/
#include "r_typedefs.h"

/* List of the section of variables with initial value */
typedef struct {
    void    *rom_s;     /* Top address on ROM    */
    void    *rom_e;     /* Bottom address on ROM */
    void    *ram_s;     /* Top address on RAM    */
} DTBL_S;

/* List of the section of variables with zero clear */
typedef struct {
    void    *b_s;       /* Top address    */
    void    *b_e;       /* Bottom address */
} BTBL_S;


#ifndef ON_RAM
extern  short   __vect_load_start;
extern  short   __vect_load_end;
extern  short   __vect_exec_start;
#endif

extern  short   __fastcode_load_start;
extern  short   __fastcode_load_end;
extern  short   __fastcode_exec_start;

extern  short   __data_load_start;
extern  short   __data_load_end;
extern  short   __data_exec_start;

extern  short   __data2_load_start;
extern  short   __data2_load_end;
extern  short   __data2_exec_start;

extern  short   __uncached_RAM2_load_start;
extern  short   __uncached_RAM2_load_end;
extern  short   __uncached_RAM2_exec_start;

#if 0
extern  short   __code_spibsc_write_operation_load_start;
extern  short   __code_spibsc_write_operation_load_end;
extern  short   __code_spibsc_write_operation_exec_start;

extern  short   __data_spibsc_write_operation_load_start;
extern  short   __data_spibsc_write_operation_load_end;
extern  short   __data_spibsc_write_operation_exec_start;
#endif

extern  short   __bss_start;
extern  short   __bss_end;

extern  short   __bss2_start;
extern  short   __bss2_end;

extern  short   __uncached_RAM_start;
extern  short   __uncached_RAM_end;

#if 0
extern  short   __bss_spibsc_write_operation_start;
extern  short   __bss_spibsc_write_operation_end;
#endif

extern  short   __module2_load_start;
extern  short   __module2_load_end;
extern  short   __module2_exec_start;

extern  short   __module3_exec_start;
extern  short   __module3_exec_end;

const DTBL_S    DTBL[] =
{
#ifndef ON_RAM
    { &__vect_load_start, &__vect_load_end, &__vect_exec_start },
#endif
    { &__fastcode_load_start, &__fastcode_load_end, &__fastcode_exec_start },
    { &__data_load_start, &__data_load_end, &__data_exec_start },
    { &__data2_load_start, &__data2_load_end, &__data2_exec_start },
    { &__uncached_RAM2_load_start, &__uncached_RAM2_load_end, &__uncached_RAM2_exec_start },
#if 0
    { &__code_spibsc_write_operation_load_start, &__code_spibsc_write_operation_load_end, &__code_spibsc_write_operation_exec_start },
    { &__data_spibsc_write_operation_load_start, &__data_spibsc_write_operation_load_end, &__data_spibsc_write_operation_exec_start },
#endif
    /*  {   _sectop("D"),   _secend("D"),   _sectop("R")    },*/
    {   0,  0,  0   },  /* terminator */
};

const BTBL_S    BTBL[] =
{
    { &__bss_start, &__bss_end },
    { &__bss2_start, &__bss2_end },
    { &__uncached_RAM_start, &__uncached_RAM_end },
#if 0
    { &__bss_spibsc_write_operation_start, &__bss_spibsc_write_operation_end },
#endif
/*  {   _sectop("B"),   _secend("B")    },*/
    {   0,  0   },  /* terminator */
};

const DTBL_S    DTBL_F[] =
{
    { &__module2_load_start, &__module2_load_end, &__module2_exec_start },
    /*  {   _sectop("D"),   _secend("D"),   _sectop("R")    },*/
    {   0,  0,  0   },  /* terminator */
};

const BTBL_S    BTBL_F[] =
{
    { &__module3_exec_start, &__module3_exec_end },
/*  {   _sectop("B"),   _secend("B")    },*/
    {   0,  0   },  /* terminator */
};


/* End of File */
