/*
 * servo_robotis.c
 *
 *  Created on: 2019/09/02
 *      Author: n-okada
 */

#include	"r_typedefs.h"
#include	"iodefine.h"
#include	"r_gpio_drv_api.h"
#include	"r_scifa_drv_api.h"
#include	"r_os_abstraction_api.h"
#include	<math.h>

/***********************************************************************************************************************
 * Constant values and type definitions
 ***********************************************************************************************************************/

//#define 	USE_DEBUG_PRINTF_INFORMATION

#define	DYNAINST_PING				(0x01)
#define	DYNAINST_READ_DATA			(0x02)
#define	DYNAINST_WRITE_DATA			(0x03)
#define	DYNAINST_REG_WRITE			(0x04)
#define	DYNAINST_ACTION				(0x05)
#define	DYNAINST_RESET				(0x06)
#define	DYNAINST_SYNC_WRITE			(0x83)

#define	DYNAPARA_ANGLE_FULLRANGE	(4096)
#define	DYNAPARA_ANGLE_HALFRANGE	(2048)	// == (DYNAPARA_ANGLE_FULLRANGE + 1) / 2)
#define	DYNAPARA_ANGLE_CENTER		(2047)	// == (DYNAPARA_ANGLE_FULLRANGE + 1) / 2 - 1)

#define	BUF_SIZE					(64)

#define	D_DIR_WRITE					(1)
#define	D_DIR_READ					(0)
#define	D_FULL_DUPLEX				(1)
#define	D_HALF_DUPLEX				(0)

#define	D_OFFSET_ID					(11)
#define	D_CNT_SERVO					(5)

#define	D_DIV_SLOWSETHOME			(100)
#define	D_TIME_SLOWSETHOME			(50)

//#define 	CONNECT_SERVO_TO_SCIFA0
//#define 	CONNECT_SERVO_TO_SCIFA1
#define 	CONNECT_SERVO_TO_SCIFA2
//#define 	CONNECT_SERVO_TO_SCIFA3
#define 	CONNECT_SERVO_TO_SCIFA4		// Console

typedef	union {
	uint16_t	w;
	uint8_t		b[2];
} uint16_u;

/***********************************************************************************************************************
 * Global variables and functions
 ***********************************************************************************************************************/
uint8_t		r_buf_rxd2[BUF_SIZE];
uint8_t		r_buf_txd2[BUF_SIZE];

uint16_t	r_angle_init[D_CNT_SERVO] = {
				DYNAPARA_ANGLE_CENTER,				// 11
				DYNAPARA_ANGLE_CENTER,				// 12
				DYNAPARA_ANGLE_CENTER,				// 13
				DYNAPARA_ANGLE_CENTER,				// 14
				DYNAPARA_ANGLE_CENTER				// 15
			};
uint16_u	r_angle[D_CNT_SERVO];
uint16_t	r_current_angle[D_CNT_SERVO];

st_stream_t		fp0, fp1, fp2, fp3, fp4;

extern	int_t	g_gpio_handle;

st_r_drv_gpio_pin_rw_t gs_pA7[2] = {{GPIO_PORT_A_PIN_7, GPIO_LEVEL_LOW,  GPIO_SUCCESS},
									{GPIO_PORT_A_PIN_7, GPIO_LEVEL_HIGH, GPIO_SUCCESS}};
st_r_drv_gpio_pin_rw_t gs_p72[2] = {{GPIO_PORT_7_PIN_2, GPIO_LEVEL_LOW,  GPIO_SUCCESS},
									{GPIO_PORT_7_PIN_2, GPIO_LEVEL_HIGH, GPIO_SUCCESS}};
st_r_drv_gpio_pin_rw_t gs_pF3[2] = {{GPIO_PORT_F_PIN_3, GPIO_LEVEL_LOW,  GPIO_SUCCESS},
									{GPIO_PORT_F_PIN_3, GPIO_LEVEL_HIGH, GPIO_SUCCESS}};
