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
 * @headerfile     r_scifa_hld_prv.h
 * @brief          SCIFA High level driver private header
 * @version        1.00
 * @date           15.05.2018
 *******************************************************************************/
/*******************************************************************************
 * History       : DD.MM.YYYY Version Description
 *               :
 *******************************************************************************/
#ifndef SRC_RENESAS_AUTOMATED_TEST_R_SCIFA_INC_R_SCIFA_HLD_PRV_H_
#define SRC_RENESAS_AUTOMATED_TEST_R_SCIFA_INC_R_SCIFA_HLD_PRV_H_

#include "r_scifa_drv_sc_cfg.h"     /* Smart Configurator Settings*/

/******************************************************************************
 Functions Prototypes
 ******************************************************************************/

/**
 * @brief r_scifa_hld_prv_open opens the SCIFA device driver.
 *
 * Configures the SCIFA channel, transmission and reception buffer depending on
 * the smart configurator.
 *
 * @param[in]  channel Channel to open.
 * @param[in]  file_mode File mode for R/W access.
 *
 * @retval 0  Success
 * @retval -1 Fail
 */
int_t r_scifa_hld_prv_open(int_t channel, int_t file_mode);

/**
 * @brief r_scifa_hld_prv_close closes the SCIFA device driver
 *
 * The close function destroys the resources used in opening
 * a channel.
 *
 * @param[in] channel Channel to close.
 *
 * @return None.
 *
*/
void  r_scifa_hld_prv_close(int_t channel);

/**
 * @brief r_scifa_hld_prv_read reads data from the SCIFA
 *
 * This function reads the data received from the chosen channel
 * and stores it in the passed by reference buffer.
 *
 * @param[in] channel Channel to read from.
 *
 * @param[out] p_buffer Buffer used to store data.
 *
 * @param[in] max_count Max amount of bytes to be read.
 *
 * @retval  N Where N is the number of bytes read
 * @retval -1 Fail
*/
int_t r_scifa_hld_prv_read(int_t channel, uint8_t *p_buffer, uint32_t max_count);

/**
 * @brief r_scifa_hld_prv_write writes data to the SCIFA device.
 *
 * Contains a state machine to handle writing when the SCIFA,
 * is closed, Running, idle or broken.
 *
 * @param[in] channel Channel to be written to.
 *
 * @param[in] p_buffer Buffer of data to be written
 *
 * @param[in] ui_count Number of bytes to be written.
 *
 * @retval 0  Success
 * @retval -1 Fail
*/
int_t r_scifa_hld_prv_write(int_t channel, const uint8_t *p_buffer, uint32_t ui_count);

/**
 * @brief r_scifa_hld_prv_set_config sets SCIFA configuration.
 *
 * This function configures and starts the SCIFA.
 *
 * @param[in] channel Channel to configure.
 *
 * @param[in] p_config The data to be used to configure the channel.
 *
 * @param[in] file_mode The required file mode (read, write etc.)
 *
 * @retval 0  Success
 * @retval -1 Fail
 */
int_t r_scifa_hld_prv_set_config(int_t channel, scifa_config_t* p_config, int_t file_mode);

/**
 * @brief r_scifa_hld_prv_get_config Retrieves the current configuration
 * of the SCIFA driver.
 *
 * Allows for the reading of current SCIFA settings. This allows for safe
 * changes to the current config of the SCIFA.
 *
 * @param[in] channel:   Channel to get configuration for.
 * @param[out] p_config: Configuration struct to populate with
 *                       retrieved configuration.
 *
 * @retval  0 Success
 * @retval -1 Fail
*/
int_t r_scifa_hld_prv_get_config(int_t channel, scifa_config_t* p_config);

int_t r_scifa_hld_dma_read_abort(int_t channel);
int_t r_scifa_hld_dma_write_abort(int_t channel);
int_t r_scifa_hld_dma_read_next(int_t channel, st_scifa_dma_rw_t *read_next);
int_t r_scifa_hld_dma_write_next(int_t channel, st_scifa_dma_rw_t *write_next);

#endif /* SRC_RENESAS_AUTOMATED_TEST_R_SCIFA_INC_R_SCIFA_HLD_PRV_H_ */
