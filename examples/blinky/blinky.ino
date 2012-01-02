/*****************************************************************************
 * blinky.ino
 *
 * An example total control lighting script which causes each pixel to blink
 * on and off in slightly randomized simes around 1 second on and 1 second
 * off and in a color randomly selected from red, orange, yellow, green, and
 * blue. 
 *
 * Copyright 2012 Christopher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt along with this library.
 ****************************************************************************/
#include <SPI.h>
#include <TCL.h>

const int LEDS = 100;
const int COLORS = 6;
const int BLACK = 0;
const int RED = 1;
const int ORANGE = 2;
const int YELLOW = 3;
const int GREEN = 4;
const int BLUE = 5;

byte color_values[COLORS][3];
long change_time[LEDS];
int current_color[LEDS];

void setup() {
  int i;
  unsigned long time;
  
  TCL.begin();
  
  color_values[BLACK][0] = 0x00;
  color_values[BLACK][1] = 0x00;
  color_values[BLACK][2] = 0x00;
  
  color_values[RED][0]=0xff;
  color_values[RED][1]=0x00;
  color_values[RED][2]=0x00;
  
  color_values[ORANGE][0]=0xff;
  color_values[ORANGE][1]=0x60;
  color_values[ORANGE][2]=0x00;
  
  color_values[YELLOW][0]=0xff;
  color_values[YELLOW][1]=0xb0;
  color_values[YELLOW][2]=0x00;
  
  color_values[GREEN][0]=0x00;
  color_values[GREEN][1]=0x80;
  color_values[GREEN][2]=0x00;
  
  color_values[BLUE][0]=0x00;
  color_values[BLUE][1]=0x00;
  color_values[BLUE][2]=0xff;

  time = millis();
  for(i=0;i<LEDS;i++) {
    change_time[i] = time+random(700,1300);
    current_color[i]=BLACK;
  }
  update_strand();
}

void loop() {
  int i;
  unsigned long time;
  
  time=millis();
  
  for(i=0;i<LEDS;i++) {
    if(change_time[i]<time) {
      change_time[i]=time+random(700,1300);
      if(current_color[i]==BLACK) {
        current_color[i]=random(1,COLORS);
      }
      else {
        current_color[i]=BLACK;
      }
    }
  }
  update_strand();
}

void update_strand() {
  int i;
  int color;
  
  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    color = current_color[i];
    TCL.sendColor(color_values[color][0],color_values[color][1],color_values[color][2]);
  }
  TCL.sendEmptyFrame();
}
