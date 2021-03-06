/*
  CoDrone.h - CoDrone library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  LastUpdate : 2018-01-30
*/

#ifndef CoDrone_h
#define CoDrone_hs
#include "Arduino.h"
#include <avr/interrupt.h>

/***********************************************************************/

# define JOY_UP_LIMIT          1023 - 100
# define JOY_UP_RETURN_LIMIT   512	+ 100
# define JOY_DOWN_LIMIT        0 	+ 100
# define JOY_DOWN_RETURN_LIMIT 512 	- 100
	
/***********************************************************************/
//////////////////////////typedef///////////////////////////////////////
/***********************************************************************/

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;
typedef uint32_t u32;
//typedef uint16_t u16;
typedef uint8_t u8;

/***********************************************************************/
////////////////////////Serial Select////////////////////////////////////
/***********************************************************************/
#if defined(UBRRH) || defined(UBRR0H)
#define FIND_HWSERIAL0
#endif

#if defined(UBRR1H)
#define FIND_HWSERIAL1
#endif

#if defined (FIND_HWSERIAL1)	//Serial Other Setting	- two serial
#define DRONE_SERIAL 	Serial1		//drone serial
#define DEBUG_SERIAL    Serial		//debug serial1

#else							//Serial Smart Setting	- one serial
#define DRONE_SERIAL 	Serial		//drone serial	
#define DEBUG_SERIAL    Serial1		//debug serial1

#endif

/***********************************************************************/
////////////////////////////HEADER///////////////////////////////////////
/***********************************************************************/
//START CODE
#define START1    			0x0A
#define START2   			0x55

/***********************************************************************/

//serial buffer
#if defined (FIND_HWSERIAL1)	// Atmega128
#define MAX_PACKET_LENGTH 	200

#else							// Smart Setting
#define MAX_PACKET_LENGTH 	40
#endif

/***********************************************************************/

//#define	SEND_CHECK_TIME    	3
#define	SEND_CHECK_TIME    		50

/***********************************************************************/

#define ROLL						CoDrone.roll
#define PITCH						CoDrone.pitch
#define YAW							CoDrone.yaw
#define THROTTLE					CoDrone.throttle

#define STATE						CoDrone.state
#define SEND_INTERVAL				CoDrone.SendInterval
#define ANALOG_OFFSET				CoDrone.analogOffset
#define BATTERY						CoDrone.battery
#define RSSI						CoDrone.rssi

#define AttitudeROLL				CoDrone.attitudeRoll
#define AttitudePITCH				CoDrone.attitudePitch
#define AttitudeYAW					CoDrone.attitudeYaw

/***********************************************************************/

#define DiscoverStop  			cType_LinkDiscoverStop
#define DiscoverStart  			cType_LinkDiscoverStart

#define PollingStop				cType_LinkRssiPollingStop
#define PollingStart			cType_LinkRssiPollingStart

#define	PAIRING					CoDrone.pairing

#define LinkModeMute 			LinkBroadcast_Mute
#define LinkModeActive			LinkBroadcast_Active
#define LinkModePassive 		LinkBroadcast_Passive

#define	NearbyDrone    			1
#define	ConnectedDrone  		2
#define AddressInputDrone 		3
#define	Nearest					1

//eeprom address
#define	EEP_AddressCheck   		10
#define	EEP_AddressFirst  		11
#define	EEP_AddressEnd  		15

/////////////////////////////////////////////////////////////////////////

#define FREE_PLAY				0
#define TEAM_RED				1
#define TEAM_BLUE				2
#define TEAM_GREEN				3
#define TEAM_YELLOW				4

#define MAX_ENERGY				8
/**********************	IR DATA****************************************/

#define FREE_MISSILE		0xaa01
#define RED_MISSILE			0xbb01
#define BLUE_MISSILE		0xcc01
#define GREEN_MISSILE		0xdd01
#define YELLOW_MISSILE		0xee01

/***********************************************************************/

#define Flight 					dMode_Flight
#define FlightNoGuard			dMode_FlightNoGuard,
#define FlightFPV				dMode_FlightFPV
#define Drive 				 	dMode_Drive
#define DriveFPV				dMode_DriveFPV

#define Absolute 				cSet_Absolute
#define Relative		 		cSet_Relative

#define TakeOff 				fEvent_TakeOff
#define FlipFront				fEvent_FlipFront
#define FlipRear				fEvent_FlipRear
#define FlipLeft				fEvent_flipLeft
#define FlipRight				fEvent_FlipRight
#define Stop					fEvent_Stop
#define Landing					fEvent_Landing
#define TurnOver				fEvent_TurnOver
#define Shot					fEvent_Shot
#define UnderAttack				fEvent_UnderAttack
#define Square					fEvent_Square
#define CircleLeft				fEvent_CircleLeft
#define CircleRight				fEvent_CircleRight
#define Rotate180				fEvent_Rotate180

#define RollIncrease			trim_RollIncrease
#define RollDecrease			trim_RollDecrease
#define PitchIncrease			trim_PitchIncrease
#define PitchDecrease			trim_PitchDecrease
#define YawIncrease				trim_YawIncrease
#define YawDecrease				trim_YawDecrease
#define ThrottleIncrease		trim_ThrottleIncrease
#define ThrottleDecrease		trim_ThrottleDecrease

// 2018, 1, 22 added
#define LEFT 					direction_left
#define FORWARD 				direction_forward
#define RIGHT 					direction_right
#define BACKWARD				direction_backward
#define UP  					direction_up
#define DOWN 					direction_down

// 2018, 3, 12 added
#define ZIGZAG 					Seq_zigzag
#define SWAY 					Seq_sway
#define SQUARE 					Seq_square
#define CIRCLE 					Seq_circle
#define SPIRAL 					Seq_spiral
#define TRIANGLE 				Seq_triangle
#define HOP 					Seq_hop

