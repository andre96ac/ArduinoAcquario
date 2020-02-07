
#include <RTClib.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>

#include "./Const/Const.h"
#include "./CommonFunc/CommonFunc.cpp"

#include "./Led/Led.cpp"
#include "./Messaggio/Messaggio.cpp"
#include "./LedController/LedController.cpp"
#include "./Temporizzatore/Temporizzatore.cpp"
#include "./Database/Database.cpp"
#include "./Termometro/Termometro.cpp"
#include "./Osmo/Osmo.cpp"


//creo l'orologio
RTC_DS1307 orologio;

 
// Viene inizializzata la libreria Ethernet di Arduino e il webserver gira sulla porta 80
EthernetServer server(PORT);

Database db(&orologio);

void setup() 
{
  //se l'ho impostato, attiva il watchdog
  if (WATCHDOG_ENABLED)
    wdt_enable(WDTO_8S);
  //

  //effettue le inizializzazioni
  Serial.begin(9600);
  Wire.begin();
  orologio.begin();
  Ethernet.begin(MAC, IP);
  server.begin();

  //avvisami se l'orologio non sta funzionando
  if (! orologio.isrunning()) 
  {
    Serial.println(F("RTC is NOT running!"));
  }


  //setto l'orologio all'ora di compilazione
  //orologio.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // Serial.print("Clock set at: ");
  // Serial.print(orologio.now().hour());
  // Serial.print(":");
  // Serial.print(orologio.now().minute());
  // Serial.print(":");
  // Serial.println(orologio.now().minute());
  Serial.print(F("Server is at "));
  Serial.println(Ethernet.localIP());
  Serial.print(F("Free RAM at start: "));
  Serial.println(freeRam());
}
 
