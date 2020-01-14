
class osmo
{
    private:
        Led *pL;
        byte switch1Pin, switch2Pin;
        
        bool osmoState, switch1State, switch2state;
    public: 
        osmo(Led *led, byte normalSwitch, byte emergencySwitch)
        {
            pL=led;
            switch1Pin=normalSwitch;
            switch2Pin=emergencySwitch;
            switch1State=SPENTO;
            switch2state=SPENTO;
            pinMode(switch1Pin, INPUT);
            pinMode(switch2Pin, INPUT);
            osmoState=SPENTO;
        };

        ~osmo()
        {
            setState(SPENTO);
        }

        setState(bool stato)
        {
            if (stato==ACCESO)
            {
                pL->spegni();
                pL->isBusy(true);
                osmoState=ACCESO;
            }
            else
            {
                pL->spegni();
                pL->isBusy(false);
                osmoState=SPENTO;
            }
            
        };
        

        changeState()
        {
            if (osmoState==ACCESO)
                setState(SPENTO);
            else
                setState(ACCESO);
        }
        
        ceckLevel()
        {
            switch1State=digitalRead(switch1Pin);
            switch2state=digitalRead(switch2Pin);
            if((switch1State==ACCESO)&&(switch2state==ACCESO))
                pL->accendi()
            else
                pL->spegni();
        }
}