enum Direction
{
	direction_none = 0,
	direction_left,
	direction_forward,
	direction_right,
	direction_backward,
	direction_up,
	direction_down,
	direction_EndOfType
};

enum Sequence
{
	Seq_none = 0,
	Seq_zigzag,
	Seq_sway,
	Seq_square,
	Seq_circle,
	Seq_spiral,
	Seq_triangle,
	Seq_hop,
	Seq_EndOfType,
};
enum Angle
{
	ANGLE_30 = 30,
	ANGLE_45 = 45,
	ANGLE_60 = 60,
	ANGLE_90 = 90,
	ANGLE_120 = 120,
	ANGLE_135 = 135,
	ANGLE_150 = 150,
	ANGLE_180 = 180,
	ANGLE_210 = 210,
	ANGLE_225 = 225,
	ANGLE_240 = 240,
	ANGLE_270 = 270,
	ANGLE_300 = 300,
	ANGLE_315 = 315, 
	ANGLE_330 = 330
};
//
typedef struct gyrodata
{
	int roll;
	int pitch;
	int yaw;
}gyrodata;

typedef struct acceldata
{
	int x;
	int y;
	int z;
}acceldata;

//angle
typedef struct angledata
{
	int roll;
	int pitch;
	int yaw;
}angledata;

typedef struct trimdata
{
	int roll;
	int pitch;
	int yaw;
	int throttle;
}trimdata;

typedef struct optdata
{
	int x;
	int y;
}optdata;







/***********************************************************************/
/////////////////////////LINK MODULE/////////////////////////////////////
/***********************************************************************/
enum ModeLink
{
	linkMode_None = 0,	 	 	///< ¾øÀ½
	linkMode_Boot,	 	 	 	///< ºÎÆÃ 	 	
	linkMode_Ready,	 		 	///< ´ë±â(¿¬°á Àü)
	linkMode_Connecting,	 	///< ÀåÄ¡ ¿¬°á Áß
	linkMode_Connected,	 	 	///< ÀåÄ¡ ¿¬°á ¿Ï·á
	linkMode_Disconnecting,		///< ÀåÄ¡ ¿¬°á ÇØÁ¦ Áß
	linkMode_ReadyToReset,		///< ¸®¼Â ´ë±â(1ÃÊ µÚ¿¡ ÀåÄ¡ ¸®¼Â)	
	linkMode_EndOfType
};

enum ModeLinkBroadcast
{
	LinkBroadcast_None = 0, 	///< ¾øÀ½
	LinkBroadcast_Mute, 		///< LINK ¸ðµâ µ¥ÀÌÅÍ ¼Û½Å Áß´Ü . ¾ÆµÎÀÌ³ë Æß¿þ¾î ´Ù¿î·Îµå
	LinkBroadcast_Active, 		///< ÆäÆ®·Ð ¿¬°á ¸ðµå . ¸ðµå ÀüÈ¯ ¸Þ¼¼Áö Àü¼Û
	LinkBroadcast_Passive, 		///< ÆäÆ®·Ð ¿¬°á ¸ðµå . ¸ðµå ÀüÈ¯ ¸Þ¼¼Áö Àü¼ÛÇÏÁö ¾ÊÀ½
	LinkBroadcast_EndOfType
};

enum EventLink
{
	linkEvent_None = 0,								///< ¾øÀ½
	
	linkEvent_SystemReset,							///< ½Ã½ºÅÛ ¸®¼Â
	
	linkEvent_Initialized,							///< ÀåÄ¡ ÃÊ±âÈ­ ¿Ï·á
	
	linkEvent_Scanning,								///< ÀåÄ¡ °Ë»ö ½ÃÀÛ
	linkEvent_ScanStop,								///< ÀåÄ¡ °Ë»ö Áß´Ü

	linkEvent_FoundDroneService,					///< µå·Ð ¼­ºñ½º °Ë»ö ¿Ï·á

	linkEvent_Connecting,							///< ÀåÄ¡ ¿¬°á ½ÃÀÛ		
	linkEvent_Connected,							///< ÀåÄ¡ ¿¬°á

	linkEvent_ConnectionFaild,						///< ¿¬°á ½ÇÆÐ
	linkEvent_ConnectionFaildNoDevices,				///< ¿¬°á ½ÇÆÐ - ÀåÄ¡°¡ ¾øÀ½
	linkEvent_ConnectionFaildNotReady,				///< ¿¬°á ½ÇÆÐ - ´ë±â »óÅÂ°¡ ¾Æ´Ô

	linkEvent_PairingStart,							///< Æä¾î¸µ ½ÃÀÛ
	linkEvent_PairingSuccess,						///< Æä¾î¸µ ¼º°ø
	linkEvent_PairingFaild,							///< Æä¾î¸µ ½ÇÆÐ

	linkEvent_BondingSuccess,						///< Bonding ¼º°ø

	linkEvent_LookupAttribute,						///< ÀåÄ¡ ¼­ºñ½º ¹× ¼Ó¼º °Ë»ö(GATT Event ½ÇÇà)

	linkEvent_RssiPollingStart,						///< RSSI Ç®¸µ ½ÃÀÛ
	linkEvent_RssiPollingStop,						///< RSSI Ç®¸µ ÁßÁö

	linkEvent_DiscoverService,						///< ¼­ºñ½º °Ë»ö
	linkEvent_DiscoverCharacteristic,				///< ¼Ó¼º °Ë»ö
	linkEvent_DiscoverCharacteristicDroneData,		///< ¼Ó¼º °Ë»ö
	linkEvent_DiscoverCharacteristicDroneConfig,	///< ¼Ó¼º °Ë»ö
	linkEvent_DiscoverCharacteristicUnknown,		///< ¼Ó¼º °Ë»ö
	linkEvent_DiscoverCCCD,							///< CCCD °Ë»ö

	linkEvent_ReadyToControl,						///< Á¦¾î ÁØºñ ¿Ï·á

