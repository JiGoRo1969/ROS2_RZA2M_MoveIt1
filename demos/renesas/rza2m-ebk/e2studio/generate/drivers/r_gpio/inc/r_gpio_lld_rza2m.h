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
* File Name   : r_gpio_lld_rza2m.h
* Description :
******************************************************************************/
#ifndef R_GPIO_LLD_RZA2M_H_
#define R_GPIO_LLD_RZA2M_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_typedefs.h"
#include "iodefine.h"
#include "r_gpio_drv_api.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/* Version Number of API */

#define GPIO_RZ_LLD_DRV_NAME ("LLD EBK_RZA2M GPIO")

/** Major Version Number of API */
#define GPIO_LLD_VERSION_MAJOR      (1)
/** Minor Version Number of API */
#define GPIO_LLD_VERSION_MINOR      (2)
/** Minor Version Number of API */
#define GPIO_LLD_BUILD_NUM          (0)
/** Unique ID */
#define GPIO_RZ_LLD_UID             (60)


#define GPIO_PORT_0         ((r_gpio_port_t)0x0000)
#define GPIO_PORT_1         ((r_gpio_port_t)0x0100)
#define GPIO_PORT_2         ((r_gpio_port_t)0x0200)
#define GPIO_PORT_3         ((r_gpio_port_t)0x0300)
#define GPIO_PORT_4         ((r_gpio_port_t)0x0400)
#define GPIO_PORT_5         ((r_gpio_port_t)0x0500)
#define GPIO_PORT_6         ((r_gpio_port_t)0x0600)
#define GPIO_PORT_7         ((r_gpio_port_t)0x0700)
#define GPIO_PORT_8         ((r_gpio_port_t)0x0800)
#define GPIO_PORT_9         ((r_gpio_port_t)0x0900)
#define GPIO_PORT_A         ((r_gpio_port_t)0x0A00)
#define GPIO_PORT_B         ((r_gpio_port_t)0x0B00)
#define GPIO_PORT_C         ((r_gpio_port_t)0x0C00)
#define GPIO_PORT_D         ((r_gpio_port_t)0x0D00)
#define GPIO_PORT_E         ((r_gpio_port_t)0x0E00)
#define GPIO_PORT_F         ((r_gpio_port_t)0x0F00)
#define GPIO_PORT_G         ((r_gpio_port_t)0x1000)
#define GPIO_PORT_H         ((r_gpio_port_t)0x1100)
#define GPIO_PORT_J         ((r_gpio_port_t)0x1200)
#define GPIO_PORT_K         ((r_gpio_port_t)0x1300)
#define GPIO_PORT_L         ((r_gpio_port_t)0x1400)
#define GPIO_JPORT_0        ((r_gpio_port_t)0x1500)
#define GPIO_PORT_MAX       (0x15)
#define GPIO_PORT_CKIO      ((r_gpio_port_t)0x8000)
#define GPIO_PORT_SD0       ((r_gpio_port_t)0x8100)
#define GPIO_PORT_SD1       ((r_gpio_port_t)0x8200)
#define GPIO_PORT_SPIBSC    ((r_gpio_port_t)0x8300)
#define GPIO_PORT_MASK      ((r_gpio_port_t)0xFF00)
#define GPIO_PORT_SHIFT     (8)

