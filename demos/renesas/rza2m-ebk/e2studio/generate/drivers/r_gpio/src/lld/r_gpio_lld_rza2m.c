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
* File Name    : r_gpio_lld_rza2m.c
* Device(s)    : RZ/A2M
* Tool-Chain   : e2Studio Ver 7.4.0
*              : GCC ARM Embedded 5.4.1.20160919
* OS           : None
* H/W Platform : RZ/A2M Evaluation Board
* Description  : RZ/A2M Sample Program - Low level function of GPIO module
* Operation    :
* Limitations  :
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <string.h>
#include "r_typedefs.h"
#include "r_compiler_abstraction_api.h"
#include "r_os_abstraction_api.h"
#include "iodefine.h"
#include "iobitmask.h"
#include "r_gpio_drv_link.h"
#include "rza_io_regrw.h"
#include "r_gpio_drv_sc_cfg.h"


/******************************************************************************
Macro definitions
******************************************************************************/

/*
 * This control SHOULD be in r_gpio_drv_sc_cfg.h BUT when sc runs the contents of this file
 * is overwritten (in error), as only sections marked (This code is auto-generated. Do not edit manually)
 * should be modified. When the move to putting auto-generated table code into .c files is addressed
 * this issue shall be resolved
 */
#define GPIO_CFG_PARAM_CHECKING_ENABLE (1)

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum
{
    GPIO_NOT_IN_USE,                /*!< Not configured */
    GPIO_IN_USE,                    /*!< Configured */
} e_r_drv_gpio_inuse_t;

typedef struct
{
    volatile void * const p_reg;    /*!< Register address */
    uint8_t               shift;    /*!< bit shift */
    uint32_t              mask;     /*!< bit mask */
} st_r_reg_shift_mask_t;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/

static bool_t is_dedicated_pin(r_gpio_port_pin_t pin);

/*! Table of valid GPIO functionality */
static const uint8_t gs_r_drv_gpio_support[] =
{   /*!< implemented pins */
    0x7F, 0x1F, 0x0F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x7F, 0xFF,
    0xFF, 0x7F, 0xFF, 0x3F, 0x1F, 0x03
};

static const uint8_t gs_r_drv_gpio_dscr_8ma_support[] =
{   /*!< DSCR supported pins for 8mA */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFC, 0x00, 0x7F, 0x00, 0x00, 0x00
};

static const uint8_t gs_r_drv_gpio_dscr_4ma_support[] =
{   /*!< DSCR supported pins for 4mA */
    0x7F, 0x1F, 0x0F, 0x3F, 0xFF, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0x00, 0x7F, 0xFF,
    0xFF, 0x7F, 0xFF, 0x3F, 0x00, 0x00
};

/*! Table of "In-use" pin locking */
static uint8_t gs_r_drv_gpio_in_use[GPIO_PORT_MAX + 1] = {};

/*! LLD Version Information */
static const st_drv_info_t gs_lld_info =
{
    {
        ((GPIO_LLD_VERSION_MAJOR << 16) + GPIO_LLD_VERSION_MINOR)
    },
    GPIO_LLD_BUILD_NUM,
    GPIO_RZ_LLD_DRV_NAME
};

/*! flags for checking first time initialised */
static bool_t gs_r_drv_gpio_initialised = false;

/*! 2bit width register's (DSCR, etc) pin mask array */
static const uint32_t gs_mask_2bit_register[] =
{
    0x03uL << 0,
    0x03uL << 2,
    0x03uL << 4,
    0x03uL << 6,
    0x03uL << 8,
    0x03uL << 10,
    0x03uL << 12,
    0x03uL << 14,
    0x03uL << 16,
    0x03uL << 18,
    0x03uL << 20,
    0x03uL << 22,
    0x03uL << 24,
    0x03uL << 26,
    0x03uL << 28,
    0x03uL << 30,
};

/*! 2 bit width registers (DSCR, etc) pin shift array */
static const uint32_t gs_shift_2bit_register[] =
{
    0,
    2,
    4,
    6,
    8,
    10,
    12,
    14,
    16,
    18,
    20,
    22,
    24,
    26,
    28,
    30,
};

/*! 1 bit width registers (PMR, etc) pin mask array */
static const uint32_t gs_mask_1bit_register[] =
{
    0x01uL << 0,
    0x01uL << 1,
    0x01uL << 2,
    0x01uL << 3,
    0x01uL << 4,
    0x01uL << 5,
    0x01uL << 6,
    0x01uL << 7,
    0x01uL << 8,
    0x01uL << 9,
    0x01uL << 10,
    0x01uL << 11,
    0x01uL << 12,
    0x01uL << 13,
    0x01uL << 14,
    0x01uL << 15,
};

/*! 1 bit width registers (PMR) pin shift array */
static const uint32_t gs_shift_1bit_register[] =
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
};

/*! SDMMC0 group driver strength register table */
static const st_r_reg_shift_mask_t gs_sd0_reg[] =
{
    {&GPIO.PSDMMC0.LONG, GPIO_PSDMMC0_SD0_CLK_DRV_SHIFT,  GPIO_PSDMMC0_SD0_CLK_DRV},  /*!< GPIO_PIN_SD0_CLK */
    {&GPIO.PSDMMC0.LONG, GPIO_PSDMMC0_SD0_CMD_DRV_SHIFT,  GPIO_PSDMMC0_SD0_CMD_DRV},  /*!< GPIO_PIN_SD0_CMD */
    {&GPIO.PSDMMC0.LONG, GPIO_PSDMMC0_SD0_DAT0_DRV_SHIFT, GPIO_PSDMMC0_SD0_DAT0_DRV}, /*!< GPIO_PIN_SD0_DAT0 */
    {&GPIO.PSDMMC0.LONG, GPIO_PSDMMC0_SD0_DAT1_DRV_SHIFT, GPIO_PSDMMC0_SD0_DAT1_DRV}, /*!< GPIO_PIN_SD0_DAT1 */
    {&GPIO.PSDMMC0.LONG, GPIO_PSDMMC0_SD0_DAT2_DRV_SHIFT, GPIO_PSDMMC0_SD0_DAT2_DRV}, /*!< GPIO_PIN_SD0_DAT2 */
    {&GPIO.PSDMMC0.LONG, GPIO_PSDMMC0_SD0_DAT3_DRV_SHIFT, GPIO_PSDMMC0_SD0_DAT3_DRV}, /*!< GPIO_PIN_SD0_DAT3 */
    {&GPIO.PSDMMC1.LONG, GPIO_PSDMMC1_SD0_DAT4_DRV_SHIFT, GPIO_PSDMMC1_SD0_DAT4_DRV}, /*!< GPIO_PIN_SD0_DAT4 */
    {&GPIO.PSDMMC1.LONG, GPIO_PSDMMC1_SD0_DAT5_DRV_SHIFT, GPIO_PSDMMC1_SD0_DAT5_DRV}, /*!< GPIO_PIN_SD0_DAT5 */
    {&GPIO.PSDMMC1.LONG, GPIO_PSDMMC1_SD0_DAT6_DRV_SHIFT, GPIO_PSDMMC1_SD0_DAT6_DRV}, /*!< GPIO_PIN_SD0_DAT6 */
    {&GPIO.PSDMMC1.LONG, GPIO_PSDMMC1_SD0_DAT7_DRV_SHIFT, GPIO_PSDMMC1_SD0_DAT7_DRV}, /*!< GPIO_PIN_SD0_DAT7 */
    {&GPIO.PSDMMC1.LONG, GPIO_PSDMMC1_SD0_RSTN_DRV_SHIFT, GPIO_PSDMMC1_SD0_RSTN_DRV}, /*!< GPIO_PIN_SD0_RST */
};

/*! SDMMC1 group driver strength register table */
static const st_r_reg_shift_mask_t gs_sd1_reg[] =
{
    {&GPIO.PSDMMC2.LONG, GPIO_PSDMMC2_SD1_CLK_DRV_SHIFT,  GPIO_PSDMMC2_SD1_CLK_DRV},  /*!< GPIO_PIN_SD1_CLK */
    {&GPIO.PSDMMC2.LONG, GPIO_PSDMMC2_SD1_CMD_DRV_SHIFT,  GPIO_PSDMMC2_SD1_CMD_DRV},  /*!< GPIO_PIN_SD1_CMD */
    {&GPIO.PSDMMC2.LONG, GPIO_PSDMMC2_SD1_DAT0_DRV_SHIFT, GPIO_PSDMMC2_SD1_DAT0_DRV}, /*!< GPIO_PIN_SD1_DAT0 */
    {&GPIO.PSDMMC2.LONG, GPIO_PSDMMC2_SD1_DAT1_DRV_SHIFT, GPIO_PSDMMC2_SD1_DAT1_DRV}, /*!< GPIO_PIN_SD1_DAT1 */
    {&GPIO.PSDMMC2.LONG, GPIO_PSDMMC2_SD1_DAT2_DRV_SHIFT, GPIO_PSDMMC2_SD1_DAT2_DRV}, /*!< GPIO_PIN_SD1_DAT2 */
    {&GPIO.PSDMMC2.LONG, GPIO_PSDMMC2_SD1_DAT3_DRV_SHIFT, GPIO_PSDMMC2_SD1_DAT3_DRV}, /*!< GPIO_PIN_SD1_DAT3 */
};

