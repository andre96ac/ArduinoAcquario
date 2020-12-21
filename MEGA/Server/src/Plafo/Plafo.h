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


#ifndef PLAFO_H
#define PLAFO_H
#include "./Channel.h"
#include "../Const/Const.h"

class Plafo
{
    private:

    byte fanPin;
    bool fanState;

    public:
    
    Channel* ligthChannels[NMAXCONTROLLERS];
    Plafo();    
    void setFanPin(byte pin);
    byte getFanPin();
    bool getFanState();

    void esegui();
    
};

#endif