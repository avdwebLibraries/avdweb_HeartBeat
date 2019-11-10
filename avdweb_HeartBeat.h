#ifndef HeartBeat_H
#define HeartBeat_H

class SimpleSoftPWM // only for LEDs and heating
{ public:
    bool pwm(byte value); // 0 ... 255

  private:
    unsigned long start_us, periodTime_us=19890; // minimum frequency to prevent LED flickering = 50Hz
};

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