#define GPIO_PORT_0_PIN_0   ((r_gpio_port_pin_t)0x0000)
#define GPIO_PORT_0_PIN_1   ((r_gpio_port_pin_t)0x0001)
#define GPIO_PORT_0_PIN_2   ((r_gpio_port_pin_t)0x0002)
#define GPIO_PORT_0_PIN_3   ((r_gpio_port_pin_t)0x0003)
#define GPIO_PORT_0_PIN_4   ((r_gpio_port_pin_t)0x0004)
#define GPIO_PORT_0_PIN_5   ((r_gpio_port_pin_t)0x0005)
#define GPIO_PORT_0_PIN_6   ((r_gpio_port_pin_t)0x0006)
#define GPIO_PORT_1_PIN_0   ((r_gpio_port_pin_t)0x0100)
#define GPIO_PORT_1_PIN_1   ((r_gpio_port_pin_t)0x0101)
#define GPIO_PORT_1_PIN_2   ((r_gpio_port_pin_t)0x0102)
#define GPIO_PORT_1_PIN_3   ((r_gpio_port_pin_t)0x0103)
#define GPIO_PORT_1_PIN_4   ((r_gpio_port_pin_t)0x0104)
#define GPIO_PORT_2_PIN_0   ((r_gpio_port_pin_t)0x0200)
#define GPIO_PORT_2_PIN_1   ((r_gpio_port_pin_t)0x0201)
#define GPIO_PORT_2_PIN_2   ((r_gpio_port_pin_t)0x0202)
#define GPIO_PORT_2_PIN_3   ((r_gpio_port_pin_t)0x0203)
#define GPIO_PORT_3_PIN_0   ((r_gpio_port_pin_t)0x0300)
#define GPIO_PORT_3_PIN_1   ((r_gpio_port_pin_t)0x0301)
#define GPIO_PORT_3_PIN_2   ((r_gpio_port_pin_t)0x0302)
#define GPIO_PORT_3_PIN_3   ((r_gpio_port_pin_t)0x0303)
#define GPIO_PORT_3_PIN_4   ((r_gpio_port_pin_t)0x0304)
#define GPIO_PORT_3_PIN_5   ((r_gpio_port_pin_t)0x0305)
#define GPIO_PORT_4_PIN_0   ((r_gpio_port_pin_t)0x0400)
#define GPIO_PORT_4_PIN_1   ((r_gpio_port_pin_t)0x0401)
#define GPIO_PORT_4_PIN_2   ((r_gpio_port_pin_t)0x0402)
#define GPIO_PORT_4_PIN_3   ((r_gpio_port_pin_t)0x0403)
#define GPIO_PORT_4_PIN_4   ((r_gpio_port_pin_t)0x0404)
#define GPIO_PORT_4_PIN_5   ((r_gpio_port_pin_t)0x0405)
#define GPIO_PORT_4_PIN_6   ((r_gpio_port_pin_t)0x0406)
#define GPIO_PORT_4_PIN_7   ((r_gpio_port_pin_t)0x0407)
#define GPIO_PORT_5_PIN_0   ((r_gpio_port_pin_t)0x0500)
#define GPIO_PORT_5_PIN_1   ((r_gpio_port_pin_t)0x0501)
#define GPIO_PORT_5_PIN_2   ((r_gpio_port_pin_t)0x0502)
#define GPIO_PORT_5_PIN_3   ((r_gpio_port_pin_t)0x0503)
#define GPIO_PORT_5_PIN_4   ((r_gpio_port_pin_t)0x0504)
#define GPIO_PORT_5_PIN_5   ((r_gpio_port_pin_t)0x0505)
#define GPIO_PORT_5_PIN_6   ((r_gpio_port_pin_t)0x0506)
#define GPIO_PORT_5_PIN_7   ((r_gpio_port_pin_t)0x0507)
#define GPIO_PORT_6_PIN_0   ((r_gpio_port_pin_t)0x0600)
#define GPIO_PORT_6_PIN_1   ((r_gpio_port_pin_t)0x0601)
#define GPIO_PORT_6_PIN_2   ((r_gpio_port_pin_t)0x0602)
#define GPIO_PORT_6_PIN_3   ((r_gpio_port_pin_t)0x0603)
#define GPIO_PORT_6_PIN_4   ((r_gpio_port_pin_t)0x0604)
#define GPIO_PORT_6_PIN_5   ((r_gpio_port_pin_t)0x0605)
#define GPIO_PORT_6_PIN_6   ((r_gpio_port_pin_t)0x0606)
#define GPIO_PORT_6_PIN_7   ((r_gpio_port_pin_t)0x0607)
#define GPIO_PORT_7_PIN_0   ((r_gpio_port_pin_t)0x0700)
#define GPIO_PORT_7_PIN_1   ((r_gpio_port_pin_t)0x0701)
#define GPIO_PORT_7_PIN_2   ((r_gpio_port_pin_t)0x0702)
#define GPIO_PORT_7_PIN_3   ((r_gpio_port_pin_t)0x0703)
#define GPIO_PORT_7_PIN_4   ((r_gpio_port_pin_t)0x0704)
#define GPIO_PORT_7_PIN_5   ((r_gpio_port_pin_t)0x0705)
#define GPIO_PORT_7_PIN_6   ((r_gpio_port_pin_t)0x0706)
#define GPIO_PORT_7_PIN_7   ((r_gpio_port_pin_t)0x0707)
#define GPIO_PORT_8_PIN_0   ((r_gpio_port_pin_t)0x0800)
#define GPIO_PORT_8_PIN_1   ((r_gpio_port_pin_t)0x0801)
#define GPIO_PORT_8_PIN_2   ((r_gpio_port_pin_t)0x0802)
#define GPIO_PORT_8_PIN_3   ((r_gpio_port_pin_t)0x0803)
#define GPIO_PORT_8_PIN_4   ((r_gpio_port_pin_t)0x0804)
#define GPIO_PORT_8_PIN_5   ((r_gpio_port_pin_t)0x0805)
#define GPIO_PORT_8_PIN_6   ((r_gpio_port_pin_t)0x0806)
#define GPIO_PORT_8_PIN_7   ((r_gpio_port_pin_t)0x0807)
#define GPIO_PORT_9_PIN_0   ((r_gpio_port_pin_t)0x0900)
#define GPIO_PORT_9_PIN_1   ((r_gpio_port_pin_t)0x0901)
#define GPIO_PORT_9_PIN_2   ((r_gpio_port_pin_t)0x0902)
#define GPIO_PORT_9_PIN_3   ((r_gpio_port_pin_t)0x0903)
#define GPIO_PORT_9_PIN_4   ((r_gpio_port_pin_t)0x0904)
#define GPIO_PORT_9_PIN_5   ((r_gpio_port_pin_t)0x0905)
#define GPIO_PORT_9_PIN_6   ((r_gpio_port_pin_t)0x0906)
#define GPIO_PORT_9_PIN_7   ((r_gpio_port_pin_t)0x0907)
#define GPIO_PORT_A_PIN_0   ((r_gpio_port_pin_t)0x0A00)
#define GPIO_PORT_A_PIN_1   ((r_gpio_port_pin_t)0x0A01)
#define GPIO_PORT_A_PIN_2   ((r_gpio_port_pin_t)0x0A02)
#define GPIO_PORT_A_PIN_3   ((r_gpio_port_pin_t)0x0A03)
#define GPIO_PORT_A_PIN_4   ((r_gpio_port_pin_t)0x0A04)
#define GPIO_PORT_A_PIN_5   ((r_gpio_port_pin_t)0x0A05)
#define GPIO_PORT_A_PIN_6   ((r_gpio_port_pin_t)0x0A06)
#define GPIO_PORT_A_PIN_7   ((r_gpio_port_pin_t)0x0A07)
#define GPIO_PORT_B_PIN_0   ((r_gpio_port_pin_t)0x0B00)
#define GPIO_PORT_B_PIN_1   ((r_gpio_port_pin_t)0x0B01)
#define GPIO_PORT_B_PIN_2   ((r_gpio_port_pin_t)0x0B02)
#define GPIO_PORT_B_PIN_3   ((r_gpio_port_pin_t)0x0B03)
#define GPIO_PORT_B_PIN_4   ((r_gpio_port_pin_t)0x0B04)
#define GPIO_PORT_B_PIN_5   ((r_gpio_port_pin_t)0x0B05)
#define GPIO_PORT_C_PIN_0   ((r_gpio_port_pin_t)0x0C00)
#define GPIO_PORT_C_PIN_1   ((r_gpio_port_pin_t)0x0C01)
#define GPIO_PORT_C_PIN_2   ((r_gpio_port_pin_t)0x0C02)
#define GPIO_PORT_C_PIN_3   ((r_gpio_port_pin_t)0x0C03)
#define GPIO_PORT_C_PIN_4   ((r_gpio_port_pin_t)0x0C04)
#define GPIO_PORT_C_PIN_5   ((r_gpio_port_pin_t)0x0C05)
#define GPIO_PORT_C_PIN_6   ((r_gpio_port_pin_t)0x0C06)
#define GPIO_PORT_C_PIN_7   ((r_gpio_port_pin_t)0x0C07)
#define GPIO_PORT_D_PIN_0   ((r_gpio_port_pin_t)0x0D00)
#define GPIO_PORT_D_PIN_1   ((r_gpio_port_pin_t)0x0D01)
#define GPIO_PORT_D_PIN_2   ((r_gpio_port_pin_t)0x0D02)
#define GPIO_PORT_D_PIN_3   ((r_gpio_port_pin_t)0x0D03)
#define GPIO_PORT_D_PIN_4   ((r_gpio_port_pin_t)0x0D04)
#define GPIO_PORT_D_PIN_5   ((r_gpio_port_pin_t)0x0D05)
#define GPIO_PORT_D_PIN_6   ((r_gpio_port_pin_t)0x0D06)
#define GPIO_PORT_D_PIN_7   ((r_gpio_port_pin_t)0x0D07)
#define GPIO_PORT_E_PIN_0   ((r_gpio_port_pin_t)0x0E00)
#define GPIO_PORT_E_PIN_1   ((r_gpio_port_pin_t)0x0E01)
#define GPIO_PORT_E_PIN_2   ((r_gpio_port_pin_t)0x0E02)
#define GPIO_PORT_E_PIN_3   ((r_gpio_port_pin_t)0x0E03)
#define GPIO_PORT_E_PIN_4   ((r_gpio_port_pin_t)0x0E04)
#define GPIO_PORT_E_PIN_5   ((r_gpio_port_pin_t)0x0E05)
#define GPIO_PORT_E_PIN_6   ((r_gpio_port_pin_t)0x0E06)
#define GPIO_PORT_F_PIN_0   ((r_gpio_port_pin_t)0x0F00)
#define GPIO_PORT_F_PIN_1   ((r_gpio_port_pin_t)0x0F01)
#define GPIO_PORT_F_PIN_2   ((r_gpio_port_pin_t)0x0F02)
#define GPIO_PORT_F_PIN_3   ((r_gpio_port_pin_t)0x0F03)
#define GPIO_PORT_F_PIN_4   ((r_gpio_port_pin_t)0x0F04)
#define GPIO_PORT_F_PIN_5   ((r_gpio_port_pin_t)0x0F05)
#define GPIO_PORT_F_PIN_6   ((r_gpio_port_pin_t)0x0F06)
#define GPIO_PORT_F_PIN_7   ((r_gpio_port_pin_t)0x0F07)
#define GPIO_PORT_G_PIN_0   ((r_gpio_port_pin_t)0x1000)
#define GPIO_PORT_G_PIN_1   ((r_gpio_port_pin_t)0x1001)
#define GPIO_PORT_G_PIN_2   ((r_gpio_port_pin_t)0x1002)
#define GPIO_PORT_G_PIN_3   ((r_gpio_port_pin_t)0x1003)
#define GPIO_PORT_G_PIN_4   ((r_gpio_port_pin_t)0x1004)
#define GPIO_PORT_G_PIN_5   ((r_gpio_port_pin_t)0x1005)
#define GPIO_PORT_G_PIN_6   ((r_gpio_port_pin_t)0x1006)
#define GPIO_PORT_G_PIN_7   ((r_gpio_port_pin_t)0x1007)
#define GPIO_PORT_H_PIN_0   ((r_gpio_port_pin_t)0x1100)
#define GPIO_PORT_H_PIN_1   ((r_gpio_port_pin_t)0x1101)
#define GPIO_PORT_H_PIN_2   ((r_gpio_port_pin_t)0x1102)
#define GPIO_PORT_H_PIN_3   ((r_gpio_port_pin_t)0x1103)
#define GPIO_PORT_H_PIN_4   ((r_gpio_port_pin_t)0x1104)
#define GPIO_PORT_H_PIN_5   ((r_gpio_port_pin_t)0x1105)
#define GPIO_PORT_H_PIN_6   ((r_gpio_port_pin_t)0x1106)
#define GPIO_PORT_J_PIN_0   ((r_gpio_port_pin_t)0x1200)
#define GPIO_PORT_J_PIN_1   ((r_gpio_port_pin_t)0x1201)
#define GPIO_PORT_J_PIN_2   ((r_gpio_port_pin_t)0x1202)
#define GPIO_PORT_J_PIN_3   ((r_gpio_port_pin_t)0x1203)
#define GPIO_PORT_J_PIN_4   ((r_gpio_port_pin_t)0x1204)
#define GPIO_PORT_J_PIN_5   ((r_gpio_port_pin_t)0x1205)
#define GPIO_PORT_J_PIN_6   ((r_gpio_port_pin_t)0x1206)
#define GPIO_PORT_J_PIN_7   ((r_gpio_port_pin_t)0x1207)
#define GPIO_PORT_K_PIN_0   ((r_gpio_port_pin_t)0x1300)
#define GPIO_PORT_K_PIN_1   ((r_gpio_port_pin_t)0x1301)
#define GPIO_PORT_K_PIN_2   ((r_gpio_port_pin_t)0x1302)
#define GPIO_PORT_K_PIN_3   ((r_gpio_port_pin_t)0x1303)
#define GPIO_PORT_K_PIN_4   ((r_gpio_port_pin_t)0x1304)
#define GPIO_PORT_K_PIN_5   ((r_gpio_port_pin_t)0x1305)
#define GPIO_PORT_L_PIN_0   ((r_gpio_port_pin_t)0x1400)
#define GPIO_PORT_L_PIN_1   ((r_gpio_port_pin_t)0x1401)
#define GPIO_PORT_L_PIN_2   ((r_gpio_port_pin_t)0x1402)
#define GPIO_PORT_L_PIN_3   ((r_gpio_port_pin_t)0x1403)
#define GPIO_PORT_L_PIN_4   ((r_gpio_port_pin_t)0x1404)
#define GPIO_JPORT_0_PIN_0  ((r_gpio_port_pin_t)0x1500)
#define GPIO_JPORT_0_PIN_1  ((r_gpio_port_pin_t)0x1501)
#define GPIO_PORT_PIN_MAX   ((r_gpio_port_pin_t)0x7FFF)

