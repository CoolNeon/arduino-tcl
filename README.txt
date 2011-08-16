Arduino Total Control Lighting Library
Copyright 2011 Christopher De Vries

This library allows you to control Cool Neon's Total Control Lighting using an
Arduino. The library is built on SPI and requires that the Arduino SPI library
also be included.

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

