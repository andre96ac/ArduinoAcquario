
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

#include "Channel.h"
#include "../Const/Const.h"


Channel::Channel(byte presa, RTC_DS1307* orologio)
{
    pin=presa;
    tipoAccensione=MANUALE;
    statoAccensione=SPENTO;
    pClock=orologio;
    pinMode(pin, OUTPUT);

};

void Channel::setTipoAccensione(TipoAccensione tipo)
{
    tipoAccensione=tipo;
};

void Channel::setStatoAccensione(byte stato)
{
    tipoAccensione=MANUALE;
    statoAccensione=stato;
};

void Channel::setTimer(DateTime* oraAccensione, DateTime* oraSpegnimento)
{
    accensione=oraAccensione;
    spegnimento=oraSpegnimento;
};

bool Channel::setDurata(int minuti)
{
    bool error=true;
    if (minuti>=1&&minuti<=60)
    {
        durataAccensione=minuti;
        error=false;
    }
    return error;
};

byte Channel::getStato()
{
    return statoAccensione;
};

byte Channel::getPresa()
{
    return pin;
}

void Channel::esegui()
{
    int secAcc=((accensione->hour())*60*60)+((accensione->minute())*60);
    int secSpegn=((spegnimento->hour())*60*60)+((spegnimento->minute())*60);
    int secNow=(pClock->now().hour()*60*60)+(pClock->now().minute()*60);
    int secDurata=(durataAccensione*60);

    if (tipoAccensione==AUTOMATICA)
    {
        //se mi trovo in fase di accensione
        if ((secNow>secAcc)&&(secNow<=secAcc+secDurata))
        {
            statoAccensione=map(secNow,secAcc,secAcc+secDurata, 0, 255);
        }
        //se mi trovo in fase di spegnimento
        else if ((secNow>=secSpegn-secDurata)&&(secNow<secSpegn))
        {
            statoAccensione=map(secNow,secSpegn-secDurata,secSpegn, 255, 0);
        }
        //se la plafo è accesa
        else if ((secNow>secAcc+secDurata)&&(secNow<secSpegn-secDurata))
        {
            statoAccensione=255;
        }
        //se la plafo è spenta
        else
        {
            statoAccensione=0;
        }
        
    }

    analogWrite(pin, statoAccensione);
};

void Channel::changeTipoAccensione()
{
    if (tipoAccensione==MANUALE)
        tipoAccensione=AUTOMATICA;
    else if (tipoAccensione==AUTOMATICA)
        tipoAccensione=MANUALE;
};

TipoAccensione Channel::getTipoAccensione()
{
    return tipoAccensione;
};

DateTime Channel::getAccensione()
{
    return accensione;
};

DateTime Channel::getSpegnimento()
{
    return spegnimento;
};
int Channel::getDurataAccensione()
{
    return durataAccensione;
}