	linkEvent_Disconnecting,						///< ÀåÄ¡ ¿¬°á ÇØÁ¦ ½ÃÀÛ
	linkEvent_Disconnected,							///< ÀåÄ¡ ¿¬°á ÇØÁ¦ ¿Ï·á

	linkEvent_GapLinkParamUpdate,					///< GAP_LINK_PARAM_UPDATE_EVENT

	linkEvent_RspReadError,							///< RSP ÀÐ±â ¿À·ù
	linkEvent_RspReadSuccess,						///< RSP ÀÐ±â ¼º°ø

	linkEvent_RspWriteError,						///< RSP ¾²±â ¿À·ù
	linkEvent_RspWriteSuccess,						///< RSP ¾²±â ¼º°ø

	linkEvent_SetNotify,							///< Notify È°¼ºÈ­

	linkEvent_Write,								///< µ¥ÀÌÅÍ ¾²±â ÀÌº¥Æ®

	EndOfType
};


/***********************************************************************/
//////////////////////////////DRONE/////////////////////////////////////
/***********************************************************************/
enum DataType
{
	dType_None = 0, 				///< ¾øÀ½
	
	// ½Ã½ºÅÛ Á¤º¸
	dType_Ping, 					///< Åë½Å È®ÀÎ(reserve)
	dType_Ack, 						///< µ¥ÀÌÅÍ ¼ö½Å¿¡ ´ëÇÑ ÀÀ´ä
	dType_Error, 					///< ¿À·ù(reserve, ºñÆ® ÇÃ·¡±×´Â ÃßÈÄ¿¡ ÁöÁ¤)
	dType_Request, 					///< ÁöÁ¤ÇÑ Å¸ÀÔÀÇ µ¥ÀÌÅÍ ¿äÃ»
	dType_DeviceName, 				///< ÀåÄ¡ÀÇ ÀÌ¸§ º¯°æ
	
	// Á¶Á¾, ¸í·É
	dType_Control = 0x10, 			///< Á¶Á¾
	dType_Command, 					///< ¸í·É
	dType_Command2, 				///< ´ÙÁß ¸í·É(2°¡Áö ¼³Á¤À» µ¿½Ã¿¡ º¯°æ)
	DType_Command3, 				///< ´ÙÁß ¸í·É(3°¡Áö ¼³Á¤À» µ¿½Ã¿¡ º¯°æ)
	
	// LED
	dType_LedMode = 0x20, 			///< LED ¸ðµå ÁöÁ¤
	dType_LedMode2, 				///< LED ¸ðµå 2°³ ÁöÁ¤
	dType_LedModeCommand, 			///< LED ¸ðµå, Ä¿¸Çµå
	dType_LedModeCommandIr, 		///< LED ¸ðµå, Ä¿¸Çµå, IR µ¥ÀÌÅÍ ¼Û½Å
	dType_LedModeColor, 			///< LED ¸ðµå 3»ö Á÷Á¢ ÁöÁ¤
	dType_LedModeColor2, 			///< LED ¸ðµå 3»ö Á÷Á¢ ÁöÁ¤ 2°³
	dType_LedEvent, 				///< LED ÀÌº¥Æ®
	dType_LedEvent2, 				///< LED ÀÌº¥Æ® 2°³,
	dType_LedEventCommand, 			///< LED ÀÌº¥Æ®, Ä¿¸Çµå
	dType_LedEventCommandIr,		///< LED ÀÌº¥Æ®, Ä¿¸Çµå, IR µ¥ÀÌÅÍ ¼Û½Å
	dType_LedEventColor, 			///< LED ÀÌº¥Æ® 3»ö Á÷Á¢ ÁöÁ¤
	dType_LedEventColor2, 			///< LED ÀÌº¥Æ® 3»ö Á÷Á¢ ÁöÁ¤ 2°³
	
	//update-170426
	dType_LedDefaultColor,  		// LED ÃÊ±â ¸ðµå 3»ö Á÷Á¢ ÁöÁ¤
    dType_LedDefaultColor2, 		// LED ÃÊ±â ¸ðµå 3»ö Á÷Á¢ ÁöÁ¤ 2°³
	
	// »óÅÂ
	dType_Address = 0x30, 			///< IEEE address
	dType_State, 					///< µå·ÐÀÇ »óÅÂ(ºñÇà ¸ðµå, ¹æÀ§±âÁØ, ¹èÅÍ¸®·®)
	dType_Attitude, 				///< µå·ÐÀÇ ÀÚ¼¼(Vector)
	dType_GyroBias,					///< ÀÚÀÌ·Î ¹ÙÀÌ¾î½º °ª(Vector)
	dType_TrimAll, 					///< ÀüÃ¼ Æ®¸² (ºñÇà+ÁÖÇà)ü
	dType_TrimFlight,				///< ºñÇà Æ®¸²
	dType_TrimDrive, 				///< ÁÖÇà Æ®¸²
			
	//update-170426
	dType_CountFlight,            	// ºñÇà °ü·Ã Ä«¿îÆ®
	dType_CountDrive,             	// ÁÖÇà °ü·Ã Ä«¿îÆ® 
						
	// µ¥ÀÌÅÍ ¼Û¼ö½Å	
	dType_IrMessage = 0x40, 		///< IR µ¥ÀÌÅÍ ¼Û¼ö½Å
		
