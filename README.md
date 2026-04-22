# Arduino Total Control Lighting Library

Copyright 2011 Christopher De Vries

This library allows you to control Cool Neon's Total Control Lighting using an Arduino. The library is built on SPI and requires that the Arduino SPI library also be included.

## Installation

To install this library, unzip it into the `libraries` directory of your Arduino sketchbook folder. If there is not already a folder named `libraries`, create it.

You will need to modify `TCL.h` to choose between bit-bang mode on 2 digital IO pins or SPI mode by uncommenting **one and only one** of the `#define` statements for `TCL_DIO` or `TCL_SPI`. If you select `TCL_DIO`, you should also modify the `#define`s for `TCL_CLOCKPIN` and `TCL_DATAPIN` to select the pins you will use for Clock and Data, respectively.

## Hardware

The Total Control Lighting strands use 4 wires to provide both power and communication. If you are using the Cool Neon connectors, the wires are designated with the following colors:

| Wire color | Signal |
|---|---|
| Red | +5V |
| Yellow | Clock |
| Green | Data |
| Blue | Ground |

If you are using a small number of LEDs the Arduino itself can provide power to the strand, but for a significant number of lights (greater than 5) an external power source should be attached. The Arduino will control the lights using the Clock and Data wires.

In SPI mode, connect the wires as follows:

| Signal | Arduino UNO | Arduino Mega |
|---|---|---|
| Clock | D13 | D52 |
| Data | D11 | D51 |

Be sure there is a common ground between the Arduino and the Total Control Lighting strand.

## Software

In order to use the library, your sketch should start with the following `#include` directives:

```cpp
#include <SPI.h>
#include <TCL.h>
```

Initialize the SPI bus in `setup()`:

```cpp
TCL.begin();
```

Before sending a group of colors to your LEDs, send an empty frame to initialize the strand:

```cpp
TCL.sendEmptyFrame();
```

You must also call this after every set of colors is sent to the strand.

To send an RGB color:

```cpp
TCL.sendColor(byte red, byte green, byte blue);
```

For example, to send a yellow pixel:

```cpp
TCL.sendColor(0xff, 0xb0, 0x00);
```

The first color you send will be the color of the first pixel (closest to the Arduino), the next will be the next pixel, and so on down the line. When you are done sending colors, finish with:

```cpp
TCL.sendEmptyFrame();
```

## Developer Shield

Cool Neon also sells a developer shield which is a useful add-on for using Total Control Lighting with an Arduino. The shield includes a +5V DC power input cable with a 2.1mm jack (compatible with Cool Neon wall-wart power supplies, which will power the Arduino as well as the lights), a female Total Control Lighting output connector, four potentiometers, two momentary buttons, and two switches.

If you hold the developer shield with the two-position switches at the top and the potentiometers at the bottom, then going clockwise from upper-left:

- Potentiometers connect to analog input pins A0–A3
- Momentary switches (bottom to top) connect to digital pins D4 and D5
- Two-position switches (bottom to top) connect to digital pins D6 and D7

When closed, the switches connect the pin to ground, so internal pull-up resistors are required. The library configures the inputs correctly when you call:

```cpp
TCL.setupDeveloperShield();
```

### Pin Aliases

| Alias | Pin | Hardware |
|---|---|---|
| `TCL_POT1` | A0 | Potentiometer 1 |
| `TCL_POT2` | A1 | Potentiometer 2 |
| `TCL_POT3` | A2 | Potentiometer 3 |
| `TCL_POT4` | A3 | Potentiometer 4 |
| `TCL_MOMENTARY1` | D4 | Momentary button 1 |
| `TCL_MOMENTARY2` | D5 | Momentary button 2 |
| `TCL_SWITCH1` | D6 | Two-position switch 1 |
| `TCL_SWITCH2` | D7 | Two-position switch 2 |

If you are using the metallic purple developer shield/Arduino case, the aliases correspond to the following silkscreened labels:

| Alias | Silkscreen label |
|---|---|
| `TCL_POT1` | Pin 1 |
| `TCL_POT2` | Pin 0 |
| `TCL_POT3` | Pin 2 |
| `TCL_POT4` | Pin 3 |
| `TCL_MOMENTARY1` | Pin 5 |
| `TCL_MOMENTARY2` | Pin 4 |
| `TCL_SWITCH1` | Pin 6 |
| `TCL_SWITCH2` | Pin 7 |

For example, to read the state of button 1:

```cpp
state = digitalRead(TCL_MOMENTARY1);
```

`state == HIGH` means the button is open (not pressed); `state == LOW` means it is closed (pressed). All digital buttons and switches are pulled up to HIGH when open and go LOW when closed.

## Example Code

Several examples are available in the Arduino examples menu under **TCL**:

- **blinky** — Causes the lights to blink at slightly randomized times in random colors.
- **color_designer** — Uses the developer shield potentiometers to search for colors. Colors cascade down the strand as you turn the first three potentiometers (red, green, blue). Press the first momentary button to output the corresponding `sendColor()` command over the serial port (9600 bps).
- **fire** — Shows flickering with random colors (between yellow and red) and random intensity to simulate fire.
- **rainbow** — A static red, orange, yellow, green, blue repeating sequence sent to the strand.
- **serialcontrol** — Allows direct control of TCL pixels from a computer over a serial connection using a simple ASCII-based protocol. Used by the PixelPainter application.

## Revision History

- **Version 1.3.2** — Current release.
- **Version 1.2** *(January 2, 2012)* — Added support for the Cool Neon developer shield, a color designer example, and a sketch for pixel control over serial.
- **Version 1.1** *(December 11, 2011)* — Updated to work with the Arduino 1.0 IDE.
- **Version 1.0** *(August 16, 2011)* — Initial release using the Arduino SPI library to control generation 1 TCL strands on pre-Arduino 1.0 IDE.
