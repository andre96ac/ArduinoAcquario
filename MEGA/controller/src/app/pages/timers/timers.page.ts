import { Component, OnInit } from '@angular/core';
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';
import { TemporizzatoreModel } from 'src/app/models/temporizzatore.model';
import { ModalController } from '@ionic/angular';
import { AddPage } from './add/add.page';
import { ProviderAst } from '@angular/compiler';
import { Time } from '@angular/common';

@Component({
  selector: 'app-timers',
  templateUrl: './timers.page.html',
  styleUrls: ['./timers.page.scss'],
})
export class TimersPage implements OnInit {

  loadedConfig: ConfigModel = new ConfigModel;
  configChanged: Subscription;

  constructor(private dataService: DataService, private modalCtrl: ModalController) {
  }
  
  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(newConfig =>{
      this.loadedConfig=newConfig
    })
    this.dataService.getConfig();
  }

  onDeleteElement(id:number)
  {
    this.dataService.removeTemporizzatore(id);
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
      this.dataService.addTemporizzatore(newTemporizzatore);
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

}
