#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#define ACCESO 1
#define SPENTO 0
#define NMAXPARAMS 30

//creo l'orologio
RTC_DS1307 orologio;
 
// Mac Address di Arduino
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192, 168, 1, 3};
 
// Viene inizializzata la libreria Ethernet di Arduino e il webserver gira sulla porta 80
EthernetServer server(80);
 
class Led
{
    private:
      bool stato=SPENTO;
      int pin;
      bool busy=false;
    public:
      Led(int nPin)
      {
        pin=nPin;
        pinMode(pin, OUTPUT);
      };
      bool isBusy()
      {
        return busy;
      };
      void isBusy(bool scelta)
      {
        busy= scelta;
      }
      void accendi()
      {
        digitalWrite(pin, HIGH);
        stato=ACCESO;
      };
      void spegni()
      {
        digitalWrite(pin, LOW);
        stato=SPENTO;
      };
      bool returnStato()
      {
        return stato;
      };
      void blink(int millis)
      {
        accendi();
        delay(millis);
        spegni();
        delay(millis);
      };
      void cambiaStato()
      {
        if (stato==SPENTO)
          accendi();
        else
          spegni();
      };
      int returnPin()
      {
        return pin;
      };
};

/*vecchia versione del parser
class Messaggio2
{
  private:
    String mex;
    String comando;
    int param[NMAXPARAMS];
    int nparams;

  public:
    //oltre a costruire l'oggetto, qui avviene la decodifica della stringa
    //la stringa è di tipo: GET IP....?comando&par1&par2...*
    Messaggio2(String messaggio)
    {    
      int id1, id2;
      String strPar;
      nparams=0;
      mex=messaggio;
      Serial.println("messaggio completo");
      Serial.println(mex);
      id1=mex.indexOf('?');
      if ((mex.indexOf('&', id1+1))>=0) 
        id2=mex.indexOf('&', id1+1);
      else
        id2=mex.indexOf('*', id1+1);
      comando=mex.substring(id1+1,id2);
      
      while(id2>=0)
      {
        id1=id2;
        if ((mex.indexOf('&'),id1+1)>=0)
          id2=mex.indexOf('&',id1+1);
        else
          id2=mex.indexOf('*',id1+1);
        
        strPar=mex.substring(id1+1, id2);
        param[nparams]=atoi(strPar.c_str());
        nparams++;
      }
    };     

    //la funzione restituisce un indirizzo alla stringa del comando
    String* returnComando()
    {
      return &comando;
    };

    //la funzione restituisce un  indirizzo a vettore di parametri
    int* returnParams()
    {
      return &param[0];
    };

    int returnNParams()
    {
        return nparams;
    }
};
*/

class Messaggio{
  private:
    char mex[NMAXPARAMS*3];
    char *parsedMex;
    String comando; //il comando restituito
    int param[NMAXPARAMS]; //l'array di parametri restituiti
    int nparams;
    char *singleParam;

  public:
    Messaggio(String messaggio){
      nparams=0;
      messaggio.toCharArray(mex, NMAXPARAMS*3);
      Serial.println("################ REQUEST ##################");
      Serial.println(mex);
      Serial.println("################ END REQUEST ##################");
      parsedMex=strtok(mex, "?");
      parsedMex=strtok(NULL, "?");
      parsedMex=strtok(parsedMex, "*");
      comando=String(strtok(parsedMex, "&"));
      singleParam=(strtok(NULL, "&"));
      param[nparams]=atoi(singleParam);
      while(singleParam)
      {
        nparams++;
        singleParam=(strtok(NULL, "&"));
        param[nparams]=atoi(singleParam);
      }
  
    }
    //la funzione restituisce un indirizzo alla stringa del comando
    String* returnComando()
    {
      return &comando;
    };

    //la funzione restituisce un  indirizzo a vettore di parametri
    int* returnParams()
    {
      return &param[0];
    };

    int returnNParams()
    {
        return nparams;
    }
};

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
    LedController(int identifiativo)
    {
      id=identifiativo;
      time=0;
      state=SPENTO;
    };

    ~LedController()
    {
      setState(SPENTO);
    }
    bool returnState()
    {
      return state;
    }
    void setLeds(Led *ptrLed1, Led *ptrLed2)
    {
      pL1=ptrLed1;
      pL2=ptrLed2;
    };
    void setTime(int intervallo)
    {
      deltaTime=intervallo;
    };
    void setState(bool stato)
    {
      state=stato;
      if(state==ACCESO)
      {
        pL1->isBusy(true);
        pL2->isBusy(true);
        pL1->accendi();
        pL2->spegni();
        
      }
      else
      {
        pL1->isBusy(false);
        pL2->isBusy(false);
        pL1->spegni();
        pL2->spegni();
      }
      
    };

    void changeState()
    {
      if (state==ACCESO)
        setState(SPENTO);
      else
        setState(ACCESO);      
    }
    
    void lampeggia()
    {
      if ((millis()>=(time+deltaTime))&&(state==ACCESO))
      {
        pL1->cambiaStato();
        pL2->cambiaStato();
        time=millis();
      }
    };

    int returnTime()
    {
      return deltaTime;
    };
    int returnId()
    {
      return id;
    }
};

