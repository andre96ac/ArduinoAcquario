#include "Database.h"

#include <RTClib.h>
#include <SD.h>

#include "../Const/Const.h"

  //############# COSTRUTTORE ######################
  Database::Database (RTC_DS1307 *clock)
  {
      dPinsBusy[0]=1;
      dPinsBusy[1]=1;
      dPinsBusy[2]=0;
      dPinsBusy[3]=0;
      dPinsBusy[4]=1;//utilizzato per l'SD
      dPinsBusy[5]=0;
      dPinsBusy[6]=0;
      dPinsBusy[7]=0;
      dPinsBusy[8]=0;
      dPinsBusy[9]=0;
      dPinsBusy[10]=1;//utilizzato per l'ethernet
      dPinsBusy[11]=1;
      dPinsBusy[12]=1;
      dPinsBusy[13]=1;
      dPinsBusy[30]=0;
      dPinsBusy[32]=0;
      
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
      if (leds[posizione]->isBusy())
        error=true;
      else
      {
        leds[posizione]->spegni();
        delete leds[posizione];
        leds[posizione]=NULL;
        dPinsBusy[pin]=false;
      }
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
        // cambia stato
        controllers[posizione]->changeState();
    
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
        temporizzatori[temporizzatorePosition(id)]->changeState();      
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


//################ FUNZIONI OSMO ##########################

bool Database::addOsmo(int id, byte normalSwitchPin, byte emergencySwitchPin, byte pinDevice)
{
  bool error=true;
  //se le due prese associate agli switch sono libere, e il led non è occupato
  if ((!dPinsBusy[normalSwitchPin]&&!dPinsBusy[emergencySwitchPin])&&(!leds[ledPosition(pinDevice)]->isBusy()))
  {
    //scorri l'array di osmos
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
      //se trovi una posizione libera
      if (osmos[i]==NULL)
      {
        //crea un nuovo osmo nella posizione trovata, e setta l'errore a false
        osmos[i]=new Osmo(id, leds[ledPosition(pinDevice)], normalSwitchPin, emergencySwitchPin );
        dPinsBusy[normalSwitchPin]=true;
        dPinsBusy[emergencySwitchPin]=true;
        error=false;
        break;
      }
    }
  }
  return error;
}

/**La funzione restituisce l'indice del device all'interno del vettore. se il device non è trovato, restituisce -1 */
int Database::osmoPosition(int id)
{
  int posizione=-1;
  for (int i=0; i<NMAXCONTROLLERS; i++)
  {
    if (osmos[i]!=NULL)
    {
      if (osmos[i]->getConfig()->id==id)
      {
        posizione=i;
        break;
      }
    }
  }
  return posizione;
}

bool Database:: changeOsmoState (int id)
{
  bool error=true;
  if (osmoPosition(id)>=0)
  {
    osmos[osmoPosition(id)]->changeState();
    error=false;
  }
  return error;
}

bool Database:: deleteOsmo(int id)
{
  bool error=true;
  int posizione = osmoPosition(id);
  if (posizione>=0)
  {
    dPinsBusy[osmos[posizione]->getConfig()->switch1Pin]=false;
    dPinsBusy[osmos[posizione]->getConfig()->switch2Pin]=false;      
    delete osmos[posizione];
    osmos[posizione]=NULL;
    error=false;
  }
  return error;
}

  
//################# FUNZIONI PLAFO #######################

bool Database::addPlafoChannel(byte presa)
{
  bool error=true;
  if (dPinsBusy[presa]==false)
  {
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
      if (plafoniera.ligthChannels[i]==NULL)
      {
        plafoniera.ligthChannels[i]=new Channel(presa, pClock);
        dPinsBusy[presa]=true;
        error=false;
        break;
      }
    }
  }
  return error;
};

int Database::plafoChannelPosition(byte presa)
{
  int posizione=-1;
  for (int i=0; i<NMAXCONTROLLERS;i++)
  {
    if (plafoniera.ligthChannels[i]->getPresa()==presa)
    {
      posizione=i;
      break;
    }
  }
  return posizione;
};

bool Database::deletePlafoChannel(byte presa)
{
  bool error=true;
  int posizione=plafoChannelPosition(presa);
  if (posizione>=0)
  {
    dPinsBusy[presa]=false;
    delete plafoniera.ligthChannels[posizione];
    plafoniera.ligthChannels[posizione]=NULL;
    error=false;
  }
  return error;
};

bool Database::setStatePlafoChannel(byte presa, byte potenza)
{
  bool error=true;
  int posizione=plafoChannelPosition(presa);
  if (posizione>=0)
  {
    plafoniera.ligthChannels[posizione]->setStatoAccensione(potenza);
    error=false;
  }
  return error;
};

