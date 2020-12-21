#ifndef CHANNEL_H
#define CHANNEL_H

#include <RTClib.h>


enum TipoAccensione
{
    AUTOMATICA=0,
    MANUALE=1
};


class Channel
{
    private:
        byte pin;
        TipoAccensione tipoAccensione;
        byte statoAccensione;
        DateTime *accensione;
        DateTime *spegnimento;
        int durataAccensione;
        RTC_DS1307* pClock;


    public:
        Channel(byte presa, RTC_DS1307* orologio);
        void setTipoAccensione(TipoAccensione tipo);
        void changeTipoAccensione();
        void setStatoAccensione(byte stato);
        void setTimer(DateTime* oraAccensione, DateTime* oraSpegnimento);
        bool setDurata(int minuti);

        byte getStato();
        byte getPresa();
        TipoAccensione getTipoAccensione();
        DateTime getAccensione();
        DateTime getSpegnimento();
        int getDurataAccensione();
 
        void esegui();
};


#endif