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

/* Damon Reid - Cube Pilot Australia */
#pragma once

#include "AP_WindVane_Backend.h"

class AP_WindVane_SSI : public AP_WindVane_Backend
{
public:
    // constructor
    using AP_WindVane_Backend::AP_WindVane_Backend;

    // initialization
    void init(const AP_SerialManager& serial_manager) override;
    
    void update_direction() override;

    uint32_t lshift(uint32_t x, uint32_t by);
    void delay(uint32_t us);

    uint8_t clockPulse = 50;
    uint8_t Miso = 51;
    uint8_t Css = 52;
};