	// ¼¾¼­
	dType_ImuRawAndAngle = 0x50, 	///< IMU Raw + Angle
	dType_Pressure, 				///< ¾Ð·Â ¼¾¼­ µ¥ÀÌÅÍ
	dType_ImageFlow, 				///< ImageFlow
	dType_Button, 					///< ¹öÆ° ÀÔ·Â
	dType_Battery, 					///< ¹èÅÍ¸®
	dType_Motor, 					///< ¸ðÅÍ Á¦¾î ¹× ÇöÀç Á¦¾î °ª È®ÀÎ
	dType_Temperature, 				///< ¿Âµµ
	//update-170426
	dType_Range,					// °Å¸® ¼¾¼­
	// ¸µÅ© º¸µå
	dType_LinkState = 0xE0,			///< ¸µÅ© ¸ðµâÀÇ »óÅÂ
	dType_LinkEvent,				///< ¸µÅ© ¸ðµâÀÇ ÀÌº¥Æ®
	dType_LinkEventAddress,			///< ¸µÅ© ¸ðµâÀÇ ÀÌº¥Æ® + ÁÖ¼Ò
	dType_LinkRssi,					///< ¸µÅ©¿Í ¿¬°áµÈ ÀåÄ¡ÀÇ RSSI°ª
	dType_LinkDiscoveredDevice,		///< °Ë»öµÈ ÀåÄ¡
	dType_LinkPasscode,          	///< ¿¬°áÇÒ ´ë»ó ÀåÄ¡ÀÇ ¾ÏÈ£ ÁöÁ¤
	dType_StringMessage = 0xD0, 	///< ¹®ÀÚ¿­ ¸Þ¼¼Áö
	dType_EndOfType
};

/***********************************************************************/
enum CommandType
{
	cType_None = 0, 				///< ÀÌº¥Æ® ¾øÀ½
	
	// ¼³Á¤	
	cType_ModeDrone = 0x10, 		///< µå·Ð µ¿ÀÛ ¸ðµå ÀüÈ¯
	
	// Á¦¾î
	cType_Coordinate = 0x20, 		///< ¹æÀ§ ±âÁØ º¯°æ
	cType_Trim, 										///< Æ®¸² º¯°æ
	cType_FlightEvent, 				///< ºñÇà ÀÌº¥Æ® ½ÇÇà
	cType_DriveEvent, 				///< ÁÖÇà ÀÌº¥Æ® ½ÇÇà
	cType_Stop, 					///< Á¤Áö
	cType_ResetHeading = 0x50, 		///< ¹æÇâÀ» ¸®¼Â(¾Û¼Ö·çÆ® ¸ðµå ÀÏ ¶§ ÇöÀç headingÀ» 0µµ·Î º¯°æ)
	cType_ClearGyroBiasAndTrim, 	/// ÀÚÀÌ·Î ¹ÙÀÌ¾î½º¿Í Æ®¸² ¼³Á¤ ÃÊ±âÈ­
	
	//update-170426
	cType_ClearTrim,					// Æ®¸² ÃÊ±âÈ­
	
	// Åë½Å
	cType_PairingActivate = 0x80, 	///< Æä¾î¸µ È°¼ºÈ­
	cType_PairingDeactivate, 		///< Æä¾î¸µ ºñÈ°¼ºÈ­
	cType_TerminateConnection, 		///< ¿¬°á Á¾·á
	
	// ¿äÃ»
	cType_Request = 0x90, 			///< ÁöÁ¤ÇÑ Å¸ÀÔÀÇ µ¥ÀÌÅÍ ¿äÃ»
	
	// ¸µÅ© º¸µå
	cType_LinkModeBroadcast = 0xE0, ///< LINK ¼Û¼ö½Å ¸ðµå ÀüÈ¯
	cType_LinkSystemReset, 			///< ½Ã½ºÅÛ Àç½ÃÀÛ
	cType_LinkDiscoverStart, 		///< ÀåÄ¡ °Ë»ö ½ÃÀÛ
	cType_LinkDiscoverStop, 		///< ÀåÄ¡ °Ë»ö Áß´Ü
	cType_LinkConnect, 				///< ¿¬°á
	cType_LinkDisconnect, 			///< ¿¬°á ÇØÁ¦
	cType_LinkRssiPollingStart, 	///< RSSI ¼öÁý ½ÃÀÛ
	cType_LinkRssiPollingStop, 		///< RSSI ¼öÁý Áß´Ü

	cType_EndOfType
};

/***********************************************************************/
enum ModeDrone
{
	dMode_None = 0, 				///< ¾øÀ½
	
	dMode_Flight = 0x10, 			///< ºñÇà ¸ðµå(°¡µå Æ÷ÇÔ)
	dMode_FlightNoGuard, 			///< ºñÇà ¸ðµå(°¡µå ¾øÀ½)
	dMode_FlightFPV, 				///< ºñÇà ¸ðµå(FPV)
	
	dMode_Drive = 0x20, 			///< ÁÖÇà ¸ðµå
	dMode_DriveFPV, 				///< ÁÖÇà ¸ðµå(FPV)
	dMode_Test = 0x30, 				///< Å×½ºÆ® ¸ðµå
	dMode_EndOfType
};

/***********************************************************************/
enum ModeVehicle
{
	vMode_None = 0,
	vMode_Boot, 					///< ºÎÆÃ
	vMode_Wait, 					///< ¿¬°á ´ë±â »óÅÂ
	vMode_Ready, 					///< ´ë±â »óÅÂ
	vMode_Running, 					///< ¸ÞÀÎ ÄÚµå µ¿ÀÛ
	vMode_Update, 					///< Æß¿þ¾î ¾÷µ¥ÀÌÆ®
	vMode_UpdateComplete,			///< Æß¿þ¾î ¾÷µ¥ÀÌÆ® ¿Ï·á
	vMode_Error, 					///< ¿À·ù
	vMode_EndOfType
};

/***********************************************************************/
enum ModeFlight
{
	fMode_None = 0,
	fMode_Ready, 					///< ºñÇà ÁØºñ
	fMode_TakeOff, 					///< ÀÌ·ú (Flight·Î ÀÚµ¿ÀüÈ¯)
	fMode_Flight, 					///< ºñÇà
	fMode_Flip, 					///< È¸Àü
	fMode_Stop, 					///< °­Á¦ Á¤Áö
	fMode_Landing, 					///< Âø·ú
	fMode_Reverse, 					///< µÚÁý±â
	fMode_Accident, 				///< »ç°í (Ready·Î ÀÚµ¿ÀüÈ¯)
	fMode_Error, 					///< ¿À·ù
	fMode_EndOfType
};

