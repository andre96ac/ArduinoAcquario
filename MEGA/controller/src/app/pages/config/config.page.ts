import { Component, OnInit } from '@angular/core';
import { LocalService } from 'src/app/services/local.service';
import { Storage } from '@ionic/storage';
import { AlertController } from '@ionic/angular';

@Component({
  selector: 'app-config',
  templateUrl: './config.page.html',
  styleUrls: ['./config.page.scss'],
})
export class ConfigPage implements OnInit {

  loadedIp: string;
  loadedPort: string;


  constructor(private localService: LocalService, private storage: Storage, private alertCtrl: AlertController) { }

  ngOnInit() {
    this.loadedIp=this.localService.myIp;
    this.loadedPort=this.localService.myPort;
  }

  onSubmit()
  {
    this.alertCtrl.create({
      header: 'Sei Sicuro?',
      message: 'Settaggi errati non permetteranno la comunicazione con il controller',
      buttons: [
        {
          text: 'Conferma',
          handler: ()=>{
            this.localService.myIp=this.loadedIp;
            this.localService.myPort=this.loadedPort;
          }
        },
        {
          text: 'Annulla',
          handler: ()=>{}
        }
      ]
    }).then(alert=>{
      alert.present();
    })
  }

}
