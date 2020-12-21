
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

#ifndef MESSAGGIO_H
#define MESSAGGIO_H

#include "../Const/Const.h"

class Messaggio{
  private:
    char mex[NMAXPARAMS*3];
    char *parsedMex;
    String comando; //il comando restituito
    int param[NMAXPARAMS]; //l'array di parametri restituiti
    int nparams;
    char *singleParam;

  public:
    Messaggio(String messaggio);
    //la funzione restituisce un indirizzo alla stringa del comando
    String* returnComando(void);
    //la funzione restituisce un  indirizzo a vettore di parametri
    int* returnParams(void);
    int returnNParams(void);
};

#endif