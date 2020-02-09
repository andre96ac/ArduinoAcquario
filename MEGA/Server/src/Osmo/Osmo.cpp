#include "Osmo.h"

    Osmo::Osmo(int identificativo, Led *led, byte normalSwitch, byte emergencySwitch)
    {
        id=identificativo;
        pL=led;
        pL->isBusy(true);
        switch1Pin=normalSwitch;
        switch2Pin=emergencySwitch;
        switch1State=SPENTO;
        switch2State=SPENTO;
        pinMode(switch1Pin, INPUT);
        pinMode(switch2Pin, INPUT);
        osmoState=SPENTO;
        emptyError=false;
        reflowStartTime=0;
    };

    Osmo::~Osmo()
    {
        pL->isBusy(false);
        setState(SPENTO);
    };

    void Osmo::setState(bool stato)
    {
        if (stato==ACCESO)
        {
            emptyError=false;
            pL->spegni();
            osmoState=ACCESO;    
        }
        else
        {
            pL->spegni();
            osmoState=SPENTO;
        }
        
    };


    void Osmo::changeState()
    {
        if (osmoState==ACCESO)
            setState(SPENTO);
        else
            setState(ACCESO);
    }

    void Osmo::ceckLevel()
    {
        switch1State=digitalRead(switch1Pin);
        switch2State=digitalRead(switch2Pin);
        if (osmoState==ACCESO)
        {
            if((switch1State==ACCESO)&&(switch2State==ACCESO))
            {
                pL->accendi();
                //se sto iniziando ora il reflow, mi annoto il tempo
                if (reflowStartTime==0)
                {
                    reflowStartTime=millis();
                }
                //se ho superato il tempo massimo di reflow, spengo l'osmo ed indico l'errore
                else if (millis()-MAX_REFLOW_MILLIS>=reflowStartTime)
                {
                    reflowStartTime=0;
                    emptyError=true;
                    setState(SPENTO);
                }
            }
            else
            {
                reflowStartTime=0;
                pL->spegni();
            }
        } 
    }

    OsmoConfig* Osmo::getConfig()
    {
        OsmoConfig* config=new OsmoConfig;
        config->id=id;
        config->pL=pL;
        config->switch1Pin=switch1Pin;
        config->switch2Pin=switch2Pin;
        config->osmoState=osmoState;
        config->switch1State=switch1State;
        config->switch2State=switch2State;
        config->emptyError=emptyError;
        return config;
    }



