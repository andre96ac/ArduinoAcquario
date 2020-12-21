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

#include "Osmo.h"

    Osmo::Osmo(int identificativo, Led *led, byte normalSwitch, byte emergencySwitch)
    {
        id=identificativo;
        pL=led;
        pL->isBusy(true);
        switch1Pin=normalSwitch;
        switch2Pin=emergencySwitch;
        switch1State=SPENTO;
        switch2State=SPENTO;
        pinMode(switch1Pin, INPUT);
        pinMode(switch2Pin, INPUT);
        osmoState=SPENTO;
        emptyError=false;
        reflowStartTime=0;
        config=new OsmoConfig;
    };

    Osmo::~Osmo()
    {
        pL->isBusy(false);
        setState(SPENTO);
    };

    void Osmo::setState(bool stato)
    {
        if (stato==ACCESO)
        {
            emptyError=false;
            pL->spegni();
            osmoState=ACCESO;    
        }
        else
        {
            pL->spegni();
            osmoState=SPENTO;
        }
        
    };


    void Osmo::changeState()
    {
        if (osmoState==ACCESO)
            setState(SPENTO);
        else
            setState(ACCESO);
    }

    void Osmo::ceckLevel()
    {
        switch1State=digitalRead(switch1Pin);
        switch2State=digitalRead(switch2Pin);
        if (osmoState==ACCESO)
        {
            if((switch1State==ACCESO)&&(switch2State==ACCESO))
            {
                pL->accendi();
                //se sto iniziando ora il reflow, mi annoto il tempo
                if (reflowStartTime==0)
                {
                    reflowStartTime=millis();
                }
                //se ho superato il tempo massimo di reflow, spengo l'osmo ed indico l'errore
                else if (millis()-MAX_REFLOW_MILLIS>=reflowStartTime)
                {
                    reflowStartTime=0;
                    emptyError=true;
                    setState(SPENTO);
                }
            }
            else
            {
                reflowStartTime=0;
                pL->spegni();
            }
        } 
    }

    OsmoConfig* Osmo::getConfig()
    {
        config->id=id;
        config->pL=pL;
        config->switch1Pin=switch1Pin;
        config->switch2Pin=switch2Pin;
        config->osmoState=osmoState;
        config->switch1State=switch1State;
        config->switch2State=switch2State;
        config->emptyError=emptyError;
        return config;
    }



