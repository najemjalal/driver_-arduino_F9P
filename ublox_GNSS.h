/******************************************************************************
u-blox_GNSS.h
u-blox GNSS Arduino


******************************************************************************/

#ifndef __ublox_GNSS__
#define __ublox_GNSS__

#include "stdint.h"

#if defined(ARDUINO)
	#if ARDUINO >= 100
    #include "Arduino.h"
	#else
    #include "WProgram.h"      // this lib is a definition file created by and for the wiring project and board.   to make libraries compatible with latest Arduino IDE
	#endif
#endif

#ifdef GNSS_DEBUG
	namespace {      
  		template<typename T>
  		static void DBG(T last) {
    	GNSS_DEBUG.println(last);
		}
		
		template<typename T, typename... Args>
		static void DBG(T head, Args... tail) {
			GNSS_DEBUG.print(head);
			GNSS_DEBUG.print(' ');
			DBG(tail...);
		}
	}
#else
  #define DBG(...)
#endif

// Power Save Mode
typedef enum
{
	CONTINOUS,
	PSM_1HZ,
	ON_OFF
	//...
} psmMode_t;  
// FIX Flags
typedef enum
{
	NO_FIX,
	DEAD_RECKONING,
	FIX_2D,
	FIX_3D,
	GNSS_AND_DEAD_RECKONING,
	TIME_ONLY
	//...
} fixType_t;  


class GNSS
{
public:
	Stream&       stream;
	// Assign serial interface to be used with the module
	GNSS( Stream& stream ) : stream(stream){}
	
	// Empty begin() starts module on default, non-power saving mode, or PSM_1HZ.
	bool init( psmMode_t m = CONTINOUS );

	// Send message and check Acknoledge message
	bool sendUBX( byte *msg, uint32_t size);

	// UBX-CFG-CFG -> Reset module to factory settings;
	//void factoryRST( void );

	// UBX-CFG-CFG -> Save Configuration to the non-volatile message
  	bool saveCFG( void );

  // Read Serial RX buffer just to clean it
  void clearUART( void );


private:

	#define UART_TIMEOUT 	2000
	#define FIX_TIMEOUT		6000

	bool gnss_init = false;   // declartion gnss_init with the value false(0)

	
	// Convert 32 bits variable to 4x char
	void bits_char( uint32_t c, uint8_t *_c );

	// UBX Checksum
	bool crc( byte *msg, uint32_t size);
  
	byte _saveCFG[21] = {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,     //J'ai vérifié  cette trame sur ublox, elle est bien identique
                  		0x00, 0x00, 0x00, 0x07, 0x21, 0xAF};    

};


#endif