bool Database::setTimerPlafoChannel(byte presa, int hAcc, int minAcc, int hSpegn, int minSpegn, int minDurata)
{
  bool error=true;
  int posizione=plafoChannelPosition(presa);
  if (posizione>=0)
  {
    plafoniera.ligthChannels[posizione]->setTimer(new DateTime(0,0,0,hAcc,minAcc,0),new DateTime(0,0,0,hSpegn,minSpegn));
    plafoniera.ligthChannels[posizione]->setDurata(minDurata);
    error=false;
  }
  return error;
};

bool Database::changeTypeAccPlafoChannel(byte presa)
{
  int posizione=plafoChannelPosition(presa);
  bool error=true;
  if (posizione>=0)
  {
    plafoniera.ligthChannels[posizione]->changeTipoAccensione();
    error=false;
  }
  return error;
}

bool Database::setPlafoFan(byte presa)
{
  bool error=true;
  if (dPinsBusy[presa]==false)
  {
    if (plafoniera.getFanPin()<NDIGITALPIN)
    {
      dPinsBusy[plafoniera.getFanPin()]=false;
    }
    dPinsBusy[presa]=true;
    plafoniera.setFanPin(presa);    
    error=false;
  }
  return error;
}





//################ FUNZIONI GENERALI ######################

  StaticJsonDocument<CONFIGJSONSIZE> Database::prepareJson()
  {
    //creo il json
    StaticJsonDocument<CONFIGJSONSIZE>(jsonDocument);
    JsonObject jsonSystemTime=jsonDocument.createNestedObject("systemtime");
    JsonArray jsonLeds=jsonDocument.createNestedArray("leds");
    JsonArray jsonControllers=jsonDocument.createNestedArray("controllers");
    JsonArray jsonTemporizzatori=jsonDocument.createNestedArray("temporizzatori");
    JsonArray jsonTermometri=jsonDocument.createNestedArray("termometri");
    JsonArray jsonOsmos=jsonDocument.createNestedArray("osmos");
    JsonArray jsonDPinBusy=jsonDocument.createNestedArray("dpinbusy");
    JsonObject jsonPlafo=jsonDocument.createNestedObject("plafoniera");
    JsonArray jsonChannels=jsonPlafo.createNestedArray("channels");

    //recupero data ed ora di sistema e la inserisco nel json
    DateTime now=pClock->now();
    jsonSystemTime["year"]=now.year();
    jsonSystemTime["month"]=now.month();
    jsonSystemTime["day"]=now.day();
    jsonSystemTime["hour"]=now.hour();
    jsonSystemTime["minute"]=now.minute();
    jsonSystemTime["second"]=now.second();

    //inserisco nel json tutti i dati della plafoniera
    jsonPlafo["fanpin"]=plafoniera.getFanPin();
    jsonPlafo["fanstate"]=plafoniera.getFanState();
    //ora inserisco nell'oggetto plafoniera, tutti i dati di tutti i canali
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
      if(plafoniera.ligthChannels[i]!=NULL)
      {
        JsonObject jsonChannel =jsonChannels.createNestedObject();
        jsonChannel["pin"]=plafoniera.ligthChannels[i]->getPresa();
        jsonChannel["tipoaccensione"]=plafoniera.ligthChannels[i]->getTipoAccensione();
        jsonChannel["statoaccensione"]=plafoniera.ligthChannels[i]->getStato();
        jsonChannel["hacc"]=plafoniera.ligthChannels[i]->getAccensione().hour();
        jsonChannel["minacc"]=plafoniera.ligthChannels[i]->getAccensione().minute();
        jsonChannel["hspegn"]=plafoniera.ligthChannels[i]->getSpegnimento().hour();
        jsonChannel["minspegn"]=plafoniera.ligthChannels[i]->getSpegnimento().minute();
        jsonChannel["durataciclo"]=plafoniera.ligthChannels[i]->getDurataAccensione();
      }
    }
    


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
    //scorro l'array di controllers, temporizzatori, termometri ed osmoregolatori
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
      if (osmos[i]!=NULL)
      {
        JsonObject jsonOsmo=jsonOsmos.createNestedObject();
        jsonOsmo["id"]=osmos[i]->getConfig()->id;
        jsonOsmo["idled"]=osmos[i]->getConfig()->pL->returnPin();
        jsonOsmo["idSwitch1"]=osmos[i]->getConfig()->switch1Pin;
        jsonOsmo["idSwitch2"]=osmos[i]->getConfig()->switch2Pin;
        jsonOsmo["stateSwitch1"]=osmos[i]->getConfig()->switch1State;
        jsonOsmo["stateSwitch2"]=osmos[i]->getConfig()->switch2State;
        jsonOsmo["state"]=osmos[i]->getConfig()->osmoState;
        jsonOsmo["emptyError"]=osmos[i]->getConfig()->emptyError;
      }
    }

    //aggiungo i dati della plafo
    return jsonDocument;
  };

  //######################################### QUI BISOGNA IMPLEMENTARE IL BINDING
  void Database::loadFromFile(char* nomeFile)
  {
    File file;
    file=SD.open(nomeFile);
    // creo il Json
    StaticJsonDocument<CONFIGJSONSIZE>(jsonDocument);
    //deserializzo il contenuto del file all'interno del json
    if (file)
    {
      deserializeJson(jsonDocument, file);
    }

    //carico dal json l'array dpinbusy
    int i=0;
    JsonArray jsonBusys=jsonDocument["dpinbusy"].as<JsonArray>();
    for (JsonObject jsonBusy : jsonBusys )
    {
      dPinsBusy[i]=jsonBusy;
      i++;
    }

    //carico i leds
    i=0;
    JsonArray jsonLeds=jsonDocument["leds"].as<JsonArray>();
    for (JsonObject jsonLed : jsonLeds)
    {
      leds[i]=new Led(jsonLed["id"],0);
      leds[i]->setState(jsonLed["stato"]);
      leds[i]->isBusy(jsonLed["busy"]);
      i++;
    }

    //carico i controllers
    JsonArray jsonControllers=jsonDocument["controllers"].as<JsonArray>();
    i=0;
    for (JsonObject jsonController : jsonControllers)
    {
      controllers[i]=new LedController((int)jsonController["id"]);
      controllers[i]->setLeds(
        (leds[ledPosition(jsonController["idled1"])]),
        (leds[ledPosition(jsonController["idled2"])])
        );
      controllers[i]->setTime(jsonController["deltatime"]);
      controllers[i]->setState(jsonController["state"]);
      i++;
    }

    //carico i temporizzatori
    JsonArray jsonTemporizzatori=jsonDocument["temmporizzatori"].as<JsonArray>();
    i=0;
    for (JsonObject jsonTemporizzatore : jsonTemporizzatori)
    {
      temporizzatori[i]=new Temporizzatore(jsonTemporizzatore["id"], pClock);
      temporizzatori[i]->setLed(leds[ledPosition(jsonTemporizzatore["idled"])]);
      temporizzatori[i]->setAccensione(jsonTemporizzatore["hacc"],jsonTemporizzatore["minacc"]);
      temporizzatori[i]->setSpegnimento(jsonTemporizzatore["hspegn"],jsonTemporizzatore["minspegn"]);
      temporizzatori[i]->setState(jsonTemporizzatore["state"]);
      i++;
    }

    //carico i termometri
    i=0;
    JsonArray jsonTermometri=jsonDocument["termometri"].as<JsonArray>();
    for (JsonObject jsonTermometro : jsonTermometri)
    {
      int tipo=jsonTermometro["type"];
      if(tipo==TERMOMETRO)
      {
        termometri[i]=new Termometro(jsonTermometro["id"],jsonTermometro["pinterm"]);
      }
      else if(tipo==TERMOSTATO)
      {
        termometri[i]=new Termometro(
          jsonTermometro["id"],
          jsonTermometro["pinterm"],
          leds[ledPosition(jsonTermometro["idrisc"])],
          jsonTermometro["settemp"]
          );
      }
      else if (tipo==CLIMA)
      {
        termometri[i]=new Termometro(
          jsonTermometro["id"],
          jsonTermometro["pinterm"],
          leds[ledPosition(jsonTermometro["idrisc"])],
          leds[ledPosition(jsonTermometro["idrefrig"])],
          jsonTermometro["settemp"],
          jsonTermometro["deltatemp"]
          );
      }
      termometri[i]->state(jsonTermometro["stato"]);
      i++;
    }

    //carico gli osmoregolatori
    i=0;
    JsonArray jsonOsmos=jsonDocument["osmos"].as<JsonArray>();
    for (JsonObject jsonOsmo: jsonOsmos)
    {
      osmos[i]= new Osmo(
        jsonOsmo["id"],
        leds[ledPosition(jsonOsmo["idled"])],
        jsonOsmo["idSwitch1"],
        jsonOsmo["idSwitch2"]        
        );
        osmos[i]->setState(jsonOsmo["state"]);
      i++;
    }
  }

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
      //faccio funzionare tutti gli osmo
      if (osmos[i]!=NULL)
        osmos[i]->ceckLevel();
      //
    }  
    //faccio funzionare la plafoniera (che regolerà la ventola e farà funzionare tutti i canali)
    plafoniera.esegui();
  };

  void Database::setClock(byte year, byte month, byte day, byte hour, byte minute)
  {
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

    pClock->adjust(DateTime(year, month, day, hour, minute, 0));
  }


