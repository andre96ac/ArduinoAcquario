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
    LedController(int identifiativo);
    
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