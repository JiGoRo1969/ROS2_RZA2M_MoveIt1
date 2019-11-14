/*
// Copyright 2019 eSOL Co.,Ltd.
// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <uxr/client/client.h>
#include <ucdr/microcdr.h>

#include <FreeRTOS.h>
#include <task.h>

#include "ros2_sample.h"


/* GPIO-LED */
#define MAIN_PRV_LED_ON     (1)
#define MAIN_PRV_LED_OFF    (0)
extern int g_my_gpio_handle ;

/* Transport */
#if (DDS_TRANSPORT == DDS_TRANSPORT_UDP)
 static uxrUDPPlatform  platform;
#else /* (DDS_TRANSPORT == DDS_TRANSPORT_TCP) */
 static uxrTCPPlatform  platform;
#endif

/* LED */
static uint32_t gs_main_led_flg = 0;      /* LED lighting/turning off */

static void discovery_agent( uxrAgentAddress* chosen );
static bool on_agent_found(const uxrAgentAddress* address, void* args);

/*****************************/
/* Toggle the heartbeat LED2 */
/*****************************/
void led_toggle( void )
{
    gs_main_led_flg ^= 1;
    if (MAIN_PRV_LED_ON == gs_main_led_flg) {
        PORTA.PODR.BIT.PODR6 = 0;
    }
    else {
        PORTA.PODR.BIT.PODR6 = 1;
    }
}

#if (DDS_TRANSPORT == DDS_TRANSPORT_UDP)
/*****************************/
/* Create UDP transport      */
/*****************************/
bool create_transport_UDP( uxrUDPTransport* ptransport , uxrUDPPlatform*  pplatform )
{
    uxrAgentAddress chosen;

    discovery_agent( &chosen );
    return uxr_init_udp_transport( ptransport, pplatform, chosen.ip, chosen.port);
}
#endif

#if (DDS_TRANSPORT == DDS_TRANSPORT_TCP)
/*****************************/
/* Create TCP transport      */
/*****************************/
bool create_transport_TCP( uxrTCPTransport* ptransport , uxrTCPPlatform*  pplatform )
{
    uxrAgentAddress chosen;

    discovery_agent( &chosen );
    return uxr_init_tcp_transport( ptransport, pplatform, chosen.ip, chosen.port);
}
#endif

/*****************************/
/* Discovery Agent           */
/*****************************/
static void discovery_agent( uxrAgentAddress* pchosen )
{
	fprintf(stdout, "Discovery Agent...\r\n");
	fflush(stdout);

	/* Wait for network configuration */
	vTaskDelay(5000);

	/* Try forever until Agent is found */
	uxr_discovery_agents_default( INT_MAX, 1000, (uxrOnAgentFound*)on_agent_found, pchosen );

	fprintf(stdout, "Chosen agent => ip: %s , port: %d \r\n", pchosen->ip, pchosen->port);
	fflush(stdout);
}

/*****************************/
/* Discovery Agent call back */
/*****************************/
static bool on_agent_found(const uxrAgentAddress* paddress, void* args)
{
    uxrAgentAddress* addrinfo = (uxrAgentAddress*)args;
    addrinfo->ip = paddress->ip;
    addrinfo->port = paddress->port;

    fprintf(stdout,"Found  agent => ip: %s , port: %d\r\n" , paddress->ip , paddress->port);
    fflush(stdout);
    return true;
}
