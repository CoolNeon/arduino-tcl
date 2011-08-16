/*****************************************************************************
 * rainbow.pde
 *
 * This example will send a sequence of rainbow colors down a 25 pixel long
 * strand of total control lighting. The Arduino will send an update every
 * second to the strand, although this is unnecessary and if you disconnect
 * the Arduino from the strand, you will see that as long as the lights have
 * power, they will retain the last color information sent to them.
 *
 * Copyright 2011 Christopher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt along with this library.
 ****************************************************************************/
#include <SPI.h>
#include <TCL.h>

const int LEDS 25; // There are 25 LEDs in the Total Control Lighting Strand
const byte red[] = {0xff, 0xff, 0xff, 0x00, 0x00};
const byte green[] = {0x00, 0x60, 0xb0, 0x80, 0x00};
const byte blue[] = {0x00, 0x00, 0x00, 0x00, 0xff};

void setup() {
  SPI.begin();

}

void loop() {
  int i;

  SPI.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    SPI.sendColor(red[i%5],green[i%5],blue[i%5]);
  }
  SPI.sendEmptyFrame();

  delay(1000);
}
