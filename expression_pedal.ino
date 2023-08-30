#include "MIDIUSB.h"

#define pin A0

const uint8_t channel = 1;
const uint8_t control = 11;
const uint8_t minValue = 0;
const uint8_t maxValue = 127;
const unsigned minSignal = 0u;
const unsigned maxSignal = 1023u;

uint8_t lastValue = 0;
uint8_t tempAnalog = 0;


void setup() {
  Serial.begin(300);
}

void loop() {
  const uint8_t value =
      map(analogRead(pin), minSignal, maxSignal, minValue, maxValue);

  if (value != lastValue) {
    const midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
    MidiUSB.sendMIDI(event);
    MidiUSB.flush();
  }

  lastValue = value;

  delay(5);
}
