#include "avdweb_HeartBeat.h"

const byte LedPin = 13;
HeartBeat heartBeat(LedPin);

void setup(void) {}

void loop(void) {
  heartBeat.poll(); // first 4sec heartBeat LED
  if (millis() > 4000)
    heartBeat.blinkLED(3); // after 4sec diagnostic blinking LED error code 3
}
