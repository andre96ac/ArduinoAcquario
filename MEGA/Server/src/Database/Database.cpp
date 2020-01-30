#include "Database.h"

#include <RTClib.h>

#include "../Const/Const.h"

  //############# COSTRUTTORE ######################
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


  //################ FUNZIONI LED ######################
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
  };

  bool Database::addLed (int pin, int tipo)
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
          leds[i]=new Led(pin, tipo);
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
      leds[posizione]=NULL;
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


  //################ FUNZIONI CONTROLLER ######################
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

  bool Database::deletController(int id)
  {
    bool error=false;
    if (controllerPosition(id)==-1)
      error= true;
    else
    {
      int posizione = controllerPosition(id);
      delete controllers[posizione];
      controllers[posizione]=NULL;
    }
    return error; 
    
  }

  int Database::controllerPosition(int id)
  {
    int posizione=-1;
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
      if (controllers[i]->returnId()==id)
      {
        posizione= i;
        break;
      }
    }
    return posizione;
  };

  bool Database::changeControllerState(int id)
  {
    bool errore=false;
    int posizione=controllerPosition(id);
    //se il controller non esiste, ritorna errore
    if (posizione==-1)
    {
      errore=true;
    }
    else //altrimenti, se esiste
    {
      //controlla se almeno uno dei led associati è occupato, e se stò cercando di ACCENDERE il controller
      if (((leds[
        ledPosition(controllers[controllerPosition(id)]->returnIdLed1())
        ]->isBusy())
        ||
        (leds[ledPosition(controllers[controllerPosition(id)]->returnIdLed2())
        ]->isBusy())
      )&&(controllers[posizione]->returnState()==SPENTO))
      {
        //se si, ritorna errore
        errore=true;
      }
      else
      {
        //altrimenti cambia stato
        controllers[posizione]->changeState();
      }
    }
    return errore;    
  };


  //################ FUNZIONI TEMPORIZZATORE ######################

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
    int posizione=-1;
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
      if(temporizzatori[i]->returnId()==id)
      {
        posizione=i;
      }
    }
    return posizione;
  };

  bool Database::resetTemporizzatore(int id, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento)
  {
    bool error=false;
    if(temporizzatorePosition(id)==-1)
      error=true;
    else
    {
      temporizzatori[temporizzatorePosition(id)]->setAccensione(oraAccensione,minutiAccensione);
      temporizzatori[temporizzatorePosition(id)]->setSpegnimento(oraSpegnimento, minutiSpegnimento);
    } 
    return error;
  };

  bool Database::deleteTemporizzatore(int id)
  {
    bool error=false;
    int posizione=temporizzatorePosition(id);
    if (posizione==-1)
      error=true;
    else
    {
      delete temporizzatori[posizione];
      temporizzatori[posizione]=NULL;
    }
    
  };

  bool Database::changeStateTemporizzatore(int id)
  {
    bool error =false;
    if (temporizzatorePosition(id)==-1)
      error=true;
    else
    {
      if ((leds[ledPosition(temporizzatori[temporizzatorePosition(id)]->returnIdLed())]->isBusy())
      &&(temporizzatori[temporizzatorePosition(id)]->returnState()==SPENTO))
      {
        error=true;
      }
      else
      {
        temporizzatori[temporizzatorePosition(id)]->changeState();
      }
      
    }

    return error;
  };


  //################ FUNZIONI TERMOMETRO ######################

  int Database::termometroPosition(int idTermometro)
  {
    int posizione=-1;
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
      if(termometri[i]->getId()==idTermometro)
      {
        posizione=i;
        break;
      }
    }
    return posizione;
  };
  
  bool Database::addTermometro (int id, int pinTermometro, int pinRiscaldatore, int pinRefrigeratore, int temperatura, int differenziale)
  {
    int posizioneLibera=-1;
    if (!dPinsBusy[pinTermometro])
    {
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        if (termometri[i]==NULL)
        {
          posizioneLibera=i;
          break;
        }
      }
    }
    if (posizioneLibera==-1)
      return true;
    else
    {
      termometri[posizioneLibera]=new Termometro(id, pinTermometro, leds[ledPosition(pinRiscaldatore)], leds[ledPosition(pinRefrigeratore)], temperatura, differenziale);
      dPinsBusy[pinTermometro]=true;
      return false;
    }
  };

  bool Database::addTermometro (int id, int pinTermometro, int pinRiscaldatore,  int temperatura)
  {
    int posizioneLibera=-1;
    if (!dPinsBusy[pinTermometro])
    {
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        if (termometri[i]==NULL)
        {
          posizioneLibera=i;
          break;
        }
      }
    }
    if (posizioneLibera==-1)
      return true;
    else
    {
      termometri[posizioneLibera]=new Termometro(id, pinTermometro, leds[ledPosition(pinRiscaldatore)], temperatura);
      dPinsBusy[pinTermometro]=true;
      return false;
    }
  };
  bool Database::addTermometro (int id, int pinTermometro)
  {
    int posizioneLibera=-1;
    if (!dPinsBusy[pinTermometro])
    {
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        if (termometri[i]==NULL)
        {
          posizioneLibera=i;
          break;
        }
      }
    }
    if (posizioneLibera==-1)
      return true;
    else
    {
      termometri[posizioneLibera]=new Termometro(id, pinTermometro);
      dPinsBusy[pinTermometro]=true;
      return false;
    }
  };

  bool Database::deleteTermometro(int id)
  {
    if (termometroPosition(id)==-1)
      return true;
    else
    {
      int posizione=termometroPosition(id);
      dPinsBusy[
        termometri[posizione]->getPinTerm()
      ]=false;
      delete termometri[posizione];
      termometri[posizione]=NULL;
      return false;
    }
  };

  bool Database::changeTermometroState(int id)
  {
    bool error=false;
    if(termometroPosition(id)==-1)
      error=true;
    else
    {
      termometri[termometroPosition(id)]->changeState(); 
    }
    return error; 
  }


