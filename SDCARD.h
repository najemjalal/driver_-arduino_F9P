#ifndef SDCARD_H
#define SDCARD_H

#include <Arduino.h>
#undef LITTLE_ENDIAN
#undef max
#undef min // To avoid multiple definition of min/max functions
//#include <iostream>

// SDCARD.cpp
void sdcard_cardInit();
void sdcard_cardInfo();
void sdcard_volumeInfo();
void sdcard_checkDirectory(String directory);
void sdcard_filesInfo();
void sdcard_writeFile(String file,String data);
void sdcard_readFile(String f);
void sdcard_deleteFile(String f);

String sdcard_getFileLine(String f);

#endif
