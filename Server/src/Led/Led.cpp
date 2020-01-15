#include "led.h"
#include "../Const/Const.h"

      Led::Led(int nPin)
      {
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