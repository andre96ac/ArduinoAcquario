

/*
Questo programma mostra come sia possibile inserire del codice HTML all'interno della
pagina web del webserver di Arduino*/
 
#include <SPI.h>
#include <Ethernet.h>
#define ACCESO 1
#define SPENTO 0
#define NMAXPARAMS 10
#define NMAXCONTROLLERS 5
 
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
    Led *pL1, *pL2;
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
    void setLeds(Led* ptrLed1, Led* ptrLed2)
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
        pL1->accendi();
        pL2->spegni();
      }
      else
      {
        pL1->spegni();
        pL2->spegni();
      }
      
    };
    
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
};

class Database
{
  private: 
    static const int NMAXLED=10;
    static const int NDIGITALPIN=14;
    static const int NANALOGPIN=6;
    int nControllers;
    //static const int NMAXCONTROLLERS=5;
    Led *leds[NMAXLED];
    LedController *controllers[NMAXCONTROLLERS];
    bool dPinsBusy[NDIGITALPIN]={1,1,0,0,0,0,0,0,0,0,1,1,1,1};

  public:
    Database ()
    {
      nControllers=0;
    };

    void AddLed (int pin)
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
      //cerca se c'è effettivamente un led con quel pin assegnato e lo rimuove
      for (int i=0; i<NMAXLED; i++)
      {
        if (leds[i]->returnPin()==pin)
        {
          delete leds[i];
          dPinsBusy[pin]=false;
        }
      }

    }

};



Led led1(3), led2(5), led3(7);
LedController *controllers[NMAXCONTROLLERS];
int ncontroller=0;

void setup() {
  Serial.begin(9600);
  // Viene inilizzato il webserver e la connessione di rete
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

}
 
void loop() {
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
          client.println("HTTP/1.1 200 OK");         
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
    delay(1);
    // Viene chiusta la connessione
    client.stop();
    Serial.println("client disconnected");
  }
  
  //esecuzione pratica delle azioni 
  Messaggio messaggio(request);
    if (*(messaggio.returnComando())=="switch")
    {
      switch ((messaggio.returnParams())[0])
      {
        case 1:
          led1.cambiaStato();
          Serial.println("ho cambiato stato al led 1");
          break;
        case 2:
          led2.cambiaStato();
          Serial.println("ho cambiato stato al led 2");
          break;
        case 3:
          led3.cambiaStato();
          Serial.println("ho cambiato stato al led 3");
          break;
      }
    }
    //se il comando è newcontroller
    else if (*(messaggio.returnComando())=="newcontroller")
    {
      //creo il nuovo controller(ora gli assegno di default i due led) e setto il tempo sulla base del primo parametro
      controllers[ncontroller]=new LedController(ncontroller);
      controllers[ncontroller]->setLeds(&led1,&led2);
      controllers[ncontroller]->setTime(messaggio.returnParams()[0]);
      Serial.println(messaggio.returnParams()[0]);
      Serial.println("ho creato un nuovo controller");
      Serial.println(controllers[ncontroller]->returnTime());
      ncontroller++;
    }
    //se il comando è SetcontrollerOn
    else if (*(messaggio.returnComando())=="setcontrolleron")
    {
      //setto come "ACCESO" il controller che si trova nella posizione indicata dal primo parametro ricevuto
      controllers[((messaggio.returnParams())[0])]->setState(ACCESO);
      Serial.println("ho settato il controller ");
      Serial.println(((messaggio.returnParams())[0]));
    }
    //se il comando è SetcontrollerOn
    else if (*(messaggio.returnComando())=="setcontrolleroff")
    {
      //setto come "SPENTO" il controller che si trova nella posizione del primo parametro ricevuto
      controllers[((messaggio.returnParams())[0])]->setState(SPENTO);
    }
  for (int i=0; i<NMAXCONTROLLERS; i++)
  {
    if (controllers[i]!=NULL)
    {
      controllers[i]->lampeggia();
    }
  }
}