#include "ublox_GNSS.h"
#include "stdint.h"

void GNSS::clearUART( void )     // to clear the buffer 
{
  while( stream.available() > 0 )
    stream.read();
}

void GNSS::bits_char( uint32_t c, uint8_t *_c )
{
  for( int i = 0; i < 4; i++)
  {
    _c[i] = ( c >> 8*i ) & 0xFF;
    Serial.println(_c[i]);
  }
  Serial.println("\ntest pour fonction bits_char ");
  
}

bool GNSS::init( psmMode_t m )
{     
  
	stream.write( 0xFF );          // Send something to wake GNSS
  delay(1000);
  
  // Disable NMEA, UBX-CFG-PRT -> Enable UBX over UART1 and Baud rate 9600
  /* byte message[] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00,
                    0x80, 0x25, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9A, 0x79}; */
  byte message[] = {0x00,0x00,0x00,0x01}  // test simple pour savoir si le checksum sera bon    
   
  Serial.println("\ntest pour fonction init psmMode_t m :envoie la trame byte message...");
  bool ret = sendUBX(message, sizeof(message));
  Serial.println("\ntest pour fonction init psmMode_t m:  trame byte message envoyé ");

  // Clear NMEA messages
  clearUART();
 
 
  Serial.println("\nnous sommes entrées dans le mode CONTINUOUS ");
   
  /*byte confmessage[] = {0xB5, 0x62, 0x06, 0x86, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //J'ai vérifié  cette trame sur ublox, elle est bien identique
                          0x95, 0x61};       */
  byte confmessage[] = {0x01};   // test simple pour savoir si le checksum sera bon    
  ret &= sendUBX( confmessage, sizeof(confmessage) );
   
   
   
  DBG("UBX-CFG-CFG -> Saving configuration");
  Serial.println("\ntest saveCFG(); dans init ");
  ret &=  saveCFG();
  delay(800);
  
  gnss_init = ret;
  Serial.println("\n gnss_init = ");
  Serial.println(gnss_init);
	return gnss_init;   
}  


bool GNSS::sendUBX( byte *msg, uint32_t size )
{
  //clearUART();
  //DBG("Sending UBX");
  stream.write(msg, size);
  uint32_t sze = size;
  Serial.println("\nsize:");
  Serial.println(sze);
  int i = 0;
  byte _msg[10];
  uint32_t startMillis = millis();
  uint32_t curMillis;
 do{  
    curMillis= millis();
    delay(0);  
    while (stream.available() > 0)   // Stream.available()  gets the number of bytes available in the stream. This is only for bytes that have already arrived.
    {
      _msg[i] = stream.read();     //stream.read read() reads characters from an incoming stream to the buffer.
      i++;
      Serial.println("_msg[i]");
      Serial.println(_msg[i]);
      if (i < sze) continue;   //  if (i < 10) continue;
    }
    /*Serial.print(curMillis); 
    Serial.print(","); 
    Serial.print(startMillis); 
    Serial.print(","); 
    Serial.print(curMillis - startMillis);
    Serial.print(",");
    Serial.println(UART_TIMEOUT); */
    clearUART();      // important
  } while ( curMillis - startMillis < UART_TIMEOUT);     // timeout
 
   Serial.println("\nJe suis sorti la boucle senduBX millis ");
  // Clear Version message from UART
   clearUART();

/*  while( i > 0 ) {
    DBG(_msg[i-1]);
    i--;
  }*/

  if( _msg[3] == 0 )
  {
    // Message Not-Acknowledged
    DBG("Message Not-Acknowledged");
    Serial.println("Message Not-Acknowledged");
    Serial.println("\n on est dans la condition if _msg[3]==0"); 
    Serial.println("_msg[3]=");
    Serial.println(_msg[3]);
    Serial.println("\n");
    return false;   
  }  

  return crc( _msg , sizeof(_msg) );

}


bool GNSS::crc( byte *msg, uint32_t size)
{  
  uint32_t s = size;
  uint8_t CK_A = 0, CK_B = 0;
  
  for( uint8_t i = 2; i < (s-2) ; i++)        
  {
    CK_A = CK_A + msg[i];
    CK_B = CK_B + CK_A;
  }
  bool checksum = ( CK_A == msg[s-2] && CK_B == msg[s-1]);
  DBG("CRC = ", checksum);
  Serial.println("checksum");
  Serial.println(checksum);
  Serial.println("CK_A");
  Serial.println(CK_A);
  Serial.println("CK_B");
  Serial.println(CK_B);
  return checksum;   

}  

/*void GNSS::factoryRST( void )
{ Serial.println("\nNous sommes entrées dans la mèthode factoryRST ");
  // first send dumb data to make sure its on
  stream.write(0xFF);
  Serial.println("\nEnvoi d'un message RST qui sera   ");
  byte message[] = {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,    // trame vérifié sur ublox Revert to defalut configuration
                    0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x07, 0x1F, 0x9E};
               
  Serial.println(message[0]);
  Serial.println(message[1]); 
  Serial.println(message[2]);
  Serial.println(message[3]);
  Serial.println(message[4]);
  Serial.println(message[5]);
  Serial.println(message[6]);
  stream.write(message, sizeof(message));
}
 */
bool GNSS::saveCFG()
{  Serial.println("\nNous sommes entrées dans la mèthode saveCFG ");
   clearUART();
   return sendUBX( _saveCFG, sizeof(_saveCFG));
}
