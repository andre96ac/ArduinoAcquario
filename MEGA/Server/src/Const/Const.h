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
#define MAX_REFLOW_MILLIS 10000 //il tempo di rabbocco massimo prima del blocco del controller
#define WATCHDOG_ENABLED false //abilitazione del watchdog
#define RESET_COUNT_ADDRESS 1 //l'indirizzo in EEPROM del contatore dei reset
#define N_MAX_RESET 2 //il numero massimo dei riavvii da effettuare prima di resettare la scheda
#define PIN_SD 4 //il pin del lettore sd
#define PIN_ETH 10
#define CONFIG_FILE_NAME "config.txt" //il nume del file di configurazione

//parametri di rete
#define PORT 11111 //porta del server
const byte MAC[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Mac Address di Arduino
const byte IP[] = {192, 168, 1, 3}; //ip di arduino

//dimensione del json di configurazione
const int CONFIGJSONSIZE=(
                            JSON_OBJECT_SIZE(7) //oggetto generale
                            +JSON_OBJECT_SIZE(6) //oggetto contenente data ed ora di sistema
                            +JSON_ARRAY_SIZE(NDIGITALPIN) //array delle prese libere/occupate
                            +4*JSON_ARRAY_SIZE(NMAXCONTROLLERS) //i 4 array che contengono gli oggetti controller
                            +JSON_ARRAY_SIZE(NMAXLED) //l'array che contiene gli oggetti device
                            +NMAXLED*JSON_OBJECT_SIZE(3) //i gli oggetti led
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(5) 
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(7)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(8)
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(8)

                            +JSON_OBJECT_SIZE(3)//l'oggetto "plafoniera"
                            +JSON_ARRAY_SIZE(NMAXCONTROLLERS)//l'array di canali della plafoniera
                            +NMAXCONTROLLERS*JSON_OBJECT_SIZE(8)//i singoli oggetti "canale"
                        );



enum {TERMOMETRO, TERMOSTATO, CLIMA};


#endif
