#include "Plafo.h"

Plafo::Plafo()
{
    fanPin=255;
}

void Plafo::setFanPin(byte pin)
{
    fanPin=pin;
}

void Plafo::esegui()
{
    fanState=SPENTO;
    for (int i=0; i<NMAXCONTROLLERS; i++)
    {
        ligthChannels[i]->esegui();
        if (ligthChannels[i]->getStato()>10)
        {
            fanState=ACCESO;
        }

    }
    digitalWrite(fanPin, fanState);
}

byte Plafo::getFanPin()
{
    return fanPin;
} 

bool Plafo::getFanState()
{
    return fanState;
}
