#include <RTClib.h>



/*
Questo programma mostra come sia possibile inserire del codice HTML all'interno della
pagina web del webserver di Arduino*/
 
#include <SPI.h>
#include <Ethernet.h>
#define ACCESO 1
#define SPENTO 0
#define NMAXPARAMS 10
 
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

class Messaggio
{
  private:
    String mex;
    String comando;
    int param[NMAXPARAMS];
    int nparams;

  public:
    //oltre a costruire l'oggetto, qui avviene la decodifica della stringa
    //la stringa è di tipo: GET IP....?comando&par1&par2...*
    Messaggio(String messaggio)
    {    
      int id1, id2;
      String strPar;
      nparams=0;

      mex=messaggio;
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

  public:
    Database ()
    {
    };

    //ritrona la posizione di un led con uno specifico pin all'interno del vettore di led,
    //se il led non c'è, ritorna -1
    int ledPosition(int pin)
    {
      int i=-1;
      for (i=0; i<NMAXLED; i++)
      {
        if (leds[i]->returnPin()==pin)
          break;
      }
      return i;
    }

    bool addLed (int pin)
    {
      bool error=false
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

    void removeLed(int pin)
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

    bool cambiaStatoLed(int pin)
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

    void addController(int id, int pin1, int pin2, int secondi)
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
    }



    void executeTimingFunctions()
    {
      //faccio funzionare tutti i controller
      for (int i=0; i<NMAXCONTROLLERS; i++)
      {
        if (controllers[i]!=NULL)
          controllers[i]->lampeggia();
      }
    };
};

Database db;

void setup() {
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
  bool executionError, requestError=false;
  // Vengono ascoltati nuovi client
  EthernetClient client = server.available();
  if (client) 
  {
    Serial.println("new client");
    // Finisce una richiesta HTTP
    boolean currentLineIsBlank = true;
    request ="";
    //mentre il client è connesso, scarica la richiesta
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
    //inizializzo (e quindi faccio il parsing) il messaggio
    Messaggio messaggio(request);
    //esecuzione pratica dell'azione richiesta 
    if ((*(messaggio.returnComando()))=="switch")
      executionError=db.cambiaStatoLed((messaggio.returnParams())[0]);
    else if ((*(messaggio.returnComando()))=="addled")
      executionError=db.addLed((messaggio.returnParams())[0]);
    else if ((*(messaggio.returnComando()))=="removeled")
      executionError=db.removeLed((messaggio.returnParams())[0]);
    else if ((*(messaggio.returnComando()))=="addcontroller")
    {
      executionError=db.addController(
        ((messaggio.returnParams())[0]),
        ((messaggio.returnParams())[1]),
        ((messaggio.returnParams())[2]),
        ((messaggio.returnParams())[3])
        );
    }
    else if ((*(messaggio.returnComando()))=="changecontrollerstate")
    {
      executionError=db.changeControllerState(messaggio.returnParams()[0]);
    }
    //se il comando ricevuto non è nessuno dei precedenti
    else
    {
      requestError==true;
    }
    //invio la risposta
    if (requestError)
    {
      client.println("HTTP/1.1 400 Bad Request");  
    }
    else if (executionError)
    {
      client.println("HTTP/1.1 500 Internal Server Error");  
    }
    else 
    {
      client.println("HTTP/1.1 200 OK");  
    }
    // Viene chiusta la connessione
    client.stop();
    Serial.println("client disconnected");
  }
  db.executeTimingFunctions();
}
    
   