/***********************************************************************/
enum ModeDrive
{
	dvMode_None = 0,
	dvMode_Ready, 					///< ÁØºñ
	dvMode_Start, 					///< Ãâ¹ß
	dvMode_Drive, 					///< ÁÖÇà
	dvMode_Stop, 					///< °­Á¦ Á¤Áö
	dvMode_Accident, 				///< »ç°í (Ready·Î ÀÚµ¿ÀüÈ¯)
	dvMode_Error, 					///< ¿À·ù
	dvMode_EndOfType
};

/***********************************************************************/
enum SensorOrientation
{
	senOri_None = 0,
	senOri_Normal, 					///< Á¤»ó
	senOri_ReverseStart, 			///< µÚÁýÈ÷±â ½ÃÀÛ
	senOri_Reverse, 				///< µÚÁýÈû
	senOri_EndOfType
};

/***********************************************************************/
enum Coordinate
{
	cSet_None = 0, 					///< ¾øÀ½
	
	cSet_Absolute, 					///< °íÁ¤ ÁÂÇ¥°è
	cSet_Relative, 					///< »ó´ë ÁÂÇ¥°è
	
	cSet_EndOfType
};

/***********************************************************************/

enum Trim
{
	trim_None = 0, 					///< ¾øÀ½
	trim_RollIncrease, 				///< Roll Áõ°¡
	trim_RollDecrease, 				///< Roll °¨¼Ò
	trim_PitchIncrease, 			///< Pitch Áõ°¡
	trim_PitchDecrease, 			///< Pitch °¨¼Ò
	trim_YawIncrease, 				///< Yaw Áõ°¡
	trim_YawDecrease, 				///< Yaw °¨¼Ò
	trim_ThrottleIncrease, 			///< Throttle Áõ°¡
	trim_ThrottleDecrease, 			///< Throttle °¨¼Ò
	trim_EndOfType
};

/***********************************************************************/

enum FlightEvent
{
	fEvent_None = 0, 				///< ¾øÀ½
	
	fEvent_TakeOff, 				///< ÀÌ·ú
	
	fEvent_FlipFront, 				///< È¸Àü
	fEvent_FlipRear, 				///< È¸Àü
	fEvent_flipLeft, 				///< È¸Àü
	fEvent_FlipRight, 				///< È¸Àü
	
	fEvent_Stop, 					///< Á¤Áö	
	fEvent_Landing, 				///< Âø·ú
	fEvent_TurnOver, 				///< µÚÁý±â
	
	fEvent_Shot, 					///< ¹Ì»çÀÏÀ» ½ò ¶§ ¿òÁ÷ÀÓ
	fEvent_UnderAttack, 			///< ¹Ì»çÀÏÀ» ¸ÂÀ» ¶§ ¿òÁ÷ÀÓ
	
	fEvent_Square, 					///< Á¤¹æÇâ µ¹±â
	fEvent_CircleLeft, 				///< ¿ÞÂÊÀ¸·Î È¸Àü
	fEvent_CircleRight, 			///< ¿À¸¥ÂÊÀ¸·Î È¸Àü
	fEvent_Rotate180,				///< 180µµ È¸Àü
	
	fEvent_EndOfType
};

enum DriveEvent
{
	dEvent_None = 0,
	dEvent_Ready, 					///< ÁØºñ
	dEvent_Start, 					///< Ãâ¹ß
	dEvent_Drive, 					///< ÁÖÇà
	dEvent_Stop, 					///< °­Á¦ Á¤Áö
	dEvent_Accident, 				///< »ç°í (Ready·Î ÀÚµ¿ÀüÈ¯)
	dEvent_Error, 					///< ¿À·ù
	dEvent_EndOfType
};

/***********************************************************************/
enum Request
{		
	// »óÅÂ
	Req_Address = 0x30, 			///< IEEE address
	Req_State, 						///< µå·ÐÀÇ »óÅÂ(ºñÇà ¸ðµå, ¹æÀ§±âÁØ, ¹èÅÍ¸®·®)
	Req_Attitude, 					///< µå·ÐÀÇ ÀÚ¼¼(Vector)
	Req_GyroBias, 					///< ÀÚÀÌ·Î ¹ÙÀÌ¾î½º °ª(Vector)
	Req_TrimAll, 					///< ÀüÃ¼ Æ®¸²
	Req_TrimFlight, 				///< ºñÇà Æ®¸²
	Req_TrimDrive, 					///< ÁÖÇà Æ®¸²
	
	//update-170426
	Req_CountFlight,            	// ºñÇà °ü·Ã Ä«¿îÆ®
	Req_CountDrive,             	// ÁÖÇà °ü·Ã Ä«¿îÆ® 
	 
	// ¼¾¼­
	Req_ImuRawAndAngle = 0x50, 		///< IMU Raw + Angle
	Req_Pressure, 					///< ¾Ð·Â ¼¾¼­ µ¥ÀÌÅÍ
	Req_ImageFlow, 					///< ImageFlow
	Req_Button, 					///< ¹öÆ° ÀÔ·Â
	Req_Battery, 					///< ¹èÅÍ¸®
	Req_Motor, 						///< ¸ðÅÍ Á¦¾î ¹× ÇöÀç Á¦¾î °ª È®ÀÎ
	Req_Temperature, 				///< ¿Âµµ
		//update-170426				// °Å¸® ¼¾¼­
	Req_Range,
	Req_EndOfType
};

/***********************************************************************/
enum ModeLight
{
  Light_None,
  WaitingForConnect, 				///< ¿¬°á ´ë±â »óÅÂ
  Connected,
  
