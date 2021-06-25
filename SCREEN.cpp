/*
SCREEN.cpp - Class file for the OLED Display.


*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <U8g2lib.h>

#include "SCREEN.h"

// Constructor of oled screen object
// Controller : SH1106
// Size : 128x64
// Buffer size : 2
// Communication : Hardware I2C
U8G2_SH1106_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0);

// Screen initialisation
bool SCREEN::begin(void)
{
    u8g2.begin();

    delay(100);

    return true;
}

// Display gps values
void SCREEN::updatevalues_display(char *RTCTime, char *kbd01String, char * kbd02String, char *kbd03String, char *kbd04String)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x8_tr);    
    u8g2.drawStr(20,8,"RTC Time:");
    u8g2.drawStr(70,8,RTCTime);
    u8g2.drawStr(20,38,"Keyboard test");
    u8g2.drawStr(0,51,kbd01String);
    u8g2.drawStr(35,51,kbd02String);
    u8g2.drawStr(70,51,kbd03String);
    u8g2.drawStr(100,51,kbd04String);
  } while ( u8g2.nextPage() );
}

// Display init screen
void SCREEN::initscreen_display(void)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(24,12,"KheoPS+");
    u8g2.drawStr(12,60,"Archeorient");
  } while ( u8g2.nextPage() );
}
