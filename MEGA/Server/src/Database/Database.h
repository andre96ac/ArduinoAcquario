#ifndef DATABASE_H
#define DATABASE_H

#include <RTClib.h>

#include "../Led/Led.h"
#include "../LedController/LedController.h"
#include "../Temporizzatore/Temporizzatore.h" 

#include "../Const/Const.h"

class Database
{
  private: 
    //questo è il json che contiene i dati da mandare
    //################################ DA SCOMMENTARE SU NUOVA BOARD ######################
    static const int CONFIGJSONSIZE=(
                                    JSON_OBJECT_SIZE(4)
                                    +2*JSON_ARRAY_SIZE(NMAXCONTROLLERS)
                                    +JSON_ARRAY_SIZE(NMAXLED)
                                    +NMAXLED*JSON_OBJECT_SIZE(3)
                                    +NMAXCONTROLLERS*JSON_OBJECT_SIZE(5)
                                    +NMAXCONTROLLERS*JSON_OBJECT_SIZE(7)
                                    );
    Led *leds[NMAXLED];
    LedController *controllers[NMAXCONTROLLERS];
    bool dPinsBusy[NDIGITALPIN];
    Temporizzatore *temporizzatori[NMAXCONTROLLERS];
    RTC_DS1307 *pClock;

  public:
    Database (RTC_DS1307 *clock);

    //ritrona la posizione di un led con uno specifico pin all'interno del vettore di led,
    //se il led non c'è, ritorna -1
    int ledPosition(int pin);

    bool addLed (int pin);

    bool removeLed(int pin);

    bool cambiaStatoLed(int pin);

    bool addController(int id, int pin1, int pin2, int secondi);

    void deletController(int id);

    int controllerPosition(int id);
    
    void changeControllerState(int id);

    void addTemporizzatore(int id, int pin, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento);

    int temporizzatorePosition(int id);

    void resetTemporizzatore(int id, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento);
   
    void deleteTemporizzatore(int id);

    void changeStateTemporizzatore(int id);

    //############################# FUNZIONE JSON, DA SCOMMENTARE SU NUOVA BOARD #####################
    void sendConfiguration(EthernetClient *client)
    {
      //creo il json
      StaticJsonDocument<CONFIGJSONSIZE>(jsonDocument);
      //creo il campo temperatura ed assegno un valore di test
      jsonDocument["temperatura"]=5;
      JsonArray jsonLeds=jsonDocument.createNestedArray("leds");
      JsonArray jsonControllers=jsonDocument.createNestedArray("controllers");
      JsonArray jsonTemporizzatori=jsonDocument.createNestedArray("temporizzatori");
      //scorro l'array di led
      for (int i=0; i<NMAXLED; i++)
      {
        //se c'è un led
        if (leds[i]!=NULL)
        {
          //creo l'elemento e lo valorizzo
          JsonObject jsonLed=jsonLeds.createNestedObject();
          jsonLed["id"]=leds[i]->returnPin();
          jsonLed["stato"]=leds[i]->returnStato();
          jsonLed["busy"]=leds[i]->isBusy();
        }
      }
      //scorro l'array di controllers e temporizzatori
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        //se c'è un controller
        if (controllers[i]!=NULL)
        {
          //creo l'oggetto e lo valorizzo
          JsonObject jsonController=jsonControllers.createNestedObject();
          jsonController["id"]=controllers[i]->returnId();
          jsonController["idled1"]=controllers[i]->returnIdLed1();
          jsonController["idled2"]=controllers[i]->returnIdLed2();
          jsonController["deltatime"]=controllers[i]->returnTime();
          jsonController["state"]=controllers[i]->returnState();
        }
        //se c'è un temporizzatore
        if (temporizzatori[i]!=NULL)
        {
          //recupero ora e minuti di accensione e spegnimento
          DateTime acc=temporizzatori[i]->returnAccensione();
          DateTime spegn=temporizzatori[i]->returnSpegnimento();
          //creo l'oggetto e lo valorizzo
          JsonObject jsonTemporizzatore=jsonTemporizzatori.createNestedObject();
          jsonTemporizzatore["id"]=temporizzatori[i]->returnId();
          jsonTemporizzatore["idled"]=temporizzatori[i]->returnIdLed();
          jsonTemporizzatore["hacc"]=acc.hour();
          jsonTemporizzatore["minacc"]=acc.minute();
          jsonTemporizzatore["hspegn"]=spegn.hour();
          jsonTemporizzatore["minspegn"]=spegn.minute();
          jsonTemporizzatore["state"]=temporizzatori[i]->returnState();
        }
      }
      //ora che il json è pronto, lo spedisco al client
      serializeJson(jsonDocument, *client);
      serializeJson(jsonDocument, Serial);
    };

    void executeTimingFunctions();
};


#endif