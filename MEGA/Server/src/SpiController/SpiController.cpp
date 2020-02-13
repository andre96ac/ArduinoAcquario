#include "SpiController.h"

byte _SpiController:: pinE;
byte _SpiController:: pinS;

void _SpiController :: begin(byte pinEthernet, byte pinSd)
{
    pinMode(pinEthernet, OUTPUT);
    pinMode(pinSd, OUTPUT);
    pinMode (CC_MEGA_PIN, OUTPUT);
    switchToEth();
};

void _SpiController::switchToSd()
{
    digitalWrite(pinE, HIGH);
    digitalWrite(pinS, LOW);
    Serial.println(F("sto attivando la sd"));
};

void _SpiController::switchToEth()
{
    digitalWrite(pinS, HIGH);
    digitalWrite(pinE, LOW);
    Serial.println(F("sto attivando l'eth"));

}

_SpiController SpiController;


