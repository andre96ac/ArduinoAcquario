import { ControllerModel } from './controller.model';
import { LedModel } from './led.model';
import { TemporizzatoreModel } from './temporizzatore.model';
import { TermometroModel } from './termometro.model';

export class ConfigModel
{
    leds:LedModel[]=[];
    controllers:ControllerModel[]=[];
    temporizzatori:TemporizzatoreModel[]=[];
    termometri:TermometroModel[]=[];  
    dpinbusy:boolean[]=[];  
}