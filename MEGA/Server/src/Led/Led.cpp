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

#include "led.h"
#include "../Const/Const.h"

      Led::Led(int nPin, int tipo)
      {
        type=tipo;
        stato=SPENTO;
        busy=false;
        pin=nPin;
        pinMode(pin, OUTPUT);
      }
     
      bool Led::isBusy()
      {
        return busy;
      }

      void Led::isBusy(bool scelta)
      {
        busy= scelta;
      }

      void Led::accendi()
      {
        digitalWrite(pin, HIGH);
        stato=ACCESO;
      }

      void Led::spegni()
      {
        digitalWrite(pin, LOW);
        stato=SPENTO;
      }

      bool Led::returnStato()
      {
        return stato;
      }

      void Led::blink(int millis)
      {
        accendi();
        delay(millis);
        spegni();
        delay(millis);
      }

      void Led::cambiaStato()
      {
        if (stato==SPENTO)
          accendi();
        else
          spegni();
      }

      int Led::returnPin()
      {
        return pin;
      }

      void Led::setState(bool scelta)
      {
        if (scelta==ACCESO)
        {
          accendi();
        }
        else
        {
          spegni();
        }
      }