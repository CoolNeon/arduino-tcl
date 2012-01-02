/*****************************************************************************
 * serialcontrol.ino
 *
 * This code reads commands from the serial port at 115200 bps and controls an
 * arbitraty number of total control lighting pixels. There are two commands.
 * The commands are described below.
 *
 * CHECK
 * When receiving the command "CHECK" followed by a newline, the program
 * responds by sending "CONNECT" followed by a newline. This is meant to
 * check for an established connection. Occasionally there is some noise when
 * a program first connects and you may need to resend "CHECK"
 *
 * DATA [n]
 * The command "DATA" is followed by an integer and a newline. The integer
 * indicates how many triplets of RGB color data follow. Each color is sent as
 * a single byte, so each triplet is three bytes. The program will then enter
 * a loop to read 3n bytes of data. It will send a blank frame to the pixels,
 * send the RGB data to the pixels, and then send another blank frame after
 * reading all n triplets. 
 *
 * The commands are sent in ASCII and the integer in decimal. The bytes are
 * sent in binary red, green, then blue. The maximum command length (excluding
 * bytes, which are of a fixed and known length) is 128 bytes of ASCII. 
 *
 * Copyright 2011-2012 Christopher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt along with this library.
 ****************************************************************************/
#include <SPI.h>
#include <TCL.h>

char incomingBuffer[128];
int bufPosition;

void setup() {
  Serial.begin(115200);
  TCL.begin();
}

void loop() {
  int inbyte;
  String inputCommand;
  String color_frames_string;
  char color_frames_chararray[6];
  byte red, green, blue;
  int color_frames;
  int i;
  
  if(Serial.available()>0) {
    inbyte = Serial.read();
    if(inbyte==10) {
      // Command Received, parse it
      incomingBuffer[bufPosition]='\0';
      inputCommand = String(incomingBuffer);
      bufPosition=0;
      if(inputCommand.equals(String("CHECK"))) {
        Serial.println("CONNECT");
      }
      else if(inputCommand.startsWith(String("DATA"))) {
        color_frames_string = inputCommand.substring(5);
        color_frames_string.toCharArray(color_frames_chararray,6);
        color_frames = atoi(color_frames_chararray);
        TCL.sendEmptyFrame();
        for(i=0;i<color_frames;i++) {
          while(!Serial.available()) { }
          red = (byte)Serial.read();
          while(!Serial.available()) { }
          green = (byte)Serial.read();
          while(!Serial.available()) { }
          blue = (byte)Serial.read();
          TCL.sendColor(red,green,blue);
        }
        TCL.sendEmptyFrame();
      }
    }
    else {
      incomingBuffer[bufPosition]=(char)inbyte;
      bufPosition++;
      if(bufPosition==128) {
        Serial.println("OVERFLOW");
        bufPosition=0;
      }
    }
  } 
}
