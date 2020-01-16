import { Component } from '@angular/core';
import { HttpConnectionService } from '../servizi/http-connection.service'
import { stringify } from 'querystring';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  constructor(private httpConnectionService : HttpConnectionService) {};
  btnLed1()
  {
    let risposta;

    this.httpConnectionService.sendCommand('?command=switch&id=1').subscribe( (risposta) =>
    {
      console.log(risposta);
    }
    );
    
  };
  btnLed2()
  {
    let risposta;

    this.httpConnectionService.sendCommand('?command=switch&id=2').subscribe( (risposta) =>
    {
      console.log(risposta);
    }
    );
    
  }
}
