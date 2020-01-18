#ifndef DATABASE_H
#define DATABASE_H

#include <RTClib.h>

#include "../Led/Led.h"
#include "../LedController/LedController.h"
#include "../Temporizzatore/Temporizzatore.h" 
#include "../Termometro/Termometro.h"

#include "../Const/Const.h"

class Database
{
  private: 
    Led *leds[NMAXLED];
    LedController *controllers[NMAXCONTROLLERS];
    bool dPinsBusy[NDIGITALPIN];
    Temporizzatore *temporizzatori[NMAXCONTROLLERS];
    Termometro *termometri[NMAXCONTROLLERS];
    RTC_DS1307 *pClock;

  public:
    Database (RTC_DS1307 *clock);

    //ritrona la posizione di un led con uno specifico pin all'interno del vettore di led,
    //se il led non c'è, ritorna -1
    int ledPosition(int pin);
    bool addLed (int pin, int tipo);
    bool removeLed(int pin);
    bool cambiaStatoLed(int pin);


    void changeControllerState(int id);
    bool addController(int id, int pin1, int pin2, int secondi);
    int controllerPosition(int id);
    bool deletController(int id);


    void addTemporizzatore(int id, int pin, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento);
    int temporizzatorePosition(int id);
    void changeStateTemporizzatore(int id);
    bool deleteTemporizzatore(int id);
    bool resetTemporizzatore(int id, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento);

   
    bool addTermometro (int id, int pinTermometro, int pinRiscaldatore, int pinRefrigeratore, int temperatura, int differenziale);
    bool addTermometro (int id, int pinTermometro, int pinRiscaldatore, int temperatura);
    bool addTermometro (int id, int pinTermometro);
    int termometroPosition(int idTermometro);
    bool changeTermometroState (int idTermometro);
    bool deleteTermometro(int id);


    //############################# FUNZIONE JSON, DA SCOMMENTARE SU NUOVA BOARD #####################
   

    void sendConfiguration(EthernetClient *client);
    void executeTimingFunctions();

};


#endif