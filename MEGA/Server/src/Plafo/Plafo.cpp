
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

#include "Plafo.h"

Plafo::Plafo()
{
    fanPin=255;
}

void Plafo::setFanPin(byte pin)
{
    fanPin=pin;
}

void Plafo::esegui()
{
    fanState=SPENTO;
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
        ligthChannels[i]->esegui();
        if (ligthChannels[i]->getStato()>10)
        {
            fanState=ACCESO;
        }

    }
    digitalWrite(fanPin, fanState);
}

byte Plafo::getFanPin()
{
    return fanPin;
} 

bool Plafo::getFanState()
{
    return fanState;
}
