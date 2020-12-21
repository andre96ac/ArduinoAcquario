#ifndef PLAFO_H
#define PLAFO_H
#include "./Channel.h"
#include "../Const/Const.h"

class Plafo
{
    private:

    byte fanPin;
    bool fanState;

    public:
    
    Channel* ligthChannels[NMAXCONTROLLERS];
    Plafo();    
    void setFanPin(byte pin);
    byte getFanPin();
    bool getFanState();

    void esegui();
    
};

#endif