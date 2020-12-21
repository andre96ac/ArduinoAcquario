# ArduinoAcquario


ArduinoAcquario è un software completo, modulare, e completamente configurabile, pensato per essere installato su Arduino MEGA,  per la gestione remota del propio acquario.
ArduinoAcquario è completamente personalizzabile: è possibile prototipare la propria soluzione, e successivamente definire a runtime, tramite app, tutti i dispositivi collegati.

Il progetto si compone di due parti: 
La parte "Server" contiene il codice lato server che dovrà essere caricato sulla scheda, e che si occuperà di ricevere i comandi via ethernet, gestire lo stato dei dispositivi di conseguenza, e memorizzare tutte le informazioni di configurazione.
La parte "Client", invece, è costituita da un'applicazione mobile sviluppata in Angular-Ionic-Capacitor in grado di visualizzare lo stato corrente di tutti i dispositivi del sistema, e di permettere, tramite l'invio di comandi via web, la configurazione completa del controller

### Features:
##### -Accensione/spegnimento dispositvi:
E' possibile collegare qualsiasi dispositivo ad una presa di Arduino libera, e, tramite l'applicazione mobile, gestirne l'accensione e lo spegnimento da remoto, sia in modo        manuale, che temporizzato

##### -Controller Pompe di movimento:
E' possibile, tramite l'apposito menù pompe, gestire l'accensione e lo spegnimento temporizzato, continuo o alternato delle pompe di movimento, per adattarne il funzionamento ad ogni necessità (es. simulare il moto ondoso, o le correnti di marea).

##### -Controller temperatura
E' possibile integrare facilmente una sonda di temperatura ed utilizzarla per comandare disposistivi quali, ad esempio un riscaldatore, delle ventole, o un refrigeratore. E' inoltre possibile includere una seconda sonda che funga da cutoff di emergenza, qualora la prima sonda dovesse guastarsi

##### -Controller rabbocco automatico
E' presente un sistema completo di gestione del rabbocco automatico: è possibile collegare fino a due sensori di livello (uno di lavoro, ed uno di emergenza), per monitorare il livello dell'acqua, ed azionare una pompa all'occorrenza

### Funzionalità di sicuezza:

##### -Gestione di eventuale mancanza di connessione ad internet
Tutte la configurazione impostata viene salvata localmente all'interno di una microSd, per questo, un'eventuale mancanza temporanea della connettività internet è del tutto ininfluente: ovviamente non sarà momentaneamente possibile controllare lo stato dei dispositivi tramite l'applicazione, ma la centralina continuerà a funzionare normalmente fino al ripristino della connettività

##### -Gestione di eventuali blackout
Il server è programmato per salvare tutte le impostazioni configurate all'interno di una microSD (lo slot per microSd è normalmente incluso nella EthernetShield, necessaria per il funzionamento del progetto. In caso di blackout, al ripristino dell'alimentazione tutte le impostazioni verranno ricaricate automaticamente, e la centralina riprenderà a funzionare normalmente 

##### -Gestione di eventuali blocchi della centralina
Il software è configurato per attivare il watchdog timer di sicurezza di Arduino: qualora, per impostazioni errate, o per qualunque causa, Arduino dovesse bloccarsi, il watchdog interverrà forzando un reset del sistema per risolvere il blocco. Al riavvio, il sistema cercherà di caricare l'ultima configurazione funzionante; qualora ciò non dovesse essere possibile, la configurazione presente verrà cancellata, ed il sistema sarà resettato.


###### Il progetto è utilizzabile solo per la versione MEGA della scheda, arduino UNO non dispone di sufficeinte memoria, nonchè di sufficienti porte per collegare un numero accettabile di dispositivi; per questo, la versione per Arduino uno (che è possibile trovare nella cartella UNO del progetto), è rimasta incompleta.