  EyeNone = 0x10,
  EyeHold, 							///< ÁöÁ¤ÇÑ »ö»óÀ» °è¼Ó ÄÔ
  EyeMix, 							///< ¼øÂ÷ÀûÀ¸·Î LED »ö º¯°æ
  EyeFlicker, 						///< ±ôºýÀÓ
  EyeFlickerDouble, 				///< ±ôºýÀÓ(µÎ ¹ø ±ôºýÀÌ°í ±ôºýÀÎ ½Ã°£¸¸Å­ ²¨Áü)
  EyeDimming, 						///< ¹à±â Á¦¾îÇÏ¿© ÃµÃµÈ÷ ±ôºýÀÓ
  
  ArmNone = 0x40,
  ArmHold, 							///< ÁöÁ¤ÇÑ »ö»óÀ» °è¼Ó ÄÔ
  ArmMix, 							///< ¼øÂ÷ÀûÀ¸·Î LED »ö º¯°æ
  ArmFlicker, 						///< ±ôºýÀÓ
  ArmFlickerDouble, 				///< ±ôºýÀÓ(µÎ ¹ø ±ôºýÀÌ°í ±ôºýÀÎ ½Ã°£¸¸Å­ ²¨Áü)
  ArmDimming, 						///< ¹à±â Á¦¾îÇÏ¿© ÃµÃµÈ÷ ±ôºýÀÓ
  ArmFlow, 							///< ¾Õ¿¡¼­ µÚ·Î Èå¸§
  ArmFlowReverse, 					///< µÚ¿¡¼­ ¾ÕÀ¸·Î Èå¸§
  EndOfLedMode
};

enum LED
{
  LED_NONE = 0x10,
  LED_HOLD,
  LED_MIX, 
  LED_FLICKER,
  LED_FLICKERDOUBLE,
  LED_DIMMING,
  LED_FLOW, 
  LED_FLOWREVERSE, 	
  LED_EndOfType
};

/***********************************************************************/
enum Colors
{
	AliceBlue, AntiqueWhite, Aqua,
	Aquamarine, Azure, Beige,
	Bisque, Black, BlanchedAlmond,
	Blue, BlueViolet, Brown,
	BurlyWood, CadetBlue, Chartreuse,
	Chocolate, Coral, CornflowerBlue,
	Cornsilk, Crimson, Cyan,
	DarkBlue, DarkCyan, DarkGoldenRod,
	DarkGray, DarkGreen, DarkKhaki,
	DarkMagenta, DarkOliveGreen, DarkOrange,
	DarkOrchid, DarkRed, DarkSalmon,
	DarkSeaGreen, DarkSlateBlue, DarkSlateGray,
	DarkTurquoise, DarkViolet, DeepPink,
	DeepSkyBlue, DimGray, DodgerBlue,
	FireBrick, FloralWhite, ForestGreen,
	Fuchsia, Gainsboro, GhostWhite,
	Gold, GoldenRod, Gray,
	Green, GreenYellow, HoneyDew,
	HotPink, IndianRed, Indigo,
	Ivory, Khaki, Lavender,
	LavenderBlush, LawnGreen, LemonChiffon,
	LightBlue, LightCoral, LightCyan,
	LightGoldenRodYellow, LightGray, LightGreen,
	LightPink, LightSalmon, LightSeaGreen,
	LightSkyBlue, LightSlateGray, LightSteelBlue,
	LightYellow, Lime, LimeGreen,
	Linen, Magenta, Maroon,
	MediumAquaMarine, MediumBlue, MediumOrchid,
	MediumPurple, MediumSeaGreen, MediumSlateBlue,
	MediumSpringGreen, MediumTurquoise, MediumVioletRed,
	MidnightBlue, MintCream, MistyRose,
	Moccasin, NavajoWhite, Navy,
	OldLace, Olive, OliveDrab,
	Orange, OrangeRed, Orchid,
	PaleGoldenRod, PaleGreen, PaleTurquoise,
	PaleVioletRed, PapayaWhip, PeachPuff,
	Peru, Pink, Plum,
	PowderBlue, Purple, RebeccaPurple,
	Red, RosyBrown, RoyalBlue,
	SaddleBrown, Salmon, SandyBrown,
	SeaGreen, SeaShell, Sienna,
	Silver, SkyBlue, SlateBlue,
	SlateGray, Snow, SpringGreen,
	SteelBlue, Tan, Teal,
	Thistle, Tomato, Turquoise,
	Violet, Wheat, White,
	WhiteSmoke, Yellow, YellowGreen,
	EndOfColor
};

/***********************************************************************/

class CoDroneClass
{
public:

/////////////////////////////////////////////////////////////////////////

	void begin(long baud);	
	
	void Receive(void);
		
	void Control();
	void Control(int interval);

	void Send_Command(int sendCommand, int sendOption);	
	void Send_Processing(byte _data[], byte _length, byte _crc[]);
	
/////////////////////////////////////////////////////////////////////////

	void LinkReset();
	void Send_LinkState();
	void Send_LinkModeBroadcast(byte mode);
	
/////////////////////////////////////////////////////////////////////////
	
	void AutoConnect(byte mode);
  	void AutoConnect(byte mode, byte address[]);
	void Send_ConnectAddressInputDrone(byte address[]);
	void Send_ConnectConnectedDrone();
	void Send_ConnectNearbyDrone();	
	void Send_Connect(byte index);
	void Send_Disconnect();		
	void Send_Discover(byte action);
	void Send_Check(byte _data[], byte _length, byte _crc[]);

/////////////////////////////////////////////////////////////////////////

	void Send_Ping();
	void Send_ResetHeading();			
	void Send_RSSI_Polling(byte action);	
	void Send_DroneMode(byte event);
	void Send_Coordinate(byte mode);	
	void Send_ClearGyroBiasAndTrim();		
	void DroneModeChange(byte event);			
	void FlightEvent(byte event);
	void DriveEvent(byte event);		

/////////////////////////////////////////////////////////////////////////

