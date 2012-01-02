Arduino Total Control Lighting Library
Copyright 2011 Christopher De Vries

This library allows you to control Cool Neon's Total Control Lighting using an
Arduino. The library is built on SPI and requires that the Arduino SPI library
also be included.

Installation
------------
To install this library, unzip it into the "libraries" directory of your
Arduino sketchbook folder. If there is not already a folder named "libraries"
then create it. 

Hardware
--------
The Total Control Lighting strands use 4 wires to provide both power and
communication. If you are using the Cool Neon connectors, the wires are
designated with the following colors.

Red:    +5V
Yellow: Clock
Green:  Data
Blue:   Ground

If you are using a small number of LEDs the Arduino itself can provide power
to the strand, but for a significant number of lights (greater than 5) an
external power source should be attached. The Arduino will control the lights
using the Clock and Data wires.

The Clock wire should be connected to the SPI clock out of the Arduino. For an
Arduino UNO this is digital IO Pin 13, for an Arduino Mega this is digital IO
pin 52. The Data line should be connected to the SPI MOSI line, which for an
Arduino UNO is digital IO Pin 11, and for an Arduino Mega is digital IO pin
51. Be sure there is a common ground between the Arduino and the Total Control
Lighting and your LED strand should be ready to receive data.

Software
--------
In order to use the library, your sketch should start with the following
#include directives:

#include <SPI.h>
#include <TCL.h>

Before starting communication, initialize the SPI bus by issuing the command:

TCL.begin();

Before sending a group of colors to your LEDs, you must send 4 bytes of 0s to
initialize the strand. You can do this using the command:

TCL.sendEmptyFrame();

You must also do this after every set of colors is sent to the strand.

To send an RGB color, use the command:

TCL.sendColor(byte red, byte green, byte blue);

So, for example to send a yellow pixel, I would issue the command:

TCL.sendColor(0xff,0xb0,0x00);

The first color you send, will be the color of the first pixel (closest to the
Arduino), the next will be the next pixel and so on down the line.

When you are done sending colors, remember to finish with

TCL.sendEmptyFrame();

Developer Shield
----------------
Cool Neon also sells a developer shield which is a very useful add-on to using
Total Control Lighting with an Arduino. The shield includes a +5V DC power
input cable with a 2.1mm jack, compatible with the wall-wart power supplies
Cool Neon sells (which will power the Arduino as well as the lights). There is
also a female total control lighting output, which can connect directly to the
total control lighting pixel strands. What makes the shield special is it also
comes with four potentiometers, two momentary buttons, and two switches which
can be configured as inputs to the Arduino. 

If you hold the developer shield so that the two-position switches are at the
top and the potentiometers are at the bottom, then going clockwise from
upper-left the potentiometers connect to analog input pins 0, 1, 2, and 3. The
momentary switches, moving from bottom to top connect to digital pins 4 and 5,
and the two-position switches from bottom to top connect to digital pins 6 and
7. When closed, the switches connect the pin to ground, so you should
configure them to use the internal pull-up resistors. The total control
library configures the inputs correctly if you issue the command:

TCL.setupDeveloperShield();

There are also defined aliases for each input device:

TCL_POT1       : Potentiometer 1
TCL_POT2       : Potentiometer 2
TCL_POT3       : Potentiometer 3
TCL_POT4       : Potentiometer 4
TCL_MOMENTARY1 : Button 1
TCL_MOMENTARY2 : Button 2
TCL_SWITCH1    : Two-position Switch 1
TCL_SWITCH2    : Two-position Switch 2

So, for example to read the state of button 1 I would issue the command:

state = digitalRead(TCL_MOMENTARY1);

It would return state==HIGH if the button was open (not being pressed) and
state==LOW if the button was closed (being pressed). 

Example Code
------------
Several examples are loaded into the Arduino examples menu under "TCL." These
examples include the following:

blinky - A sketch that causes the lights to blink at slightly randomized times
in random colors. 

color_designer - A sketch that lets you use to the developer shield
potentiometers to search for colors. The colors will cascade down the lighting
strand as you turn the first three potentiometers. The first one adjusts the
amount of red, the second the amount of green, and the third the amount of
blue. If you find a color you like just hit the first momentary button and it
will send the appropriate "sendColor" command over the serial port so you can
add it to your own code. Be sure to use the serial monitor set to 9600 bps in
order to use this feature.

fire - A sketch that shows flickering with random colors (between yellow and
red) and random intensity meant to simulate fire.

rainbow - A static red,orange,yellow,green,blue repeating sequence sent onto
the strand.

serialcontrol - A sketch which allows for direct control of the total control
lighting pixels from a computer over a serial connection to the arduino. It
uses a simple ASCII based protocol. This sketch is used by the PixelPainter
application and a little more information about it can be found in the
comments within the sketch.

Revision History
----------------
January 2, 2012 - Version 1.2 - Added support for the Cool Neon developer
shield as well as a color designer in the example code and a sketch that
allows for control of pixels over a serial line to the computer.

December 11, 2011 - Version 1.1 - Library was updated to work on the Version
1.0 Arduino IDE.

August 16, 2011 - Version 1.0 - Library works using the Arduino SPI library to
control generation 1 total control lighting strands on pre-Arduino 1.0 IDE.

