/*****************************************************************************
 * TCL.h
 *
 * Copyright 2011-2012 Christpher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt
 ****************************************************************************/
#ifndef TCL_h
#define TCL_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SPI.h"

#define TCL_POT1 A0
#define TCL_POT2 A1
#define TCL_POT3 A2
#define TCL_POT4 A3
#define TCL_MOMENTARY1 4
#define TCL_MOMENTARY2 5
#define TCL_SWITCH1 6
#define TCL_SWITCH2 7

class TclClass {
  public:
    static void begin();
    static void setupDeveloperShield();
    static void end();
    static void sendFrame(byte flag, byte red, byte green, byte blue);
    static void sendColor(byte red, byte green, byte blue);
    static void sendEmptyFrame();
    static byte makeFlag(byte red, byte green, byte blue);
};

extern TclClass TCL;
#endif