class Temporizzatore
{
  private:
    int id;
    Led *pL;
    DateTime *oraAccensione;
    DateTime *oraSpegnimento;
    bool state;
    long unsigned int secondiGiornoAccensione, secondiGiornoSpegnimento, secondiGiornoNow;
  public:
    Temporizzatore(int identificativo)
    {
      id=identificativo;
      state=SPENTO;
      oraAccensione= new DateTime(0,0,0,0,0,0);
      oraSpegnimento= new DateTime(0,0,0,0,0,0);
      Serial.println("ho creato il temporizzatore con id");
      Serial.println(id);
      
    };

    ~Temporizzatore()
    {
      setState(SPENTO);
    }

    int returnId()
    {
      return id;
    };

    DateTime returnAccensione()
    {
      return oraAccensione;
    };

    DateTime returnSpegnimento()
    {
      return oraSpegnimento;
    }

    void setLed(Led *led)
    {
      pL=led;
      Serial.println("ho settato il led");
      Serial.println(pL->returnPin());
    };

    void setAccensione(int ora, int minuti)
    {
      delete (oraAccensione);
      oraAccensione=new DateTime(0,0,0,ora,minuti,0);
      Serial.println("ho settato l'accensione con orario ");
      Serial.print(oraAccensione->hour());
      Serial.print(" ");
      Serial.print(oraAccensione->minute());
      //devo anche aggiornare i secondiGiornoAccensione
      secondiGiornoAccensione=ora*60*60+minuti*60;
    };

    void setSpegnimento(int ora, int minuti)
    {
      delete (oraSpegnimento);
      oraSpegnimento=new DateTime(0,0,0,ora,minuti,0);

      Serial.println("ho settato lo spegnimento con orario ");
      Serial.print(oraSpegnimento->hour());
      Serial.print(" ");
      Serial.print(oraSpegnimento->minute());
      secondiGiornoSpegnimento=ora*60*60+minuti*60;
    };

    void setState(bool stato)
    {
      state=stato;
      if (state==ACCESO)
      {
        pL->isBusy(true);
        pL->spegni();
        Serial.println("ho acceso il temporizzatore");
      }
      else
      {
        pL->isBusy(false);
        pL->spegni();
        Serial.println("ho spento il temporizzatore");
      }
    };

    void changeState()
    {
      if (state==ACCESO)
        setState(SPENTO);
      //
      else
        setState(ACCESO);
      //    
        
    };

    void esegui()
    {
      secondiGiornoNow=(orologio.now().hour()*60*60+orologio.now().minute()*60+orologio.now().second());
      /* STAMPA ORARI X DEBUG
      Serial.println(secondiGiornoAccensione);
      Serial.println(secondiGiornoNow);
      Serial.println(secondiGiornoSpegnimento);*/
      if (state==ACCESO)
      {
        if((secondiGiornoNow>=secondiGiornoAccensione)&&(secondiGiornoNow<secondiGiornoSpegnimento))
        {
          //accendo solo se effettivamente non è acceso
          if(pL->returnStato()!=ACCESO)
            pL->accendi();
          //
        }
        else
        {
          pL->spegni();
        }
      }
    };
    
};

class Database
{
  private: 
    static const int NMAXLED=10;
    static const int NDIGITALPIN=14;
    static const int NANALOGPIN=6;
    static const int NMAXCONTROLLERS=5;
    Led *leds[NMAXLED];
    LedController *controllers[NMAXCONTROLLERS];
    bool dPinsBusy[NDIGITALPIN]={1,1,0,0,0,0,0,0,0,0,1,1,1,1};
    Temporizzatore *temporizzatori[NMAXCONTROLLERS];

  public:
    Database ()
    {
    };

    //ritrona la posizione di un led con uno specifico pin all'interno del vettore di led
    int ledPosition(int pin)
    {
      int i;
      for (i=0; i<NMAXLED; i++)
      {
        if (leds[i]->returnPin()==pin)
          break;
      }
      return i;
    }

    void addLed (int pin)
    {
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
    };

    void removeLed(int pin)
    {
      int posizione=ledPosition(pin);
      leds[posizione]->spegni();
      delete leds[posizione];
      dPinsBusy[pin]=false;
    };

    void cambiaStatoLed(int pin)
    {
      int posizione=ledPosition(pin);
      if (leds[posizione]->isBusy()==false)
        leds[posizione]->cambiaStato();
    };

    void addController(int id, int pin1, int pin2, int secondi)
    {
      //trovo il primo spazio nell'array di controllers
      for (int i=0; i<NMAXCONTROLLERS;i++)
      {
        if (controllers[i]==NULL)
        {
          //creo il nuovo controller nello spazio vuoto trovato
          controllers[i]= new LedController(id);
          //setto i led passando l'indirizzo dell elemento alla posizione trovata da ledPosition()
          controllers[i]->setLeds((leds[ledPosition(pin1)]),(leds[ledPosition(pin2)]));
          //setto il tempo sulla base del parametro
          controllers[i]->setTime(secondi);
          break;
        }
      }
    };

