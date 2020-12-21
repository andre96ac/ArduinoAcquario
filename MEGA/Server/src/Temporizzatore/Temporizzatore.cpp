
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

#include "Temporizzatore.h"
#include "../Const/Const.h"

Temporizzatore::Temporizzatore(int identificativo, RTC_DS1307 *clock )
{
    pClock=clock;
    id=identificativo;
    state=SPENTO;
    oraAccensione= new DateTime(0,0,0,0,0,0);
    oraSpegnimento= new DateTime(0,0,0,0,0,0);
    Serial.println(F("ho creato il temporizzatore con id"));
    Serial.println(id);
    
};

Temporizzatore::~Temporizzatore()
{
    setState(SPENTO);
    pL->isBusy(false);
}

int Temporizzatore::returnId()
{
    return id;
};

int Temporizzatore::returnIdLed()
{
    return pL->returnPin();
};


DateTime *Temporizzatore::returnAccensione()
{
    return oraAccensione;
};

DateTime *Temporizzatore::returnSpegnimento()
{
    return oraSpegnimento;
}

bool Temporizzatore::returnState()
{
    return state;
}

void Temporizzatore::setLed(Led *led)
{
    pL=led;
    pL->isBusy(true);
};

void Temporizzatore::setAccensione(int ora, int minuti)
{
    delete (oraAccensione);
    oraAccensione=new DateTime(0,0,0,ora,minuti,0);
    Serial.println(F("ho settato l'accensione con orario "));
    Serial.print(oraAccensione->hour());
    Serial.print(F(" "));
    Serial.print(oraAccensione->minute());
    //devo anche aggiornare i secondiGiornoAccensione
    secondiGiornoAccensione=ora*60*60+minuti*60;
};

void Temporizzatore::setSpegnimento(int ora, int minuti)
{
    delete (oraSpegnimento);
    oraSpegnimento=new DateTime(0,0,0,ora,minuti,0);

    Serial.println(F("ho settato lo spegnimento con orario "));
    Serial.print(oraSpegnimento->hour());
    Serial.print(F(" "));
    Serial.print(oraSpegnimento->minute());
    secondiGiornoSpegnimento=ora*60*60+minuti*60;
};

void Temporizzatore::setState(bool stato)
{
    state=stato;
    if (state==ACCESO)
    {
    pL->spegni();
    Serial.println(F("ho acceso il temporizzatore"));
    }
    else
    {
    pL->spegni();
    Serial.println(F("ho spento il temporizzatore"));
    }
};

void Temporizzatore::changeState()
{
    if (state==ACCESO)
    setState(SPENTO);
    //
    else
    setState(ACCESO);
    //    
    
};

void Temporizzatore::esegui()
{
    secondiGiornoNow=(pClock->now().hour()*60*60+pClock->now().minute()*60+pClock->now().second());
    /* STAMPA ORARI X DEBUG
    Serial.println(secondiGiornoAccensione);
    Serial.println(secondiGiornoNow);
    Serial.println(secondiGiornoSpegnimento);*/
    if (state==ACCESO)
    {
    if((secondiGiornoNow>=secondiGiornoAccensione)&&(secondiGiornoNow<secondiGiornoSpegnimento))
    {
        //accendo solo se effettivamente non è acceso
        if(pL->returnStato()!=ACCESO)
        pL->accendi();
        //
    }
    else
    {
        pL->spegni();
    }
    }
};
