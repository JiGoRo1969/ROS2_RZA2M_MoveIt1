/*
Amazon FreeRTOS
Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 http://aws.amazon.com/freertos
 http://www.FreeRTOS.org
*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Version includes. */
#include "aws_application_version.h"

/* System init includes. */
#include "aws_system_init.h"

/* Logging includes. */
#include "aws_logging_task.h"

/* Key provisioning includes. */
#include "aws_dev_mode_key_provisioning.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"

/* Demo includes */
#include "aws_demo_runner.h"
#include "aws_clientcredential.h"


//190325 modified for RZ/A2M. It is for RZ/A2M. -->
/*from app.c*/
#include "queue.h"
#include <stdio.h>
#include <string.h>

#include "r_devlink_wrapper.h"
#include "r_ether_rza2_if.h"
#include "FreeRTOS_IP_Private.h"

/* Aws Library Includes includes. */
#include "aws_system_init.h"
#include "aws_logging_task.h"
#include "aws_application_version.h"
#include "aws_dev_mode_key_provisioning.h"

/*from main.c*/
#include <fcntl.h>
#include <unistd.h>
#include "r_typedefs.h"
#include "iodefine.h"
#include "r_cpg_drv_api.h"
#include "r_ostm_drv_api.h"
#include "r_scifa_drv_api.h"
#include "r_gpio_drv_api.h"
#include "r_startup_config.h"
#include "compiler_settings.h"
#include "main.h"
#include "r_os_abstraction_api.h"
#include "r_task_priority.h"
#include "version.h"
#include "console.h"
//190325 modified for RZ/A2M. It is for RZ/A2M. <--

#define mainLOGGING_TASK_STACK_SIZE         ( configMINIMAL_STACK_SIZE * 6 )
#define mainLOGGING_MESSAGE_QUEUE_LENGTH    ( 15 )
#define mainTEST_RUNNER_TASK_STACK_SIZE    ( configMINIMAL_STACK_SIZE * 8 )

// Modify 2018.08.31 -->
#define IGMP_TEST1  0
#define IGMP_TEST3  0
// Modify 2018.08.31 <--

#if 0    //190325 modified for RZ/A2M. It is for RX. -->
/* Declare the firmware version structure for all to see. */
const AppVersion32_t xAppFirmwareVersion = {
   .u.x.ucMajor = APP_VERSION_MAJOR,
   .u.x.ucMinor = APP_VERSION_MINOR,
   .u.x.usBuild = APP_VERSION_BUILD,
};
#endif    //190325 modified for RZ/A2M. It is for RX.  <--

/* The MAC address array is not declared const as the MAC address will
normally be read from an EEPROM and not hard coded (in real deployed
applications).*/
static uint8_t ucMACAddress[ 6 ] =
{
    configMAC_ADDR0,
    configMAC_ADDR1,
    configMAC_ADDR2,
    configMAC_ADDR3,
    configMAC_ADDR4,
    configMAC_ADDR5
}; //XXX

/* Define the network addressing.  These parameters will be used if either
ipconfigUDE_DHCP is 0 or if ipconfigUSE_DHCP is 1 but DHCP auto configuration
failed. */
static const uint8_t ucIPAddress[ 4 ] =
{
    configIP_ADDR0,
    configIP_ADDR1,
    configIP_ADDR2,
    configIP_ADDR3
};
static const uint8_t ucNetMask[ 4 ] =
{
    configNET_MASK0,
    configNET_MASK1,
    configNET_MASK2,
    configNET_MASK3
};
static const uint8_t ucGatewayAddress[ 4 ] =
{
    configGATEWAY_ADDR0,
    configGATEWAY_ADDR1,
    configGATEWAY_ADDR2,
    configGATEWAY_ADDR3
};

/* The following is the address of an OpenDNS server. */
static const uint8_t ucDNSServerAddress[ 4 ] =
{
    configDNS_SERVER_ADDR0,
    configDNS_SERVER_ADDR1,
    configDNS_SERVER_ADDR2,
    configDNS_SERVER_ADDR3
};

st_r_drv_gpio_pin_rw_t	gs_p60[2] =
{
	{GPIO_PORT_6_PIN_0, GPIO_LEVEL_LOW,  GPIO_SUCCESS},
	{GPIO_PORT_6_PIN_0, GPIO_LEVEL_HIGH, GPIO_SUCCESS}
};

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
p_mutex_t *g_pMutex;
double g_info[21] = {0};

int_t	g_gpio_handle;

/**
 * @brief Application task startup hook.
 */
void vApplicationDaemonTaskStartupHook( void );