st_r_drv_gpio_pin_rw_t gs_pF0[2] = {{GPIO_PORT_F_PIN_0, GPIO_LEVEL_LOW,  GPIO_SUCCESS},
									{GPIO_PORT_F_PIN_0, GPIO_LEVEL_HIGH, GPIO_SUCCESS}};
st_r_drv_gpio_pin_rw_t gs_pA2[2] = {{GPIO_PORT_A_PIN_3, GPIO_LEVEL_LOW,  GPIO_SUCCESS},
									{GPIO_PORT_A_PIN_3, GPIO_LEVEL_HIGH, GPIO_SUCCESS}};
st_r_drv_gpio_pin_rw_t gs_pB0[2] = {{GPIO_PORT_B_PIN_0, GPIO_LEVEL_LOW,  GPIO_SUCCESS},
									{GPIO_PORT_B_PIN_0, GPIO_LEVEL_HIGH, GPIO_SUCCESS}};

#define	SET_DIR0(X)				{direct_control(g_gpio_handle, CTL_GPIO_PIN_WRITE, &gs_pA7[(X)]);}
#define	SET_DIR1(X)				{direct_control(g_gpio_handle, CTL_GPIO_PIN_WRITE, &gs_p72[(X)]);}
#define	SET_DIR2(X)				{direct_control(g_gpio_handle, CTL_GPIO_PIN_WRITE, &gs_pF3[(X)]);}
#define	SET_DIR3(X)				{direct_control(g_gpio_handle, CTL_GPIO_PIN_WRITE, &gs_pF0[(X)]);}
#define	SET_DIR4(X)				{direct_control(g_gpio_handle, CTL_GPIO_PIN_WRITE, &gs_pA2[(X)]);}
#define	SET_DUPLEX2(X)			SET_DIR2(X)
#define	SET_DUPLEX3(X)			SET_DIR3(X)
#define	SET_DUPLEX4(X)			SET_DIR4(X)

/***********************************************************************************************************************
 * Function Name: r_servo_init_port
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void	r_servo_init_port( void )
{
	//
	// SCIF0 SEL0	RS485 I/F
	//
#ifdef CONNECT_SERVO_TO_SCIFA0
	SET_DIR0(D_DIR_WRITE);
	fp0.sc_config_index = R_SC0;
	g_scifa_driver.open(&fp0);
#endif
	//
	// SCIF1 SEL1	RS485 I/F
	//
#ifdef CONNECT_SERVO_TO_SCIFA1
	SET_DIR1(D_DIR_WRITE);
	fp1.sc_config_index = R_SC1;
	g_scifa_driver.open(&fp1);
#endif
	//
	// SCIF2 SEL2
	//
#ifdef CONNECT_SERVO_TO_SCIFA2
	SET_DUPLEX2(D_FULL_DUPLEX);
	fp2.sc_config_index = R_SC2;
	g_scifa_driver.open(&fp2);
#endif
	//
	// SCIF3 SEL3
	//
#ifdef CONNECT_SERVO_TO_SCIFA3
	SET_DUPLEX3(D_FULL_DUPLEX);
	fp3.sc_config_index = R_SC3;
	g_scifa_driver.open(&fp3);
#endif
	//
	// SCIF4 SEL4
	//
#ifdef CONNECT_SERVO_TO_SCIFA4
	SET_DUPLEX4(D_FULL_DUPLEX);
//	fp4.sc_config_index = R_SC4;
//	g_scifa_driver.open(&fp4);
#endif
	//
	//	Power Gate(PB0) ON(=1) to use SERVO MOTOR
	//
    direct_control(g_gpio_handle, CTL_GPIO_PIN_WRITE, &gs_pB0[1]);
}

/***********************************************************************************************************************
* Function Name: r_servo_set_position
* Arguments    : Servo ID = r_id, Servo Position = r_val
* Return Value : None
***********************************************************************************************************************/
void	r_servo_set_position(
	uint16_t	r_id,
	uint16_t	r_val
)
{
	if(DYNAPARA_ANGLE_FULLRANGE <= r_val) {
		r_val = DYNAPARA_ANGLE_FULLRANGE - 1;
	}
	r_angle[r_id].w = r_val;
}


