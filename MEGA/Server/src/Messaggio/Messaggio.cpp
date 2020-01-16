#include "Messaggio.h"
#include "../Const/Const.h"


    Messaggio::Messaggio(String messaggio){
      nparams=0;
      messaggio.toCharArray(mex, NMAXPARAMS*3);
      Serial.println(F("################ REQUEST ##################"));
      Serial.println(mex);
      Serial.println(F("################ END REQUEST ##################"));
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
    String* Messaggio::returnComando()
    {
      return &comando;
    };

    //la funzione restituisce un  indirizzo a vettore di parametri
    int* Messaggio::returnParams()
    {
      return &param[0];
    };

    int Messaggio::returnNParams()
    {
        return nparams;
    }
