#ifndef TEMPORIZZATORE_H
#define TEMPORIZZATORE_H

#include <RTClib.h>
#include "../Led/Led.h"

class Temporizzatore
{
  private:
    int id;
    Led *pL;
    DateTime *oraAccensione;
    DateTime *oraSpegnimento;
    bool state;
    long unsigned int secondiGiornoAccensione, secondiGiornoSpegnimento, secondiGiornoNow;
    RTC_DS1307 *pClock;
  public:
    Temporizzatore(int identificativo, RTC_DS1307 *clock );
    ~Temporizzatore();
    int returnId();
    int returnIdLed();
    DateTime returnAccensione();
    DateTime returnSpegnimento();
    bool returnState();
    void setLed(Led *led);
    void setAccensione(int ora, int minuti);
    void setSpegnimento(int ora, int minuti);
    void setState(bool stato);
    void changeState();
    void esegui();
};

#endif