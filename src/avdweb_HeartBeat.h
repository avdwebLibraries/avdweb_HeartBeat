/**
 * avdweb_HeartBeat.h
 *
 * avdweb_HeartBeat - Heart Beat Library for
 *  diagnostic blinking LED error code and much more!
 * ===========================================================
 *
 * Sources
 * -------
 * https://github.com/avandalen/avdweb_HeartBeat
 *
 * Website
 * -------
 * http://www.avdweb.nl/arduino/hardware-interfacing/heartbeat.html
 *
 * License
 * --------
 * SPDX: GPL-3.0-or-later
 *
 *  avdweb_HeartBeat - Heart Beat Library for diagnostic blinking LED error code
 *    and much more!
 *  Copyright (C) 2012-2024 Albert van Dalen <http://www.avdweb.nl>
 *  Copyright (C) 2024 Abhijit Bose (aka. Boseji) :contributor:
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HeartBeat_H
#define HeartBeat_H

#include <Arduino.h>

class SimpleSoftPWM // only for LEDs and heating
{
public:
  bool pwm(byte value); // 0 ... 255

private:
  unsigned long start_us,
      periodTime_us =
          19890; // minimum frequency to prevent LED flickering = 50Hz
};

class HeartBeat {
public:
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
#endif /* HeartBeat_H */
