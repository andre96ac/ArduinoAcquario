
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


#ifndef TERMOMETRO_H
#define TERMOMETRO_H

#include "../Led/Led.h"
#include "../Const/Const.h"
#include <OneWire.h>

class Termometro
{
    private:
        int _id;
        bool _state;
        int thermPin;
        Led* pRiscaldatore;
        Led* pRefrigeratore;
        int temperature;
        int type;
        int settedTemperature;
        int delta;

    public:
        Termometro(int identificativo, int pinTermometro, Led* riscaldatore, int temperatura);
        Termometro(int identificativo, int pinTermometro, Led* riscaldatore, Led* refrigeratore, int temperatura, int differenziale);
        Termometro(int identificativo, int pinTermometro);
        ~Termometro();
        void state(bool stato);
        bool state(void);
        void changeState();
        void resetTemperature(int temperature);
        int getTemperature();
        int getId();
        int getPinTerm();
        int getType();
        int getSetTemperature();
        int getDelta();
        Led* getRiscaldatore();
        Led* getRefrigeratore();
        void readSensor();
        void esegui();

};


#endif