/*! SPIBSC group driver strength register table */
static const st_r_reg_shift_mask_t gs_qspi_reg[] =
{
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI0_SPCLK_DRV_SHIFT,  GPIO_PSPIBSC_QSPI0_SPCLK_DRV},  /*!< GPIO_PIN_QSPI0_SPCLK */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI0_IO0_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO0_DRV},    /*!< GPIO_PIN_QSPI0_IO0 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI0_IO1_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO1_DRV},    /*!< GPIO_PIN_QSPI0_IO1 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI0_IO2_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO2_DRV},    /*!< GPIO_PIN_QSPI0_IO2 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI0_IO3_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO3_DRV},    /*!< GPIO_PIN_QSPI0_IO3 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI0_SSL_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_SSL_DRV},    /*!< GPIO_PIN_QSPI0_SSL */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_RPC_RESETN_DRV_SHIFT,   GPIO_PSPIBSC_RPC_RESETN_DRV},   /*!< GPIO_PIN_RPC_RESET */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_RPC_WPN_DRV_SHIFT,      GPIO_PSPIBSC_RPC_WPN_DRV},      /*!< GPIO_PIN_RPC_WP */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI1_SPCLK_DRV_SHIFT,  GPIO_PSPIBSC_QSPI1_SPCLK_DRV},  /*!< GPIO_PIN_QSPI1_SPCLK */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI1_IO0_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO0_DRV},    /*!< GPIO_PIN_QSPI1_IO0 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI1_IO1_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO1_DRV},    /*!< GPIO_PIN_QSPI1_IO1 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI1_IO2_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO2_DRV},    /*!< GPIO_PIN_QSPI1_IO2 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI1_IO3_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO3_DRV},    /*!< GPIO_PIN_QSPI1_IO3 */
    {&GPIO.PSPIBSC.LONG, GPIO_PSPIBSC_QSPI1_SSL_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_SSL_DRV},    /*!< GPIO_PIN_QSPI1_SSL */
};

/*! gpio mutex for serialisation */
static void * gsp_gpio_mutex = NULL;

/**
 * @brief      r_gpio_unprotect
 *
 *             This function un-protects PFS registers.
 */
static void r_gpio_unprotect(void)
{
    /* Set B0WI to 0 for PFSWE bit as writable */
    RZA_IO_RegWrite_8(&GPIO.PWPR.BYTE, 0, GPIO_PWPR_B0WI_SHIFT, GPIO_PWPR_B0WI);

    /* Set PFSWE to 1 for PxxPFS register as writable */
    RZA_IO_RegWrite_8(&GPIO.PWPR.BYTE, 1, GPIO_PWPR_PFSWE_SHIFT, GPIO_PWPR_PFSWE);
}
/******************************************************************************
 * End of function r_gpio_unprotect
 ******************************************************************************/

/**
 * @brief      r_gpio_protect
 *
 *             This function protects PFS registers.
 */
static void r_gpio_protect(void)
{
    /* Set PFSWE to 0 for PxxPFS register as not-writable */
    RZA_IO_RegWrite_8(&GPIO.PWPR.BYTE, 0, GPIO_PWPR_PFSWE_SHIFT, GPIO_PWPR_PFSWE);

    /* Set B0WI to 1 for PFSWE bit as not-writable */
    RZA_IO_RegWrite_8(&GPIO.PWPR.BYTE, 1, GPIO_PWPR_B0WI_SHIFT, GPIO_PWPR_B0WI);
}
/******************************************************************************
 * End of function r_gpio_protect
 ******************************************************************************/

/**
 * @brief          r_gpio_pin_function_check
 *                 Checks to see if a pin supports a certain function
 * @param[in]      check_array: Which support array to use
 * @param[in]      port_number: Which port to use
 * @param[in]      pin_number: Which pin to use
 * @retval         true     Functionality is supported on this pin
 * @retval         false    Functionality is not supported on this pin
 */
static bool_t r_gpio_pin_function_check (const uint8_t * check_array, uint8_t port_number, uint8_t pin_number)
{
    bool_t res = true;

    /* range check for port */
    if (port_number > GPIO_PORT_MAX)
    {
        /* out of range */
        res = false;
    }

    /* range check for pin
     * 7 : Maximum pin number in RZ/A2M
     * (if porting other device, check if this setting is suitable)
     */
    if (pin_number > 7)
    {
        /* out of range */
        res = false;
    }


    #if defined(GPIO_CFG_PARAM_CHECKING_ENABLE) && (0 != GPIO_CFG_PARAM_CHECKING_ENABLE)
	if ((check_array[port_number] & (1u << pin_number)) == 0)
	{
		res = false;
	}
    #endif

    return res;
}
/******************************************************************************
 * End of function r_gpio_pin_function_check
 ******************************************************************************/

/**
 * @brief          r_gpio_make_port_num
 *                 make port number from port name
 * @param[in]      port: port name
 * @param[out]     p_port_number: port number
 */
