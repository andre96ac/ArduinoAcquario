import { Injectable } from '@angular/core';
import { ConfigModel } from '../models/config.model'
import { LedModel } from '../models/led.model';
import { ControllerModel } from '../models/controller.model';
import { TemporizzatoreModel } from '../models/temporizzatore.model';
import { TermometroModel, TermometroType } from '../models/termometro.model';
import { LocalService } from './local.service'

import { HttpClient } from '@angular/common/http';
import { Subject } from 'rxjs'

@Injectable({
  providedIn: 'root'
})
export class DataService {

  private _config= new ConfigModel;

  public configChanged= new Subject<ConfigModel>();
  public ledsChanged= new Subject<LedModel[]>();

  constructor(private httpClient : HttpClient, private localService : LocalService) { }

  getConfig()
  {
    let request = this.localService.myUrl+'getconfig*'
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
      (this.localService.myUrl+'addled&'+pin+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status);
        this.getConfig();
        
      })
      ;

  }
  switch (pin: number)
  {
    this.httpClient.get<any>(
      (this.localService.myUrl+'switch&'+pin+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
        this.getConfig();
      });

  }
  removeLed (pin : number)
  {
    this.httpClient.get<any>(
      (this.localService.myUrl+'removeled&'+pin+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status);
        this.getConfig();
      });

  }

  addController(item:ControllerModel)
  {
    this.httpClient.get<any>(
      (this.localService.myUrl+'addcontroller&'+item.id+'&'+item.idled1+'&'+item.idled2+'&'+item.deltatime+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status);
        this.getConfig();
      });
  }
  changeControllerState (id: number)
  {
    this.httpClient.get<any>(
      (this.localService.myUrl+'changecontrollerstate'+'&'+id+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
        this.getConfig();
      });

  }
  removeController(id:number)
  {
    this.httpClient.get<any>(
      (this.localService.myUrl+'removecontroller'+'&'+id+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
        this.getConfig();
      });

  }

   addTemporizzatore(item: TemporizzatoreModel){

    this.httpClient.get<any>(
      (this.localService.myUrl+'addtemporizzatore&'+item.id+'&'+item.idled+'&'+item.hacc+'&'+item.minacc+'&'+item.hspegn+'&'+item.minspegn+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status);
        this.getConfig();
      });
  }
  removeTemporizzatore(id:number){
    this.httpClient.get<any>(
      (this.localService.myUrl+'removetemporizzatore'+'&'+id+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
        this.getConfig();
      });


  }
  changeTemporizzatoreState(id: number){
    this.httpClient.get<any>(
      (this.localService.myUrl+'changetemporizzatorestate'+'&'+id+'*'), {
        observe:'response',
        responseType: 'text' as 'json'
      })
      .subscribe(risposta => {
        console.log(risposta.status)
        this.getConfig();
      });


  }

  addTermometro(item: TermometroModel)
  {
    if(item.type==TermometroType.TERMOMETRO)
    {
      this.httpClient.get<any>(
        (this.localService.myUrl+'addtermometro&'+item.id+'&'+item.pinterm+'*'), {
          observe: 'response',
          responseType: 'text' as 'json'
        }
      ).subscribe(response=>{
        console.log (response.status);
        this.getConfig();
      })
    }


    else if(item.type==TermometroType.TERMOSTATO)
    {
      this.httpClient.get<any>(
        (this.localService.myUrl+'addtermometro&'+item.id+'&'+item.pinterm+'&'+item.idrisc+'&'+item.settemp+'*'),{
          observe: 'response',
          responseType: 'text' as 'json'
        }
      ).subscribe(response=>{
        console.log(response.status);
        this.getConfig();
      })
    }



    else if (item.type==TermometroType.CLIMA)
    {
      this.httpClient.get<any>(
        (this.localService.myUrl+'addtermometro&'+item.id+'&'+item.pinterm+'&'+item.idrisc+'&'+item.idrefrig+'&'+item.settemp+'&'+item.deltatemp+'*'),
        {
          observe: 'response',
          responseType: 'text' as 'json'
        }
      ).subscribe(response=>{
        console.log(response.status)
        this.getConfig();
      })
      
    }

  }

  changeTermometroState(id: number)
  {
    this.httpClient.get<any>(
      (this.localService.myUrl+'changetermometrostate'+'&'+id+'*'), {
        observe: 'response',
        responseType: 'text' as 'json'
      }
    ).subscribe(response=>{
      console.log(response.status);
      this.getConfig();
    })
  }

  removeTermometro(id: number){
    this.httpClient.get<any>(
      (this.localService.myUrl+'removetermometro'+'&'+id+'*'),
      {
        observe: 'response',
        responseType: 'text' as 'json'
      }
    ).subscribe(response=>{
      console.log (response.status);
      this.getConfig();
    })
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
    let url = this.localService.myUrl+'addled&'+pin+'*';
    this.myGet(url)
    .subscribe(result => {
      this.error=false;
    } )
  }*/


}

  