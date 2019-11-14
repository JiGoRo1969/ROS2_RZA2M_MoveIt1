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
 * File Name    : r_rza2m_riic_lld_api.h
 * Description  : RIIC Low level API header
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_typedefs.h"
#include "r_rza2m_riic_lld_cfg.h"

#ifndef SRC_RENESAS_DRIVERS_R_RIIC_INC_R_RIIC_LLD_RZA2M_API_H_
    #define SRC_RENESAS_DRIVERS_R_RIIC_INC_R_RIIC_LLD_RZA2M_API_H_

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/** Version Number of API. */
    #define STDIO_RIIC_RZ_LLD_DRV_NAME ("LLD EBK_RZA2M RIIC")
/** Major Version Number of API. */
    #define STDIO_RIIC_RZ_LLD_VERSION_MAJOR      (1)
/** Minor Version Number of API. */
    #define STDIO_RIIC_RZ_LLD_VERSION_MINOR      (1)
/** Minor Version Number of API. */
    #define STDIO_RIIC_RZ_LLD_BUILD_NUM          (0)
/** Unique ID. */
    #define STDIO_RIIC_RZ_LLD_UID                (55)

    #define RIIC_MODE_SLAVE_IMPLEMENTED  (0)  /* Compiling switch in implementing slave mode */
    #define RIIC_ADRESS_10_IMPLEMENTED   (0)  /* Compiling switch in implementing slave mode */

/* Total channels supported */
    #define R_CFG_RIIC_DRV_CHANNELS_AVAIL_PRV    (4)

/******************************************************************************
 Typedef definitions
 ******************************************************************************/

typedef enum
{
    RIIC_SUB_ADDR_NONE = 0, /*!< No sub-address to be provided (not required or using internal pointer) */
    RIIC_SUB_ADDR_WIDTH_8_BITS = 1, /*!< 8-bit address to be provided */
    RIIC_SUB_ADDR_WIDTH_16_BITS = 2, /*!< 16-bit address to be provided */
    RIIC_SUB_ADDR_WIDTH_32_BITS = 3, /*!< 32-bit address to be provided */
    RIIC_SUB_ADDR_MAX = 4
} e_riic_sub_addr_type_t;

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpadded"
typedef struct r_drv_riic_transfer_t
{
        uint16_t               device_address; /*!< Device I2C address */
        e_riic_sub_addr_type_t sub_address_type; /*!< addressing mode for transfer */
        uint32_t               sub_address; /*!< Start address of registers to access in device */
        uint32_t               number_of_bytes; /*!< Number of bytes to read or write */
        uint8_t                *p_data_buffer; /*!< Pointer to source/destination buffer */
} st_r_drv_riic_transfer_t;
    #pragma GCC diagnostic pop

    #if (RIIC_MODE_SLAVE_IMPLEMENTED == 1)
typedef enum
{
    RIIC_MODE_MASTER = 0, /*!< Select Master mode */
    RIIC_MODE_SLAVE = 1, /*!< Select Slave mode */
    RIIC_MODE_MAX = 2
}e_riic_mode_t;
    #else
typedef enum
{
    RIIC_MODE_MASTER = 0, /*!< Select Master mode */
    RIIC_MODE_MAX = 1
} e_riic_mode_t;
    #endif

    #if (RIIC_ADRESS_10_IMPLEMENTED == 1)
typedef enum
{
    RIIC_DEVICE_ADDR_7 = 0, /*!< 7bit address format */
    RIIC_DEVICE_ADDR_10 = 1, /*!< 10bit address format */
    RIIC_DEVICE_ADDR_MAX = 2
}e_riic_device_addr_len_t;
    #else
typedef enum
{
    RIIC_DEVICE_ADDR_7 = 0, /*!< 7bit address format */
    RIIC_DEVICE_ADDR_MAX = 1
} e_riic_device_addr_len_t;
    #endif

typedef enum
{
    RIIC_FREQUENCY_100KHZ = 0, /*!< 100kHz clock frequency */
    RIIC_FREQUENCY_400KHZ = 1, /*!< 400kHz clock frequency */
    RIIC_FREQUENCY_1MHZ = 2, /*!< 1MHz clock frequency */
    RIIC_FREQUENCY_MAX = 3
} e_riic_clk_frequency_t;

