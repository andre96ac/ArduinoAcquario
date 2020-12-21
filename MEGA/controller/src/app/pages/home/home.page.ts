// Copyright 2020 Andrea Cuppini

// This file is part of ArduinoAcquario.
// ArduinoAcquario is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Nome-Programma is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.

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



