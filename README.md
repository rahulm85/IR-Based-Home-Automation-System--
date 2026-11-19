# IR-Based Home Automation System

An independently written Arduino C++ implementation for controlling three light channels using an infrared remote, an IR receiver, and a relay module.

## Hardware configuration

- Arduino Uno
- TSOP1838-compatible IR receiver (OUT -> D11)
- 3 channels of a 4-channel relay module (IN1 -> D8, IN2 -> D9, IN3 -> D10)
- IR remote
- Appropriate isolated power supply and enclosure

## Software

- C++ using the Arduino framework
- Arduino IDE
- Arduino-IRremote library, version 4.x

## Features

- Receives and decodes IR remote signals.
- Prints received raw IR codes to the Serial Monitor.
- Supports toggling each of three relay channels.
- Supports all-channels ON and all-channels OFF commands.
- Ignores repeat frames to prevent repeated toggling while a button is held.
- Uses configurable active-LOW / active-HIGH relay logic.

## Setup

1. Install the **IRremote** library (4.x) through Arduino IDE Library Manager.
2. Open `IRHomeAutomation.ino`.
3. Confirm the receiver and relay pin assignments match your wiring.
4. Keep the `BUTTON_*` constants at zero for the first upload.
5. Upload the sketch and open Serial Monitor at **9600 baud**.
6. Press each remote button and note the hexadecimal raw code printed.
7. Put each code into its matching `BUTTON_*` constant, using the `0x...UL` format.
8. Upload again and test each command with the relay outputs disconnected from mains-powered loads first.

## Default command mapping

| Remote button constant | Action |
|---|---|
| `BUTTON_LIGHT_1` | Toggle relay channel 1 |
| `BUTTON_LIGHT_2` | Toggle relay channel 2 |
| `BUTTON_LIGHT_3` | Toggle relay channel 3 |
| `BUTTON_ALL_ON` | Turn all three channels on |
| `BUTTON_ALL_OFF` | Turn all three channels off |

The raw codes are intentionally left unconfigured because IR codes vary by remote. Do not use example codes from another remote without measuring and verifying them.

## Safety

Relay outputs may switch lethal mains voltage. Never wire or touch mains circuits while energized. Start testing with low-voltage loads. For AC appliance control, use a properly rated enclosed relay assembly, fusing, strain relief, insulation, and qualified supervision. The low-voltage Arduino circuit must remain safely isolated from mains wiring.

## Project status and attribution

This repository contains an original implementation written for this project; it does not copy source files from the earlier reference repository. The initial project concept was informed by the publicly viewable [AC Lights Controlling Using IR Remote reference](https://github.com/kapujaganmohanreddy/AC-Lights-Controlling-Using-IR-Remote). The implementation here is independently authored.
