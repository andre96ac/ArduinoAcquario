import { ControllerModel } from './controller.model';
import { LedModel } from './led.model';
import { TemporizzatoreModel } from './temporizzatore.model';
import { TermometroModel } from './termometro.model';
import { OsmoModel } from './osmo.model';

export class ConfigModel
{
    systemtime: SystemTime = new SystemTime;
    leds:LedModel[]=[];
    controllers:ControllerModel[]=[];
    temporizzatori:TemporizzatoreModel[]=[];
    termometri:TermometroModel[]=[];  
    osmo : OsmoModel[]=[]
    dpinbusy:boolean[]=[];  
}

class SystemTime
{
    year : number;
    month : number;
    day : number;
    hour : number;
    minute : number;
    second : number;
}