typedef enum
{
    RIIC_SLAVE_ADDR_NUM_0 = 0, /* Own slave address number = 0 */
    RIIC_SLAVE_ADDR_NUM_1 = 1, /* Own slave address number = 1 */
    RIIC_SLAVE_ADDR_NUM_2 = 2, /* Own slave address number = 2 */
    RIIC_SLAVE_ADDR_NUM_MAX = 3
} e_riic_slave_addr_num_t;

typedef enum
{
    RIIC_DUTY_10 = 0, /*!< Duty Cycle 10%*/
    RIIC_DUTY_20 = 1, /*!< Duty Cycle 20%*/
    RIIC_DUTY_30 = 2, /*!< Duty Cycle 30%*/
    RIIC_DUTY_40 = 3, /*!< Duty Cycle 40%*/
    RIIC_DUTY_50 = 4, /*!< Duty Cycle 50%*/
    RIIC_DUTY_60 = 5, /*!< Duty Cycle 60%*/
    RIIC_DUTY_70 = 6, /*!< Duty Cycle 70%*/
    RIIC_DUTY_80 = 7, /*!< Duty Cycle 80%*/
    RIIC_DUTY_90 = 8, /*!< Duty Cycle 90%*/
    RIIC_DUTY_MAX = 9
} e_riic_clk_duty_t;

typedef enum
{
    RIIC_FILTER_NOT_USED = 0, /*!< Filter not used */
    RIIC_FILTER_STAGE_1 = 1, /*!< Noise Filter 1stag e*/
    RIIC_FILTER_STAGE_2 = 2, /*!< Noise Filter 2stage */
    RIIC_FILTER_STAGE_3 = 3, /*!< Noise Filter 3stage */
    RIIC_FILTER_STAGE_4 = 4, /*!< Noise Filter 4stage */
    RIIC_FILTER_STAGE_MAX = 5
} e_riic_filter_t;

typedef enum
{
    RIIC_TIMEOUT_NOT_USED = 0, /*!< Timeout not used */
    RIIC_TIMEOUT_LONG = 1, /*!< Use timeout counter of Long mode */
    RIIC_TIMEOUT_SHORT = 2, /*!< Use timeout counter of Short mode */
    RIIC_TIMEOUT_MAX = 3
} e_riic_timeout_t;

typedef enum
{
    RIIC_FORMAT_I2C = 0, /*!< RIIC Format */
    RIIC_FORMAT_SMBUS = 1, /*!< SMBUS Format */
    RIIC_FORMAT_MAX = 2
} e_riic_format_t;

/* RIIC init structure with smart configurator */
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpadded"
typedef struct
{
        e_riic_mode_t            riic_mode; /*!< Select Master mode or Slave mode*/
        bool_t                   slave_address_enable[RIIC_SLAVE_ADDR_NUM_MAX]; /*!< Select Slave mode enable or disable on Slave mode*/
        uint16_t                 slave_address[RIIC_SLAVE_ADDR_NUM_MAX]; /*!< Own Slave address on Slave mode*/
        e_riic_device_addr_len_t slave_address_length[RIIC_SLAVE_ADDR_NUM_MAX]; /*!< Select Slave address (7bit or 10bit) length on Slave mode*/
        e_riic_clk_frequency_t   frequency; /*!< Select RIIC frequency*/
        e_riic_clk_duty_t        duty; /*!< Select Duty cycle*/
        uint32_t                 rise_time; /*!< Delay time of SCL rise time (value dependent on board circuit design)*/
        uint32_t                 fall_time; /*!< Delay time of SCL fall time (value dependent on board circuit design)*/
        e_riic_filter_t          noise_filter_stage; /*!< Select noise filter stages*/
        e_riic_timeout_t         timeout; /*!< Select timeout*/
        e_riic_format_t          format; /*!< Select bus format */
        bool_t                   host_address_enabled; /*!< Detection of host address enable or disable */
        uint8_t                  tei_priority; /*!< Set transfer end interrupt priority*/
        uint8_t                  ri_priority; /*!<  Set receive data full interrupt priority*/
        uint8_t                  ti_priority; /*!< Set transfer empty interrupt priority*/
        uint8_t                  spi_priority; /*!< Set detection of stop condition interrupt priority*/
        uint8_t                  sti_priority; /*!< Set detection of start condition interrupt priority*/
        uint8_t                  naki_priority; /*!< Set receive NACK interrupt priority*/
        uint8_t                  ali_priority; /*!< Set arbitration interrupt priority*/
        uint8_t                  tmoi_priority; /*!< Set SCL timeout interrupt priority*/
} st_riic_config_t;
    #pragma GCC diagnostic pop
/******************************************************************************
 Variable Externs
 ******************************************************************************/

