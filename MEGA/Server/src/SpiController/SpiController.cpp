

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

#include "SpiController.h"

byte _SpiController:: pinE;
byte _SpiController:: pinS;

void _SpiController :: begin(byte pinEthernet, byte pinSd)
{
    pinMode(pinEthernet, OUTPUT);
    pinMode(pinSd, OUTPUT);
    pinMode (CC_MEGA_PIN, OUTPUT);
    switchToEth();
};

void _SpiController::switchToSd()
{
    digitalWrite(pinE, HIGH);
    digitalWrite(pinS, LOW);
    Serial.println(F("sto attivando la sd"));
};

void _SpiController::switchToEth()
{
    digitalWrite(pinS, HIGH);
    digitalWrite(pinE, LOW);
    Serial.println(F("sto attivando l'eth"));

}

_SpiController SpiController;


