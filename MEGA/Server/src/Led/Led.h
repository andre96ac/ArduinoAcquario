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