#define GPIO_DEDICATED_PIN_MIN   ((r_gpio_port_pin_t)0x8000)
#define GPIO_PIN_CKIO        ((r_gpio_port_pin_t)0x8000)
#define GPIO_PIN_SD0_ALL     ((r_gpio_port_pin_t)0x81FF)
#define GPIO_PIN_SD0_CLK     ((r_gpio_port_pin_t)0x8100)
#define GPIO_PIN_SD0_CMD     ((r_gpio_port_pin_t)0x8101)
#define GPIO_PIN_SD0_DAT0    ((r_gpio_port_pin_t)0x8102)
#define GPIO_PIN_SD0_DAT1    ((r_gpio_port_pin_t)0x8103)
#define GPIO_PIN_SD0_DAT2    ((r_gpio_port_pin_t)0x8104)
#define GPIO_PIN_SD0_DAT3    ((r_gpio_port_pin_t)0x8105)
#define GPIO_PIN_SD0_DAT4    ((r_gpio_port_pin_t)0x8106)
#define GPIO_PIN_SD0_DAT5    ((r_gpio_port_pin_t)0x8107)
#define GPIO_PIN_SD0_DAT6    ((r_gpio_port_pin_t)0x8108)
#define GPIO_PIN_SD0_DAT7    ((r_gpio_port_pin_t)0x8109)
#define GPIO_PIN_SD0_RST     ((r_gpio_port_pin_t)0x810A)
#define GPIO_PIN_SD1_ALL     ((r_gpio_port_pin_t)0x82FF)
#define GPIO_PIN_SD1_CLK     ((r_gpio_port_pin_t)0x8200)
#define GPIO_PIN_SD1_CMD     ((r_gpio_port_pin_t)0x8201)
#define GPIO_PIN_SD1_DAT0    ((r_gpio_port_pin_t)0x8202)
#define GPIO_PIN_SD1_DAT1    ((r_gpio_port_pin_t)0x8203)
#define GPIO_PIN_SD1_DAT2    ((r_gpio_port_pin_t)0x8204)
#define GPIO_PIN_SD1_DAT3    ((r_gpio_port_pin_t)0x8205)
#define GPIO_PIN_SPIBSC_ALL  ((r_gpio_port_pin_t)0x83FF)
#define GPIO_PIN_QSPI0_SPCLK ((r_gpio_port_pin_t)0x8300)
#define GPIO_PIN_QSPI0_IO0   ((r_gpio_port_pin_t)0x8301)
#define GPIO_PIN_QSPI0_IO1   ((r_gpio_port_pin_t)0x8302)
#define GPIO_PIN_QSPI0_IO2   ((r_gpio_port_pin_t)0x8303)
#define GPIO_PIN_QSPI0_IO3   ((r_gpio_port_pin_t)0x8304)
#define GPIO_PIN_QSPI0_SSL   ((r_gpio_port_pin_t)0x8305)
#define GPIO_PIN_RPC_RESET   ((r_gpio_port_pin_t)0x8306)
#define GPIO_PIN_RPC_WP      ((r_gpio_port_pin_t)0x8307)
#define GPIO_PIN_QSPI1_SPCLK ((r_gpio_port_pin_t)0x8308)
#define GPIO_PIN_QSPI1_IO0   ((r_gpio_port_pin_t)0x8309)
#define GPIO_PIN_QSPI1_IO1   ((r_gpio_port_pin_t)0x830A)
#define GPIO_PIN_QSPI1_IO2   ((r_gpio_port_pin_t)0x830B)
#define GPIO_PIN_QSPI1_IO3   ((r_gpio_port_pin_t)0x830C)
#define GPIO_PIN_QSPI1_SSL   ((r_gpio_port_pin_t)0x830D)
#define GPIO_PIN_MASK        ((r_gpio_port_pin_t)0x00FF)
#define GPIO_NOT_ALLOCATE    ((r_gpio_port_pin_t)0x7FFF)