void loop() 
{

  char c;
  String request; 
  int nParams;
  int* params;
  String* command;
  bool executionError, requestError, requestedConfig=false;
  // Vengono ascoltati nuovi client
  EthernetClient client = server.available();
  if (client) 
  {
    Serial.println(F("new client"));
    // Finisce una richiesta HTTP
    boolean currentLineIsBlank = true;
    request ="";
    executionError=false;
    requestError=false;
    //mentre il client è connesso, scarica la richiesta
    while (client.connected()) 
    {
      if (client.available()) 
      {
        c = client.read();
        if(request.length()<NMAXPARAMS*3){
          request +=c;
        }
        // Se viene completato l'invio della richiesta HTTP, allora passo al blocco successivo
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
    Serial.println(*messaggio.returnComando());

    //esecuzione pratica dell'azione richiesta 
    if ((*(messaggio.returnComando()))=="switch")
      executionError=db.cambiaStatoLed((messaggio.returnParams())[0]);
    //
    else if ((*(messaggio.returnComando()))=="addled")
      executionError=db.addLed(
        (messaggio.returnParams())[0],
        (messaggio.returnParams())[1]
        );
    //
    else if ((*(messaggio.returnComando()))=="removeled")
      executionError=db.removeLed((messaggio.returnParams())[0]);
    //
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
      executionError = db.changeControllerState(messaggio.returnParams()[0]);
    } 
    else if ((*(messaggio.returnComando()))=="removecontroller")
      executionError=db.deletController(messaggio.returnParams()[0]);
    //
    else if ((*(messaggio.returnComando()))=="addtemporizzatore")
    {
        db.addTemporizzatore(//manca gestione errori
        ((messaggio.returnParams())[0]),
        ((messaggio.returnParams())[1]),
        ((messaggio.returnParams())[2]),
        ((messaggio.returnParams())[3]),
        ((messaggio.returnParams())[4]),
        ((messaggio.returnParams())[5])
      );
    }
    else if ((*(messaggio.returnComando()))=="changetemporizzatorestate")
      executionError = db.changeStateTemporizzatore(messaggio.returnParams()[0]);
    //
    else if (*(messaggio.returnComando())=="resettemporizzatore")
    {
      executionError=db.resetTemporizzatore(//manca gestione errori
        ((messaggio.returnParams())[0]),
        ((messaggio.returnParams())[1]),
        ((messaggio.returnParams())[2]),
        ((messaggio.returnParams())[3]),
        ((messaggio.returnParams())[4])
      );
    }
    else if (*(messaggio.returnComando())=="removetemporizzatore")
    {
      executionError=db.deleteTemporizzatore(//manca gestione errori
        ((messaggio.returnParams())[0])
      );
    }
    else if (*(messaggio.returnComando())=="addtermometro")
    {
      if (messaggio.returnNParams()==2)
      {
        executionError=db.addTermometro(
          ((messaggio.returnParams())[0]),
          ((messaggio.returnParams())[1])
        );
      }
      else if(messaggio.returnNParams()==4)
      {
        executionError=db.addTermometro(
          ((messaggio.returnParams())[0]),
          ((messaggio.returnParams())[1]),
          ((messaggio.returnParams())[2]),
          ((messaggio.returnParams())[3])
        );
      }
      else if(messaggio.returnNParams()==6)
      {
        executionError=db.addTermometro(
          ((messaggio.returnParams())[0]),
          ((messaggio.returnParams())[1]),
          ((messaggio.returnParams())[2]),
          ((messaggio.returnParams())[3]),
          ((messaggio.returnParams())[4]),
          ((messaggio.returnParams())[5])
        );
      }
    }
    else if (*(messaggio.returnComando())=="changetermometrostate")
    {
      executionError= db.changeTermometroState(
        (messaggio.returnParams()[0])
      );
    }
    else if (*(messaggio.returnComando())=="removetermometro")
      executionError=db.deleteTermometro(      messaggio.returnParams()[0]    );
    //
    else if (*(messaggio.returnComando())=="addosmo")
    {
      executionError=db.addOsmo(
        ((messaggio.returnParams())[0]),
        ((messaggio.returnParams())[1]),
        ((messaggio.returnParams())[2]),
        ((messaggio.returnParams())[3])
      );
    }
    else if (*(messaggio.returnComando())=="changeosmostate")
    {
      executionError= db.changeOsmoState(
        (messaggio.returnParams()[0])
      );
    }
    else if (*(messaggio.returnComando())=="removeosmo")
    {
      executionError= db.deleteOsmo(
        (messaggio.returnParams()[0])
      );
    }
    else if (*(messaggio.returnComando())=="setclock")
    {
      db.setClock(
          ((messaggio.returnParams())[0]),
          ((messaggio.returnParams())[1]),
          ((messaggio.returnParams())[2]),
          ((messaggio.returnParams())[3]),
          ((messaggio.returnParams())[4])
      );
    }
    else if(*(messaggio.returnComando())=="getconfig")
    {
      requestedConfig=true;
    }
    //se il comando ricevuto non è nessuno dei precedenti
    else
    {
      requestError=true;
    }
    //invio la risposta
    if (requestError)//errore nella formulazione della richiesta
    {
      client.println(F("HTTP/1.1 400 Bad Request"));
      client.println(F("Content-Type: text/html"));
      //client.println(F("Access-Control-Allow-Origin: http://localhost:8100"));
      client.println(F("Access-Control-Allow-Origin: *"));
      client.println();
      client.println(F("Parametri richiesta errati"));
    }
    else if (executionError)//errore nell'esecuzione della richiesta
    {
      client.println(F("HTTP/1.1 500 Internal Server Error"));
      client.println(F("Content-Type: text/html"));
      // client.println(F("Access-Control-Allow-Origin: http://localhost:8100"));
      client.println(F("Access-Control-Allow-Origin: *"));
      client.println();
      client.println(F("Errore interno, impossibile portare a termine l'operazione"));      
    }
    else //altrimenti, se è tutto ok
    {
      //se è stata richiesta la configurazione
      if (requestedConfig)
      {
        //mando risposta OK
        client.println(F("HTTP/1.1 200 OK"));
        client.println(F("Content-Type: application/json"));
        // client.println(F("Access-Control-Allow-Origin: http://localhost:8100"));
        client.println(F("Access-Control-Allow-Origin: *"));
        client.println(); 
        //mando il json
        db.sendConfiguration(&client);
        requestedConfig=false;
      }
      else //altrimenti
      {
        //mando solo risposta OK
        client.println(F("HTTP/1.1 200 OK"));
        client.println(F("Content-Type: text/html"));
        client.println(F("Access-Control-Allow-Origin: *"));
        client.println(); 
        client.println(F("Operazione eseguita"));
      }
    }
    // Viene chiusta la connessione
    client.stop();
    Serial.println(F("client disconnected"));
  }
  db.executeTimingFunctions();
  wdt_reset();
}