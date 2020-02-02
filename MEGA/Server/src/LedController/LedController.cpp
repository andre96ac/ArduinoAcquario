    #include "LedController.h"


  
    LedController::LedController(int identifiativo)
    {
      id=identifiativo;
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
      if ((millis()>=(time+deltaTime))&&(state==ACCESO))
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

