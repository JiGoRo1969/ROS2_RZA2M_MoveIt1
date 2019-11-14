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
#include "r_os_abstraction_api.h"

#include <uxr/client/client.h>
#include <ucdr/microcdr.h>

#include <FreeRTOS.h>
#include <task.h>
#include <r_devlink_wrapper.h>
#include <r_gpio_drv_api.h>
#include "ros2_sample.h"
#include "Ros2Info.h"

/* Micro-XRCE-DDS-Client key identifier of the client.
   If multiple clients connect to the same agent, each client must have a different key. */
#define CLIENT_KEY      0xAAAABBBB

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
#define STREAM_HISTORY  1
#else
#define STREAM_HISTORY  8
#endif

/* Transport */
#if (DDS_TRANSPORT == DDS_TRANSPORT_UDP)
#define BUFFER_SIZE     UXR_CONFIG_UDP_TRANSPORT_MTU * STREAM_HISTORY
static uxrUDPPlatform  platform;
static uxrUDPTransport transport;

#else /* (DDS_TRANSPORT == DDS_TRANSPORT_TCP) */
#define BUFFER_SIZE     UXR_CONFIG_TCP_TRANSPORT_MTU * STREAM_HISTORY
static uxrTCPPlatform  platform;
static uxrTCPTransport transport;
#endif

static uxrSession session;
static uxrObjectId datawriter_id;
static uxrStreamId output_stream;
static uxrStreamId input_stream;
static bool connected = true;

/* stream */
static uint8_t output_stream_buffer[BUFFER_SIZE];
static uint8_t input_stream_buffer[BUFFER_SIZE];
static Ros2Info topic = {0};

static void prvUXRManagerTask(void * pvParameters);

/** External Variable */
extern p_mutex_t *g_pMutex;
extern double g_info[21];

extern void	r_servo_send( void );

