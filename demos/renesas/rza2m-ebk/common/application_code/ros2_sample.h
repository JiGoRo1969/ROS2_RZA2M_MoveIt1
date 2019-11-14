/***********************************************************************************************************************
 * File Name    : ros2_sample.h
 * Description  : This module solves all the world's problems
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 15.01.2007 1.00     First Release
 **********************************************************************************************************************/
#ifndef _ROS2_SAMPLE_H_
#define _ROS2_SAMPLE_H_

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <uxr/client/client.h>

/* Agent Transport define */
#define DDS_TRANSPORT_TCP    0
#define DDS_TRANSPORT_UDP    1

/* use serial channel define */
#define TRANSPORT_SERIAL_CH_SCIFA0  0
#define TRANSPORT_SERIAL_CH_SCIFA1  1
#define TRANSPORT_SERIAL_CH_SCIFA2  2
#define TRANSPORT_SERIAL_CH_SCIFA3  3
#define TRANSPORT_SERIAL_CH_SCIFA4  4

/* Client Streams */
#define CLIENT_STREAMS_RELIABLE     0
#define CLIENT_STREAMS_BESTEFFORT   1

/* Client demo mode */
#define CLIENT_DEMO_PUBLISHER       0
#define CLIENT_DEMO_SUBSCRIBER      1

/* Demos common */
extern void led_toggle( void );

#if (DDS_TRANSPORT == DDS_TRANSPORT_TCP)
extern bool create_transport_TCP( uxrTCPTransport* ptransport , uxrTCPPlatform*  pplatform );
#else /* (DDS_TRANSPORT == DDS_TRANSPORT_UDP) */
extern bool create_transport_UDP( uxrUDPTransport* ptransport , uxrUDPPlatform*  pplatform );
#endif


#endif /* _ROS2_SAMPLE_H_ */
