/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Damon Reid - CubePilot Australia */

#include "AP_WindVane_SSI.h"
#include <AP_HAL/AP_HAL.h>

extern const AP_HAL::HAL& hal;

void AP_WindVane_SSI::init(const AP_SerialManager& serial_manager)
{
    //Initialising states and values of Pins
    hal.gpio->pinMode(Css, HAL_GPIO_OUTPUT);
    hal.gpio->pinMode(Miso, HAL_GPIO_INPUT);
    hal.gpio->pinMode(clockPulse, HAL_GPIO_OUTPUT);
}

uint32_t AP_WindVane_SSI::lshift(uint32_t x, uint32_t by)
{
  return x*2^by;
}

void AP_WindVane_SSI::delay(uint32_t us) 
{
    uint64_t timestamp = AP_HAL::micros64();
    while (AP_HAL::micros64() < timestamp + 1)
    {

    }
}


void AP_WindVane_SSI::update_direction()
{
        hal.gpio->pinMode(Css, HAL_GPIO_OUTPUT);
    hal.gpio->pinMode(Miso, HAL_GPIO_INPUT);
    hal.gpio->write(Miso,0);
    hal.gpio->pinMode(clockPulse, HAL_GPIO_OUTPUT);
  uint16_t a;
  uint32_t num = 0;
  float angle = 0;
  hal.gpio->write(Css,0);
  delay(1);
  hal.gpio->write(clockPulse,0);
delay(1);
  //segments each value to its appropriate place in binary sequence
  for(uint16_t i  = 0; i<10; i++)
  {
    hal.gpio->write(clockPulse,1);
delay(1);
    a = hal.gpio->read(Miso);
    delay(1);
    a = hal.gpio->read(Miso);
    //bitshifts appropriately
    if(a == 1)
    {
      num = num + (1 << (9 - i));
    }

    hal.gpio->write(clockPulse,0);
delay(1);
  }
  hal.gpio->write(clockPulse, 1);
  hal.gpio->write(Css,1);
  delay(1);
  angle = (360*num)/1023.0f; //calculates angle in degrees
  _frontend._direction_apparent_raw  = radians(angle + _frontend._dir_analog_bearing_offset);
   //gcs().send_text(MAV_SEVERITY_INFO, "WindVane: %.1f",            (double)angle);
  
}
