/*
DS1340.h - Header file for the DS1340 Real Time Clock Sensor Arduino Library.

Version: 1.0.0
(c) 2014 Korneliusz Jarzebski
www.jarzebski.pl

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

#ifndef DS1340_h
#define DS1340_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DS1340_ADDRESS                (0x68)

class DS1340
{
    public:

    char *trame;
    bool bRTChour_updated = false ; // RTC hour updated by GPS frame ?

    void initTime();
    char *getTime();
    void setTime(char *timeframe, char *dateframe = NULL);


    private:

    byte      Second;     // Store second value
    byte      Minute;     // Store minute value
    byte      Hour;       // Store hour value
    byte      Day;        // Store day value
    byte      Date;       // Store date value
    byte      Month;      // Store month value
    byte      Year;       // Store year value

};

#endif