/***********************************************************************************************************************
* Function Name: r_servo_set_angle
* Arguments    : Servo ID = r_id, Servo Angle = r_val
* Return Value : None
***********************************************************************************************************************/
void	r_servo_set_angle(
	uint16_t	r_id,
	int32_t		r_val
)
{
	if(+DYNAPARA_ANGLE_HALFRANGE <= r_val) {
		r_val = +(DYNAPARA_ANGLE_HALFRANGE - 1);
	}
	if(-DYNAPARA_ANGLE_HALFRANGE >= r_val) {
		r_val = -(DYNAPARA_ANGLE_HALFRANGE - 1);
	}
	r_val += DYNAPARA_ANGLE_CENTER;
	r_angle[r_id].w = (uint16_t)r_val;
}

/***********************************************************************************************************************
* Function Name: calc_crc16
***********************************************************************************************************************/
static
uint16_t	calc_crc16(
	uint8_t		*ptr,
	uint8_t		len
)
{
	uint16_t	crc;
	uint8_t		i, j;

	crc = 0;
	for( i = 0; i < len; i++ ) {
		crc = crc ^ (uint16_t)(ptr[i] << 8);
		for( j = 0; j < 8; j++ ) {
			if( crc & 0x8000 ) {
				crc = (uint16_t)(crc << 1U) ^ 0x8005U;
			}
			else {
				crc = (uint16_t)(crc << 1U);
			}
		}
	}
	return crc;
}

