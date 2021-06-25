/*
define.h - Header file for the define Arduino Library.

Version: 1.0.0
(c) 2019 Lionel Darras

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

#ifndef define_h
#define define_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define OUT_BUZZER_PIN                  A5      // output buzzer command
#define IN_KBD01_PIN                    7       // input keyboard button 1
#define IN_KBD02_PIN                    6       // input keyboard button 2
#define IN_KBD03_PIN                    5       // input keyboard button 3
#define IN_KBD04_PIN                    4       // input keyboard button 4
#define IN_MODE01_PIN                   A1
#define IN_MODE02_PIN                   A2
#define OUT_RADIO_CSN_PIN               A6
#define OUT_LED01_PIN                   A3
#define OUT_LED02_PIN                   A4
//#define OUT_RADIO_CE_PIN                0
#define IN_RTC_OUT_PIN                  3
#define IN_BUT1_PIN                     2
#define IN_BUT2_PIN                     1
#define OUT_SDCARDERROR_LED_PIN         A4      // output led, lighted if SDCARD error

#define SAMPLES_TMS 20
#define SAMPLES_TS (float)(SAMPLES_TMS)/1000
#define FRAME_TMS 1000  
#define SAMPLES_NB  FRAME_TMS/SAMPLES_TMS

#endif
