    
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
    
    #include "LedController.h"
    #include "../Const/Const.h"


  
    LedController::LedController(int identificativo)
    {
      id=identificativo;
      time=0;
      state=SPENTO;
    };

    LedController::~LedController()
    {
      setState(SPENTO);
      pL1->isBusy(false);
      pL2->isBusy(false);
    }
    bool LedController::returnState()
    {
      return state;
    }
    void LedController::setLeds(Led *ptrLed1, Led *ptrLed2)
    {
      pL1=ptrLed1;
      pL2=ptrLed2;
      pL1->isBusy(true);
      pL2->isBusy(true);

    };
    void LedController::setTime(int intervallo)
    {
      deltaTime=intervallo;
    };
    void LedController::setState(bool stato)
    {
      state=stato;
      if(state==ACCESO)
      {
        pL1->accendi();
        pL2->spegni();
      }
      else
      {
        pL1->spegni();
        pL2->spegni();
      }
      
    };

    void LedController::changeState()
    {
      if (state==ACCESO)
        setState(SPENTO);
      else
        setState(ACCESO);      
    }
    
    void LedController::lampeggia()
    {
      if (((millis()-deltaTime)>=time)&&(state==ACCESO))
      {
        pL1->cambiaStato();
        pL2->cambiaStato();
        time=millis();
      }
    };

    int LedController::returnTime()
    {
      return deltaTime;
    };
    int LedController::returnId()
    {
      return id;
    };
    int LedController::returnIdLed1()
    {
      return pL1->returnPin();
    };
    int LedController::returnIdLed2()
    {
      return pL2->returnPin();
    }

