
#ifndef SPICONTROLLER_H
#define SPICONTROLLER_H

#define CC_MEGA_PIN 5

class _SpiController
{
    private:
         static byte pinS;
         static byte pinE;
    public:
        static void begin (byte pinEthernet, byte pinSd);
        static void switchToSd();
        static void switchToEth();      
};

#endif