/***********************************************************************************************************************
 * Function Name: r_servo_init
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
static
void	r_servo_init( void )
{
	uint16_u	sum;

	r_buf_txd2[ 0]	= 0xFF;							// preamble
	r_buf_txd2[ 1]	= 0xFF;							// preamble
	r_buf_txd2[ 2]	= 0xFD;							// preamble
	r_buf_txd2[ 3]	= 0x00;							// preamble
	r_buf_txd2[ 4]	= 0xFE;							// ID(fixed 254)
	r_buf_txd2[ 5]	= 24 - 7;						// Low(Length)
	r_buf_txd2[ 6]	= 0;							// High(Length)
	r_buf_txd2[ 7]	= DYNAINST_SYNC_WRITE;			// Instruction
	r_buf_txd2[ 8]	= 68;							// Low(Item)  = status return level
	r_buf_txd2[ 9]	= 0;							// High(Item) = status return level
	r_buf_txd2[10]	= 1;							// Low(Byte Size)
	r_buf_txd2[11]	= 0;							// High(Byte Size)
	r_buf_txd2[12]	= 0 + D_OFFSET_ID;				// ID
	r_buf_txd2[13]	= 1;							// 0=ping, 1=ping+read, 2=all
	r_buf_txd2[14]	= 1 + D_OFFSET_ID;				// ID
	r_buf_txd2[15]	= 1;							// 0=ping, 1=ping+read, 2=all
	r_buf_txd2[16]	= 2 + D_OFFSET_ID;				// ID
	r_buf_txd2[17]	= 1;							// 0=ping, 1=ping+read, 2=all
	r_buf_txd2[18]	= 3 + D_OFFSET_ID;				// ID
	r_buf_txd2[19]	= 1;							// 0=ping, 1=ping+read, 2=all
	r_buf_txd2[20]	= 4 + D_OFFSET_ID;				// ID
	r_buf_txd2[21]	= 1;							// 0=ping, 1=ping+read, 2=all
	sum.w			= calc_crc16(r_buf_txd2, 22);	// Check SUM
	r_buf_txd2[22]	= sum.b[0];
	r_buf_txd2[23]	= sum.b[1];
	//
#ifdef CONNECT_SERVO_TO_SCIFA0
	SET_DIR0(D_DIR_WRITE);
	g_scifa_driver.write( &fp4, r_buf_txd2, 24 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA1
	SET_DIR1(D_DIR_WRITE);
	g_scifa_driver.write( &fp1, r_buf_txd2, 24 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA2
	SET_DUPLEX2(D_FULL_DUPLEX);
	g_scifa_driver.write( &fp2, r_buf_txd2, 24 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA3
	SET_DUPLEX3(D_FULL_DUPLEX);
	g_scifa_driver.write( &fp3, r_buf_txd2, 24 );
#endif
#ifdef	USE_DEBUG_PRINTF_INFORMATION
	fprintf(stdout,"init:");
	for(int i = 0; i < 24; i++) {
		fprintf(stdout,"%02lX,", r_buf_rxd2[i]);
	}
	fprintf(stdout,"\n");
#endif	// USE_DEBUG_PRINTF_INFORMATION
	//
	R_OS_TaskSleep(10);
	//
	r_buf_txd2[ 0]	= 0xFF;							// preamble
	r_buf_txd2[ 1]	= 0xFF;							// preamble
	r_buf_txd2[ 2]	= 0xFD;							// preamble
	r_buf_txd2[ 3]	= 0x00;							// preamble
	r_buf_txd2[ 4]	= 0xFE;							// ID(fixed 254)
	r_buf_txd2[ 5]	= 24 - 7;						// Low(Length)
	r_buf_txd2[ 6]	= 0;							// High(Length)
	r_buf_txd2[ 7]	= DYNAINST_SYNC_WRITE;			// Instruction
	r_buf_txd2[ 8]	= 64;							// Low(Item)  = Torque Enable
	r_buf_txd2[ 9]	= 0;							// High(Item) = Torque Enable
	r_buf_txd2[10]	= 1;							// Low(Byte Size)
	r_buf_txd2[11]	= 0;							// High(Byte Size)
	r_buf_txd2[12]	= 0 + D_OFFSET_ID;				// ID
	r_buf_txd2[13]	= 1;							// 1=enable, 0=disable
	r_buf_txd2[14]	= 1 + D_OFFSET_ID;				// ID
	r_buf_txd2[15]	= 1;							// 1=enable, 0=disable
	r_buf_txd2[16]	= 2 + D_OFFSET_ID;				// ID
	r_buf_txd2[17]	= 1;							// 1=enable, 0=disable
	r_buf_txd2[18]	= 3 + D_OFFSET_ID;				// ID
	r_buf_txd2[19]	= 1;							// 1=enable, 0=disable
	r_buf_txd2[20]	= 4 + D_OFFSET_ID;				// ID
	r_buf_txd2[21]	= 1;							// 1=enable, 0=disable
	sum.w			= calc_crc16(r_buf_txd2, 22);	// Check SUM
	r_buf_txd2[22]	= sum.b[0];
	r_buf_txd2[23]	= sum.b[1];
	//
#ifdef CONNECT_SERVO_TO_SCIFA0
	SET_DIR0(D_DIR_WRITE);
	g_scifa_driver.write( &fp4, r_buf_txd2, 24 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA1
	SET_DIR1(D_DIR_WRITE);
	g_scifa_driver.write( &fp1, r_buf_txd2, 24 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA2
	SET_DUPLEX2(D_FULL_DUPLEX);
	g_scifa_driver.write( &fp2, r_buf_txd2, 24 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA3
	SET_DUPLEX3(D_FULL_DUPLEX);
	g_scifa_driver.write( &fp3, r_buf_txd2, 24 );
#endif
#ifdef	USE_DEBUG_PRINTF_INFORMATION
	fprintf(stdout,"init:");
	for(int i = 0; i < 24; i++) {
		fprintf(stdout,"%02lX,", r_buf_rxd2[i]);
	}
	fprintf(stdout,"\n");
#endif	// USE_DEBUG_PRINTF_INFORMATION
	R_OS_TaskSleep(10);
}

/***********************************************************************************************************************
 * Function Name: r_servo_send
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void	r_servo_send( void )
{
	uint16_u	sum;

	r_buf_txd2[ 0]	= 0xFF;							// preamble
	r_buf_txd2[ 1]	= 0xFF;							// preamble
	r_buf_txd2[ 2]	= 0xFD;							// preamble
	r_buf_txd2[ 3]	= 0x00;							// preamble
	r_buf_txd2[ 4]	= 0xFE;							// ID(fixed 254)
	r_buf_txd2[ 5]	= 39 - 7;						// Low(Length)
	r_buf_txd2[ 6]	= 0;							// High(Length)
	r_buf_txd2[ 7]	= DYNAINST_SYNC_WRITE;			// Instruction
	r_buf_txd2[ 8]	= 0x74;							// Low(Item)  = Goal Position
	r_buf_txd2[ 9]	= 0;							// High(Item) = Goal Position
	r_buf_txd2[10]	= 4;							// Low(Byte Size)
	r_buf_txd2[11]	= 0;							// High(Byte Size)
	r_buf_txd2[12]	= 0 + D_OFFSET_ID;				// ID
	r_buf_txd2[13]	= r_angle[0].b[0];				// low(angle)
	r_buf_txd2[14]	= r_angle[0].b[1];				// high(angle)
	r_buf_txd2[15]	= 0;							//
	r_buf_txd2[16]	= 0;							//
	r_buf_txd2[17]	= 1 + D_OFFSET_ID;				// ID
	r_buf_txd2[18]	= r_angle[1].b[0];				// low(angle)
	r_buf_txd2[19]	= r_angle[1].b[1];				// high(angle)
	r_buf_txd2[20]	= 0;							//
	r_buf_txd2[21]	= 0;							//
	r_buf_txd2[22]	= 2 + D_OFFSET_ID;				// ID
	r_buf_txd2[23]	= r_angle[2].b[0];				// low(angle)
	r_buf_txd2[24]	= r_angle[2].b[1];				// high(angle)
	r_buf_txd2[25]	= 0;							//
	r_buf_txd2[26]	= 0;							//
	r_buf_txd2[27]	= 3 + D_OFFSET_ID;				// ID
	r_buf_txd2[28]	= r_angle[3].b[0];				// low(angle)
	r_buf_txd2[29]	= r_angle[3].b[1];				// high(angle)
	r_buf_txd2[30]	= 0;							//
	r_buf_txd2[31]	= 0;							//
	r_buf_txd2[32]	= 4 + D_OFFSET_ID;				// ID
	r_buf_txd2[33]	= r_angle[4].b[0];				// low(angle)
	r_buf_txd2[34]	= r_angle[4].b[1];				// high(angle)
	r_buf_txd2[35]	= 0;							//
	r_buf_txd2[36]	= 0;							//
	sum.w			= calc_crc16(r_buf_txd2, 37);	// Check SUM
	r_buf_txd2[37]	= sum.b[0];
	r_buf_txd2[38]	= sum.b[1];
	//
#ifdef CONNECT_SERVO_TO_SCIFA0
	SET_DIR0(D_DIR_WRITE);
	g_scifa_driver.write( &fp4, r_buf_txd2, 39 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA1
	SET_DIR1(D_DIR_WRITE);
	g_scifa_driver.write( &fp1, r_buf_txd2, 39 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA2
	SET_DUPLEX2(D_FULL_DUPLEX);
	g_scifa_driver.write( &fp2, r_buf_txd2, 39 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA3
	SET_DUPLEX3(D_FULL_DUPLEX);
	g_scifa_driver.write( &fp3, r_buf_txd2, 39 );
#endif
#ifdef	USE_DEBUG_PRINTF_INFORMATION
	fprintf(stdout,"send:");
	for(int i = 0; i < 39; i++) {
		fprintf(stdout,"%02lX,", r_buf_rxd2[i]);
	}
	fprintf(stdout,"\n");
#endif	// USE_DEBUG_PRINTF_INFORMATION
}

/***********************************************************************************************************************
 * Function Name: r_servo_get_position
 ***********************************************************************************************************************/
