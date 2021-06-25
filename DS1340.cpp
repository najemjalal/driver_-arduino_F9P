/*
DS1340.cpp - Class file for the DS1340 Real Time Clock Sensor Arduino Library.

Version: 1.0.0
(c) 2018 Lionel Darras

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <math.h>

#include "UTILS.h"
#include "DS1340.h"

void DS1340::initTime()
{
  bRTChour_updated = false;  
}


/*******************************************************************************
                   getTime function
*******************************************************************************/ 
char *DS1340::getTime()
{
  char tempchar [8];
  byte i = 0;
  Wire.beginTransmission(DS1340_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  
  Wire.requestFrom(DS1340_ADDRESS, 7);
  delete[] trame;
  trame = new char(17);
  tempchar [0] = 0;
  tempchar [1] = 0;
  tempchar [2] = 0;
  tempchar [3] = 0;
  tempchar [4] = 0;
  tempchar [5] = 0;
  tempchar [6] = 0;
  while(Wire.available())          // Checkf for data from slave
  { 
    tempchar [i] = Wire.read(); // receive a byte as character 
    i++;
  } 
  Second = tempchar [0];
  Minute = tempchar [1];
  Hour   = tempchar [2];
  Date   = tempchar [4];
  Month  = tempchar [5];
  Year   = tempchar [6];

   trame [0]= (Hour>>4) + '0';
   trame [1]= (Hour & 0x0f) + '0';
   trame [2]= (Minute>>4) + '0';
   trame [3]= (Minute & 0x0f) + '0';
   trame [4]= (Second>>4) + '0';
   trame [5]= (Second & 0x0f) + '0';
   trame [6]= '.';
   trame [7]= '0';
   trame [8]= '0';
   trame [9]= (Date>>4) + '0';
   trame[10]= (Date & 0x0f) + '0';
   trame[11]= (Month>>4) + '0';
   trame[12]= (Month & 0x0f) + '0';
   trame[13]= (Year>>4) + '0';
   trame[14]= (Year & 0x0f) + '0';
   trame[15]= '\0';
   
   return trame; 
}

  
/*******************************************************************************
                   setTime function
*******************************************************************************/ 
void DS1340::setTime(char *timetrame, char *datetrame)
{
  byte i = 0;

  Hour = (timetrame [1] - '0') + 10 * (timetrame [0] - '0');
  Minute = (timetrame [3] - '0')  + 10 * (timetrame [2] - '0'); 
  Second = (timetrame [5] - '0')  + 10 * (timetrame [4] - '0'); 

  if (datetrame != NULL)
  {
    Date = (datetrame [1] - '0') + 10 * (datetrame [0] - '0');
    Month = (datetrame [3] - '0')  + 10 * (datetrame [2] - '0');
    Year = (datetrame [5] - '0')  + 10 * (datetrame [4] - '0');
  }

  Wire.beginTransmission(DS1340_ADDRESS);  
  Wire.write(0);
  Wire.write(DECtoBCD(Second+1));
  Wire.write(DECtoBCD(Minute));
  Wire.write(DECtoBCD(Hour));
  if (datetrame != NULL)
  {
    Wire.write(1);
    Wire.write(DECtoBCD(Date));
    Wire.write(DECtoBCD(Month));
    Wire.write(DECtoBCD(Year));
    Wire.write(0);    
  }
  Wire.endTransmission();    
}

  
