# Copilot Instructions

## Project Overview

This is **CoolNeon TCL** (Total Control Lighting), an Arduino C++ library for controlling [Cool Neon TCL LED pixel strands](https://github.com/CoolNeon/arduino-tcl/). The library supports both hardware SPI and software bit-bang (DIO) communication modes.

- **Author:** Christopher De Vries
- **License:** Artistic License 2.0
- **Arduino Library Registry name:** `CoolNeon TCL`
- **Version:** tracked in `library.properties`

## Repository Structure

```
TCL.h                  # Library header — mode selection, pin aliases, class declaration
TCL.cpp                # Library implementation
library.properties     # Arduino Library Manager metadata (name, version, author, etc.)
build.xml              # Ant build file
examples/
  blinky/              # Random blink in random colors
  color_designer/      # Developer shield potentiometer color picker with serial output
  fire/                # Flickering fire effect
  PixelStepper/        # Developer shield button/switch-driven stepper
  rainbow/             # Static rainbow pattern
  serialcontrol/       # Control lights over serial
```

## Library Architecture

### Communication Modes

The mode is selected by a `#define` at the top of `TCL.h`. Exactly one must be active:

```cpp
//#define TCL_DIO   // Bit-bang on any 2 digital pins
#define TCL_SPI     // Hardware SPI (default)
```

- **SPI mode**: Uses the Arduino `SPI` library. Clock on D13 (UNO) / D52 (Mega); Data on D11 (UNO) / D51 (Mega).
- **DIO mode**: Bit-bang using `TCL_CLOCKPIN` and `TCL_DATAPIN` (default pins 0 and 1; change in `TCL.h`).

### Wire Protocol

Each pixel frame is 4 bytes: `flag | blue | green | red` (blue-first on wire). The flag byte encodes the two MSBs of each color channel (inverted) to help the strand distinguish data from clock glitches. An **empty frame** (4 zero bytes) must be sent before and after every group of pixel colors.

### Public API (`TclClass`, exposed as global `TCL`)

| Method | Description |
|---|---|
| `TCL.begin()` | Initialize SPI or DIO; call once in `setup()` |
| `TCL.end()` | Release SPI bus |
| `TCL.sendEmptyFrame()` | Send 4 zero bytes; required before and after pixel data |
| `TCL.sendColor(r, g, b)` | Send one pixel; auto-calculates flag |
| `TCL.sendFrame(flag, r, g, b)` | Send one pixel with a manually supplied flag |
| `TCL.makeFlag(r, g, b)` | Compute the flag byte for a given color |
| `TCL.setAll(n, r, g, b)` | Set all `n` LEDs to one color (wraps empty frames) |
| `TCL.setupDeveloperShield()` | Configure developer shield inputs with internal pull-ups |

### Developer Shield Pin Aliases

| Alias | Pin | Hardware |
|---|---|---|
| `TCL_POT1`–`TCL_POT4` | A0–A3 | Potentiometers |
| `TCL_MOMENTARY1`, `TCL_MOMENTARY2` | D4, D5 | Momentary buttons (LOW when pressed) |
| `TCL_SWITCH1`, `TCL_SWITCH2` | D6, D7 | Two-position switches (LOW when closed) |

## Coding Conventions

- Plain Arduino C++ (`byte`, `int`, `boolean`); no C++ stdlib.
- Colors are `byte` (0–255) for R, G, B channels.
- Every sketch includes `<SPI.h>` and `<TCL.h>` (SPI must come first in SPI mode).
- Every pixel loop is wrapped with `TCL.sendEmptyFrame()` before and after.
- Example sketches use a `const int LEDS` to configure strand length (commonly 25 or 100).
- File headers include copyright, license note, and a short description.

## Example Sketch Pattern

```cpp
#include <SPI.h>
#include <TCL.h>

const int LEDS = 100;

void setup() {
  TCL.begin();
}

void loop() {
  TCL.sendEmptyFrame();
  for (int i = 0; i < LEDS; i++) {
    TCL.sendColor(red, green, blue);
  }
  TCL.sendEmptyFrame();
  delay(50);
}
```

## Releases

Releases are created automatically by the GitHub Actions workflow at `.github/workflows/release.yml` when a PR is merged into `main`. The release tag and title are taken from the `version` field in `library.properties`. Bump `version` in `library.properties` before merging a PR to publish a new release.
