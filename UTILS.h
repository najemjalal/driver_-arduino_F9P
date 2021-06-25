/*
UTILS.h - Header file for the utility Arduino Library.

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

#ifndef UTILS_h
#define UTILS_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/* Converts a value from decimal to BCD */
byte DECtoBCD(byte val);
byte BCDtoDEC(byte val);
void ftoa(float f, char *str, uint8_t precision);

#endif