static void r_gpio_make_port_num (r_gpio_port_t port, uint8_t * p_port_number)
{
    /* It is okay for using higher 8bit of unsigned 16bit pin value */
    *p_port_number = (uint8_t)((port & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT);

    return;
}
/******************************************************************************
 * End of function r_gpio_make_port_num
 ******************************************************************************/

/**
 * @brief          r_gpio_make_port_pin_num
 *                 make port number and pin number from pin name
 * @param[in]      pin: pin name
 * @param[out]     p_port_number: port number
 * @param[out]     p_pin_number: pin number
 */
static void r_gpio_make_port_pin_num (r_gpio_port_pin_t pin, uint8_t * p_port_number, uint8_t * p_pin_number)
{
    /* It is okay for using higher 8bit of unsigned 16bit pin value */
    *p_port_number = (uint8_t)((pin & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT);

    /* It is okay for using lower 8bit of unsigned 16bit pin value */
    *p_pin_number = (uint8_t)(pin & GPIO_PIN_MASK);

    return;
}
/******************************************************************************
 * End of function r_gpio_make_port_pin_num
 ******************************************************************************/

/**
 * @brief          r_gpio_pin_check_in_use
 *                 check the pin is allocated or not
 * @param[in]      pin: pin name
 * @retval         GPIO_SUCCESS                   not used
 * @retval         GPIO_ERR_PIN_ALREADY_IN_USE    in use
 * @retval         GPIO_ERR_INVALID_PIN           pin is not exist on this device
 */
static e_r_drv_gpio_err_t r_gpio_pin_check_in_use(r_gpio_port_pin_t pin)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port; 
    uint8_t u_pin; 
    uint32_t u_mask;
    bool_t avail;

    err = GPIO_SUCCESS;

    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    u_mask = gs_mask_1bit_register[u_pin];

    /* dedicated pins are always valid */
    if (is_dedicated_pin(pin))
    {
        err = GPIO_SUCCESS;
        avail = false;
    }
    else
    {
        /* check valid pin */
        avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
        if ( !avail )
        {
            err = GPIO_ERR_INVALID_PIN;
        }
    }

    if ( avail )
    {
        /* 0 is not in use, not 0 is in use */
        if ( 0 == (gs_r_drv_gpio_in_use[u_port] & u_mask) )
        {
            err = GPIO_SUCCESS;
        }
        else
        {
            err = GPIO_ERR_PIN_ALREADY_IN_USE;
        }
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_pin_check_in_use
 ******************************************************************************/

/**
 * @brief          is_dedicated_pin
 *                 Checks if the pin is dedicated
 * @param[in]      pin:    Pin number
 * @retval         true    This is a dedicated pin
 * @retval         false   This is not a dedicated pin
 */
static bool_t is_dedicated_pin(r_gpio_port_pin_t pin)
{
    uint_t i;

    /* In RZ/A2M the dedicated pin are assigned a value more than GPIO_DEDICATED_PIN_MIN(0x8000) */
    if (pin >= GPIO_DEDICATED_PIN_MIN)
    {
        return true;
    }

    return false;
}
/******************************************************************************
 * End of function is_dedicated_pin
 ******************************************************************************/

/**
 * @brief          r_gpio_pin_set_in_use
 *                 change status of the pin allocated or not
 * @param[in]      pin: pin name
 * @param[in]      state: GPIO_IN_USE       to change as allocated
 *                        GPIO_NOT_IN_USE   to change as not allocated
 * @retval         GPIO_SUCCESS                   successfully changed
 * @retval         GPIO_ERR_INVALID_PIN           pin is not exist on this device
 */
static e_r_drv_gpio_err_t r_gpio_pin_set_in_use(r_gpio_port_pin_t pin, e_r_drv_gpio_inuse_t state)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    uint8_t u_mask;
    bool_t  avail;

    err = GPIO_SUCCESS;

    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    u_mask = (uint8_t)gs_mask_1bit_register[u_pin];

    /* dedicated pins are ignore state and always valid */
    if (is_dedicated_pin(pin))
    {
        err = GPIO_SUCCESS;
        avail = false;
    }
    else
    {
        /* check valid pin */
        avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
        if (!avail)
        {
            err = GPIO_ERR_INVALID_PIN;
        }
    }

    if (avail)
    {
        /* change state to "in use" or "not in use" */
        if (GPIO_IN_USE == state)
        {
            gs_r_drv_gpio_in_use[u_port] |= u_mask;
        }
        else
        {
            /* cast to target variable type(uint8_t) from int */
            gs_r_drv_gpio_in_use[u_port] &= (uint8_t)(~u_mask);
        }
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_pin_set_in_use
 ******************************************************************************/

/**
 * @brief          r_gpio_pin_is_available
 *                 Checks if the pin is available
 * @param[in]      pin: pin name
 * @retval         true    Functionality is supported on this pin
 * @retval         false   Functionality is not supported on this pin
 */
static bool_t r_gpio_pin_is_available (r_gpio_port_pin_t pin)
{
    bool_t res;
    uint8_t u_port;
    uint8_t u_pin;

    res = true;

    if (is_dedicated_pin(pin))
    {
        /* check if valid dedicated pins */
        R_COMPILER_Nop();
    }
    else
    {
        r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
        res = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    }

    return res;
}
/******************************************************************************
 * End of function r_gpio_pin_is_available
 ******************************************************************************/

/**
 * @brief          r_gpio_scan_sc_config
 *                 Obtaining the SC default configuration for the specified pin
 * @param[in]      pin: pin name
 * @return         pointer to the configuration data or NULL if not found
 */
static const st_r_drv_gpio_pin_config_t * r_gpio_scan_sc_config(r_gpio_port_pin_t pin)
{
    int_t index;
    int_t count;

    count = (sizeof GPIO_SC_TABLE_INIT) / (sizeof *GPIO_SC_TABLE_INIT);

    for (index = 0; index < count; index++)
    {
        if (pin == GPIO_SC_TABLE_INIT[index].pin)
        {
            return &GPIO_SC_TABLE_INIT[index].configuration;
        }
    }

    count = (sizeof GPIO_SC_TABLE_MANUAL) / (sizeof *GPIO_SC_TABLE_MANUAL);

    for (index = 0; index < count; index++)
    {
        if (pin == GPIO_SC_TABLE_MANUAL[index].pin)
        {
            return &GPIO_SC_TABLE_MANUAL[index].configuration;
        }
    }

    return NULL;
}
/******************************************************************************
 * End of function r_gpio_scan_sc_config
 ******************************************************************************/

/**
 * @brief          r_gpio_set_output_current_pin
 *                 set output current
 * @param[in]      pin: which pin to set
 * @param[in]      current: set current to
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_set_output_current_pin(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t current)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;
    volatile uint16_t * p_pdr;

    uint16_t dscr;
    uint16_t mask_16;
    uint16_t shift;

    err = GPIO_SUCCESS;
    dscr = 0;
    avail = true;

    /* get SC default setting */
    if (GPIO_CURRENT_SC_DEFAULT == current)
    {
        /* override from default pin level if specified as SC_DEFAULT */
        const st_r_drv_gpio_pin_config_t * p_config = r_gpio_scan_sc_config(pin);
        if (NULL == p_config)
        {
            /* configuration error if not exist in SC table */
            err = GPIO_ERR_INVALID_CFG;
        }
        else
        {
            current = p_config->current;
        }
    }

    if ( GPIO_SUCCESS == err )
    {
        /* check if valid general purpose io pin for selected current */
        /* and set DSCR value
         *   1:     4mA
         *   3:     8mA
         *   other: invalid
         */
        r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
        if ( GPIO_CURRENT_8mA == current )
        {
            avail = r_gpio_pin_function_check(gs_r_drv_gpio_dscr_8ma_support, u_port, u_pin);
            dscr = 3;
        }
        else if ( GPIO_CURRENT_4mA == current )
        {
            avail = r_gpio_pin_function_check(gs_r_drv_gpio_dscr_4ma_support, u_port, u_pin);
            dscr = 1;
        }
        else
        {
            /* not supported current */
            err = GPIO_ERR_INVALID_CFG;
        }
    }

    if ( (GPIO_SUCCESS == err) && (!avail) )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        /* each DSCR bit data have 2bit width */
        shift = (uint16_t)gs_shift_2bit_register[u_pin];
        mask_16 = (uint16_t)gs_mask_2bit_register[u_pin];

        p_pdr = &PORT0.DSCR.WORD;
        RZA_IO_RegWrite_16(&p_pdr[u_port], dscr, shift, mask_16);
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_set_output_current_pin
 ******************************************************************************/

/**
 * @brief          r_gpio_get_output_current_pin
 *                 obtaining output current
 * @param[in]      pin: which pin to set
 * @param[out]     p_current: obtained current
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_get_output_current_pin(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t * p_current)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;
    volatile uint16_t * p_pdr;

    uint16_t dscr;
    uint16_t mask_16;
    uint16_t shift;

    err = GPIO_SUCCESS;

    /* check if valid 8mA DSCR io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_dscr_8ma_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail 8mA setting on device : check 4mA availability */
        avail = r_gpio_pin_function_check(gs_r_drv_gpio_dscr_4ma_support, u_port, u_pin);
    }

    if ( !avail )
    {
        /* both 4mA and 8mA is not avail */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        /* each DSCR bit data have 2bit width */
        shift = (uint16_t)gs_shift_2bit_register[u_pin];
        mask_16 = (uint16_t)gs_mask_2bit_register[u_pin];

        p_pdr = &PORT0.DSCR.WORD;
        dscr = RZA_IO_RegRead_16(&p_pdr[u_port], shift, mask_16);

        switch ( dscr )
        {
            /* DSCR value
             *   1:     4mA
             *   3:     8mA
             *   other: invalid
             */
            case 3:     /* 8mA */
            {
                *p_current = GPIO_CURRENT_8mA;
                break;
            }

            case 1:     /* 4mA */
            {
                *p_current = GPIO_CURRENT_4mA;
                break;
            }

            default:
            {
                err = GPIO_ERR_INVALID_CFG;
                break;
            }
        }
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_get_output_current_pin
 ******************************************************************************/

/**
 * @brief          r_gpio_set_output_current_ckio
 *                 set PCKIO register
 * @param[in]      pckio: value to set
 * @retval         GPIO_SUCCESS    Successful operation (always)
 */
static e_r_drv_gpio_err_t r_gpio_set_output_current_ckio(uint8_t pckio)
{
    RZA_IO_RegWrite_8(&GPIO.PCKIO.BYTE, pckio, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    return GPIO_SUCCESS;
}
/******************************************************************************
 * End of function r_gpio_set_output_current_ckio
 ******************************************************************************/

/**
 * @brief          r_gpio_get_output_current_ckio
 *                 get PCKIO register
 * @param[out]     p_pckio: value to get
 * @retval         GPIO_SUCCESS    Successful operation (always)
 */
static e_r_drv_gpio_err_t r_gpio_get_output_current_ckio(uint8_t *p_pckio)
{
    *p_pckio = RZA_IO_RegRead_8(&GPIO.PCKIO.BYTE, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    return GPIO_SUCCESS;
}
/******************************************************************************
 * End of function r_gpio_get_output_current_ckio
 ******************************************************************************/

/**
 * @brief          r_gpio_set_output_current_sd0
 *                 set output current for dedicated SD0 port
 * @param[in]      pin: which pin to set
 * @param[in]      current: driver strength
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_set_output_current_sd0(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t current)
{
    e_r_drv_gpio_err_t err;
    uint32_t poc2;
    volatile void *p_reg;
    uint32_t value;
    uint32_t mask;
    uint32_t shift;

    err = GPIO_SUCCESS;

    /* boundary check and error if over */
    if ( (pin < GPIO_PIN_SD0_CLK) || (GPIO_PIN_SD0_RST < pin) )
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        if ( GPIO_PIN_SD0_CLK == pin )
        {
            /* SD0_CLK pin driver strength is only support as 12mA */
            if ( GPIO_CURRENT_12mA != current )
            {
                err = GPIO_ERR_INVALID_CFG;
            }
        }
        else
        {
            /* except SD0_CLK pin driver strength is only support as 6mA */
            if ( GPIO_CURRENT_6mA != current )
            {
                err = GPIO_ERR_INVALID_CFG;
            }
        }
    }

    if ( GPIO_SUCCESS == err )
    {
        /* SD0 drive strength value is affected by poc2 voltage setting. */
        poc2 = RZA_IO_RegRead_32(&GPIO.PPOC.LONG, GPIO_PPOC_POC2_SHIFT, GPIO_PPOC_POC2);
        if ( 1 == poc2 )
        {
            /* if 3.3v, the value must be 2 */
            value = 2;
        }
        else
        {
            /* if 1.8v, the value must be 3 */
            value = 3;
        }

        /* using distance from GPIO_PIN_SD0_CLK as index of gs_sd0_reg */
        p_reg = gs_sd0_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_SD0_CLK].p_reg;
        shift = gs_sd0_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_SD0_CLK].shift;
        mask = gs_sd0_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_SD0_CLK].mask;

        /* write target register */
        RZA_IO_RegWrite_32((volatile uint32_t*)p_reg, value, shift, mask);
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_set_output_current_sd0
 ******************************************************************************/

/**
 * @brief          r_gpio_get_output_current_sd0
 *                 get output current for dedicated SD0 port
 * @param[in]      pin: which pin to get
 * @param[out]     p_current: driver strength
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_get_output_current_sd0(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t * p_current)
{
    e_r_drv_gpio_err_t err;

    err = GPIO_SUCCESS;

    /* boundary check and error if over */
    if ( (pin < GPIO_PIN_SD0_CLK) || (GPIO_PIN_SD0_RST < pin) )
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        if ( GPIO_PIN_SD0_CLK == pin )
        {
            /* SD0_CLK pin driver strength is always 12mA */
            *p_current = GPIO_CURRENT_12mA;
        }
        else
        {
            /* except SD0_CLK pin driver strength is always 6mA */
            *p_current = GPIO_CURRENT_6mA;
        }
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_get_output_current_sd0
 ******************************************************************************/

/**
 * @brief          r_gpio_set_output_current_sd1
 *                 set output current for dedicated SD1 port
 * @param[in]      pin: which pin to set
 * @param[in]      current: driver strength
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_set_output_current_sd1(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t current)
{
    e_r_drv_gpio_err_t err;
    uint32_t poc3;
    volatile void *p_reg;
    uint32_t value;
    uint32_t mask;
    uint32_t shift;

    err = GPIO_SUCCESS;

    /* boundary check and error if over */
    if ( (pin < GPIO_PIN_SD1_CLK) || (GPIO_PIN_SD1_DAT3 < pin) )
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        if ( GPIO_PIN_SD1_CLK == pin )
        {
            /* SD1_CLK pin driver strength is only support as 12mA */
            if ( GPIO_CURRENT_12mA != current )
            {
                err = GPIO_ERR_INVALID_CFG;
            }
        }
        else
        {
            /* except SD1_CLK pin driver strength is only support as 6mA */
            if ( GPIO_CURRENT_6mA != current )
            {
                err = GPIO_ERR_INVALID_CFG;
            }
        }
    }

    if ( GPIO_SUCCESS == err )
    {
        /* SD1 drive strength value is affected by poc3 voltage setting. */
        poc3 = RZA_IO_RegRead_32(&GPIO.PPOC.LONG, GPIO_PPOC_POC3_SHIFT, GPIO_PPOC_POC3);
        if ( 1 == poc3 )
        {
            /* if 3.3v, the value must be 2 */
            value = 2;
        }
        else
        {
            /* if 1.8v, the value must be 3 */
            value = 3;
        }

        /* using distance from GPIO_PIN_SD1_CLK as index of gs_sd1_reg */
        p_reg = gs_sd1_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_SD1_CLK].p_reg;
        shift = gs_sd1_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_SD1_CLK].shift;
        mask = gs_sd1_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_SD1_CLK].mask;

        /* write target register */
        RZA_IO_RegWrite_32((volatile uint32_t*)p_reg, value, shift, mask);
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_set_output_current_sd1
 ******************************************************************************/

