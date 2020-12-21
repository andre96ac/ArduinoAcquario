
// Copyright 2020 Andrea Cuppini

// This file is part of ArduinoAcquario.
// ArduinoAcquario is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Nome-Programma is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.

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