uint16_t	r_servo_get_position(
	uint8_t	id
)
{
	uint16_u	sum;
	uint16_u	retval;

	r_buf_txd2[ 0]	= 0xFF;							// preamble
	r_buf_txd2[ 1]	= 0xFF;							// preamble
	r_buf_txd2[ 2]	= 0xFD;							// preamble
	r_buf_txd2[ 3]	= 0x00;							// preamble
	r_buf_txd2[ 4]	= id + D_OFFSET_ID;				// ID
	r_buf_txd2[ 5]	= 14 - 7;						// Low(Length)
	r_buf_txd2[ 6]	= 0;							// High(Length)
	r_buf_txd2[ 7]	= DYNAINST_READ_DATA;			// Instruction
	r_buf_txd2[ 8]	= 132;							// Low(Item)  = Present Position
	r_buf_txd2[ 9]	= 0;							// High(Item) = Present Position
	r_buf_txd2[10]	= 4;							// Low(Byte Size)
	r_buf_txd2[11]	= 0;							// High(Byte Size)
	sum.w			= calc_crc16(r_buf_txd2, 12);	// Check SUM
	r_buf_txd2[12]	= sum.b[0];
	r_buf_txd2[13]	= sum.b[1];
	//
#ifdef CONNECT_SERVO_TO_SCIFA2
	SET_DUPLEX2(D_HALF_DUPLEX);
	r_buf_rxd2[14 + 9] = r_buf_rxd2[14 + 10] = 0;
	g_scifa_driver.write( &fp2, r_buf_txd2, 14 );
#endif
#ifdef CONNECT_SERVO_TO_SCIFA3
	SET_DUPLEX3(D_HALF_DUPLEX);
	r_buf_rxd2[14 + 9] = r_buf_rxd2[14 + 10] = 0;
	g_scifa_driver.write( &fp3, r_buf_txd2, 14 );
#endif
	//
	R_OS_TaskSleep(3);
	retval.w = 0;
	//
#ifdef CONNECT_SERVO_TO_SCIFA2
	g_scifa_driver.read( &fp2, r_buf_rxd2, 14+15 );
	if((0 != r_buf_rxd2[14 + 9]) || (0 != r_buf_rxd2[14 + 10]))
	{
		retval.b[0] = r_buf_rxd2[14 +  9];
		retval.b[1] = r_buf_rxd2[14 + 10];
	}
	SET_DUPLEX2(D_FULL_DUPLEX);
#endif
#ifdef CONNECT_SERVO_TO_SCIFA3
	g_scifa_driver.read( &fp3, r_buf_rxd2, 14+15 );
	if((0 != r_buf_rxd2[14 + 9]) || (0 != r_buf_rxd2[14 + 10]))
	{
		retval.b[0] = r_buf_rxd2[14 +  9];
		retval.b[1] = r_buf_rxd2[14 + 10];
	}
	SET_DUPLEX3(D_FULL_DUPLEX);
#endif
	return retval.w;
}

