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

#ifndef OSMO_H
#define OSMO_H

#include "../Const/Const.h"
#include "../Led/Led.h"

class OsmoConfig
{
    public:
        int id;
        Led *pL;
        byte switch1Pin, switch2Pin;
        bool osmoState, switch1State, switch2State, emptyError;
};

class Osmo
{
    private:
        int id;
        Led *pL;
        byte switch1Pin, switch2Pin;
        bool osmoState, switch1State, switch2State, emptyError;
        long int reflowStartTime;
        OsmoConfig* config;
    public: 
        Osmo(int identificativo, Led *led, byte normalSwitch, byte emergencySwitch);

        ~Osmo();
        
        void setState(bool stato);

        void changeState();
        
        void ceckLevel();


        Led* returnLed();

        OsmoConfig* getConfig();
       
};


#endif