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
* File Name : r_mmu_hld_prv.h
* Description :
******************************************************************************/
#ifndef R_BSP_MMU_INIT_H
#define R_BSP_MMU_INIT_H

#include "r_typedefs.h"
#include "driver.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/* Version Number of API */

#define STDIO_MMU_RZ_LLD_DRV_NAME ("LLD EBK_RZA2M MMU")

/** Major Version Number of API */
#define STDIO_MMU_RZ_LLD_VERSION_MAJOR      (1)
/** Minor Version Number of API */
#define STDIO_MMU_RZ_LLD_VERSION_MINOR      (2)
/** Minor Version Number of API */
#define STDIO_MMU_RZ_LLD_BUILD_NUM          (0)
/** Unique ID */
#define STDIO_MMU_RZ_LLD_UID                (0)


/* GUI selectable area attributes */
/* Unused area */
#define MMU_ATTR_UNUSED                     (MMU_ATTR_STRONGLY_BASE     |MMU_ATTR_NONSECURE|MMU_ATTR_EXECUTE_NEVER|MMU_ATTR_AP1|MMU_ATTR_AP0)

/* Reserved area */
#define MMU_ATTR_RESERVED                   (MMU_ATTR_STRONGLY_BASE     |MMU_ATTR_NONSECURE|MMU_ATTR_EXECUTE_NEVER)
/* Strongly-ordered, secure and Never-execute */
#define MMU_ATTR_STRONGLY                   (MMU_ATTR_STRONGLY_BASE     |                   MMU_ATTR_EXECUTE_NEVER|MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Strongly-ordered, non-secure and Never-execute */
#define MMU_ATTR_STRONGLY_NS                (MMU_ATTR_STRONGLY_BASE     |MMU_ATTR_NONSECURE|MMU_ATTR_EXECUTE_NEVER|MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Strongly-ordered, non-secure and Executable */
#define MMU_ATTR_STRONGLY_NS_EXECUTABLE     (MMU_ATTR_STRONGLY_BASE     |MMU_ATTR_NONSECURE|                       MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Shareable Device, secure */
#define MMU_ATTR_DEVICE                     (MMU_ATTR_DEVICE_BASE                          |MMU_ATTR_EXECUTE_NEVER|MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Shareable Device, non-secure */
#define MMU_ATTR_DEVICE_NS                  (MMU_ATTR_DEVICE_BASE       |MMU_ATTR_NONSECURE|MMU_ATTR_EXECUTE_NEVER|MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Normal, non-secure, and non-cacheable */
#define MMU_ATTR_NORMAL                     (MMU_ATTR_NORMAL_BASE       |MMU_ATTR_NONSECURE                       |MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Normal, non-secure, and L1 cacheable */
#define MMU_ATTR_NORMAL_L1CACHE             (MMU_ATTR_NORMAL_BASE       |MMU_ATTR_NONSECURE|MMU_ATTR_CACHE(1,0)   |MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Normal, non-secure, and L2 cacheable */
#define MMU_ATTR_NORMAL_L2CACHE             (MMU_ATTR_NORMAL_BASE       |MMU_ATTR_NONSECURE|MMU_ATTR_CACHE(0,1)   |MMU_ATTR_AP1|MMU_ATTR_AP0)
/* Normal, non-secure, and L1/L2 cacheable */
#define MMU_ATTR_NORMAL_L1L2CACHE           (MMU_ATTR_NORMAL_CACHED_BASE|MMU_ATTR_NONSECURE                       |MMU_ATTR_AP1|MMU_ATTR_AP0)

/* if customer wants to custom value (not listed above),
 * GUI generates value combination of definitions below.
 */
/* Strongly-Ordered TEX=0, C=0, B=0 */
#define MMU_ATTR_STRONGLY_BASE                           (0x00002uL)
/* Shareable-Device TEX=0, C=0, B=1 */
#define MMU_ATTR_DEVICE_BASE                             (0x00006uL)
/* Normal TEX=4, C=0, B=0 */
#define MMU_ATTR_NORMAL_BASE                             (0x04002uL)
/* Normal TEX=1, C=1, B=1 */
#define MMU_ATTR_NORMAL_CACHED_BASE                      (0x0100EuL)

/* other parameters */
/* Non-secure */
#define MMU_ATTR_NONSECURE                               (0x80000uL)
/* Not Global */
#define MMU_ATTR_NG                                      (0x20000uL)
/* Shareable */
#define MMU_ATTR_SHAREABLE                               (0x10000uL)
/* AP2 bit */
#define MMU_ATTR_AP2                                     (0x08000uL)
/* AP1 bit */
#define MMU_ATTR_AP1                                     (0x00800uL)
/* AP0 bit */
#define MMU_ATTR_AP0                                     (0x00400uL)
/* domain */
#define MMU_ATTR_DOMAIN(a)                               (((uint32_t)(a)&15)<<5)
/* L1, L2 cache setting (only for Normal memory)
 * 0 : Non-cacheable
 * 1 : Write-Back, Write-Allocate
 * 2 : Write-Through, no Write-Allocate
 * 3 : Write-Back, no Write-Allocate
 */
#define MMU_ATTR_CACHE(l1,l2)                            ((((uint32_t)(l2)&3)<<12)|(((uint32_t)(l1)&3)<<2))
/* non-executable */
#define MMU_ATTR_EXECUTE_NEVER                           (0x00010uL)
/* C bit */
#define MMU_ATTR_C                                       (0x00008uL)
/* B bit */
#define MMU_ATTR_B                                       (0x00004uL)


/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum mmu_err
{
    MMU_SUCCESS=0,               /*!< Operation successfully completed */
    MMU_ERR_OVERFLOW=(-1),       /*!< Address overflow (VA or PA) */
    MMU_ERR_TRANSLATION=(-2),    /*!< Can not obtain physical address of virtual address */
} e_mmu_err_t;


/******************************************************************************
Functions Prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern void R_MMU_Enable( void );
extern void R_MMU_Disable( void );
extern e_mmu_err_t R_MMU_WriteTbl( uint32_t vaddress, uint32_t paddress, uint32_t size, uint32_t entry );
extern void R_MMU_Init(void);
extern uint32_t R_MMU_ReadTbl( uint32_t address );
extern e_mmu_err_t R_MMU_VAtoPA( uint32_t vaddress, uint32_t * paddress );
extern void R_MMU_TLBIALL( void );
extern void R_MMU_TLBIMVAA( const uint32_t address );

/**
 * @brief      R_MMU_GetVersion
 *
 *             Obtains driver specific version information which is used for
 *             reporting
 *
 * @param[out] pVerInfo:  driver version information is populated into this
 *                        structure.
 *                        @note the structure resources are created
 *                              by the application not this function
 *
 * @retval     DRV_SUCCESS   Successful operation.
 * @retval     DRV_ERROR     On failure
 */
extern int_t R_MMU_GetVersion(st_ver_info_t *p_ver_info);


extern uint32_t r_mmu_get_ttbcr(void);
extern void r_mmu_set_ttbcr(const uint32_t ttbcr);
extern uint32_t r_mmu_get_ttbr0(void);
extern void r_mmu_set_ttbr0(const uint32_t ttbr0);
extern uint32_t r_mmu_get_dacr(void);
extern void r_mmu_set_dacr(const uint32_t dacr);
extern uint32_t r_mmu_get_sctlr(void);
extern void r_mmu_set_sctlr(const uint32_t sctlr);
extern uint32_t r_mmu_tlbiall(void);
extern void r_mmu_tlbimvaa(const uint32_t vaddress);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*R_BSP_MMU_INIT_H*/
/* End of File */