    void deletController(int id)
    {
      delete controllers[controllerPosition(id)];
    }

    int controllerPosition(int id)
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

    void changeControllerState(int id)
    {
      int posizione=controllerPosition(id);
      controllers[posizione]->changeState();
    };

    void addTemporizzatore(int id, int pin, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento)
    {
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        if (temporizzatori[i]==NULL)
        {
          
          temporizzatori[i] = new Temporizzatore(id);
          temporizzatori[i]->setLed(leds[ledPosition(pin)]);
          temporizzatori[i]->setAccensione(oraAccensione,minutiAccensione);
          temporizzatori[i]->setSpegnimento(oraSpegnimento, minutiSpegnimento);
          break;
        }
      }
    };

    int temporizzatorePosition(int id)
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

    void resetTemporizzatore(int id, int oraAccensione, int minutiAccensione, int oraSpegnimento, int minutiSpegnimento)
    {
      temporizzatori[temporizzatorePosition(id)]->setAccensione(oraAccensione,minutiAccensione);
      temporizzatori[temporizzatorePosition(id)]->setSpegnimento(oraSpegnimento, minutiSpegnimento);
    };

    void deleteTemporizzatore(int id)
    {
      delete temporizzatori[temporizzatorePosition(id)];
    };

    void changeStateTemporizzatore(int id)
    {
      temporizzatori[temporizzatorePosition(id)]->changeState();
    }
    void executeTimingFunctions()
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
};

Database db;

void setup() {
  Wire.begin();
  //inizializzo l'orologio
  orologio.begin();
  //avvisami se l'orologio non sta funzionando
  if (! orologio.isrunning()) 
    Serial.println("RTC is NOT running!");
  //setto l'orologio all'ora di compilazione
  orologio.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

}
 
void loop() 
{
  char c;
  String request; 
  int nParams;
  int* params;
  String* command;

  // Vengono ascoltati nuovi client
  EthernetClient client = server.available();
  if (client) 
  {
    Serial.println("new client");
    // Finisce una richiesta HTTP
    boolean currentLineIsBlank = true;
    request ="";
    while (client.connected()) 
    {
      if (client.available()) 
      {
        c = client.read();
        if(request.length()<NMAXPARAMS*3){
          request +=c;
        }
        // Se viene completato l'invio della richiesta HTTP, allora il server invia la risposta
        if (c == '\n' && currentLineIsBlank) 
        { 
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    client.println("HTTP/1.1 200 OK");         
    delay(1);
    // Viene chiusta la connessione
    client.stop();
    Serial.println("client disconnected");
  }
  //esecuzione pratica delle azioni 
  Messaggio messaggio(request);
  Serial.println(request);
  if ((*(messaggio.returnComando()))=="switch")
    db.cambiaStatoLed((messaggio.returnParams())[0]);
  else if ((*(messaggio.returnComando()))=="addled")
    db.addLed((messaggio.returnParams())[0]);
  else if ((*(messaggio.returnComando()))=="removeled")
    db.removeLed((messaggio.returnParams())[0]);
  //mi aspetto un comando "?newcontroller&id&pinled1&pinled2&millisecondi"
  else if ((*(messaggio.returnComando()))=="addcontroller")
  {
    db.addController(
      ((messaggio.returnParams())[0]),
      ((messaggio.returnParams())[1]),
      ((messaggio.returnParams())[2]),
      ((messaggio.returnParams())[3])
      );
  }
  else if ((*(messaggio.returnComando()))=="changecontrollerstate")
    db.changeControllerState(messaggio.returnParams()[0]);
  else if ((*(messaggio.returnComando()))=="removecontroller")
    db.deletController(messaggio.returnParams()[0]);
  else if ((*(messaggio.returnComando()))=="addtemporizzatore")
  {
      db.addTemporizzatore(
      ((messaggio.returnParams())[0]),
      ((messaggio.returnParams())[1]),
      ((messaggio.returnParams())[2]),
      ((messaggio.returnParams())[3]),
      ((messaggio.returnParams())[4]),
      ((messaggio.returnParams())[5])
    );
  }
  else if ((*(messaggio.returnComando()))=="changetemporizzatorestate")
    db.changeStateTemporizzatore(messaggio.returnParams()[0]);
  //
  else if (*(messaggio.returnComando())=="resettemporizzatore")
  {
    db.resetTemporizzatore(
      ((messaggio.returnParams())[0]),
      ((messaggio.returnParams())[1]),
      ((messaggio.returnParams())[2]),
      ((messaggio.returnParams())[3]),
      ((messaggio.returnParams())[4])
    );
  }
  else if (*(messaggio.returnComando())=="removetemporizzatore")
  {
    db.deleteTemporizzatore(
      ((messaggio.returnParams())[0])
    );
  }
  db.executeTimingFunctions();
}
    
   