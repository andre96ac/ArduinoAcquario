// Copyright 2020 Andrea Cuppini

// This file is part of ArduinoAcquario.
// ArduinoAcquario is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Nome-Programma is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.


#ifndef SPICONTROLLER_H
#define SPICONTROLLER_H

#define CC_MEGA_PIN 5

class _SpiController
{
    private:
         static byte pinS;
         static byte pinE;
    public:
        static void begin (byte pinEthernet, byte pinSd);
        static void switchToSd();
        static void switchToEth();      
};

#endif