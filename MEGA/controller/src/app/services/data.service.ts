import { Injectable } from '@angular/core';
import { LedModel } from '../models/led.model';
import { ControllerModel } from '../models/controller.model';
import { TemporizzatoreModel } from '../models/temporizzatore.model';
import { TermometroModel } from '../models/termometro.model';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs'
import { map } from 'rxjs/operators';
import { Serializer } from '@angular/compiler';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  private _leds : LedModel[]=[];
  private _controllers: ControllerModel[]=[];
  private _temporizzatori: TemporizzatoreModel[]=[];
  private _termometri: TermometroModel[]=[];

  private _myIp: string='2.238.115.27';
  private _myPort: string ='11111';
  private _myUrl: string=('http://'+this._myIp+':'+this._myPort+'/?')

  constructor(private httpClient : HttpClient) { }

  getConfig()
  {
    let request = this._myUrl+'getconfig*'
    this.httpClient.get(request)
      .subscribe(data=>{
        this._controllers=data['controllers'];
        this._leds=data['leds'];
        this._temporizzatori=data['temporizzatori'];
        this._termometri=data['termometri'];
        console.log(this._leds);
        console.log(this._controllers);
        console.log(this._temporizzatori);
        console.log(this._termometri);
      });
  }

  addLed (pin : number)
  {
    this.httpClient.get(
      (this._myUrl+'addled&'+pin+'*')
      ).subscribe(risposta=>{
        console.log(risposta);
        return risposta['status'];
      })
      ;
  }



}

  