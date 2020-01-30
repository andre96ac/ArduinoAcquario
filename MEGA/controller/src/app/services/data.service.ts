import { Injectable } from '@angular/core';
import { ConfigModel } from '../models/config.model'
import { LedModel } from '../models/led.model';
import { ControllerModel } from '../models/controller.model';
import { TemporizzatoreModel } from '../models/temporizzatore.model';
import { TermometroModel } from '../models/termometro.model';

import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { Observable, throwError, Subject, config } from 'rxjs'
import { map, catchError, } from 'rxjs/operators';
import { Serializer } from '@angular/compiler';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  /*private _controllers: ControllerModel[]=[];
  private _temporizzatori: TemporizzatoreModel[]=[];
  private _termometri: TermometroModel[]=[];*/

  private _config= new ConfigModel;

  private _myIp: string='2.238.115.27';
  private _myPort: string ='11111';
  private _myUrl: string=('http://'+this._myIp+':'+this._myPort+'/?')

  public configChanged= new Subject<ConfigModel>();
  public ledsChanged= new Subject<LedModel[]>();



  constructor(private httpClient : HttpClient) { }

  getConfig()
  {
    let request = this._myUrl+'getconfig*'
    this.httpClient.get(request)
      .subscribe(data=>{
        //quando arrivano i dati, li inserisco nell'oggetto
        this._config.leds=data['leds'];
        this._config.controllers=data['controllers'];
        this._config.temporizzatori=data['temporizzatori'];
        this._config.termometri=data['termometri'];
        this._config.dpinbusy=data['dpinbusy'];

        //riordino gli elementi
        this._config.leds.sort((a, b)=> a.id-b.id);
        this._config.controllers.sort((a,b)=>a.id-b.id);
        this._config.temporizzatori.sort((a,b)=>a.id-b.id);
        this._config.termometri.sort((a,b)=> a.id-b.id);

        //ed emetto l'evento di configurazione cambiata
        this.configChanged.next(this._config);



      });
     
  }

  addLed (pin : number)
  {
    this.httpClient.get<any>(
      (this._myUrl+'addled&'+pin+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        //console.log(risposta);
        console.log(risposta.status);
        return risposta.status;
      })
      ;

      this.getConfig();
  }

  switch (pin: number)
  {
    this.httpClient.get<any>(
      (this._myUrl+'switch&'+pin+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
      });

      this.getConfig();
  }


  removeLed (pin : number)
  {
    this.httpClient.get<any>(
      (this._myUrl+'removeled&'+pin+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        //console.log(risposta);
        console.log(risposta.status);
        return risposta.status;
      })
      ;

      this.getConfig();
  }

  addController(id: number, idL1: number, idL2: number, ms: number)
  {
    this.httpClient.get<any>(
      (this._myUrl+'addcontroller&'+id+'&'+idL1+'&'+idL2+'&'+ms+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status);
        return risposta.status;
      })
      ;

      this.getConfig();
  }

  changeControllerState (id: number)
  {
    this.httpClient.get<any>(
      (this._myUrl+'changecontrollerstate'+'&'+id+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
      });

      this.getConfig();
  }

  removeController(id:number)
  {
    this.httpClient.get<any>(
      (this._myUrl+'removecontroller'+'&'+id+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
      });

      this.getConfig();
  }



 /* //Gestisce gli errori di risposta
  private handleError(error: HttpErrorResponse) {
    if(error.error instanceof ErrorEvent) {
      // Errore di chiamata
      console.error('Errore chiamata: ' + error.error.message);
      this.error=true;
    }
    else {
      // Errore Server
      console.error('Errore Back End:' + error.status);
      console.error('Message' + error.message);
      this.error=true;
    }

    return throwError('Si sono verificati errori in chiamata');
    
  }

  // Bisogna creare una funzione che ritorna la get solo se non è in errore
  myGet(url) {
    return this.httpClient.get<any>(url, {
      observe: 'response',
      responseType: 'text' as 'json'
    })
    .pipe(
      catchError({
        console.log (error)
      })
    )
  }

  myCall(pin : number) {
    let url = this._myUrl+'addled&'+pin+'*';
    this.myGet(url)
    .subscribe(result => {
      this.error=false;
    } )
  }*/


}

  