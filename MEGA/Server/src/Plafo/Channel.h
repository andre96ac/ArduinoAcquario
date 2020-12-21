
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

#ifndef CHANNEL_H
#define CHANNEL_H

#include <RTClib.h>


enum TipoAccensione
{
    AUTOMATICA=0,
    MANUALE=1
};


class Channel
{
    private:
        byte pin;
        TipoAccensione tipoAccensione;
        byte statoAccensione;
        DateTime *accensione;
        DateTime *spegnimento;
        int durataAccensione;
        RTC_DS1307* pClock;


    public:
        Channel(byte presa, RTC_DS1307* orologio);
        void setTipoAccensione(TipoAccensione tipo);
        void changeTipoAccensione();
        void setStatoAccensione(byte stato);
        void setTimer(DateTime* oraAccensione, DateTime* oraSpegnimento);
        bool setDurata(int minuti);

        byte getStato();
        byte getPresa();
        TipoAccensione getTipoAccensione();
        DateTime getAccensione();
        DateTime getSpegnimento();
        int getDurataAccensione();
 
        void esegui();
};


#endif