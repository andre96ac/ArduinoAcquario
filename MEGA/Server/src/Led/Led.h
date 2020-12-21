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

#ifndef LED_H
#define LED_H

class Led
{
    private:
      bool stato;
      int pin;
      bool busy;
      int type;
    public:
      Led(int nPin, int tipo);
      bool isBusy(void);      
      void isBusy(bool scelta);
      void accendi(void);
      void spegni(void);
      bool returnStato(void);
      void blink(int millis);
      void cambiaStato(void);
      int returnPin(void);
      void setState(bool scelta);
};


#endif