//################ FUNZIONI GENERALI ######################

  void Database::sendConfiguration(EthernetClient *client)
  {
    //creo il json
    StaticJsonDocument<CONFIGJSONSIZE>(jsonDocument);
    //creo il campo temperatura ed assegno un valore di test
    JsonArray jsonLeds=jsonDocument.createNestedArray("leds");
    JsonArray jsonDPinBusy=jsonDocument.createNestedArray("dpinbusy");
    JsonArray jsonControllers=jsonDocument.createNestedArray("controllers");
    JsonArray jsonTemporizzatori=jsonDocument.createNestedArray("temporizzatori");
    JsonArray jsonTermometri=jsonDocument.createNestedArray("termometri");

    //scorro l'array dpinbusy
    for (int i=0; i<NDIGITALPIN; i++)
    {
       jsonDPinBusy.add(dPinsBusy[i]);
    }

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
    //scorro l'array di controllers, temporizzatori e termometri
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
        DateTime *acc=temporizzatori[i]->returnAccensione();
        DateTime *spegn=temporizzatori[i]->returnSpegnimento();
        //creo l'oggetto e lo valorizzo
        JsonObject jsonTemporizzatore=jsonTemporizzatori.createNestedObject();
        jsonTemporizzatore["id"]=temporizzatori[i]->returnId();
        jsonTemporizzatore["idled"]=temporizzatori[i]->returnIdLed();
        jsonTemporizzatore["hacc"]=acc->hour();
        jsonTemporizzatore["minacc"]=acc->minute();
        jsonTemporizzatore["hspegn"]=spegn->hour();
        jsonTemporizzatore["minspegn"]=spegn->minute();
        jsonTemporizzatore["state"]=temporizzatori[i]->returnState();
      }
      //se c'è un termometro
      if (termometri[i]!=NULL)
      {
        JsonObject jsonTermometro=jsonTermometri.createNestedObject();
        jsonTermometro["id"]=termometri[i]->getId();
        jsonTermometro["pinterm"]=termometri[i]->getPinTerm();
        jsonTermometro["stato"]=termometri[i]->state();
        jsonTermometro["readtemp"]=termometri[i]->getTemperature();
        jsonTermometro["type"]=termometri[i]->getType();
        if ((termometri[i]->getType()==TERMOSTATO)|(termometri[i]->getType()==CLIMA))
        {
          jsonTermometro["idrisc"]=termometri[i]->getRiscaldatore()->returnPin();
          jsonTermometro["settemp"]=termometri[i]->getSetTemperature();
          if (termometri[i]->getType()==CLIMA)
          {
            jsonTermometro["idrefrig"]=termometri[i]->getRefrigeratore()->returnPin();
            jsonTermometro["deltatemp"]=termometri[i]->getDelta();
          }
        }
      }
    }
    //ora che il json è pronto, lo spedisco al client
    serializeJson(jsonDocument, *client);
    serializeJson(jsonDocument, Serial);
  };

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
      //faccio funzionare tutti i termometri
      if (termometri[i]!=NULL)
        termometri[i]->esegui();
      //
    }  
  };


