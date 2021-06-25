/*
*/

#ifndef SCREEN_h
#define SCREEN_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SCREEN
{
    public:

    bool begin(void);
    void updatevalues_display(char *RTCTime, char *kbd01String, char * kbd02String, char *kbd03String, char *kbd04String);
    void initscreen_display(void);

    private:

};

#endif
