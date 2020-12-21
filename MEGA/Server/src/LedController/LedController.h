
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

#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include "../Led/Led.h"

class LedController
{
  private:
    int id;
    Led *pL1;
    Led *pL2;
    int deltaTime;
    unsigned long time;
    bool state;
  public:
    LedController(int identificativo);
    
    ~LedController();
    
    bool returnState(void);
    
    void setLeds(Led *ptrLed1, Led *ptrLed2);
    
    void setTime(int intervallo);
    
    void setState(bool stato);
    
    void changeState(void);
    
    void lampeggia(void);

    int returnTime(void);
    
    int returnId(void);
   
    int returnIdLed1(void);
    
    int returnIdLed2(void);

};

#endif