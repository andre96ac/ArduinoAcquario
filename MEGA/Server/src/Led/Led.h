#ifndef LED_H
#define LED_H

class Led
{
    private:
      bool stato;
      int pin;
      bool busy;
    public:
      Led(int nPin);
      bool isBusy(void);      
      void isBusy(bool scelta);
      void accendi(void);
      void spegni(void);
      bool returnStato(void);
      void blink(int millis);
      void cambiaStato(void);
      int returnPin(void);
};


#endif