	void BattleShooting();
	void BattleReceive();
	void BattleBegin(byte teamSelect);	
	void BattleDamageProcess();	
	
/////////////////////////////////////////////////////////////////////////
		
	void Request_DroneState();	
	void Request_DroneAttitude();
	void Request_DroneGyroBias();	
	
	void Request_TrimAll();
	void Request_TrimFlight();
	void Request_TrimDrive();	
	
	void Request_ImuRawAndAngle();
	void Request_Pressure();
	void Request_ImageFlow();
	void Request_Button();
	void Request_Battery();
	void Request_Motor();
	void Request_Temperature();
	
	void Request_CountFlight();
	void Request_CountDrive();
	void Request_Range();
			
/////////////////////////////////////////////////////////////////////////

	void Set_Trim(byte event);
	void Set_TrimReset();
	void Set_TrimAll(int _roll, int _pitch, int _yaw, int _throttle, int _wheel);
	void Set_TrimFlight(int _roll, int _pitch, int _yaw, int _throttle);
	void Set_TrimDrive(int _wheel);

/////////////////////////////////////////////////////////////////////////

	void LedColorProcess(byte _dType, byte sendMode, byte sendColor, byte sendInterval);
	void LedColorProcess(byte _dType, byte sendMode, byte r, byte g, byte b, byte sendInterval);
	void LedColorProcess(byte _dType, byte sendMode, byte sendColor[], byte sendInterval);
	
	void LedColor(byte sendMode, byte sendColor, byte sendInterval);
	void LedColor(byte sendMode, byte r, byte g, byte b, byte sendInterval);
	void LedColor(byte sendMode, byte sendColor[], byte sendInterval);
	//void LedColorTwo(byte sendMode, byte r, byte g, byte b, byte sendInterval, byte sendMode, byte r, byte g, byte b, byte sendInterval);
	
	void LedEvent(byte sendMode, byte sendColor, byte sendInterval, byte sendRepeat);	
	void LedEvent(byte sendMode, byte r, byte g, byte b, byte sendInterval, byte sendRepeat);
	void LedEvent(byte sendMode, byte sendColor[], byte sendInterval, byte sendRepeat);
		
	void LedColorDefault(byte sendMode, byte r, byte g, byte b, byte sendInterval);
	void LedColorDefault(byte sendMode, byte sendColor[], byte sendInterval);
	//edit //170821
	void LedColorDefault(byte sendMode, byte sendColor[], byte sendInterval, byte sendMode2, byte sendColor2[], byte sendInterval2);

/////////////////////////////////////////////////////////////////////////

	void LinkStateCheck();
	void ReceiveEventCheck(byte _completeData[]);
	int LowBatteryCheck(byte value);
	void DisplayRSSI();
	
/////////////////////////////////////////////////////////////////////////

	void LED_PORTC(int value);
	void LED_DDRC(int value);
	void LED_Move_Radar(byte display);
	void LED_Start();
	void LED_Move_Slide();
	void LED_Connect();
	void LED_Standard();
	void LED_Blink(int time, int count);
	
/////////////////////////////////////////////////////////////////////////

	unsigned short CRC16_Make(unsigned char *buf, int len); //CRC16-CCITT Format
	boolean CRC16_Check(unsigned char data[], int len, unsigned char crc[]);
	
/////////////////////////////////////////////////////////////////////////

	void PrintDroneAddress();
	void DisplayAddress(byte count, byte _devName0[], byte _devName1[],byte _devName2[], byte _devName3[], byte _devName4[]);
	
/////////////////////////////////////////////////////////////////////////
	
	void ButtonPreesHoldWait(int button);
	void ButtonPreesHoldWait(int button1, int button2);		
	int AnalogScaleChange(int analogValue);			

/////////////////////////////////////////////////////////////////////////

	boolean TimeCheck(word interval); 					//milliseconds
	boolean TimeOutSendCheck(word interval); 			//milliseconds		
	boolean TimeCheckBuzz(word interval); 				//microseconds
	
/////////////////////////////////////////////////////////////////////////

	void Buzz(long frequency, int tempo);
	void BeepWarning(int count);

/////////////////////////////////////////////////////////////////////////

	int GestureFuntion(int sen1, boolean act1, int sen2, boolean act2,void(CoDroneClass::*pf)(byte), byte command);
	int GestureCheckPosition(int sen1, boolean act1, int sen2, boolean act2);
	int GestureReturnPositon(int sen1, int sen2);
		
/////////////////////////////////////////////////////////////////////////
	// 2018, 1, 22 added

	//getter and setter
	void setRoll(int _roll);
	int getRoll();

	void setPitch(int _pitch);
	int getPitch();

	void setYaw(int _yaw);
	int getYaw();

	void setThrottle(int _throttle);
	int getThrottle();

	void trim(int _roll, int _pitch, int _yaw, int _throttle);
	void resetTrim();

	//flight command
	void go(int direction);
	void go(int direction, float duration);
	void go(int direction, float duration, int power);
	

	void move();
	void move(float duration);
	void move(int _roll, int _pitch, int _yaw, int _throttle);
	void move(float duration, int _roll, int _pitch, int _yaw, int _throttle);

	void turn(int direction);
	void turn(int direction, float duration);
	void turn(int direction, float duration, int power);


	void hover(float duration);
	void turnDegree(int direction, int degree);

	//FlightEvnet
	void takeoff();
	void land();
	void emergencyStop();
/////////////////////////////////////////////////////////////////////////

	//2018. 1. 29 added
	int getHeight();
	int getPressure();
	int getDroneTemp();
	gyrodata getAngulerSpeed();
	angledata getGyroAngles();
	acceldata getAceelerometer();
	int getBatteryPercentage();
	int getBatteryVoltage();
	trimdata getTrim();
	// not finalized!!
	int getState();
	optdata getOptFlowPosition();
	void goToHeight(int set);

	boolean isUpsideDown();
	boolean isFlying();
	boolean isReadyToFly();
	

/////////////////////////////////////////////////////////////////////////

