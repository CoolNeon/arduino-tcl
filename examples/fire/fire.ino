/*****************************************************************************
 * fire.ino
 *
 * This example will send a flickering fire sequence down a 25 pixel long
 * strand of total control lighting. It uses random numbers to shift in
 * intensity and color between two color limits.
 *
 * Copyright 2011 Christopher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt along with this library.
 ****************************************************************************/
#include <SPI.h>
#include <TCL.h>

const int LEDS = 100; // There are 100 LEDs in the Total Control Lighting Strand
byte color1[] = {0xff, 0x00, 0x00};
byte color2[] = {0xff, 0x90, 0x00};

const int transition_low = 0;
const int transition_high = 101;

const int intensity_low = 0;
const int intensity_high = 101;

void setup() {
  TCL.begin();

}

void loop() {
  int i;
  int transition;
  int intensity;

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    transition=(int)random(transition_low,transition_high);
    intensity=(int)random(intensity_low,intensity_high);
    sendTransitionScaleFrame(color1,color2,transition,intensity);
  }
  TCL.sendEmptyFrame();

  delay(50);
}

void sendTransitionScaleFrame(byte *c1, byte *c2, int transition, int intensity) {
  byte rscale;
  byte gscale;
  byte bscale;

  rscale = ((c2[0]-c1[0])*transition/100+c1[0])*intensity/100;
  gscale = ((c2[1]-c1[1])*transition/100+c1[1])*intensity/100;
  bscale = ((c2[2]-c1[2])*transition/100+c1[2])*intensity/100;

  TCL.sendColor(rscale,gscale,bscale);
}
