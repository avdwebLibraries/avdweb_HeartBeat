/* 
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses.

Note: include library avdweb_VirtualDelay in library folder

Version 3-9-2017 moved from Albert library to avdweb_HeartBeat library, 
Version 8-9-2017 low number overrides high number, changed because of new VirtualDelay library
*/

#include <Arduino.h>
#include "avdweb_HeartBeat.h"
#include "avdweb_VirtualDelay.h"
//#include <Streaming.h>

bool SimpleSoftPWM::pwm(byte value) // 0 ... 255, only for LEDs
{ unsigned long now_us = micros();
  if((now_us - start_us) >= periodTime_us) start_us = now_us;
  return((now_us - start_us) < value * 78); // 19890/255=78
}

HeartBeat::HeartBeat(byte LEDpin):
LEDpin(LEDpin)
{ pinMode(LEDpin, OUTPUT);
}

void HeartBeat::poll() // 9us
{ if(blinkCounts==0) heartBeat();
  else blink();
}

void HeartBeat::heartBeat()
{ const int UledMax=250, UledMin=-50, stepInterval_ms=25, stepValue=10;
  static int i=stepValue;
  unsigned long now_ms = millis();   
  digitalWrite(LEDpin, heartBeatPWM.pwm(max(Uled, 0))); // polled PWM out
  if((now_ms - last_ms) < stepInterval_ms) return;
  last_ms = now_ms;
  if(Uled >= UledMax) i = -stepValue;
  if(Uled <= UledMin) i =  stepValue;  
  Uled += i;
}

/*                  _   _   _       _   _  
 *              ___| |_| |_| |_____| |_| |___ skip one flash to create pause
 *  blinkCounts    3         0     2     0    
 *                          reset       reset
 */

void HeartBeat::blinkLED(int _blinkCounts) 
{ if(blinkCounts==0) blinkCounts = _blinkCounts;
  else
  if(_blinkCounts < blinkCounts) blinkCounts = _blinkCounts; // low number overrides high number
}

void HeartBeat::blink() 
{ static VirtualDelay blinkOnDelay(millis), blinkOffDelay(millis); 
  static int i; 
  const int offTime_ms=400, onTime_ms=100;

  DO_ONCE(blinkOffDelay.start(offTime_ms))
  
  if(blinkOffDelay.elapsed())
  { if(i == 0) 
    { digitalWrite(LEDpin, 0); // skip one flash to create pause
      //Serial << "\ni=" << i << " LED 0 " << blinkCounts << " " << millis() << " skip";
    }
    else 
    { digitalWrite(LEDpin, 1);
      //Serial << "\ni=" << i << " LED 1 " << blinkCounts << " " << millis();
    }
    blinkOnDelay.start(onTime_ms);    
  }
  if(blinkOnDelay.elapsed()) 
  { if(i++ >= blinkCounts) 
    { i = 0; 
      blinkCounts = 0; // reset, blinkCount is set again in blinkCount() which has to be called in the loop repeatedly 
    }
    blinkOffDelay.start(offTime_ms);   
    digitalWrite(LEDpin, 0);
    //Serial << "\ni=" << i << " LED 0 " << blinkCounts << " " << millis();
  }
}
