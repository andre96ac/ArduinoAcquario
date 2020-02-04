import { Component, OnInit } from '@angular/core';
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';
import { TemporizzatoreModel } from 'src/app/models/temporizzatore.model';
import { ModalController, AlertController } from '@ionic/angular';
import { AddPage } from './add/add.page';
import { ProviderAst } from '@angular/compiler';
import { Time } from '@angular/common';
import { LedModel } from 'src/app/models/led.model';

@Component({
  selector: 'app-timers',
  templateUrl: './timers.page.html',
  styleUrls: ['./timers.page.scss'],
})
export class TimersPage implements OnInit {

  loadedConfig: ConfigModel = new ConfigModel;
  configChanged: Subscription;

  constructor(private dataService: DataService, private modalCtrl: ModalController, private alertCtrl: AlertController) {
  }
  
  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(newConfig =>{
      this.loadedConfig=newConfig
    })
    this.dataService.getConfig();
  }

  async onDeleteElement(id:number)
  {
      const alert= await this.alertCtrl.create({
      header:'Conferma',
      message: 'Desideri rimuovere il controller?',
      buttons: [
        {
          text: 'Conferma',
          handler: ()=>{
            this.dataService.removeTemporizzatore(id);
          }
        },
        {
          text: 'Annulla',
          handler:()=>{}
        }
      ]
    });

    alert.present();
  }

  onSwitch(id: number)
  {
    this.dataService.changeTemporizzatoreState(id);
  }

  async presentModal()
  {
    const modal= await this.modalCtrl.create({
      component: AddPage,
      componentProps:  {'data': this.loadedConfig.leds}
    })

    modal.onWillDismiss().then(data => {
      let newTemporizzatore : TemporizzatoreModel=data['data'];      
      if (newTemporizzatore)
      {
        this.dataService.addTemporizzatore(newTemporizzatore);

      }
    })

    modal.present();
  }

  isSwitchable(temporizzatore: TemporizzatoreModel)
  {
    let led=this.loadedConfig.leds.find(led=>{
      return led.id===temporizzatore.idled
    })
    return !((led.busy)&&(temporizzatore.state==false))
  }
  refresh(event)
  {
    this.dataService.getConfig();
    setTimeout(()=>{
      event.target.complete()
    }, 1000);
  }

  findLed(id: number): LedModel
  {
    return this.loadedConfig.leds.find(elem=>{
      return elem.id==id;
    });
  }
}
