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