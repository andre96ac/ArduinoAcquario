
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

#ifndef TEMPORIZZATORE_H
#define TEMPORIZZATORE_H

#include <RTClib.h>
#include "../Led/Led.h"

class Temporizzatore
{
  private:
    int id;
    Led *pL;
    DateTime *oraAccensione;
    DateTime *oraSpegnimento;
    bool state;
    long unsigned int secondiGiornoAccensione, secondiGiornoSpegnimento, secondiGiornoNow;
    RTC_DS1307 *pClock;
  public:
    Temporizzatore(int identificativo, RTC_DS1307 *clock );
    ~Temporizzatore();
    int returnId();
    int returnIdLed();
    DateTime *returnAccensione();
    DateTime *returnSpegnimento();
    bool returnState();
    void setLed(Led *led);
    void setAccensione(int ora, int minuti);
    void setSpegnimento(int ora, int minuti);
    void setState(bool stato);
    void changeState();
    void esegui();
};

#endif