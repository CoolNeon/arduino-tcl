/*****************************************************************************
 * Tcl.cpp
 *
 * Copyright 2011 Christpher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt
 ****************************************************************************/

#include "TCL.h"

TclClass TCL;

void TclClass::begin() {
  // Set the SPI parameters
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
}

void TclClass::end() {
  SPI.end();
}

byte TclClass::makeFlag(byte red, byte green, byte blue) {
  byte flag = 0;

  flag = (red&0xC0)>>6;
  flag |= ((green&0xC0)>>4);
  flag |= ((blue&0xC0)>>2);
  return ~flag;
}

void TclClass::sendFrame(byte flag, byte red, byte green, byte blue) {
  SPI.transfer(flag);
  SPI.transfer(blue);
  SPI.transfer(green);
  SPI.transfer(red);
}

void TclClass::sendColor(byte red, byte green, byte blue) {
  byte flag = makeFlag(red,green,blue);

  sendFrame(flag,red,green,blue);
}

void TclClass::sendEmptyFrame() {
  sendFrame(0x00,0x00,0x00,0x00);
}