/******************************************************************************
 Functions Prototypes
 ******************************************************************************/
/* ==== Functional Methods ==== */

/**
 * @brief R_RIIC_ScInitChannel Initialises a channel for set up with smart configurator parameters.
 *
 * This function configures device registers in preparation for
 * configuration with smart configurator parameters.
 *
 * @param[in] sc_config_index Index number of RIIC Initialization channel.
 * @param[in] pclk_frequency PCLK frequency for RIIC.
 *
 * @retval   0 DRV_SUCCESS
 * @retval  -1 DRV_ERROR
 */
int_t R_RIIC_ScInitChannel (int_t sc_config_index, uint32_t pclk_frequency);

/**
 * @brief R_RIIC_CloseChannel Close a channel for set up
 *
 * This function shut down the device.
 *
 * @param[in] channel Close channel number of RIIC.
 *
 * @retval   none
 */
void R_RIIC_CloseChannel (int_t channel);

/**
 * @brief R_RIIC_SetConfig configuration a channel
 *
 * This function configures device registers in preparation for
 * configuration.
 *
 * @param[in] channel Initialize channel number of RIIC.
 * @param[in] *p_config Configuration parameter.
 *
 * @retval   0 DRV_SUCCESS
 * @retval  -1 DRV_ERROR
 */
int_t R_RIIC_SetConfig (int_t channel, st_riic_config_t *p_cfg);

/**
 * @brief R_RIIC_GetConfig configuration a channel
 *
 * This function gets the parameters set in RIIC.
 *
 * @param[in] channel Target channel number of RIIC.
 * @param[in] *p_config RIIC configure parameter.
 *
 * @retval   0 DRV_SUCCESS
 * @retval  -1 DRV_ERROR
 */
int_t R_RIIC_GetConfig (int_t channel, st_riic_config_t *p_cfg);

/**
 * @brief R_RIIC_TransmitStop Issues Stop Condition on the RIIC.
 *
 * @param[in] channel Channel number to issue a Stop Condition.
 *
 * @retval  none
 */
void R_RIIC_TransmitStop (int_t channel);

/**
 * @brief R_RIIC_ClearStop Clear bit of detecting Stop Condition on the RIIC.
 *
 * @param[in] channel Channel number to clear bit of detecting Stop Condition.
 *
 * @retval  none
 */
void R_RIIC_ClearStop (int_t channel);

/**
 * @brief R_RIIC_TransmitStart Issues Start Condition on the RIIC.
 *
 * @param[in] channel Channel number to issue a Start Condition.
 *
 * @retval  none
 */
void R_RIIC_TransmitStart (int_t channel);

/**
 * @brief R_RIIC_TransmitRestart Issues Restart Condition on the RIIC.
 *
 * @param[in] channel Channel number to issue a Restart Condition.
 *
 * @retval  none
 */
void R_RIIC_TransmitRestart (int_t channel);

/**
 * @brief R_RIIC_ClearNack Clear bit of detecting NACK on the RIIC.
 *
 * @param[in] channel Channel number to clear bit of detecting NACK.
 *
 * @retval  none
 */
void R_RIIC_ClearNack (int_t channel);

/**
 * @brief R_RIIC_GetAckStatus Get the ACK state for a channel.

 * This function will get the ACK status on a channel with RI interrupt event.
 *
 * @param[in] channel  Channel to check ACK status.
 *
 * @retval  0 Received ACK
 * @retval  1 Received NACK
 */
uint8_t R_RIIC_GetAckStatus (int_t channel);

/**
 * @brief R_RIIC_TransmitAck Set to send ACK on response.
 *
 * @param[in] channel Channel number to set to send ACK.
 *
 * @retval  none
 */
void R_RIIC_TransmitAck (int_t channel);

/**
 * @brief R_RIIC_TransmitNack Set to send NACK on response.
 *
 * @param[in] channel Channel number to set to send NACK.
 *
 * @retval  none
 */
void R_RIIC_TransmitNack (int_t channel);

/**
 * @brief R_RIIC_AssertLowHold Hold the SCL in the low level.
 *
 * This function is called by HLD, and hold the SCL in the low level.
 *
 * @param[in] Channel that hold the SCL.
 *
 * @retval  none
 */
void R_RIIC_AssertLowHold (int_t channel);

/**
 * @brief R_RIIC_ReleaseLowHold release the low hold of the SCL.
 *
 * This function is called by HLD, and release the low hold of the SCL.
 *
 * @param[in] Channel that release the low hold of SCL.
 *
 * @retval  none
 */
