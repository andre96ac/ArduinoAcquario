export class TermometroModel{
    id: number;
    type:TermometroType;
    stato: boolean;
    pinTerm: number;
    redTemperature: number;
    idRiscal: number;
    idRefrig: number;
    setTemp: number;
    deltaTemp: number;


}



export enum TermometroType{

    TERMOMETRO=0,
    TERMOSTATO=1,
    TEMPORIZZATORE=2

}