/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/


/******************************************************************************
Functions Prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @brief   Hardware initialise
 *          Initialise the hardware
 * @retval  DRV_SUCCESS Always returned
 */
extern int_t R_GPIO_HWInitialise(void);

/**
 * @brief   Hardware uninitialise
 *          Uninitialise the hardware
 * @retval  DRV_SUCCESS Always returned
 */
extern int_t R_GPIO_HWUninitialise(void);

/**
 * @brief      Pin configuration set
 *             Set single pin configuration
 * @param[in]  p_config: configuration data
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinSetConfiguration(const st_r_drv_gpio_sc_config_t * p_config);

/**
 * @brief      Pin configuration get
 *             Get current pin setting
 * @param[in]  p_config->pin: the pin to get the current setting
 * @param[out] p_config->configuration: the setting
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinGetConfiguration(st_r_drv_gpio_sc_config_t * p_config);

/**
 * @brief      Initialise pins by pin list
 *             Set pin configuration by a pin list and locks the pins.
 *             Pin configuration is retrieved from the Smart Configurator table.
 * @param[in]  p_pin_list: the pin list to initialise
 * @param[in]  count: counts of the pins
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_InitByPinList(const r_gpio_port_pin_t * p_pin_list, uint32_t count);

/**
 * @brief      Clear the pins by pin list
 *             Release pins by a pin list and unlocks the pins.
 * @param[in]  p_pin_list: the pin list to clear
 * @param[in]  count: counts of the pins
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_ClearByPinList(const r_gpio_port_pin_t * p_pin_list, uint32_t count);

/**
 * @brief      Pin configuration set by SC table
 *             Optional Set a group of pins using an array of pin configurations.
 *             This function locks the pins.
 * @param[in]  p_table: the configuration list to initialise
 * @param[in]  count: counts of the pins
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_InitByTable(const st_r_drv_gpio_sc_config_t * p_table, uint32_t count);

/**
 * @brief      Clear the pins by SC table
 *             Optional release a group pins using an array of pin configurations.
 *             This function unlocks the pins.
 * @param[in]  p_table: the configuration list to clear (only using the pin number)
 * @param[in]  count: counts of the pins
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_ClearByTable(const st_r_drv_gpio_sc_config_t * p_table, uint32_t count);

/**
 * @brief      Port write
 *             Sets the logic levels on the specified port
 * @param[in]  port: the port to set
 * @param[in]  value: the value to write
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PortWrite(r_gpio_port_t port, uint8_t value);

/**
 * @brief      Port read
 *             Reads the logic levels on the specified port
 * @param[in]  port: the port to read
 * @param[out] p_value: the value read from the port
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PortRead(r_gpio_port_t port, uint8_t * p_value );

/**
 * @brief      Port direction set
 *             Sets the specified port pins to input, output or Hi-Z
 * @param[in]  port: the port to set
 * @param[in]  dir: input, output or Hi-Z
 * @param[in]  mask: which bits are to be affected
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 * @note       This function terminates the procedure incompletely if an error occurred
 */
