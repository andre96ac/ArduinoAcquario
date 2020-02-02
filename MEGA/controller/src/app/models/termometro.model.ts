export class TermometroModel{
    id: number;
    type:TermometroType;
    stato: boolean;
    pinterm: number;
    readtemp: number;
    idrisc: number;
    idrefrig: number;
    settemp: number;
    deltatemp: number;


}



export enum TermometroType{

    TERMOMETRO=0,
    TERMOSTATO=1,
    CLIMA=2

}