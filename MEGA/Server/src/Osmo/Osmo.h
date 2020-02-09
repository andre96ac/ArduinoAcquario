#ifndef OSMO_H
#define OSMO_H

#include "../Const/Const.h"
#include "../Led/Led.h"

class OsmoConfig
{
    public:
        int id;
        Led *pL;
        byte switch1Pin, switch2Pin;
        bool osmoState, switch1State, switch2State, emptyError;
};

class Osmo
{
    private:
        int id;
        Led *pL;
        byte switch1Pin, switch2Pin;
        bool osmoState, switch1State, switch2State, emptyError;
        long int reflowStartTime;
        OsmoConfig* config;
    public: 
        Osmo(int identificativo, Led *led, byte normalSwitch, byte emergencySwitch);

        ~Osmo();
        
        void setState(bool stato);

        void changeState();
        
        void ceckLevel();


        Led* returnLed();

        OsmoConfig* getConfig();
       
};


#endif