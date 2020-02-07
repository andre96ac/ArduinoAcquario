#ifndef CONST_H
#define CONST_H

#include <arduino.h>


//parametri generali
#define ACCESO 1
#define SPENTO 0
#define NMAXPARAMS 30
#define NMAXLED 10
#define NDIGITALPIN 33
#define NANALOGPIN 6
#define NMAXCONTROLLERS 5
#define WATCHDOG_ENABLED false

//parametri di rete
#define PORT 11111 //porta del server
const byte MAC[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Mac Address di Arduino
const byte IP[] = {192, 168, 1, 3}; //ip di arduino

//dimensione del json di configurazione
const int CONFIGJSONSIZE=(
                            JSON_OBJECT_SIZE(6)
                            +JSON_ARRAY_SIZE(NDIGITALPIN)
                            +4*JSON_ARRAY_SIZE(NMAXCONTROLLERS)
                            +JSON_ARRAY_SIZE(NMAXLED)
                            +NMAXLED*JSON_OBJECT_SIZE(3)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(5)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(7)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(8)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(7)
                        );



enum {TERMOMETRO, TERMOSTATO, CLIMA};


#endif
