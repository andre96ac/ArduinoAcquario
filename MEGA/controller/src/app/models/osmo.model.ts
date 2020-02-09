export class OsmoModel
{
    id : number;
    idled: number;
    idSwitch1: number;
    idSwitch2: number;
    stateSwitch1: boolean;
    stateSwitch2: boolean;
    state: boolean;

};

export enum RunningType{
    EMERGENCY = 0,
    LEVEL_OK = 10,
    REFLOW = 20,
    EMPTY = 30
}