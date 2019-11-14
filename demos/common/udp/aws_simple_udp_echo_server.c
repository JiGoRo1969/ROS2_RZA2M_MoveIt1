/*
 * Amazon FreeRTOS V1.4.5
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */


/*
 * FreeRTOS tasks are used with FreeRTOS+UDP to create a UDP echo server.  Echo
 * clients are also created, but the echo clients use Windows threads (as
 * opposed to FreeRTOS tasks) and use the Windows UDP library (Winsocks).  This
 * creates a communication between the FreeRTOS+UDP UDP/IP stack and the Windows
 * UDP/IP stack.
 *
 * See the following web page for essential demo usage and configuration
 * details:
 * http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_UDP/examples_FreeRTOS_simulator.html
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* FreeRTOS+UDP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP_Private.h"

/* Demo specific includes */
#include "aws_simple_udp_echo_server.h"
#include "aws_demo_config.h"


#define MAXLINE 1024 

/* Specifies the size of the data sent to the server in MSS units. */
#define tcpechoBUFFER_SIZE_MULTIPLIER    3

/* The maximum time to wait for a closing socket to close. */
#define tcpechoSHUTDOWN_DELAY            ( pdMS_TO_TICKS( 5000 ) )

/* The standard echo port number. */
#ifdef configUDP_ECHO_CLIENT_PORT
    #define udpechoPORT_NUMBER    configUDP_ECHO_CLIENT_PORT
#else
    #define udpechoPORT_NUMBER    7
#endif

/*-----------------------------------------------------------*/

/*
 * Uses FreeRTOS+UDP to listen for incoming echo connections, creating a task
 * to handle each connection.
 */
static void prvConnectionListeningTask( void * pvParameters );

/*
 * Created by the connection listening task to handle a single connection.
 */
static void prvServerConnectionInstance( void * pvParameters );

/*-----------------------------------------------------------*/

/* Stores the stack size passed into vStartSimpleUDPServerTasks() so it can be
 * reused when the server listening task creates tasks to handle connections. */
static uint16_t usUsedStackSize = 0;

/* Used for error reporting. */
static uint32_t ulConnectionCount = 0;

/*-----------------------------------------------------------*/

void vStartSimpleUDPServerTasks( void )
{
    /* Create the UDP echo server.  The echo server uses FreeRTOS+UDP through
     * the spoofed IP and MAC address.  The WinSock client tasks are created from
     * inside the listening task. */
    xTaskCreate( prvConnectionListeningTask,
                 "ServerListener",
                 democonfigUDP_ECHO_SERVER_TASK_STACK_SIZE,
                 NULL,
                 democonfigUDP_ECHO_SERVER_TASK_PRIORITY + 1,
                 NULL );

    /* Remember the requested stack size so it can be re-used by the server
     * listening task when it creates tasks to handle connections. */
    usUsedStackSize = democonfigUDP_ECHO_SERVER_TASK_STACK_SIZE;
}
/*-----------------------------------------------------------*/

static void prvConnectionListeningTask( void * pvParameters )
{
    struct freertos_sockaddr xClient, xBindAddress;
    Socket_t  xConnectedSocket;
    socklen_t xSize = sizeof( xClient );
    static const TickType_t xReceiveTimeOut = portMAX_DELAY;
    int8_t buffer[MAXLINE]; 
    int32_t bytes_received ;
    int32_t iReturned;


    /* Just to prevent compiler warnings. */
    ( void ) pvParameters;

    /* Attempt to open the socket. */
    xConnectedSocket = FreeRTOS_socket( FREERTOS_AF_INET, FREERTOS_SOCK_DGRAM, FREERTOS_IPPROTO_UDP );
    configASSERT( xConnectedSocket != FREERTOS_INVALID_SOCKET );

    /* Set a time out so accept() will just wait for a connection. */
    FreeRTOS_setsockopt( xConnectedSocket, 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );

    /* Bind the socket to the port that the client task will send to, then
     * listen for incoming connections. */
    xBindAddress.sin_port = udpechoPORT_NUMBER;
    xBindAddress.sin_port = FreeRTOS_htons( xBindAddress.sin_port );
    FreeRTOS_bind(xConnectedSocket, &xBindAddress, sizeof( xBindAddress ) );


    for( ;; )
    {
        /* Wait for a client data receive  */
        bytes_received = FreeRTOS_recvfrom(xConnectedSocket, (void *)buffer, MAXLINE, 0, &xClient, xSize);
        iReturned = FreeRTOS_sendto(xConnectedSocket, (void *)buffer, bytes_received, 0, &xClient, xSize);
    }
}
