/* 
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses.

Version 3-9-2017 moved from Albert library to avdweb_HeartBeat library, 
Version 8-9-2017 low number overrides high number, changed because of new virtualDelay library
*/

#include <Arduino.h>
#include "avdweb_HeartBeat.h"
#include "avdweb_VirtualDelay.h"

HeartBeat::HeartBeat(byte pin):
pin(pin)
{ pinMode(pin, OUTPUT);
}

void HeartBeat::blinkCount(int _blinkCounts) 
{ if(blinkCounts==0) blinkCounts = _blinkCounts;
  else
  if(_blinkCounts < blinkCounts) blinkCounts = _blinkCounts; // low number overrides high number
}

void HeartBeat::poll() // 9us
{ if(blinkCounts==0) heartBeat();
  else blink();
}

void HeartBeat::heartBeat()
{ const int UledMax=250, UledMin=-50, stepInterval_ms=25, stepValue=10;
  static int i=stepValue;
  unsigned long now_ms = millis();   
  digitalWrite(pin, heartBeatPWM.getLevel(max(Uled, 0))); // polled PWM out
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

void HeartBeat::blink() // this function is complex!
{ VirtualDelay blinkOnDelay(millis), blinkOffDelay(millis); // todo: static not allowed
  static int i; 
  const int offTime_ms=500, onTime_ms=100;

  if(blinkOffDelay.done(offTime_ms, 0)) 
  { if(i == 0) digitalWrite(pin, 0); // skip one flash to create pause
    else digitalWrite(pin, 1);
  }
  if(blinkOnDelay.done(onTime_ms, 1)) 
  { if(i++ >= blinkCounts) 
    { i = 0; // return virtually to start
      blinkCounts = 0; // reset
    }
    digitalWrite(pin, 0);
  }
}