/***********************************************************************************************************************
 * Function Name: r_get_current_positions
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
int		r_get_current_positions(void)
{
	int		flg_connect = 0;

	for(uint8_t i = 0; i < D_CNT_SERVO; i++) {
		r_current_angle[i] = r_servo_get_position(i);
		if(0 != r_current_angle[i])
		{
			flg_connect++;
		}
	}
	return flg_connect;
}

/***********************************************************************************************************************
 * Function Name: r_goto_home_position
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void	r_goto_home_position(void)
{
	r_servo_init();
	if(0 < r_get_current_positions())
	{
		for(int32_t j = 0; j < D_DIV_SLOWSETHOME; j++) {
			for(uint8_t i = 0; i < D_CNT_SERVO; i++) {
				uint32_t	tmpval;

				tmpval  = (uint32_t)r_current_angle[i] * (D_DIV_SLOWSETHOME - j);
				tmpval += (uint32_t)r_angle_init[i] * j;
				tmpval /= D_DIV_SLOWSETHOME;
				r_angle[i].w = (uint16_t)tmpval;
			}
			r_servo_send();
			R_OS_TaskSleep(D_TIME_SLOWSETHOME);
		}
	}
	//
	//	Servoの初期角度を設定する
	//
	r_servo_set_position(0, r_angle_init[0]);
	r_servo_set_position(1, r_angle_init[1]);
	r_servo_set_position(2, r_angle_init[2]);
	r_servo_set_position(3, r_angle_init[3]);
	r_servo_set_position(4, r_angle_init[4]);
	r_servo_send();
}

/***********************************************************************************************************************
 * EOF
 ***********************************************************************************************************************/
