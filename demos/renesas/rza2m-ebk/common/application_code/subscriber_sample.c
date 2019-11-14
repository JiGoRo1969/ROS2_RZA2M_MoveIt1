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


/* 角度計算用マクロ */
#define DEGREE_TO_VAL(n)    ( (int16_t)( ( (double)(n) / M_PI * 2048.0 ) ) )


/* Micro-XRCE-DDS-Client key identifier of the client.
   If multiple clients connect to the same agent, each client must have a different key. */
#define CLIENT_KEY      0xCCCCDDDD

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
static uint16_t read_data_req;
static uxrStreamId output_stream;
static uxrStreamId input_stream;
static bool connected = true;

/* stream */
static uint8_t output_stream_buffer[BUFFER_SIZE];
static uint8_t input_stream_buffer[BUFFER_SIZE];
static Ros2Info topic;

static void on_topic(uxrSession* session, uxrObjectId object_id, uint16_t request_id, uxrStreamId stream_id, struct ucdrBuffer* mb, void* args);
static void prvUXRManagerTask(void * pvParameters);

/** External Function */
extern uint16_t r_servo_set_angle( uint16_t r_id, int16_t r_val );
extern void r_servo_send( void );

/** External Variable */
extern p_mutex_t *g_pMutex;
extern double g_info[21];


/**************/
/* Setup Demo */
/**************/
void setup_subscriber_demo()
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
    uxr_set_topic_callback(&session, on_topic, NULL);
    if (!uxr_create_session(&session))
    {
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
    uxrObjectId participant_id = uxr_object_id(0x01, UXR_PARTICIPANT_ID);
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

    uxrObjectId topic_id = uxr_object_id(0x01, UXR_TOPIC_ID);
    const char* topic_xml = "<dds>"
                                "<topic>"
                                    "<name>rt/open_manipulator_evk/demo_arm_srv_pos_down</name>"
                                    "<dataType>std_msgs::msg::dds_::Float64MultiArray_</dataType>"
                                "</topic>"
                            "</dds>";
    uint16_t topic_req = uxr_buffer_create_topic_xml(&session, output_stream, topic_id, participant_id, topic_xml, UXR_REPLACE);

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    /* In order to avoid buffer overflow, uxr_flash_output_streams() has to be */
    /* called everytime entities message is created. */
    (void) uxr_flash_output_streams(&session);
#endif

    uxrObjectId subscriber_id = uxr_object_id(0x01, UXR_SUBSCRIBER_ID);
    const char* subscriber_xml = "";
    uint16_t subscriber_req = uxr_buffer_create_subscriber_xml(&session, output_stream, subscriber_id, participant_id, subscriber_xml, UXR_REPLACE);

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    /* In order to avoid buffer overflow, uxr_flash_output_streams() has to be */
    /* called everytime entities message is created. */
    (void) uxr_flash_output_streams(&session);
#endif

    uxrObjectId datareader_id = uxr_object_id(0x01, UXR_DATAREADER_ID);
    const char* datareader_xml = "<dds>"
                                     "<data_reader>"
                                         "<topic>"
                                             "<kind>NO_KEY</kind>"
                                             "<name>rt/open_manipulator_evk/demo_arm_srv_pos_down</name>"
                                             "<dataType>std_msgs::msg::dds_::Float64MultiArray_</dataType>"
                                         "</topic>"
                                     "</data_reader>"
                                 "</dds>";
    uint16_t datareader_req = uxr_buffer_create_datareader_xml(&session, output_stream, datareader_id, subscriber_id, datareader_xml, UXR_REPLACE);

#if(CLIENT_STREAMS == CLIENT_STREAMS_BESTEFFORT)
    /* In order to avoid buffer overflow, uxr_flash_output_streams() has to be */
    /* called everytime entities message is created. */
    (void) uxr_flash_output_streams(&session);
#else /* (CLIENT_STREAMS == CLIENT_STREAMS_RELIABLE) */
    /* Send create entities message and wait its status */
    uint8_t status[4];
    uint16_t requests[4] = {participant_req, topic_req, subscriber_req, datareader_req};
	if (!uxr_run_session_until_all_status(&session, 1000, requests, status, 4)) {
		fprintf(stdout, "Error at create entities: participant: %d topic: %d subscriber: %d datareader: %d\r\n" , status[0], status[1], status[2], status[3]);
		fflush(stdout);
	}
#endif

    /* Request topics */
    uxrDeliveryControl delivery_control = {0};
    delivery_control.max_samples = UXR_MAX_SAMPLES_UNLIMITED;
    read_data_req = uxr_buffer_request_data(&session, output_stream, datareader_id, input_stream, &delivery_control);

    xTaskCreate(prvUXRManagerTask, "Pos_Subscriber", configMINIMAL_STACK_SIZE * 10, NULL, 3, NULL);
}

/* topic callback */
static void on_topic(uxrSession* session, uxrObjectId object_id, uint16_t request_id, uxrStreamId stream_id, struct ucdrBuffer* mb, void* args)
{
    (void) session; (void) object_id; (void) request_id; (void) stream_id;

    Ros2Info_deserialize_topic(mb, &topic);

    int16_t i, val;

    R_OS_MutexAcquire( g_pMutex );
    {
        memcpy( g_info, topic.info, sizeof(g_info) );
    }
    R_OS_MutexRelease( g_pMutex );

    for ( i = 1; i <= 5; i++ )
    {
        val = DEGREE_TO_VAL( topic.info[i] );
        r_servo_set_angle( i - 1, val );
    }
    r_servo_send();
}

static void prvUXRManagerTask(void * pvParameters)
{
    /* Loop as long as client is connected to agent. */
    while (1)
    {
        /* Receive topics */
        if (connected)
        {
            uint8_t read_data_status;
            uxr_run_session_until_all_status(&session, 3000, &read_data_req, &read_data_status, 1);
        }
        else
        {
            fprintf(stdout, "sub connection error\r\n");
            fflush(stdout);
        }
        vTaskDelay(1);
    }

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
