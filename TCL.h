/*****************************************************************************
 * TCL.h
 *
 * Copyright 2011-2012 Christpher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt
 ****************************************************************************/
// Choose between bit bang (any 2 dio pins) and SPI modes
//#define TCL_DIO
#define TCL_SPI

#ifndef TCL_h
#define TCL_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef TCL_SPI
#include "SPI.h"
#endif

#define TCL_POT1 A0
#define TCL_POT2 A1
#define TCL_POT3 A2
#define TCL_POT4 A3
#define TCL_MOMENTARY1 4
#define TCL_MOMENTARY2 5
#define TCL_SWITCH1 6
#define TCL_SWITCH2 7

#ifdef TCL_DIO
#define TCL_CLOCKPIN 0
#define TCL_DATAPIN 1
#endif

class TclClass {
  public:
    static void begin();
    static void setupDeveloperShield();
    static void end();
    static void sendFrame(byte flag, byte red, byte green, byte blue);
    static void sendColor(byte red, byte green, byte blue);
    static void sendEmptyFrame();
    static byte makeFlag(byte red, byte green, byte blue);
    static void setAll(int num_leds, byte red, byte green, byte blue);
  private:
#ifdef TCL_DIO
    static byte datapinmask, clkpinmask;
    static volatile byte *dataport, *clkport;
    static void dioWrite(uint8_t c);
#endif
};

extern TclClass TCL;
#endif
