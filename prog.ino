#include <stdlib.h>
#include "Wire.h"
#include "DS1340.h"
#include "SDCARD.h"
#include "UTILS.h"
#include "SCREEN.h"
#include "define.h"
#include "FreeMemory.h"
#include "ublox_GNSS.h"
    
#define Serial_GNSS Serial1    
// Enable Serial debbug on Serial UART to see registers wrote
#define GNSS_DEBUG Serial                                        //*********************************************            
DS1340 ds1340;
SCREEN screen;
GNSS gnss( Serial_GNSS );                                        //*********************************************  

float lat, lon, acc;                                             //*********************************************

fixType_t fix = NO_FIX;                                          //*********************************************
/*******************************************************************************
                    Global variables
*******************************************************************************/ 
byte b;
char rtc_time[18] = "???";

/*******************************************************************************
                      Setup
*******************************************************************************/ 
void setup() 
{ 
  Wire.begin();
  delay(10); 
  pinMode(IN_KBD01_PIN, INPUT);
  pinMode(IN_KBD02_PIN, INPUT);
  pinMode(IN_KBD03_PIN, INPUT);
  pinMode(IN_KBD04_PIN, INPUT);
  pinMode(OUT_LED01_PIN, OUTPUT);
  pinMode(OUT_LED02_PIN, OUTPUT);
  pinMode(OUT_BUZZER_PIN, OUTPUT);
  digitalWrite(OUT_LED01_PIN, LOW);
  digitalWrite(OUT_LED02_PIN, LOW);
  digitalWrite(OUT_BUZZER_PIN, LOW);
    
  ds1340.initTime();
  ds1340.bRTChour_updated = false;
  Serial1.begin(9600);     // Serial1.begin(38400);    serial port 1, to acquisition system via Tx pin      
  delay(1000); 
  Serial.begin(9600);      // Serial.begin(38400);    serial port to acquisition system
  delay(1000); 

  Serial.setTimeout(1000);
  delay(100); 
  Serial.flush();    //waits for the transmission of outgoing serial data to complete
  delay(100);
  Serial.println("***** KheoPS+ *****");
  sdcard_cardInit(); // Initialize SD card
  screen.begin();
  delay(1000);
  screen.initscreen_display();
  delay(1000);
  strcpy(rtc_time,ds1340.getTime());
 
} 
 
/*******************************************************************************
                      Main Loop
*******************************************************************************/  
void loop() 
{  
  int kbd01_state, kbd02_state, kbd03_state, kbd04_state;
  int FreeMemory;
  char FreeMemoryString[16] ="mem";
  char kbd01String[5]="-", kbd02String[5]="-", kbd03String[5]="-", kbd04String[5]="-";
  
  kbd01_state = digitalRead(IN_KBD01_PIN);
  kbd02_state = digitalRead(IN_KBD02_PIN);
  kbd03_state = digitalRead(IN_KBD03_PIN);
  kbd04_state = digitalRead(IN_KBD04_PIN);
  sprintf(kbd01String, "%d", kbd01_state);
  sprintf(kbd02String, "%d", kbd02_state);
  sprintf(kbd03String, "%d", kbd03_state);
  sprintf(kbd04String, "%d", kbd04_state);
  
  if(kbd01_state==1)                                     
  { 
    Serial.println("test bouton 1 appuyé");
    if( gnss.init( ) )                                   
    {
      Serial.println("\nGNSS initialized.");
    }
    else
    {
      Serial.println("\nFailed to initialize GNSS module.");
    }                                                     
    delay(1000);  
  };   
   /*   
  if(kbd02_state==1)                                                      //********************************************************************
  { 
   Serial.println("test bouton 2 appuyé");
   gnss.clearUART();  
   gnss.factoryRST();   
   delay(1000); 
   gnss.clearUART();
   Serial.println("test fin de condition if pour RST");
  }; 

  if(kbd03_state==1)                                                      //********************************************************************
  {   
   gnss.clearUART();  
   gnss.saveCFG();
   delay(1000); 
   Serial.println("test fin de condition if pour saveCFG");
   gnss.clearUART();  
  }; */
  
  FreeMemory = freeMemory();
  sprintf(FreeMemoryString, "%d", FreeMemory);
  strcpy(rtc_time,ds1340.getTime());
  rtc_time[6] = '\0';

  serialEvent1();
  screen.updatevalues_display(rtc_time, kbd01String, kbd02String, kbd03String, kbd04String);

}

void serialEvent1()
{
 // passerlle communication
  //char temp[60];
 // int NbBytes;
 /* while(Serial1.available()) {
    NbBytes = Serial1.readBytes(temp,50);
    if (NbBytes != 0)
    {
      Serial.write(temp);
    } 
  }  */
 
 gnss.clearUART();  
}

  
