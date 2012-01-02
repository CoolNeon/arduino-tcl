/*****************************************************************************
 * color_designer.ino
 *
 * This sketch will allow you to use the potentiometers on the Total Control
 * Lighting Developer Shield to adjust the colors of the LEDs and select an
 * appropriate color. Push the first button to send the command which
 * generates this color back over the serial port. The colors will cascade
 * the lighting strand as you adjust the potentiometers. Be sure to open the
 * serial monitor to see the color information on your computer.
 *
 * Copyright 2011-2012 Christopher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt along with this library.
 ****************************************************************************/
#include <SPI.h>
#include <TCL.h>

const int LEDS = 100; // This assumes that there are 100 LEDs in the TCL strand.
const int update_interval = 100; // Milliseconds between color updates

/* Current values for the pixels are stored in the following three arrays */
byte red_values[LEDS];
byte green_values[LEDS];
byte blue_values[LEDS];



void setup() {
  int i;

  TCL.begin(); // Begin protocol for communicating with the TCL strand
  TCL.setupDeveloperShield(); // Set up developer shield for inputs
  Serial.begin(9600); // Start serial communication at 9600 baud

  /* Start by initializing all pixels to black */
  for(i=0;i<LEDS;i++) {
    red_values[i]=0;
    green_values[i]=0;
    blue_values[i]=0;
  }

  update_strand(); // Send the black pixels to the strand to turn off all LEDs.
}

void loop() {
  int i; // A variable for looping
  static long nextupdate=0l; // Time when next update of colors should occur.
  static boolean sent_color=false; // Have I printed out the color to serial?
  long time = millis(); // Current time in milliseconds

  /* Check if the strand should be updated */
  if(time>nextupdate) {
    /* Move colors down the line by one */
    for(i=LEDS-1;i>0;i--) {
      red_values[i]=red_values[i-1];
      green_values[i]=green_values[i-1];
      blue_values[i]=blue_values[i-1];
    }
    /* Read the current red value from potentiometer 1
     * Values are 10 bit and must be left shifted by 2 in order to fit in 8
     * bits */
    red_values[0]=analogRead(TCL_POT1)>>2;
    
    /* Read the current green value from potentiometer 2 */
    green_values[0]=analogRead(TCL_POT2)>>2;

    /* Read the current blue value from potentiometer 3 */
    blue_values[0]=analogRead(TCL_POT3)>>2;

    update_strand(); // Send all the pixels out
    nextupdate=time+update_interval; // Set the time of the next update
  }

  /* Check if the button is pressed and if we have to send a color choice to serial */
  if(digitalRead(TCL_MOMENTARY1)==LOW) { // The button is active (closed)
    if(sent_color) {
      // Do nothig. We already sent this one
    }
    else {
      sent_color=true; // Send the message only one time per button press.
      Serial.print("TCL.sendColor(0x");
      Serial.print(red_values[0],HEX);
      Serial.print(",0x");
      Serial.print(green_values[0],HEX);
      Serial.print(",0x");
      Serial.print(blue_values[0],HEX);
      Serial.println(")");
    }
  }
  else { // The button is open
    sent_color=false;
  }
}

void update_strand() {
  int i;

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(red_values[i],green_values[i],blue_values[i]);
  }
  TCL.sendEmptyFrame();
}