/**
 * @brief          r_gpio_get_output_current_sd1
 *                 get output current for dedicated SD1 port
 * @param[in]      pin: which pin to get
 * @param[out]     p_current: driver strength
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_get_output_current_sd1(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t * p_current)
{
    e_r_drv_gpio_err_t err;

    err = GPIO_SUCCESS;

    /* boundary check and error if over */
    if ( (pin < GPIO_PIN_SD1_CLK) || (GPIO_PIN_SD1_DAT3 < pin) )
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        if ( GPIO_PIN_SD1_CLK == pin )
        {
            /* SD1_CLK pin driver strength is always 12mA */
            *p_current = GPIO_CURRENT_12mA;
        }
        else
        {
            /* except SD1_CLK pin driver strength is always 6mA */
            *p_current = GPIO_CURRENT_6mA;
        }
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_get_output_current_sd1
 ******************************************************************************/

/**
 * @brief          r_gpio_set_output_current_qspi
 *                 set output current for dedicated QSPI(SPIBSC) port
 * @param[in]      pin: which pin to set
 * @param[in]      current: driver strength
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_set_output_current_qspi(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t current)
{
    e_r_drv_gpio_err_t err;
    uint32_t ppoc;
    uint32_t value;
    uint32_t mask;
    uint32_t shift;
    volatile void * p_reg;

    err = GPIO_SUCCESS;
    value = 0;

    /* boundary check and error if over */
    if ( (pin < GPIO_PIN_QSPI0_SPCLK) || (GPIO_PIN_QSPI1_SSL < pin) )
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        /* output strength must specific value depends on poc settings */
        ppoc = RZA_IO_RegRead_32(&GPIO.PPOC.LONG, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

        /* if both GPIO_PPOC_POCSEL0|GPIO_PPOC_POC0 is set, meaning their electrical characteristics fits as 3.3v */
        ppoc &= (GPIO_PPOC_POCSEL0|GPIO_PPOC_POC0);
        if ( (GPIO_PPOC_POCSEL0|GPIO_PPOC_POC0) == ppoc )
        {
            /* if 3.3v, the value must be 1 */
            if ( GPIO_CURRENT_8mA == current )
            {
                value = 1;
            }
            else
            {
                err = GPIO_ERR_INVALID_CFG;
            }
        }
        else
        {
            /* if 1.8v, the value must be 3 */
            if ( GPIO_CURRENT_12mA == current )
            {
                value = 3;
            }
            else
            {
                err = GPIO_ERR_INVALID_CFG;
            }
        }

    }

    if ( GPIO_SUCCESS == err )
    {
        /* using distance from GPIO_PIN_SD1_CLK as index of gs_sd1_reg */
        p_reg = gs_qspi_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_QSPI0_SPCLK].p_reg;
        shift = gs_qspi_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_QSPI0_SPCLK].shift;
        mask = gs_qspi_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_QSPI0_SPCLK].mask;

        /* write target register */
        RZA_IO_RegWrite_32((volatile uint32_t*)p_reg, value, shift, mask);
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_set_output_current_qspi
 ******************************************************************************/

/**
 * @brief          r_gpio_get_output_current_qspi
 *                 get output current for dedicated QSPI(SPIBSC) port
 * @param[in]      pin: which pin to get
 * @param[out]     p_current: driver strength
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_get_output_current_qspi(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t * p_current)
{
    e_r_drv_gpio_err_t err;
    uint32_t value;
    uint32_t mask;
    uint32_t shift;
    volatile void * p_reg;

    err = GPIO_SUCCESS;

    /* boundary check and error if over */
    if ( (pin < GPIO_PIN_QSPI0_SPCLK) || (GPIO_PIN_QSPI1_SSL < pin) )
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        /* using distance from GPIO_PIN_SD1_CLK as index of gs_sd1_reg */
        p_reg = gs_qspi_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_QSPI0_SPCLK].p_reg;
        shift = gs_qspi_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_QSPI0_SPCLK].shift;
        mask = gs_qspi_reg[(uint32_t)pin-(uint32_t)GPIO_PIN_QSPI0_SPCLK].mask;

        /* read target register */
        value = RZA_IO_RegRead_32(p_reg, shift, mask);

        switch ( value )
        {
            /* value table
             * 0 : Invalid
             * 1 : 8mA
             * 2 : Invalid
             * 3 : 12mA
             */
            case 1:
            {
                *p_current = GPIO_CURRENT_8mA;
                break;
            }
            case 3:
            {
                *p_current = GPIO_CURRENT_12mA;
                break;
            }
            default:
            {
                err = GPIO_ERR_INVALID_CFG;
                break;
            }
        }
    }
    return err;
}
/******************************************************************************
 * End of function r_gpio_get_output_current_qspi
 ******************************************************************************/

/**
 * @brief          r_gpio_pin_configuration
 *                 get output current for dedicated QSPI(SPIBSC) port
 * @param[in]      pin: pin name
 * @param[in]      config: configuration parameter for specified pin
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
static e_r_drv_gpio_err_t r_gpio_pin_configuration(r_gpio_port_pin_t pin, const st_r_drv_gpio_pin_config_t * config)
{
    e_r_drv_gpio_err_t err;

    err = GPIO_SUCCESS;

    /* dedicated pins have no configurable functions, thus
     * only proceed if is not dedicated pin.
     */
    if ( (GPIO_SUCCESS == err) && (pin <= GPIO_PORT_PIN_MAX) )
    {
        err = R_GPIO_PinSetFunction(pin, config->function);
    }

    /* dedicated pins or general purpose pins may change that output drive strength */
    if ( GPIO_SUCCESS == err )
    {
        err = R_GPIO_PinDscrSet(pin, config->current);
    }

    /* in RZ/A2M, dedicated pins have not support TINT.
     */
    if ( (GPIO_SUCCESS == err) && (pin <= GPIO_PORT_PIN_MAX) )
    {
        err = R_GPIO_PinTintSet(pin, config->tint);
    }

    return err;
}
/******************************************************************************
 * End of function r_gpio_pin_configuration
 ******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
/**
 * @brief          R_GPIO_HWInitialise
 *                 Prepare the GPIO driver for operation
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
int_t R_GPIO_HWInitialise(void)
{
    uint32_t count;

    /* create mutex if not created yet */
    R_OS_EnterCritical();
    if ( NULL == gsp_gpio_mutex )
    {
        gsp_gpio_mutex = R_OS_MutexCreate();
    }
    R_OS_ExitCritical();

    if ( !gs_r_drv_gpio_initialised )
    {
        /* initialise if never initialised */

        count = (sizeof gs_r_drv_gpio_in_use)/(sizeof gs_r_drv_gpio_in_use[0]);
        for ( ; count > 0; count-- )
        {
            gs_r_drv_gpio_in_use[count-1] = 0;
        }

        count = (sizeof GPIO_SC_TABLE_INIT)/(sizeof *GPIO_SC_TABLE_INIT);
        R_GPIO_InitByTable(GPIO_SC_TABLE_INIT, count);

        /* set flag as "initialised" */
        gs_r_drv_gpio_initialised = true;
    }
    return GPIO_SUCCESS;
}
/******************************************************************************
 * End of function R_GPIO_HWInitialise
 ******************************************************************************/

/**
 * @brief          R_GPIO_HWUninitialise
 *                 Finalize the GPIO driver
 * @retval         GPIO_SUCCESS    Successful operation (always)
 */