extern e_r_drv_gpio_err_t R_GPIO_PortDirectionSet(r_gpio_port_t port, e_r_drv_gpio_dir_t dir, uint8_t mask);

/**
 * @brief      Pin write
 *             Sets the logic level on the specified pin
 * @param[in]  pin: the pin to set
 * @param[in]  level: high or low
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinWrite(r_gpio_port_pin_t pin, e_r_drv_gpio_level_t level);

/**
 * @brief      Pin read
 *             Reads the logic level on the specified pin
 * @param[in]  pin: the pin to read
 * @param[out] p_level: the logic level read from the pin
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinRead(r_gpio_port_pin_t pin, e_r_drv_gpio_level_t * p_level);

/**
 * @brief      Pin direction set
 *             Sets the specified pin to input, output or Hi-Z
 * @param[in]  pin: the pin to set
 * @param[in]  dir: the direction: input, output, or Hi-Z
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinDirectionSet(r_gpio_port_pin_t pin, e_r_drv_gpio_dir_t dir);

/**
 * @brief      Pin direction get
 *             Gets the specified pin direction setting (input, output or Hi-Z)
 * @param[in]  pin: the pin to interrogate
 * @param[out] p_dir: the direction read for the pin: input, output, or Hi-Z
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinDirectionGet(r_gpio_port_pin_t pin, e_r_drv_gpio_dir_t * p_dir);

/**
 * @brief      Pin assignment set
 *             Assigns a pin to GPIO or to a peripheral
 * @param[in]  pin: the pin to assign
 * @param[in]  assignment: how to assign the pin:
 *                 GPIO_ASSIGN_TO_PERIPHERAL or GPIO_ASSIGN_TO_GPIO
 * @retval     GPIO_SUCCESS or the error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinAssignmentSet(r_gpio_port_pin_t pin, e_r_drv_gpio_assign_t assignment);

/**
 * @brief      Pin assignment get
 *             Get pin assignment: GPIO or peripheral
 * @param[in]  pin: the pin to get the current assignment setting
 * @param[out] p_assignment: set to either:
 *                 GPIO_ASSIGN_TO_PERIPHERAL or GPIO_ASSIGN_TO_GPIO
 * @retval     GPIO_SUCCESS  Successful operation
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinAssignmentGet(r_gpio_port_pin_t pin, e_r_drv_gpio_assign_t * p_assignment);

/**
 * @brief      Pin TINT set
 *             Turns interrupts on or off for a pin
 * @param[in]  pin: the pin to set the interrupts for
 * @param[in]  tint: whether to enable or disable interrupts:
 *                 GPIO_TINT_ENABLE or GPIO_TINT_DISABLE
 * @retval     GPIO_SUCCESS or the error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinTintSet(r_gpio_port_pin_t pin, e_r_drv_gpio_tint_t tint);

/**
 * @brief      Pin TINT get
 *             Reads interrupt on / off setting for a pin
 * @param[in]  pin: the pin to get the interrupts for
 * @param[out] p_tint: the interrupt setting
 *                 GPIO_TINT_ENABLE or GPIO_TINT_DISABLE
 * @retval     GPIO_SUCCESS or the error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinTintGet(r_gpio_port_pin_t pin, e_r_drv_gpio_tint_t * p_tint);

/**
 * @brief      Pin DSCR set
 *             Sets pin DSCR current to 4mA or 8mA
 * @param[in]  pin: the pin to set the DSCR for
 * @param[in]  current: the current to set:
 *                 GPIO_CURRENT_4mA or GPIO_CURRENT_8mA
 * @retval     GPIO_SUCCESS or the error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinDscrSet(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t current);

/**
 * @brief      Pin DSCR get
 *             Gets pin DSCR current setting (4mA or 8mA)
 * @param[in]  pin: the pin to get the DSCR for
 * @param[out] p_current: the current current setting:
 *                 GPIO_CURRENT_4mA or GPIO_CURRENT_8mA
 * @retval     GPIO_SUCCESS or the error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinDscrGet(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t *p_current);

/**
 * @brief      Peripheral function write
 *             Sets the peripheral function for a pin
 * @param[in]  pin: the pin to set
 * @param[in]  psel: the code for the required peripheral function
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PeripheralFunctionWrite(r_gpio_port_pin_t pin, uint8_t psel);

/**
 * @brief      Peripheral function read
 *             Gets the current peripheral function setting for a pin
 * @param[in]  pin: the pin to interrogate for the peripheral function setting
 * @param[out] p_psel: set to the code of the current peripheral function
 * @retval     GPIO_SUCCESS  Successful operation.
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PeripheralFunctionRead(r_gpio_port_pin_t pin, uint8_t *p_psel);

/**
 * @brief      R_GPIO_PinSetFunction
 *             Set the function of the specified pin
 * @param[in]  port_pin: the pin to set
 * @param[in]  function: which function to configure
 * @retval     GPIO_SUCCESS  Successful operation
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinSetFunction(r_gpio_port_pin_t port_pin, e_r_drv_gpio_function_t function);

/**
 * @brief      R_GPIO_PinGetFunction
 *             Get the function of the specified pin
 * @param[in]  port_pin: the pin to get
 * @param[out] p_function: set to the current pin function
 * @retval     GPIO_SUCCESS  Successful operation
 * @retval     error_code    The error code on failure
 */
extern e_r_drv_gpio_err_t R_GPIO_PinGetFunction(r_gpio_port_pin_t port_pin, e_r_drv_gpio_function_t *p_function);

/**
 * @brief       Get version
 *              Gets the version number of this low-level driver
 * @param[out]  p_ver_info: returns the driver information
 * @retval      DRV_SUCCESS Always returned
 */
extern int_t R_GPIO_GetVersion(st_ver_info_t *p_ver_info);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* R_GPIO_LLD_RZA2M_H_ */


/* End of File */
