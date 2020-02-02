import { Component, OnInit } from '@angular/core';
import { DataService } from '../../services/data.service'
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { LedModel } from 'src/app/models/led.model';
import { MenuController, ModalController, AlertController } from '@ionic/angular';
import { AddComponent } from './add/add.component'


@Component({
  selector: 'app-home',
  templateUrl: './home.page.html',
  styleUrls: ['./home.page.scss'],
})
export class HomePage implements OnInit {

  loadedConfig:ConfigModel=new ConfigModel;

  configChanged:Subscription;

  



  constructor(private dataService:DataService, 
              private menuController:MenuController, 
              private modalCtrl:ModalController,
              private alertCtrl: AlertController) 
              
              { }

  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(data=>{
      this.loadedConfig=data;
       //console.log(this.loadedConfig);
    })

    this.dataService.getConfig();
   
  }
 

  onClickSwitch(id:number)
  {
    this.dataService.switch(id);
  }

  

  async presentModal(){

      const modal = await this.modalCtrl.create({
        component: AddComponent,
        componentProps: {data:this.loadedConfig.dpinbusy}
      });

      modal.onWillDismiss()
      .then(data=>{
        let scelta:number=data['data'];
        if(scelta['data']<=this.loadedConfig.dpinbusy.length)
        {
          this.dataService.addLed(scelta['data']);
        }
      })
      return await modal.present();
  }

  onDeletingLed(id:number)
  {
    this.presentAlertConfirmDelete(id);

  }


  async presentAlertConfirmDelete(id) {
    const alert = await this.alertCtrl.create({
      header: 'Conferma',
      message: 'Desideri rimuovere il dispositivo?',
      buttons: [
        {
          text: 'Annulla',
          handler: () => {

          }
        }, {
          text: 'Conferma',
          handler: () => {
            this.dataService.removeLed(id);
          }
        }
      ]
    });

    await alert.present();
  }

  refresh(event)
  {
    this.dataService.getConfig();
    setTimeout(()=>{
      event.target.complete()
    }, 1000);
  }
}



