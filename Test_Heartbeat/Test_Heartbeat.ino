#include "avdweb_HeartBeat.h"
#include <Streaming.h>

const byte LedPin = 13;
HeartBeat heartBeat(LedPin);

void test_blinkLED()
{ 
 /* time [sec]     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
 * blinkLED(3)        3 3 3 3 3 3 3 3 3 3
 * blinkLED(2)                  2 2 2 
 * blinkLED(4)              4 4 4 4 4 4 4  
 * blinkLED(1)                                        1 1 1 1 1 1  
 * LED pulses     - - - 3 3 3 3 3 2 2 2 - - - - - - - - 1 1 1 1 1 1 - -                        
*/
  // < 3000ms start with heartBeat
  if(millis() > 3000 && millis() < 12000) heartBeat.blinkLED(3);  // blink LED 3x
  if(millis() > 8000 && millis() < 10000) heartBeat.blinkLED(2);  // blink LED 2x, because 2<3
  if(millis() > 6000 && millis() < 12000) heartBeat.blinkLED(4);  // ignored because 2<4
  // heartBeat between blinkLED
  if(millis() > 19000 && millis() < 24000) heartBeat.blinkLED(1); 
}

void setup(void) 
{ Serial.begin(9600);
}

void loop(void) 
{ heartBeat.poll(); 
  test_blinkLED();
}