/**
 * @brief Initializes the board.
 */
static void prvMiscInitialization( void );

/* Terminal window escape sequences */
static const char_t * const sp_clear_screen = "\x1b[2J";
static const char_t * const sp_cursor_home  = "\x1b[H";

extern void show_welcome_msg (FILE *p_out, bool_t clear_screen);

extern void	r_servo_init_port( void );
extern void r_goto_home_position(void);

extern void setup_publisher_demo( void );
extern void setup_subscriber_demo( void );


void os_main_task_t( void );
/*-----------------------------------------------------------*/

int_t main(void)
{
    int_t cpg_handle;

    /* configure any drivers that are required before the Kernel initialises */

    /* Initialize the devlink layer */
    R_DEVLINK_Init();

    /* Initialize CPG */
    cpg_handle = direct_open("cpg", 0);
    if ( cpg_handle < 0 )
    {
        /* stop execute */
        while(1);
    }

    /* Can close handle if no need to change clock after here */
    direct_close(cpg_handle);

    /* Start FreeRTOS */
    /* R_OS_InitKernel should never return */
    R_OS_KernelInit();
}


/**
 * @brief The application entry point from a power on reset is PowerON_Reset_PC()
 * in resetprg.c.
 */
void os_main_task_t( void )
{
    int_t err;
    st_r_drv_gpio_pin_list_t pin_led;
    char_t data;

	/* For information only
     * Use stdio calls to open drivers once  the kernel is initialised
     *
     * ie
     * int_t ostm3_handle;
     * ostm3_handle = open (DEVICE_INDENTIFIER "ostm2", O_RDWR);
     * close (ostm3_handle);
     */

    g_gpio_handle = open (DEVICE_INDENTIFIER "gpio", O_RDWR);

    /* On error */
    if ( g_gpio_handle < 0 )
    {
        /* stop execute */
        while(1);
    }

    /* ==== Output banner message ==== */
    printf("%s%s", sp_clear_screen, sp_cursor_home);
    show_welcome_msg(stdout, true);

    //
    // Create Mutex
    //
    g_pMutex = R_OS_MutexCreate();

    //
    // Init Servo
    //
    r_servo_init_port();
    R_OS_TaskSleep( 500 );
    r_goto_home_position();

    /*
     * Start Subscriber/Publisher
     */
    setup_publisher_demo();
    setup_subscriber_demo();

    while(1)
    {
    	static uint8_t	tick = 0;

        R_OS_TaskSleep(500);
        direct_control(g_gpio_handle, CTL_GPIO_PIN_WRITE, &gs_p60[tick]);
        tick++;
        tick &= 1;
    }
}
/*-----------------------------------------------------------*/

static void prvMiscInitialization( void )
{
    /* Initialize UART for serial terminal. */
//    uart_config();    //190325 modified for RZ/A2M. It is for RX.

    /* Start logging task. */
    xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
                            tskIDLE_PRIORITY,
                            mainLOGGING_MESSAGE_QUEUE_LENGTH );
}
/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook( void )
{
    prvMiscInitialization();

    if( SYSTEM_Init() == pdPASS )
    {
        /* Initialise the RTOS's TCP/IP stack.  The tasks that use the network
        are created in the vApplicationIPNetworkEventHook() hook function
        below.  The hook function is called when the network connects. */
        FreeRTOS_IPInit( ucIPAddress,
                         ucNetMask,
                         ucGatewayAddress,
                         ucDNSServerAddress,
                         ucMACAddress );

#if 0    //190325 modified for RZ/A2M. It is for RX. -->
        /* We should wait for the network to be up before we run any demos. */
        while( FreeRTOS_IsNetworkUp() == pdFALSE )
        {
            vTaskDelay(3000);
        }
#endif  //190325 modified for RZ/A2M. It is for RX. <--


        /* Provision the device with AWS certificate and private key. */
        vDevModeKeyProvisioning();

        /* Run all demos. */
        /* DEMO_RUNNER_RunDemos(); */
    }
}
/*-----------------------------------------------------------*/

//190325 modified for RZ/A2M. It is the same setting as RX65N -->
const char * pcApplicationHostnameHook( void )
{
    /* Assign the name "FreeRTOS" to this network node.  This function will
     * be called during the DHCP: the machine will be registered with an IP
     * address plus this name. */
    return clientcredentialIOT_THING_NAME;
}
//190325 modified for RZ/A2M. It is the same setting as RX65N <--
/*-----------------------------------------------------------*/


/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle
     * task's state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetTimerTaskMemory() to provide the memory that is
 * used by the RTOS daemon/time task. */
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

