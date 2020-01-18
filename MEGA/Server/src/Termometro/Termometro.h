#ifndef TERMOMETRO_H
#define TERMOMETRO_H

#include "../Led/Led.h"
#include "../Const/Const.h"
#include <OneWire.h>

class Termometro
{
    private:
        int _id;
        bool _state;
        int thermPin;
        Led* pRiscaldatore;
        Led* pRefrigeratore;
        int temperature;
        int type;
        int settedTemperature;
        int delta;
        OneWire ds(thermPin);//#########################################################

    public:
        Termometro(int identificativo, int pinTermometro, Led* riscaldatore, int temperatura);
        Termometro(int identificativo, int pinTermometro, Led* riscaldatore, Led* refrigeratore, int temperatura, int differenziale);
        Termometro(int identificativo, int pinTermometro);
        ~Termometro();
        void state(bool stato);
        bool state(void);
        void changeState();
        void resetTemperature(int temperature);
        int getTemperature();
        int getId();
        int getPinTerm();
        int getType();
        int getSetTemperature();
        int getDelta();
        Led* getRiscaldatore();
        Led* getRefrigeratore();
        void readSensor();
        void esegui();

};


#endif