	//2018. 2. 12 added
	void setArmRGB(byte r, byte g, byte b);
	void setEyeRGB(byte r, byte g, byte b);
	void setAllRGB(byte r, byte g, byte b);
	void setArmDefaultRGB(byte r, byte g, byte b);
	void setEyeDefaultRGB(byte r, byte g, byte b);
	void setAllDefaultRGB(byte r, byte g, byte b);

	void resetDefaultLED();

	void setArmMode(byte mode);
	void setEyeMode(byte mode);
	void setAllMode(byte mode);
	void setArmDefaultMode(byte mode);
	void setEyeDefaultMode(byte mode);
	void setAllDefaultMode(byte mode);


	//sequence
	void flySequence(int shape);
	void sway();
	void zigzag();
	void square();
	void triangle();
	void hop();
	void circle();
	void spiral();

/////////////////////////////////////////////////////////////////////////

	void testreconnect();
	void printAddress(byte mode);
	void pair(byte address[]);
	void pair();
	void pair(int mode);

	int TrimAll_Roll;
	int TrimAll_Pitch;
	int TrimAll_Yaw;
	int TrimAll_Throttle;
	int TrimAll_Wheel;

	byte cmdBuff[MAX_PACKET_LENGTH];

	byte checkHeader;
	byte cmdIndex;
	byte receiveDtype;
	byte receiveLength;
	
	byte receiveLikMode;
	byte receiveLinkState;
	int receiveEventState;
	int receiveComplete;
	
			
/////////////////////////////////////////////////////////////////////////

	byte displayMode = 1;	//smar inventor : default 1
	byte debugMode = 0;		//smar inventor : default 0
	
	byte discoverFlag;
	byte connectFlag;
			
	boolean pairing = 0;
	
	int SendInterval; //millis seconds		
	int analogOffset;
	
	byte displayLED = 0;

	byte timeOutRetry = 0;
	
	byte sendCheckCount = 0;
	byte sendCheckFlag = 0;

/////////////////////////////////////////////////////////////////////////////
	byte receiveAttitudeSuccess = 0;
	byte receiveRangeSuccess = 0;
	byte receiveGyroSuccess = 0;
	byte receiveAccelSuccess = 0;
	byte receivePressureSuccess = 0;
	byte receiveTrimSuccess = 0;
	byte receiveStateSuccess = 0;
	byte receiveBatterySuccess = 0;
	byte receiveOptSuccess = 0;

	
	byte energy = 8;	
	byte team = FREE_PLAY;
	unsigned long weapon = FREE_MISSILE;
	
/////////////////////////////////////////////////////////////////////////
	
	byte devCount = 0;
	byte devFind[5];
	
	int devRSSI0 = -1;
	int devRSSI1 = -1;
	int devRSSI2 = -1;		
	int devRSSI3 = -1;
	int devRSSI4 = -1;
	
	byte devAddress0[6];
	byte devAddress1[6];
	byte devAddress2[6];
	byte devAddress3[6];
	byte devAddress4[6];

	byte devAddressBuf[6];
	byte devAddressConnected[6];
	
/////////////////////////////////////////////////////////////////////////
	
	byte dataBuff[30];
	
	int roll = 0;
	int pitch = 0;
	int yaw = 0;
	int throttle = 0;
		
	int attitudeRoll	= 0;
	int attitudePitch	= 0;
	int attitudeYaw	= 0;
	int yawDegree = 0;

	int GyroBias_Roll	= 0;
	int GyroBias_Pitch	= 0;
	int GyroBias_Yaw	= 0;

	int ImuAccX	= 0;
	int ImuAccY	= 0;
	int ImuAccZ	= 0;
							
	int ImuGyroRoll		= 0;
	int ImuGyroPitch	= 0;
	int ImuGyroYaw		= 0;
									
	int ImuAngleRoll	= 0;
	int ImuAnglePitch	= 0;
	int ImuAngleYaw		= 0;

	long d1				= 0;
	long d2				= 0;
	long temperature	= 0;
	long pressure		= 0;

	long fVelocitySumX 	= 0;
	long fVelocitySumY	= 0;

	byte button = 0;

	int Battery_v30			= 0;
	int Battery_v33			= 0;
	int Battery_gradient	= 0;
	int Battery_yIntercept	= 0;
	int flagBatteryCalibration	= 0;
	long Battery_Raw		= 0;
	int Battery_Percent		= 0;
	int Battery_voltage		= 0;

	int countAccident	= 0;
	int countTakeOff	= 0;
	int countLanding	= 0;

	int m1_forward	= 0;
	int m1_reverse	= 0;
	int m2_forward	= 0;
	int m2_reverse	= 0;
	int m3_forward	= 0;
	int m3_reverse	= 0;
	int m4_forward	= 0;
	int m4_reverse	= 0;

	long imu_temp		= 0;
	long pressure_temp	= 0;


/////////////////////////////////////////////////////////////////////////
	
	byte linkState = 0;
	int rssi = 0;
	byte battery = 0;		
  	unsigned long	irMassageReceive;	
	byte droneState[7];		
	int sensorRange[6];		
	
	long PreviousMillis;
	long batterytime = -5000;	

	long buzzerTime;	
/////////////////////////////////////////////////////////////////////////

	int prevControl[4];
	void SequenceDelay(int setTime);
//////////////////////////////////////////////////////////////////////////	
	byte armred = 255;
	byte armgreen = 0;
	byte armblue = 0;
	byte eyered = 255;
	byte eyegreen = 0;
	byte eyeblue = 0;
	byte armmode = ArmHold;
	byte eyemode = EyeHold;
/////////////////////////////////////////////////////////////////////////

	boolean isConnected = false;
	void connect();
	void Send_reCalibration();

private:
	long PreviousBuzz;	
	long timeOutSendPreviousMillis;
};

extern CoDroneClass CoDrone;

#endif   