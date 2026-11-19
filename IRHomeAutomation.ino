/*
 * IR-Based Home Automation System
 * Board: Arduino Uno
 * IR receiver: TSOP1838 OUT -> D11
 * Relay module: IN1 -> D8, IN2 -> D9, IN3 -> D10
 *
 * Library: Arduino-IRremote 4.x (install "IRremote" from Library Manager)
 *
 * IMPORTANT:
 * 1. Upload once with the button codes below set to 0.
 * 2. Open Serial Monitor at 9600 baud and press each remote button.
 * 3. Copy the printed hexadecimal raw code into the matching constant.
 * 4. Upload again. Unknown/unconfigured codes are ignored.
 *
 * Relay modules are commonly active-LOW. Change RELAY_ON_LEVEL and
 * RELAY_OFF_LEVEL if your module uses active-HIGH logic.
 */

#include <Arduino.h>
#include <IRremote.hpp>

constexpr uint8_t IR_RECEIVE_PIN = 11;

constexpr uint8_t RELAY_PINS[] = {8, 9, 10};
constexpr uint8_t RELAY_COUNT = sizeof(RELAY_PINS) / sizeof(RELAY_PINS[0]);

constexpr uint8_t RELAY_ON_LEVEL = LOW;
constexpr uint8_t RELAY_OFF_LEVEL = HIGH;

// Replace 0 with the raw hexadecimal code printed by your remote.
// Example format: 0xBA45FF00UL (the example is not your remote's code).
constexpr uint32_t BUTTON_LIGHT_1 = 0x00000000UL;
constexpr uint32_t BUTTON_LIGHT_2 = 0x00000000UL;
constexpr uint32_t BUTTON_LIGHT_3 = 0x00000000UL;
constexpr uint32_t BUTTON_ALL_ON  = 0x00000000UL;
constexpr uint32_t BUTTON_ALL_OFF = 0x00000000UL;

bool relayIsOn[RELAY_COUNT] = {false, false, false};

void setRelay(uint8_t index, bool turnOn) {
  if (index >= RELAY_COUNT) {
    return;
  }

  relayIsOn[index] = turnOn;
  digitalWrite(RELAY_PINS[index], turnOn ? RELAY_ON_LEVEL : RELAY_OFF_LEVEL);

  Serial.print(F("Relay "));
  Serial.print(index + 1);
  Serial.println(turnOn ? F(": ON") : F(": OFF"));
}

void toggleRelay(uint8_t index) {
  if (index < RELAY_COUNT) {
    setRelay(index, !relayIsOn[index]);
  }
}

void setAllRelays(bool turnOn) {
  for (uint8_t i = 0; i < RELAY_COUNT; ++i) {
    setRelay(i, turnOn);
  }
}

void printReceivedCode(uint32_t code) {
  Serial.print(F("IR raw code: 0x"));
  Serial.println(code, HEX);
}

void handleCommand(uint32_t code) {
  printReceivedCode(code);

  if (BUTTON_LIGHT_1 != 0 && code == BUTTON_LIGHT_1) {
    toggleRelay(0);
  } else if (BUTTON_LIGHT_2 != 0 && code == BUTTON_LIGHT_2) {
    toggleRelay(1);
  } else if (BUTTON_LIGHT_3 != 0 && code == BUTTON_LIGHT_3) {
    toggleRelay(2);
  } else if (BUTTON_ALL_ON != 0 && code == BUTTON_ALL_ON) {
    setAllRelays(true);
  } else if (BUTTON_ALL_OFF != 0 && code == BUTTON_ALL_OFF) {
    setAllRelays(false);
  } else {
    Serial.println(F("No matching command configured; no relay changed."));
  }
}

void setup() {
  Serial.begin(9600);

  // Set the output latch to OFF before configuring each relay pin.
  for (uint8_t i = 0; i < RELAY_COUNT; ++i) {
    digitalWrite(RELAY_PINS[i], RELAY_OFF_LEVEL);
    pinMode(RELAY_PINS[i], OUTPUT);
  }

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.println(F("\nIR Home Automation ready."));
  Serial.println(F("Press remote buttons to read their raw codes."));
  Serial.println(F("Configure the BUTTON_* constants, then upload again."));
}

void loop() {
  if (IrReceiver.decode()) {
    const auto &decoded = IrReceiver.decodedIRData;

    // Ignore auto-repeat frames; they should not toggle a relay repeatedly.
    if ((decoded.flags & IRDATA_FLAGS_IS_REPEAT) == 0) {
      handleCommand(decoded.decodedRawData);
    } else {
      Serial.println(F("IR repeat frame ignored."));
    }

    IrReceiver.resume();
  }
}
