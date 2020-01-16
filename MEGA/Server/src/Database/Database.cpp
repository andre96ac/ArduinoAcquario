#include "Database.h"

#include <RTClib.h>

#include "../Const/Const.h"

    //questo è il json che contiene i dati da mandare
    //################################ DA SCOMMENTARE SU NUOVA BOARD ######################
    /*static const int CONFIGJSONSIZE=(
                                    JSON_OBJECT_SIZE(4)
                                    +2*JSON_ARRAY_SIZE(NMAXCONTROLLERS)
                                    +JSON_ARRAY_SIZE(NMAXLED)
                                    +NMAXLED*JSON_OBJECT_SIZE(3)
                                    +NMAXCONTROLLERS*JSON_OBJECT_SIZE(5)
                                    +NMAXCONTROLLERS*JSON_OBJECT_SIZE(7)
                                    );*/
    Database::Database (RTC_DS1307 *clock)
    {
        dPinsBusy[0]=1;
        dPinsBusy[1]=1;
        dPinsBusy[2]=0;
        dPinsBusy[3]=0;
        dPinsBusy[4]=0;
        dPinsBusy[5]=0;
        dPinsBusy[6]=0;
        dPinsBusy[7]=0;
        dPinsBusy[8]=0;
        dPinsBusy[9]=0;
        dPinsBusy[10]=1;
        dPinsBusy[11]=1;
        dPinsBusy[12]=1;
        dPinsBusy[13]=1;
        
        pClock=clock;
    };

    //ritrona la posizione di un led con uno specifico pin all'interno del vettore di led,
    //se il led non c'è, ritorna -1
    int Database::ledPosition(int pin)
    {
      int i=-1;
      for (i=0; i<NMAXLED; i++)
      {
        if (leds[i]->returnPin()==pin)
          break;
      }
      return i;
    }

    bool Database::addLed (int pin)
    {
      bool error=false;
      //se il pin è libero
      if (dPinsBusy[pin]==false)
      {
        //cerca la prima posizione libera nel vettore
        for (int i=0; i<NMAXLED; i++)
        {
          //quando la trovi
          if (leds[i]==NULL)
          {
            //crea il nuovo led ed inseriscilo nella posizione vuota trovata
            leds[i]=new Led(pin);
            //setta il pin utilizzato come occupato
            dPinsBusy[pin]=true;
            break;
          }
        }
      }
      else
      {
        error=true;
      }
      return error;      
    };

    bool Database::removeLed(int pin)
    {
      bool error=false;
      int posizione=ledPosition(pin);
      if (posizione<0)
        error=true;
      else
      {
        leds[posizione]->spegni();
        delete leds[posizione];
        dPinsBusy[pin]=false;
      }
      return error;      
    };

    bool Database::cambiaStatoLed(int pin)
    {
      bool error=false;
      int posizione=ledPosition(pin);
      if (posizione<0)
        error=true;
      else
      {
        if (leds[posizione]->isBusy()==true)
          error=true;
        else
          leds[posizione]->cambiaStato();
      }
      return error;
    };

    bool Database::addController(int id, int pin1, int pin2, int secondi)
    {
      bool errore=false;
      //trovo il primo spazio nell'array di controllers
      for (int i=0; i<NMAXCONTROLLERS;i++)
      {
        if (controllers[i]==NULL)
        {
          //creo il nuovo controller nello spazio vuoto trovato
          controllers[i]= new LedController(id);
          int posizioneLed1=ledPosition(pin1);
          int posizioneLed2=ledPosition(pin2);
          if ((posizioneLed1<0)||(posizioneLed2<0))
            errore=true;
          else
          {        
            //setto i led passando l'indirizzo dell elemento alla posizione trovata da ledPosition()
            controllers[i]->setLeds((leds[ledPosition(pin1)]),(leds[ledPosition(pin2)]));
            //setto il tempo sulla base del parametro
            controllers[i]->setTime(secondi);
          }
          break;
        }
      }
      return errore;
    };

    void Database::deletController(int id)
    {
      delete controllers[controllerPosition(id)];
    }

    int Database::controllerPosition(int id)
    {
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        if (controllers[i]->returnId()==id)
        {
          return i;
          break;
        }
      }
    };

    void Database::changeControllerState(int id)
    {
      int posizione=controllerPosition(id);
      controllers[posizione]->changeState();
    };

    void Database::addTemporizzatore(int id, int pin, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento)
    {
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        if (temporizzatori[i]==NULL)
        {
          
          temporizzatori[i] = new Temporizzatore(id, pClock);
          temporizzatori[i]->setLed(leds[ledPosition(pin)]);
          temporizzatori[i]->setAccensione(oraAccensione,minutiAccensione);
          temporizzatori[i]->setSpegnimento(oraSpegnimento, minutiSpegnimento);
          break;
        }
      }
    };

    int Database::temporizzatorePosition(int id)
    {
      int i;
      for (i=0; i<NMAXCONTROLLERS; i++)
      {
        if(temporizzatori[i]->returnId()==id)
          break;
        //
      }
      return i;
    };

    void Database::resetTemporizzatore(int id, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento)
    {
      temporizzatori[temporizzatorePosition(id)]->setAccensione(oraAccensione,minutiAccensione);
      temporizzatori[temporizzatorePosition(id)]->setSpegnimento(oraSpegnimento, minutiSpegnimento);
    };

    void Database::deleteTemporizzatore(int id)
    {
      delete temporizzatori[temporizzatorePosition(id)];
    };

    void Database::changeStateTemporizzatore(int id)
    {
      temporizzatori[temporizzatorePosition(id)]->changeState();
    }


    //############################# FUNZIONE JSON, DA SCOMMENTARE SU NUOVA BOARD #####################
    /*void sendConfiguration(EthernetClient *client)
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
    };*/


    void Database::executeTimingFunctions()
    {
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        //faccio funzionare tutti i controller
        if (controllers[i]!=NULL)
          controllers[i]->lampeggia();
        //
        //faccio funzionare tutti i temporizzatori
        if (temporizzatori[i]!=NULL)
          temporizzatori[i]->esegui();
        //
      }    
    };

