/*****************************************************************************
 * TCL.h
 *
 * Copyright 2011 Christpher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt
 ****************************************************************************/
#ifndef TCL_h
#define TCL_h
#include <Wprogram.h>
#include <SPI.h>

class TclClass {
  public:
    static void begin();
    static void end();
    static void sendFrame(byte flag, byte red, byte green, byte blue);
    static void sendColor(byte red, byte green, byte blue);
    static void sendEmptyFrame();
    static byte makeFlag(byte red, byte green, byte blue);
};

extern TclClass TCL;
#endif
