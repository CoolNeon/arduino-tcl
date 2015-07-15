/*****************************************************************************
 * PixelStepper.ino
 * Version 1.0.0
 *
 * Notes:  Needs better comments and docs!
 *
 *
 * Copyright 2014 Chris O'Halloran - cknight __ ghostwheel _ com
 * Copyright Chris O'Halloran
 * License: Attribution Non-commercial Share Alike (by-nc-sa) (CC BY-NC-SA 4.0)
 * https://creativecommons.org/licenses/by-nc-sa/4.0/
 * https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 ****************************************************************************/

#include <SPI.h>
#include <TCL.h>

const int LEDS = 25;
byte red_values[LEDS];
byte green_values[LEDS];
byte blue_values[LEDS];
byte color_temp[4];
char* myColors[]={"NULL", "RED", "GREEN", "BLUE"};

int SWITCHSTATE; // A single point of reference for the state of the switches

int MOMENTARY1_Initial_State;
int MOMENTARY2_Initial_State;
int TCL_SWITCH1_Initial_State;
int TCL_SWITCH2_Initial_State;


void setup() {
  TCL.begin();
  TCL.setupDeveloperShield();
  Serial.begin(9600); // Start serial communication at 9600 baud

  MOMENTARY1_Initial_State = digitalRead(TCL_MOMENTARY1);
  MOMENTARY2_Initial_State = digitalRead(TCL_MOMENTARY2);

  reset_strand();
  
}

void loop() {
  int i;
  
  CheckSwitches();
  check_button_press();

  for(i=1;i<LEDS;i++) {
    red_values[i]=color_temp[1];
    green_values[i]=color_temp[2];
    blue_values[i]=color_temp[3];
  }

  update_strand();
}



void print_color_status() {

  Serial.print("TCL.sendColor(0x");
  Serial.print(color_temp[1],HEX);
  Serial.print(",0x");
  Serial.print(color_temp[2],HEX);
  Serial.print(",0x");
  Serial.print(color_temp[3],HEX);
  Serial.println(")");
}




void CheckSwitches() {

  if (digitalRead(TCL_SWITCH1) == 0 && digitalRead(TCL_SWITCH2) == 0){
    SWITCHSTATE = 0;
    red_values[0] = 0;
    green_values[0] = 0;
    blue_values[0] = 0;
  }
  else if (digitalRead(TCL_SWITCH1) == 1 && digitalRead(TCL_SWITCH2) == 0){
    SWITCHSTATE = 1;
    red_values[0] = 255;
    green_values[0] = 0;
    blue_values[0] = 0;
  }
  else if (digitalRead(TCL_SWITCH1) == 0 && digitalRead(TCL_SWITCH2) == 1){
    SWITCHSTATE = 2;
    red_values[0] = 0;
    green_values[0] = 255;
    blue_values[0] = 0;
  }
  else{
    SWITCHSTATE = 3;
    red_values[0] = 0;
    green_values[0] = 0;
    blue_values[0] = 255;
  }
  
}

void check_button_press() {
  int was_reset=0;

  if (digitalRead(TCL_MOMENTARY1) != MOMENTARY1_Initial_State) { 
    while (digitalRead(TCL_MOMENTARY1) != MOMENTARY1_Initial_State) {
      if (digitalRead(TCL_MOMENTARY2) != MOMENTARY2_Initial_State && was_reset == 0) { 
        color_temp[SWITCHSTATE] = 255;
        was_reset = 1;
        Serial.print("Jump to 255: ");
        Serial.println(myColors[SWITCHSTATE]);
      }
    }
    if ( was_reset == 0 ) {
      color_temp[SWITCHSTATE] = min(color_temp[SWITCHSTATE]++, 255);
      Serial.print("up: ");
      Serial.println(myColors[SWITCHSTATE]);
    }
      print_color_status();
  }

  if (digitalRead(TCL_MOMENTARY2) != MOMENTARY2_Initial_State) { 
    while (digitalRead(TCL_MOMENTARY2) != MOMENTARY2_Initial_State) {
      if (digitalRead(TCL_MOMENTARY1) != MOMENTARY1_Initial_State && was_reset == 0) { 
        color_temp[SWITCHSTATE] = 0;
        was_reset = 1;
        Serial.print("Jump to 000: ");
        Serial.println(myColors[SWITCHSTATE]);
      }
    }
    if ( was_reset == 0 ) {
      color_temp[SWITCHSTATE] = max(color_temp[SWITCHSTATE]--, 0);
      Serial.print("down: ");
      Serial.println(myColors[SWITCHSTATE]);
    }
      print_color_status();
  }

}

void reset_strand() {
  int i;
  
  for(i=0;i<LEDS;i++) {
    red_values[i]=0;
    green_values[i]=0;
    blue_values[i]=0;
  }
  update_strand();
}


void update_strand() {
  int i;

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(red_values[i],green_values[i],blue_values[i]);
  }
  TCL.sendEmptyFrame();
}


