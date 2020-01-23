import { Injectable } from '@angular/core';
import { LedModel } from '../models/led.model';
import { ControllerModel } from '../models/controller.model';
import { TemporizzatoreModel } from '../models/temporizzatore.model';
import { TermometroModel } from '../models/termometro.model';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { Observable, throwError } from 'rxjs'
import { map, catchError, } from 'rxjs/operators';
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

  public error=false;

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
    this.httpClient.get<any>(
      (this._myUrl+'addled&'+pin+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      }).catch()
      .subscribe(risposta => {
        //console.log(risposta);
        console.log(risposta.status);
        return risposta.status;
      })
      ;
  }

  //Gestisce gli errori di risposta
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
  }


}

  