int_t R_GPIO_HWUninitialise(void)
{
    return GPIO_SUCCESS;
}
/******************************************************************************
 * End of function R_GPIO_HWUninitialise
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinSetConfiguration
 *                 Set single pin configuration
 * @param[in]      p_config: configuration data
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinSetConfiguration(const st_r_drv_gpio_sc_config_t * p_config)
{
    e_r_drv_gpio_err_t err;

    err = r_gpio_pin_configuration(p_config->pin, &p_config->configuration);

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinSetConfiguration
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinGetConfiguration
 *                 Get current pin setting
 * @param[out]     p_config: configuration data
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinGetConfiguration(st_r_drv_gpio_sc_config_t * p_config)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;

    err = GPIO_SUCCESS;

    /* reset hardware defaults */
    p_config->configuration.function = GPIO_FUNC_HIZ;
    p_config->configuration.current = GPIO_CURRENT_RESERVED;
    p_config->configuration.tint = GPIO_TINT_RESERVED;

    /* check whether multiplexed pin or not */
    r_gpio_make_port_pin_num(p_config->pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( avail )
    {
        /* function and tint are supported by pins except dedicated */
        err = R_GPIO_PinGetFunction(p_config->pin, &p_config->configuration.function);

        if ( GPIO_SUCCESS == err )
        {
            err = R_GPIO_PinTintGet(p_config->pin, &p_config->configuration.tint);
        }
    }
    else
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    if ( GPIO_SUCCESS == err )
    {
        /* output driver strength is supported both GPIO and few dedicated pins */
        /* (ignore this error code) */
        R_GPIO_PinDscrGet(p_config->pin, &p_config->configuration.current);
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinGetConfiguration
 ******************************************************************************/

/**
 * @brief          R_GPIO_InitByPinList
 *                 Set pin configuration by a pin list and locks the pins.
 *                 Pin configuration is retrieved from the Smart Configurator table.
 * @param[in]      p_pin_list: the pin list to initialise
 * @param[in]      count: counts of the pins
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_InitByPinList(const r_gpio_port_pin_t * p_pin_list, uint32_t count)
{
    e_r_drv_gpio_err_t err;
    uint32_t sc_index;
    uint32_t sc_count;
    uint32_t list_index;
    r_gpio_port_pin_t pin_number;
    bool_t pin_in_use;
    bool_t invalid_pin;

    /* serialise with multiple threads */
    R_OS_MutexAcquire(gsp_gpio_mutex);

    err = GPIO_SUCCESS;
    pin_in_use = false;
    invalid_pin = false;

    /* check if listed pin is valid and not in use */
    for (list_index = 0; list_index < count; list_index++)
    {
        pin_number = p_pin_list[list_index];

        err = r_gpio_pin_check_in_use(pin_number);

        if (GPIO_ERR_INVALID_PIN == err)
        {
        	invalid_pin = true;
        }

        if (GPIO_ERR_PIN_ALREADY_IN_USE == err)
        {
        	pin_in_use = true;
        }

        /* check that the pin is in the SC table */
        if (r_gpio_scan_sc_config(pin_number) == NULL)
        {
        	invalid_pin = true;
        	break;
        }
    }

    /* invalid pin error has priority over pin in use error */
    if (invalid_pin)
    {
    	err = GPIO_ERR_INVALID_PIN;
    }
    else if (pin_in_use)
    {
    	err = GPIO_ERR_PIN_ALREADY_IN_USE;
    }

    if ( GPIO_SUCCESS == err )
    {
        sc_count = (sizeof GPIO_SC_TABLE_INIT)/(sizeof *GPIO_SC_TABLE_INIT);

        for ( sc_index = 0; sc_index < sc_count; sc_index++ )
        {
            const st_r_drv_gpio_pin_config_t * p_config = &GPIO_SC_TABLE_INIT[sc_index].configuration;
            for ( list_index = 0; list_index < count; list_index++ )
            {
                pin_number = p_pin_list[list_index];

                if ( GPIO_SC_TABLE_INIT[sc_index].pin == pin_number )
                {
                    /* find matched pin in the SC table */
                    r_gpio_pin_configuration(pin_number, p_config);
                    r_gpio_pin_set_in_use(pin_number, GPIO_IN_USE);
                }
            }
        }

        sc_count = (sizeof GPIO_SC_TABLE_MANUAL)/(sizeof *GPIO_SC_TABLE_MANUAL);

        for ( sc_index = 0; sc_index < sc_count; sc_index++ )
        {
            const st_r_drv_gpio_pin_config_t * p_config = &GPIO_SC_TABLE_MANUAL[sc_index].configuration;
            for ( list_index = 0; list_index < count; list_index++ )
            {
                pin_number = p_pin_list[list_index];

                if ( GPIO_SC_TABLE_MANUAL[sc_index].pin == pin_number )
                {
                    /* find matched pin in the SC table */
                    r_gpio_pin_configuration(pin_number, p_config);
                    r_gpio_pin_set_in_use(pin_number, GPIO_IN_USE);
                }
            }
        }
    }

    /* serialise with multiple threads */
    R_OS_MutexRelease(gsp_gpio_mutex);

    return err;
}
/******************************************************************************
 * End of function R_GPIO_InitByPinList
 ******************************************************************************/

/**
 * @brief          R_GPIO_ClearByPinList
 *                 Release pins by a pin list and unlocks the pins.
 * @param[in]      p_pin_list: the pin list to release
 * @param[in]      count: counts of the pins
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_ClearByPinList(const r_gpio_port_pin_t * p_pin_list, uint32_t count)
{
    e_r_drv_gpio_err_t ret;
    uint32_t list_index;
    r_gpio_port_pin_t pin_number;
    st_r_drv_gpio_sc_config_t config;

    /* serialise with multiple threads */
    R_OS_MutexAcquire(gsp_gpio_mutex);

    ret = GPIO_SUCCESS;

    /* check if listed pins are valid */
    for (list_index = 0; list_index < count; list_index++)
    {
        pin_number = p_pin_list[list_index];

        /* check that the pin is valid */
        if (r_gpio_pin_check_in_use(pin_number) == GPIO_ERR_INVALID_PIN)
        {
        	ret = GPIO_ERR_INVALID_PIN;
        	break;
        }

        /* check that the pin is in the SC table */
        if (r_gpio_scan_sc_config(pin_number) == NULL)
        {
        	ret = GPIO_ERR_INVALID_PIN;
        	break;
        }
    }

    if (GPIO_SUCCESS == ret)
    {
        /* clear pins */
        for (list_index = 0; list_index < count; list_index++)
        {
            pin_number = p_pin_list[list_index];

            /* set pin configuration to Hi-Z input protection */
            config.pin = pin_number;
            config.configuration.function = GPIO_FUNC_HIZ;
            config.configuration.tint = GPIO_TINT_DISABLE;
            config.configuration.current = GPIO_CURRENT_RESERVED;
            ret = R_GPIO_PinSetConfiguration(&config);

            if (GPIO_SUCCESS != ret)
            {
                break;
            }

            r_gpio_pin_set_in_use(pin_number, GPIO_NOT_IN_USE);
        }
    }

    /* serialise with multiple threads */
    R_OS_MutexRelease(gsp_gpio_mutex);

    return ret;
}
/******************************************************************************
 * End of function R_GPIO_ClearByPinList
 ******************************************************************************/

/**
 * @brief          R_GPIO_InitByTable
 *                 Optional Set a group of pins using an array of pin configurations.
 *                 This function locks the pins
 * @param[in]      p_table: the configuration list to initialise
 * @param[in]      count: counts of the pins
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_InitByTable(const st_r_drv_gpio_sc_config_t * p_table, uint32_t count)
{
    e_r_drv_gpio_err_t err;
    uint32_t index;
    r_gpio_port_pin_t pin_number;
    bool_t pin_in_use;
    bool_t invalid_pin;

    /* serialise with multiple threads */
    R_OS_MutexAcquire(gsp_gpio_mutex);

    err = GPIO_SUCCESS;
    pin_in_use = false;
    invalid_pin = false;

    /* check if listed pin is valid and not in use */
    for (index = 0; index < count; index++)
    {
        pin_number = p_table[index].pin;

        err = r_gpio_pin_check_in_use(pin_number);

        if (GPIO_ERR_INVALID_PIN == err)
        {
        	invalid_pin = true;
        }

        if (GPIO_ERR_PIN_ALREADY_IN_USE == err)
        {
        	pin_in_use = true;
        }
    }

    /* invalid pin error has priority over pin in use error */
    if (invalid_pin)
    {
    	err = GPIO_ERR_INVALID_PIN;
    }
    else if (pin_in_use)
    {
    	err = GPIO_ERR_PIN_ALREADY_IN_USE;
    }

    /* configure pins if all pins are not in use */
    for ( index = 0; (index < count) && (GPIO_SUCCESS == err); index++ )
    {
        r_gpio_pin_configuration(p_table[index].pin, &p_table[index].configuration);
        r_gpio_pin_set_in_use(p_table[index].pin, GPIO_IN_USE);
    }

    /* serialise with multiple threads */
    R_OS_MutexRelease(gsp_gpio_mutex);

    return err;
}
/******************************************************************************
 * End of function R_GPIO_InitByTable
 ******************************************************************************/

/**
 * @brief          R_GPIO_ClearByTable
 *                 Optional release a group pins using an array of pin configurations.
 *                 This function unlocks the pins
 * @param[in]      p_table: the configuration list to clear (only using the pin number)
 * @param[in]      count: counts of the pins
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_ClearByTable(const st_r_drv_gpio_sc_config_t * p_table, uint32_t count)
{
    e_r_drv_gpio_err_t err;
    uint32_t index;
    bool_t avail;

    /* serialise with multiple threads */
    R_OS_MutexAcquire(gsp_gpio_mutex);

    err = GPIO_SUCCESS;

    for ( index = 0; index < count; index++ )
    {
        avail = r_gpio_pin_is_available(p_table[index].pin);
        if ( avail )
        {
            /* set pin configuration to Hi-Z input protection */
            R_GPIO_PinSetFunction(p_table[index].pin, GPIO_FUNC_HIZ);
        }
        r_gpio_pin_set_in_use(p_table[index].pin, GPIO_NOT_IN_USE);
    }

    /* serialise with multiple threads */
    R_OS_MutexRelease(gsp_gpio_mutex);

    return err;
}
/******************************************************************************
 * End of function R_GPIO_ClearByTable
 ******************************************************************************/

