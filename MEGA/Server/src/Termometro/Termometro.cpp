
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

#include "Termometro.h"



Termometro::Termometro(int identificativo, int pinTermometro, Led* riscaldatore, int temperatura)
{
    _id=identificativo;
    _state=SPENTO;
    thermPin=pinTermometro;
    pRiscaldatore=riscaldatore;
    pRefrigeratore=NULL;
    type=TERMOSTATO;
    pinMode(thermPin, INPUT);
    settedTemperature=temperatura;
    pRiscaldatore->spegni();
    pRiscaldatore->isBusy(true);
};
Termometro::Termometro(int identificativo, int pinTermometro)
{
    _id=identificativo;
    _state=SPENTO;
    thermPin=pinTermometro;
    pRiscaldatore=NULL;
    pRefrigeratore=NULL;
    type=TERMOMETRO;
    pinMode(thermPin, INPUT);
    
};

Termometro::Termometro(int identificativo, int pinTermometro, Led* riscaldatore, Led* refrigeratore, int temperatura, int differenziale)
{
    _id=identificativo;
    _state=SPENTO;
    thermPin=pinTermometro;
    pRiscaldatore=riscaldatore;
    pRefrigeratore=refrigeratore;
    type=CLIMA;
    pinMode(thermPin, INPUT);
    settedTemperature=temperatura;
    delta=differenziale;
    pRefrigeratore->spegni();
    pRefrigeratore->isBusy(true);
    pRiscaldatore->spegni();
    pRiscaldatore->isBusy(true);
};

Termometro::~Termometro()
{
    state(SPENTO);
    if (pRefrigeratore!=NULL)
        pRefrigeratore->isBusy(false);
    if (pRiscaldatore!=NULL)
        pRiscaldatore->isBusy(false);

};

void Termometro::state(bool stato)
{   
    pRiscaldatore->spegni();
    pRefrigeratore->spegni();
    _state=stato;
};
bool Termometro::state()
{   
    return _state;    
};

void Termometro::changeState()
{
    if (_state==ACCESO)
        state(SPENTO);
    else
        state(ACCESO);
    //
    
};
void Termometro::resetTemperature(int temperatura)
{
    settedTemperature=temperatura;
};
int Termometro::getTemperature()
{
    return temperature;
};

int Termometro::getId()
{
    return _id;
};

int Termometro::getPinTerm()
{
    return thermPin;
}

Led* Termometro::getRiscaldatore()
{
    return pRiscaldatore;
};
Led* Termometro::getRefrigeratore()
{
    return pRefrigeratore;
};

int Termometro::getType()
{
    return type;
};

int Termometro::getSetTemperature()
{
    return settedTemperature;
}

int Termometro::getDelta()
{
    return delta;
}

void Termometro::esegui() 
{
    readSensor();
    if (_state==ACCESO)
    {
        if (type==TERMOSTATO)
        {
            if (temperature<=settedTemperature)
                pRiscaldatore->accendi();
            else if (temperature>settedTemperature)
                pRiscaldatore->spegni();
        }
        else if(type==CLIMA)
        {
            if (temperature<=(settedTemperature-delta/2))
            {
                pRiscaldatore->accendi();
            }
            else if (temperature>=(settedTemperature+delta/2))
            {
                pRefrigeratore->accendi();
            }
            else 
            {
                pRefrigeratore->spegni();
                pRiscaldatore->spegni();
            }
        }
    }
};

void Termometro::readSensor()//TODO ##########################################################
{
  //returns the temperature from one DS18B20 in DEG Celsius
 
  byte data[12];
  byte addr[8];
  OneWire ds(thermPin);

 
  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return;
  }
 
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println(F("CRC is not valid!"));
      return;
  }
 
  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print(F("Device is not recognized"));
      return;
  }
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
 
  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad
 
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
 
  ds.reset_search();
 
  byte MSB = data[1];
  byte LSB = data[0];
 
  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
 
  temperature= TemperatureSum*10;
 
};