void R_RIIC_ReleaseLowHold (int_t channel);

/**
 * @brief R_RIIC_WriteByte write to the transfer data register.
 *
 * This function is called by HLD, and write to the data register.
 *
 * @param[in] Channel that write to the data register.
 *
 * @param[in] transfer data.
 *
 * @retval  none
 */
void R_RIIC_WriteByte (int_t channel, uint8_t byte);

/**
 * @brief R_RIIC_ReadByte read transfer data from register.
 *
 * This function is called by HLD, and read transfer data from register.
 *
 * @param[in] Channel that read transfer data from register.
 *
 * @retval  0x00 - 0xFF : receive data
 */
uint8_t R_RIIC_ReadByte (int_t channel);

/**
 * @brief R_RIIC_IsBusBusy get bus busy status.
 *
 * This function is called by HLD, and get bus busy status.
 *
 * @param[in] Channel that get bus busy status.
 *
 * @retval  0 Bus Free
 * @retval  1 Bus Busy
 */
uint8_t R_RIIC_IsBusBusy (int_t channel);

/**
 * @brief R_RIIC_IsStopAsserted get detection status of STOP condition.
 *
 * This function is called by HLD, and get detection status of STOP condition.
 *
 * @param[in] Channel that get detection status of STOP condition
 *
 * @retval  0 STOP condition not detected
 * @retval  1 STOP condition detected
 */
uint8_t R_RIIC_IsStopAsserted (int_t channel);

/**
 * @brief R_RIIC_WaitSlaveAddr start waiting slave address from master device.
 *
 * This function is called by HLD, and start waiting slave address from master device.
 * Also, after calling this function, it is always in the stop condition standby state.
 *
 * @param[in] RIIC cchannel of waiting slave address
 *
 * @retval    DRV_SUCCESS: Waiting slave address is suucess
 * @retval    DRV_ERROR: Waiting slave address is duplicated
 * @retval    DRV_ERROR: Waiting slave address in master mode
 */
int_t R_RIIC_WaitSlaveAddr (int_t channel);

/**
 * @brief R_RIIC_DetectTimeoutStart start count and detection of timeout.
 *
 * This function is called by HLD, and start timeout counter.
 *
 * @param[in] Channel that start timeout counter.
 *
 * @retval  none
 */
void R_RIIC_DetectTimeoutStart (int_t channel);

/**
 * @brief R_RIIC_DetectTimeoutStop stop count and detection of timeout.
 *
 * This function is called by HLD, and stop timeout counter.
 *
 * @param[in] Channel that stop timeout counter.
 *
 * @retval  none
 */
void R_RIIC_DetectTimeoutStop (int_t channel);

/**
 * @brief R_RIIC_DetectArbitrationStart start detecting of arbitration.
 *
 * This function is called by HLD, and start detecting of arbitration.
 *
 * @param[in] Channel that start detecting arbitration.
 *
 * @retval  none
 */
void R_RIIC_DetectArbitrationStart (int_t channel);

/**
 * @brief R_RIIC_DetectArbitrationStop stop detecting of arbitration.
 *
 * This function is called by HLD, and stop detecting of arbitration.
 *
 * @param[in] Channel that stop detecting arbitration.
 *
 * @retval  none
 */
void R_RIIC_DetectArbitrationStop (int_t channel);

/**
 * @brief R_RIIC_GetSlaveAddrNum get slave address number of detectinog slave address.
 *
 * This function is called by HLD, and get slave address number of detectinog slave address.
 *
 * @param[in] Channel that get slave address number of detectinog slave address.
 *
 * @retval  0: Slave address registered in slave address0 was detected
 * @retval  1: Slave address registered in slave address1 was detected
 * @retval  2: Slave address registered in slave address2 was detected
 * @retval  RIIC_SLAVE_ADDR_NUM_MAX: Slave address wasn't detected.
 */
e_riic_slave_addr_num_t R_RIIC_GetSlaveAddrNum (int_t channel);

/*==== Extended Config Functions - defined here for LLD test purposes only, not to be used in HLD ====*/

/**
 * @brief      R_RIIC_GetVersion
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
int_t R_RIIC_GetVersion (st_ver_info_t *pVerInfo);

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    #ifdef __cplusplus
}
    #endif /* __cplusplus */

#endif /* SRC_RENESAS_DRIVERS_R_RIIC_INC_R_RIIC_LLD_RZA2M_API_H_ */

/* End of File */