/**
 * @brief          R_GPIO_PortWrite
 *                 Sets the logic levels on the specified port
 * @param[in]      port: the port to set
 * @param[in]      value: the value to write
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PortWrite(r_gpio_port_t port, uint8_t value)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    volatile uint8_t * p_uaddr;

    err = GPIO_SUCCESS;

    r_gpio_make_port_num(port, &u_port);
    if(u_port > GPIO_PORT_MAX)
    {
        /* out of port range */
        err = GPIO_ERR_INVALID_PORT;
    }
    else
    {
        /* write value to port */
        p_uaddr = &PORT0.PODR.BYTE;
        RZA_IO_RegWrite_8(&p_uaddr[u_port], value, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PortWrite
 ******************************************************************************/

/**
 * @brief          R_GPIO_PortRead
 *                 Reads the logic levels on the specified port
 * @param[in]      port: the port to set
 * @param[out]     p_value: the value read from the port
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PortRead(r_gpio_port_t port, uint8_t * p_value )
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    volatile uint8_t * p_uaddr;

    err = GPIO_SUCCESS;

    r_gpio_make_port_num(port, &u_port);
    if(u_port > GPIO_PORT_MAX)
    {
        /* out of port range */
        err = GPIO_ERR_INVALID_PORT;
    }
    else
    {
        /* read port value */
        p_uaddr = &PORT0.PIDR.BYTE;
        *p_value = RZA_IO_RegRead_8(&p_uaddr[u_port], IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PortRead
 ******************************************************************************/

/**
 * @brief          R_GPIO_PortDirectionSet
 *                 Sets the specified port pins to input, output or Hi-Z
 * @param[in]      port: the port to set
 * @param[in]      dir: input, output or Hi-Z
 * @param[in]      mask: which bits are to be affected
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PortDirectionSet(r_gpio_port_t port, e_r_drv_gpio_dir_t dir, uint8_t mask)
{
    e_r_drv_gpio_err_t err;

    uint8_t pin_count;     /*!< target pin counter */

    err = GPIO_SUCCESS;

    /* a port have 8 pins */
    for ( pin_count = 0; (GPIO_SUCCESS == err) && (pin_count < 8); pin_count++ )
    {
        /* check if changing the pin */
        if ( mask & 1 )
        {
            /* call API for changing pin direction */
            err = R_GPIO_PinDirectionSet((r_gpio_port_pin_t)(port|pin_count), dir);
        }

        /* shift for next pin */
        mask = mask >> 1;
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PortDirectionSet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinWrite
 *                 Sets the logic level on the specified pin
 * @param[in]      pin: the pin to set
 * @param[in]      level: high or low
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinWrite(r_gpio_port_pin_t pin, e_r_drv_gpio_level_t level)
{
    uint8_t u_port;
    uint8_t u_pin;
    bool_t  avail;
    bool_t  dont_touch;
    volatile uint8_t * p_podr;
    uint8_t mask;
    e_r_drv_gpio_err_t gpio_err;
    uint8_t value;

    gpio_err = GPIO_SUCCESS;
    dont_touch = false;
    value = 0;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if(!avail)
    {
        gpio_err = GPIO_ERR_INVALID_PIN;
        dont_touch = true;
    }

    if ( (!dont_touch) && (GPIO_LEVEL_SC_DEFAULT == level) )
    {
        /* override from default pin level if specified as SC_DEFAULT */
        const st_r_drv_gpio_pin_config_t * p_config = r_gpio_scan_sc_config(pin);
        if(NULL == p_config)
        {
            /* error if not exist in SC table */
            gpio_err = GPIO_ERR_INVALID_CFG;
            dont_touch = true;
        }
        else
        {
            /* using function member from SC for determining output level */
            if ( GPIO_FUNC_OUT_HIGH == p_config->function )
            {
                level = GPIO_LEVEL_HIGH;
            }
            else if ( GPIO_FUNC_OUT_LOW == p_config->function )
            {
                level = GPIO_LEVEL_LOW;
            }
            else
            {
                /* do not touch if the pin is not configured as general output */
                dont_touch = true;
            }
        }
    }

    /* make bit value from level */
    if ( !dont_touch )
    {
        if ( GPIO_LEVEL_LOW == level )
        {
            value = 0;
        }
        else if ( GPIO_LEVEL_HIGH == level )
        {
            value = 1;
        }
        else if (GPIO_LEVEL_SC_DEFAULT == level)
        {
            /* do not touch if the pin is not configured as general output */
            dont_touch = true;
        }
        else
        {
            /* parameter error */
            gpio_err = GPIO_ERR_INVALID_CFG;
        }
    }

    /* write podr from value if success and level is not RESERVED */
    if ( !dont_touch )
    {
        p_podr = &(PORT0.PODR.BYTE);
        mask = (uint8_t)gs_mask_1bit_register[u_pin];
        RZA_IO_RegWrite_8(&p_podr[u_port], value, u_pin, mask);
    }

    return gpio_err;
}
/******************************************************************************
 * End of function R_GPIO_PinWrite
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinRead
 *                 Reads the logic level on the specified pin
 * @param[in]      pin: the pin to read
 * @param[out]     p_level: the logic level read from the pin
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinRead(r_gpio_port_pin_t pin, e_r_drv_gpio_level_t *p_level)
{
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;

    volatile uint8_t * p_pidr;
    uint8_t mask;
    e_r_drv_gpio_err_t gpio_err;
    uint8_t value;

    gpio_err = GPIO_SUCCESS;


    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if(!avail)
    {
        gpio_err = GPIO_ERR_INVALID_PIN;

    }
    else
    {
        /* read PIDR */
        p_pidr = &(PORT0.PIDR.BYTE);
        mask = (uint8_t)gs_mask_1bit_register[u_pin];
        value = RZA_IO_RegRead_8(&p_pidr[u_port], u_pin, mask);
        if ( 0 != value )
        {
            *p_level = GPIO_LEVEL_HIGH;
        }
        else
        {
            *p_level = GPIO_LEVEL_LOW;
        }
    }

    return gpio_err;
}
/******************************************************************************
 * End of function R_GPIO_PinRead
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinDirectionSet
 *                 Sets the specified pin to input, output or Hi-Z
 * @param[in]      pin: the port to set
 * @param[in]      dir: input, output or Hi-Z
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinDirectionSet(r_gpio_port_pin_t pin, e_r_drv_gpio_dir_t dir)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;
    volatile uint16_t * p_pdr;

    uint16_t mask_16;
    uint16_t shift;

    err = GPIO_SUCCESS;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        if ( GPIO_DIRECTION_SC_DEFAULT == dir )
        {
            /* override from default pin level if specified as SC_DEFAULT */
            const st_r_drv_gpio_pin_config_t * p_config = r_gpio_scan_sc_config(pin);
            if(NULL == p_config)
            {
                /* configuration error if not exist in SC table */
                err = GPIO_ERR_INVALID_CFG;
            }
            else
            {
                /* using function member from SC for determining direction */
                if ( (GPIO_FUNC_OUT_HIGH == p_config->function) ||
                     (GPIO_FUNC_OUT_LOW  == p_config->function) ||
                     (GPIO_FUNC_OUT      == p_config->function))
                {
                    dir = GPIO_DIRECTION_OUTPUT;
                }
                else if ( GPIO_FUNC_IN == p_config->function )
                {
                    dir = GPIO_DIRECTION_INPUT;
                }
                else
                {
                    /* configuration error if the pin is not configured as general i/o */
                    err = GPIO_ERR_INVALID_CFG;
                }
            }
        }
    }

    if ( GPIO_SUCCESS == err )
    {
        /* each PDR pin data have 2bit width */
        shift = (uint16_t)gs_shift_2bit_register[u_pin];

        /* make mask bit (0b11 << shift) */
        mask_16 = (uint16_t)gs_mask_2bit_register[u_pin];

        /* modify PDR */
        p_pdr = &PORT0.PDR.WORD;
        p_pdr = &(p_pdr[u_port]);
        switch(dir)
        {
            case GPIO_DIRECTION_INPUT:
            {
                /* write direction
                 * 2 : as input
                 */
                RZA_IO_RegWrite_16(p_pdr, 2, shift, mask_16);
                break;
            }
            case GPIO_DIRECTION_OUTPUT:
            {
                /* write direction
                 * 3 : as output
                 */
                RZA_IO_RegWrite_16(p_pdr, 3, shift, mask_16);
                break;
            }
            case GPIO_DIRECTION_HIZ:
            {
                /* write direction
                 * 0 : as hi-z protection
                 */
                RZA_IO_RegWrite_16(p_pdr, 0, shift, mask_16);
                break;
            }
            default:
            {
                err = GPIO_ERR_INVALID_CMD;
            }
        }
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinDirectionSet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinDirectionGet
 *                 Gets the specified pin direction setting (input, output or Hi-Z)
 * @param[in]      pin: the port to set
 * @param[in]      p_dir: the direction read for the pin: input, output, or Hi-Z
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinDirectionGet(r_gpio_port_pin_t pin, e_r_drv_gpio_dir_t * p_dir)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;
    volatile uint16_t * p_pdr;
    uint16_t pdr_reg;
    uint16_t mask_16;
    uint16_t shift;

    err = GPIO_SUCCESS;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        /* each PDR pin data have 2bit width */
        shift = (uint16_t)gs_shift_2bit_register[u_pin];

        /* make mask bit (0b11 << shift) */
        mask_16 = (uint16_t)gs_mask_2bit_register[u_pin];

        /* get pdr */
        p_pdr = &PORT0.PDR.WORD;
        pdr_reg = RZA_IO_RegRead_16(&p_pdr[u_port], shift, mask_16);
        switch ( pdr_reg )
        {
            case 2:     /* 2 : as input */
            {
                *p_dir = GPIO_DIRECTION_INPUT;
            }
            break;
            case 3:     /* 3 : as output */
            {
                *p_dir = GPIO_DIRECTION_OUTPUT;
            }
            break;
            case 0:     /* 0 : as hi-z protection */
            {
                *p_dir = GPIO_DIRECTION_HIZ;
            }
            break;
            default:
            {
                err = GPIO_ERR_INVALID_CFG;
            }
            break;
        }
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinDirectionGet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinAssignmentSet
 *                 Assigns a pin to GPIO or to a peripheral
 * @param[in]      pin: the pin to assign
 * @param[in]      assignment: how to assign the pin:
 *                     GPIO_ASSIGN_TO_PERIPHERAL or GPIO_ASSIGN_TO_GPIO
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinAssignmentSet(r_gpio_port_pin_t pin, e_r_drv_gpio_assign_t assignment)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    uint8_t mask_8;
    bool_t avail;
    volatile uint8_t * p_pmr;
    uint8_t shift;
    uint8_t value;

    err = GPIO_SUCCESS;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        if ( GPIO_ASSIGN_TO_GPIO == assignment )
        {
            value = 0;
        }
        else if ( GPIO_ASSIGN_TO_PERIPHERAL == assignment )
        {
            value = 1;
        }
        else
        {
            err = GPIO_ERR_INVALID_CFG;
        }
    }

    if ( GPIO_SUCCESS == err )
    {
        /* each PMR pin data have 1bit width */
        shift = (uint8_t)gs_shift_1bit_register[u_pin];

        /* make mask bit (0b1 << shift) */
        mask_8 = (uint8_t)gs_mask_1bit_register[u_pin];

        p_pmr = &PORT0.PMR.BYTE;
        RZA_IO_RegWrite_8(&p_pmr[u_port], value, shift, mask_8);
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinAssignmentSet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinAssignmentGet
 *                 Get pin assignment: GPIO or peripheral
 * @param[in]      pin: the pin to get the current assignment setting
 * @param[out]     p_assignment: how to assign the pin:
 *                     GPIO_ASSIGN_TO_PERIPHERAL or GPIO_ASSIGN_TO_GPIO
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinAssignmentGet(r_gpio_port_pin_t pin, e_r_drv_gpio_assign_t * p_assignment)
{
    e_r_drv_gpio_err_t err;
    uint8_t u_port;
    uint8_t u_pin;
    uint8_t pmr_reg;
    uint8_t mask_8;
    bool_t avail;
    volatile uint8_t * p_pmr;
    uint8_t shift;

    err = GPIO_SUCCESS;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        /* each PMR pin data have 1bit width */
        shift = (uint8_t)gs_shift_1bit_register[u_pin];

        /* make mask bit (0b1 << shift) */
        mask_8 = (uint8_t)gs_mask_1bit_register[u_pin];

        p_pmr = &PORT0.PMR.BYTE;
        pmr_reg = RZA_IO_RegRead_8(&p_pmr[u_port], shift, mask_8);

        if ( 1 == pmr_reg )
        {
            *p_assignment = GPIO_ASSIGN_TO_PERIPHERAL;
        }
        else
        {
            *p_assignment = GPIO_ASSIGN_TO_GPIO;
        }
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinAssignmentGet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinTintSet
 *                 Turns interrupts on or off for a pin
 * @param[in]      pin: the pin to set the interrupts for
 * @param[in]      tint: whether to enable or disable interrupts:
 *                 GPIO_TINT_ENABLE or GPIO_TINT_DISABLE
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinTintSet(r_gpio_port_pin_t pin, e_r_drv_gpio_tint_t tint)
{
    e_r_drv_gpio_err_t err;
    volatile uint8_t * p_uaddr;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;
    bool_t dont_touch;

    err = GPIO_SUCCESS;
    dont_touch = false;

    if ( GPIO_TINT_RESERVED == tint )
    {
        dont_touch = true;
    }

    /* get default configuration if GPIO_CURRENT_SC_DEFAULT is specified */
    if ( (!dont_touch) && (GPIO_TINT_SC_DEFAULT == tint) )
    {
        const st_r_drv_gpio_pin_config_t * p_config = r_gpio_scan_sc_config(pin);
        if(NULL == p_config)
        {
            err = GPIO_ERR_INVALID_CFG;
        }
        else
        {
            tint = p_config->tint;
        }
    }

    if ( !dont_touch )
    {
        /* check if valid general purpose io pin */
        r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
        avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
        if ( !avail )
        {
            /* not avail on device */
            err = GPIO_ERR_INVALID_PIN;
        }
        else
        {
            p_uaddr = &GPIO.P00PFS.BYTE;
            p_uaddr = &p_uaddr[(u_port*8)+u_pin];
            switch(tint)
            {
                case GPIO_TINT_ENABLE:
                {
                    /* set ISEL bit to 1 if tint enable */
                    r_gpio_unprotect();
                    RZA_IO_RegWrite_8(p_uaddr, 1, GPIO_P00PFS_ISEL_SHIFT, GPIO_P00PFS_ISEL);
                    r_gpio_protect();
                }
                break;
                case GPIO_TINT_DISABLE:
                {
                    /* set ISEL bit to 0 if tint disable */
                    r_gpio_unprotect();
                    RZA_IO_RegWrite_8(p_uaddr, 0, GPIO_P00PFS_ISEL_SHIFT, GPIO_P00PFS_ISEL);
                    r_gpio_protect();
                }
                break;
                default:
                {
                    err = GPIO_ERR_INVALID_CFG;
                }
                break;
            }

        }
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinTintSet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinTintGet
 *                 Reads interrupt on / off setting for a pin
 * @param[in]      pin: the pin to get the interrupts for
 * @param[out]     p_tint: the interrupt setting
 *                 GPIO_TINT_ENABLE or GPIO_TINT_DISABLE
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinTintGet(r_gpio_port_pin_t pin, e_r_drv_gpio_tint_t * p_tint)
{
    e_r_drv_gpio_err_t err;
    uint8_t isel;
    volatile uint8_t * p_uaddr;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;

    err = GPIO_SUCCESS;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        p_uaddr = &GPIO.P00PFS.BYTE;
        isel = RZA_IO_RegRead_8(&p_uaddr[(u_port*8)+u_pin], GPIO_P00PFS_ISEL_SHIFT, GPIO_P00PFS_ISEL);

        if ( 0 == isel )
        {
            *p_tint = GPIO_TINT_DISABLE;
        }
        else
        {
            *p_tint = GPIO_TINT_ENABLE;
        }
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinTintGet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinDscrSet
 *                 Sets pin DSCR current
 * @param[in]      pin: the pin to set the DSCR for
 * @param[in]      current: the current to set:
 *                 GPIO_CURRENT_4mA or GPIO_CURRENT_8mA
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinDscrSet(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t current)
{
    e_r_drv_gpio_err_t err;

    /* get default configuration if GPIO_CURRENT_SC_DEFAULT is specified */
    err = GPIO_SUCCESS;
    if ( GPIO_CURRENT_SC_DEFAULT == current )
    {
        const st_r_drv_gpio_pin_config_t * config = r_gpio_scan_sc_config(pin);
        if(NULL == config)
        {
            err = GPIO_ERR_INVALID_CFG;
        }
        else
        {
            current = config->current;
        }
    }

    if ( (GPIO_SUCCESS == err) && (GPIO_CURRENT_RESERVED != current) )
    {
        if ( pin <= GPIO_PORT_PIN_MAX )
        {
            /* general purpose io pins */
            err = r_gpio_set_output_current_pin(pin, current);
        }
        else if ( GPIO_PIN_CKIO == pin )
        {
            /* CKIO pin */
            err = r_gpio_set_output_current_ckio(current);
        }
        else if ( (GPIO_PIN_SD0_CLK <= pin) && (pin <= GPIO_PIN_SD0_RST) )
        {
            /* SD0 */
            err = r_gpio_set_output_current_sd0(pin, current);
        }
        else if ( (GPIO_PIN_SD1_CLK <= pin) && (pin <= GPIO_PIN_SD1_DAT3) )
        {
            /* SD1 */
            err = r_gpio_set_output_current_sd1(pin, current);
        }
        else if ( (GPIO_PIN_QSPI0_SPCLK <= pin) && (pin <= GPIO_PIN_QSPI1_SSL) )
        {
            /* SPIBSC */
            err = r_gpio_set_output_current_qspi(pin, current);
        }
        else
        {
            err = GPIO_ERR_INVALID_PIN;
        }
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinDscrSet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinDscrGet
 *                 Gets pin DSCR current setting (4mA or 8mA)
 * @param[in]      pin: the pin to set the DSCR for
 * @param[out]     p_current: the current current setting:
 *                 GPIO_CURRENT_4mA or GPIO_CURRENT_8mA
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinDscrGet(r_gpio_port_pin_t pin, e_r_drv_gpio_current_t * p_current)
{
    e_r_drv_gpio_err_t err;

    err = GPIO_SUCCESS;

    if ( pin <= GPIO_PORT_PIN_MAX )
    {
        /* general purpose io pins */
        err = r_gpio_get_output_current_pin(pin, p_current);
    }
    else if ( GPIO_PIN_CKIO == pin )
    {
        /* CKIO pin */
        err = r_gpio_get_output_current_ckio(p_current);
    }
    else if ( (GPIO_PIN_SD0_CLK <= pin) && (pin <= GPIO_PIN_SD0_RST) )
    {
        /* SD0 */
        err = r_gpio_get_output_current_sd0(pin, p_current);
    }
    else if ( (GPIO_PIN_SD1_CLK <= pin) && (pin <= GPIO_PIN_SD1_DAT3) )
    {
        /* SD1 */
        err = r_gpio_get_output_current_sd1(pin, p_current);
    }
    else if ( (GPIO_PIN_QSPI0_SPCLK <= pin) && (pin <= GPIO_PIN_QSPI1_SSL) )
    {
        /* SPIBSC */
        err = r_gpio_get_output_current_qspi(pin, p_current);
    }
    else
    {
        err = GPIO_ERR_INVALID_PIN;
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinDscrGet
 ******************************************************************************/

/**
 * @brief          R_GPIO_PeripheralFunctionWrite
 *                 Sets the peripheral function for a pin
 * @param[in]      pin: the pin to set
 * @param[in]      psel: the code for the required peripheral function
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PeripheralFunctionWrite(r_gpio_port_pin_t pin, uint8_t psel)
{
    e_r_drv_gpio_err_t err;
    volatile uint8_t * p_uaddr;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;

    err = GPIO_SUCCESS;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        p_uaddr = &GPIO.P00PFS.BYTE;
        r_gpio_unprotect();
        RZA_IO_RegWrite_8(&p_uaddr[(u_port*8)+u_pin], psel, GPIO_P00PFS_PSEL_SHIFT, GPIO_P00PFS_PSEL);
        r_gpio_protect();
    }
    return err;
}
/******************************************************************************
 * End of function R_GPIO_PeripheralFunctionWrite
 ******************************************************************************/

/**
 * @brief          R_GPIO_PeripheralFunctionRead
 *                 Gets the current peripheral function setting for a pin
 * @param[in]      pin: the pin to interrogate for the peripheral function setting
 * @param[out]     p_psel: set to the code of the current peripheral function
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PeripheralFunctionRead(r_gpio_port_pin_t pin, uint8_t * p_psel)
{
    e_r_drv_gpio_err_t err;
    volatile uint8_t * p_uaddr;
    uint8_t u_port;
    uint8_t u_pin;
    bool_t avail;

    err = GPIO_SUCCESS;

    /* check if valid general purpose io pin */
    r_gpio_make_port_pin_num(pin, &u_port, &u_pin);
    avail = r_gpio_pin_function_check(gs_r_drv_gpio_support, u_port, u_pin);
    if ( !avail )
    {
        /* not avail on device */
        err = GPIO_ERR_INVALID_PIN;
    }
    else
    {
        p_uaddr = &GPIO.P00PFS.BYTE;
        *p_psel = RZA_IO_RegRead_8(&p_uaddr[(u_port*8)+u_pin], GPIO_P00PFS_PSEL_SHIFT, GPIO_P00PFS_PSEL);
    }
    return err;
}
/******************************************************************************
 * End of function R_GPIO_PeripheralFunctionRead
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinSetFunction
 *                 Set the function of the specified pin
 * @param[in]      pin: the pin to set
 * @param[in]      function: which function to configure
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinSetFunction(r_gpio_port_pin_t pin, e_r_drv_gpio_function_t function)
{
    e_r_drv_gpio_err_t err;

    err = GPIO_SUCCESS;

    /* get default function if GPIO_FUNC_SC_DEFAULT */
    if (GPIO_FUNC_SC_DEFAULT == function)
    {
        const st_r_drv_gpio_pin_config_t * p_config = r_gpio_scan_sc_config(pin);
        if (NULL == p_config)
        {
            return GPIO_ERR_INVALID_CFG;
        }

        function = p_config->function;
    }

    if (GPIO_FUNC_HIZ == function)
    {
        /* Hi-Z protection */
        err = R_GPIO_PinDirectionSet(pin, GPIO_DIRECTION_HIZ);

        /* and assign to GPIO */
        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PinAssignmentSet(pin, GPIO_ASSIGN_TO_GPIO);
        }
    }
    else if (GPIO_FUNC_IN == function)
    {
        /* input function (procedure is described in UM) */
        err = R_GPIO_PinDirectionSet(pin, GPIO_DIRECTION_HIZ);

        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PinAssignmentSet(pin, GPIO_ASSIGN_TO_GPIO);
        }

        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PinDirectionSet(pin, GPIO_DIRECTION_INPUT);
        }
    }
    else if ((GPIO_FUNC_OUT_HIGH == function) || (GPIO_FUNC_OUT_LOW == function) || (GPIO_FUNC_OUT == function))
    {
        /* output functions  (procedure is described in UM) */

    	err = R_GPIO_PinDirectionSet(pin, GPIO_DIRECTION_HIZ);
        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PinAssignmentSet(pin, GPIO_ASSIGN_TO_GPIO);
        }

        if (GPIO_SUCCESS == err)
        {
            switch (function)
            {
                case GPIO_FUNC_OUT_HIGH:
                {
                    err = R_GPIO_PinWrite(pin, GPIO_LEVEL_HIGH);
                }
                break;

                case GPIO_FUNC_OUT_LOW:
                {
                    err = R_GPIO_PinWrite(pin, GPIO_LEVEL_LOW);
                }
                break;

                default:
                {
                    /* keep previous output state if level is not specified */
                    R_COMPILER_Nop();
                }
                break;
            }
        }

        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PinDirectionSet(pin, GPIO_DIRECTION_OUTPUT);
        }
    }
    else if ((GPIO_FUNC_PERIPHERAL0 <= function) && (function <= GPIO_FUNC_PERIPHERAL7))
    {
        /* internal peripheral functions (procedure is described in UM) */
        err = R_GPIO_PinDirectionSet(pin, GPIO_DIRECTION_HIZ);
        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PinAssignmentSet(pin, GPIO_ASSIGN_TO_GPIO);
        }

        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PeripheralFunctionWrite(pin, (uint8_t)(function - GPIO_FUNC_PERIPHERAL0));
        }

        if (GPIO_SUCCESS == err)
        {
            err = R_GPIO_PinAssignmentSet(pin, GPIO_ASSIGN_TO_PERIPHERAL);
        }
    }
    else
    {
        err = GPIO_ERR_INVALID_CFG;
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinSetFunction
 ******************************************************************************/

/**
 * @brief          R_GPIO_PinGetFunction
 *                 Get the function of the specified pin
 * @param[in]      pin: the pin to get
 * @param[out]     p_function: set to the current pin function
 * @retval         GPIO_SUCCESS    Successful operation
 * @retval         !GPIO_SUCCESS   Failure operation
 */
e_r_drv_gpio_err_t R_GPIO_PinGetFunction(r_gpio_port_pin_t pin, e_r_drv_gpio_function_t * p_function)
{
    e_r_drv_gpio_err_t err;
    e_r_drv_gpio_assign_t assignment;
    e_r_drv_gpio_dir_t dir;
    uint8_t psel;

    /* set default */
    *p_function = GPIO_FUNC_SC_DEFAULT;

    err = R_GPIO_PinAssignmentGet(pin, &assignment);
    if ( GPIO_SUCCESS == err )
    {
        if ( GPIO_ASSIGN_TO_GPIO == assignment )
        {
            err = R_GPIO_PinDirectionGet(pin, &dir);
        }
        else
        {
            err = R_GPIO_PeripheralFunctionRead(pin, &psel);
        }
    }

    if ( (GPIO_SUCCESS == err) && (GPIO_ASSIGN_TO_GPIO == assignment))
    {
        /* check GPIO Hi-Z/Input/Output */
        switch(dir)
        {
            case GPIO_DIRECTION_HIZ:
            {
                *p_function = GPIO_FUNC_HIZ;
                break;
            }
            case GPIO_DIRECTION_INPUT:
            {
                *p_function = GPIO_FUNC_IN;
                break;
            }
            case GPIO_DIRECTION_OUTPUT:
            {
                *p_function = GPIO_FUNC_OUT;
                break;
            }
            default:
            {
                err = GPIO_ERR_INVALID_CFG;
            }
        }
    }

    if ( (GPIO_SUCCESS == err) && (GPIO_ASSIGN_TO_PERIPHERAL == assignment))
    {
        *p_function = GPIO_FUNC_PERIPHERAL0 + psel;
    }

    return err;
}
/******************************************************************************
 * End of function R_GPIO_PinGetFunction
 ******************************************************************************/

/**
 * @brief       R_GPIO_GetVersion
 *              Gets the version number of this low-level driver
 * @param[out]  p_ver_info: returns the driver information
 * @retval      DRV_SUCCESS Always returned
 */
int_t R_GPIO_GetVersion(st_ver_info_t *p_ver_info)
{
    p_ver_info->lld.p_szdriver_name = gs_lld_info.p_szdriver_name;
    p_ver_info->lld.version.sub.major = gs_lld_info.version.sub.major;
    p_ver_info->lld.version.sub.minor = gs_lld_info.version.sub.minor;
    p_ver_info->lld.build = gs_lld_info.build;

    return DRV_SUCCESS;
}
/******************************************************************************
 * End of function R_GPIO_GetVersion
 ******************************************************************************/

/* End of File */
