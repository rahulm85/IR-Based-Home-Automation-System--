# IR-Based Home Automation System

An Arduino-based home lighting automation project that uses an infrared remote, an IR receiver, and a relay module to control AC lights.

## Project overview

The Arduino receives and decodes IR remote signals, then switches three relay channels to control connected lights. The documented controls include toggling individual lights and switching all lights on or off.

## Hardware and software

- Arduino Uno
- TSOP1838 IR receiver
- 4-channel relay module
- IR remote and AC light loads
- Arduino IDE
- IRremote library

## Signal and pin reference

- IR receiver output: Arduino D11
- Relay control pins: D8, D9, D10
- Relay logic in the sketch: active LOW

The IR button codes and circuit details should be checked against the original project documentation before assembling the circuit.

## Safety

This project involves mains-voltage AC wiring. Do not work on live circuits. Use suitable isolation, enclosures, insulation, and supervision from someone qualified to work with mains electricity.

## Original project and attribution

This repository is a project reference/portfolio entry. The original implementation and documentation are maintained by **kapujaganmohanreddy**:

- [Original GitHub repository](https://github.com/kapujaganmohanreddy/AC-Lights-Controlling-Using-IR-Remote)

The original repository does not show a license file. Source files have therefore not been copied into this repository. Please obtain the author's permission or a suitable license before redistributing or modifying the original code.

## Next steps

- Confirm the exact IRremote library version used by the sketch.
- Verify the IR codes with the specific remote.
- Test relay operation with a low-voltage load before any mains-connected setup.
