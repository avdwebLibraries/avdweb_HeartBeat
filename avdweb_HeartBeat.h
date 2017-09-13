#ifndef HeartBeat_H
#define HeartBeat_H

#include "Albert.h"

class HeartBeat
{ public:
    HeartBeat(byte LEDpin);
    void poll(); 
    void blinkLED(int _blinkCounts); 
  
  private:
    void heartBeat();
    void blink();
    
    SimpleSoftPWM heartBeatPWM;
  
    unsigned long last_ms;
    int Uled; 
    int blinkCounts;
    byte LEDpin;
};
#endif