/**************/
/* Setup Demo */
/**************/
void setup_publisher_demo( void )
{
    /* Transport */
#if (DDS_TRANSPORT == DDS_TRANSPORT_UDP )
   if (!create_transport_UDP(&transport , &platform))
#else /* (DDS_TRANSPORT == DDS_TRANSPORT_TCP) */
   if (!create_transport_TCP(&transport , &platform))
#endif
    {
        fprintf(stdout, "Error at create transport.\r\n");
        fflush(stdout);
        return;
    }

    /* Session */
	uxr_init_session(&session, &transport.comm, CLIENT_KEY);
	if (!uxr_create_session(&session)) {
		fprintf(stdout, "Error at create session.\r\n");
		fflush(stdout);
		return;
	}

    /* Streams */
#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    output_stream = uxr_create_output_best_effort_stream(&session, output_stream_buffer, BUFFER_SIZE);
    input_stream = uxr_create_input_best_effort_stream(&session);
#else
    output_stream = uxr_create_output_reliable_stream(&session, output_stream_buffer, BUFFER_SIZE, STREAM_HISTORY);
    input_stream = uxr_create_input_reliable_stream(&session, input_stream_buffer, BUFFER_SIZE, STREAM_HISTORY);
#endif

    /* Create entities */
    uxrObjectId participant_id = uxr_object_id(0x02, UXR_PARTICIPANT_ID);
    const char* participant_xml = "<dds>"
                                      "<participant>"
                                          "<rtps>"
                                              "<name>default_xrce_participant</name>"
                                          "</rtps>"
                                      "</participant>"
                                  "</dds>";
    uint16_t participant_req = uxr_buffer_create_participant_xml(&session, output_stream, participant_id, 0, participant_xml, UXR_REPLACE);

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    /* In order to avoid buffer overflow, uxr_flash_output_streams() has to be */
    /* called everytime entities message is created. */
    (void) uxr_flash_output_streams(&session);
#endif

    uxrObjectId topic_id = uxr_object_id(0x02, UXR_TOPIC_ID);
    const char* topic_xml = "<dds>"
                                "<topic>"
                                    "<name>rt/open_manipulator_evk/demo_arm_srv_pos_up</name>"
                                    "<dataType>std_msgs::msg::dds_::Float64MultiArray_</dataType>"
                                "</topic>"
                            "</dds>";
    uint16_t topic_req = uxr_buffer_create_topic_xml(&session, output_stream, topic_id, participant_id, topic_xml, UXR_REPLACE);

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    /* In order to avoid buffer overflow, uxr_flash_output_streams() has to be */
    /* called everytime entities message is created. */
    (void) uxr_flash_output_streams(&session);
#endif

    uxrObjectId publisher_id = uxr_object_id(0x02, UXR_PUBLISHER_ID);
    const char* publisher_xml = "";
    uint16_t publisher_req = uxr_buffer_create_publisher_xml(&session, output_stream, publisher_id, participant_id, publisher_xml, UXR_REPLACE);

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    /* In order to avoid buffer overflow, uxr_flash_output_streams() has to be */
    /* called everytime entities message is created. */
    (void) uxr_flash_output_streams(&session);
#endif

    datawriter_id = uxr_object_id(0x02, UXR_DATAWRITER_ID);
    const char* datawriter_xml = "<dds>"
                                     "<data_writer>"
                                         "<topic>"
                                             "<kind>NO_KEY</kind>"
                                             "<name>rt/open_manipulator_evk/demo_arm_srv_pos_up</name>"
                                             "<dataType>std_msgs::msg::dds_::Float64MultiArray_</dataType>"
                                         "</topic>"
                                     "</data_writer>"
                                 "</dds>";
    uint16_t datawriter_req = uxr_buffer_create_datawriter_xml(&session, output_stream, datawriter_id, publisher_id, datawriter_xml, UXR_REPLACE);

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    /* In order to avoid buffer overflow, uxr_flash_output_streams() has to be */
    /* called everytime entities message is created. */
    (void) uxr_flash_output_streams(&session);
#else /* (CLIENT_STREAMS == CLIENT_STREAMS_RELIABLE) */
    /* Send create entities message and wait its status */
    uint8_t status[4];
    uint16_t requests[4] = {participant_req, topic_req, publisher_req, datawriter_req};
	if (!uxr_run_session_until_all_status(&session, 1000, requests, status, 4)) {
		fprintf(stdout, "Error at create entities: participant: %d topic: %d publisher: %d datawriter: %d\r\n" , status[0], status[1], status[2], status[3]);
		fflush(stdout);
	}
#endif

    xTaskCreate(prvUXRManagerTask, "Pos_Publisher", configMINIMAL_STACK_SIZE * 10, NULL, 2, NULL);
}

static void prvUXRManagerTask(void * pvParameters)
{
    // double 要素のサイズを指定、dim 配列は無しにする
    topic.info_size = 21;
    topic.layout.dim_size = 0;
    topic.layout.data_offset = 0;

    /* Loop as long as client is connected to agent. */
    while ( 1 )
    {
        /* Topic serialization */
        ucdrBuffer mb = {0};
        int i;

        uint32_t topic_size = Ros2Info_size_of_topic( &topic, 0 );
        R_OS_MutexAcquire( g_pMutex );
        {
            memcpy( topic.info, g_info, sizeof(g_info) );
        }
        R_OS_MutexRelease( g_pMutex );

        uxr_prepare_output_stream(&session, output_stream, datawriter_id, &mb, topic_size);
        Ros2Info_serialize_topic(&mb, &topic);

        /* Set timeout period to 1ms in order to send messages every 10ms */
        connected = uxr_run_session_until_timeout(&session, 3000);
        if (!connected)
        {
            fprintf(stdout, "pub connection error\r\n");
            fflush(stdout);
        }

        /* Toggle the heartbeat LED */
        led_toggle();

        vTaskDelay(25);
    }

    /* 切断された場合 */
    /* Delete resources */
    (void) uxr_delete_session(&session);

    /* Close Transport */
#if (DDS_TRANSPORT == DDS_TRANSPORT_UDP)
    (void) uxr_close_udp_transport(&transport);
#else /* (DDS_TRANSPORT == DDS_TRANSPORT_TCP) */
    (void) uxr_close_tcp_transport(&transport);
#endif

    /* Delete this task */
    vTaskDelete(NULL);
}
