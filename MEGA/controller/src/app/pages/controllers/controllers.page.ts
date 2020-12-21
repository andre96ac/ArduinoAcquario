
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
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';
import { ModalController, AlertController } from '@ionic/angular';
import { ControllerModel } from 'src/app/models/controller.model';
import { AddPage } from './add/add.page';
import { LedModel } from 'src/app/models/led.model';
import { element } from 'protractor';

@Component({
  selector: 'app-controllers',
  templateUrl: './controllers.page.html',
  styleUrls: ['./controllers.page.scss'],
})
export class ControllersPage implements OnInit {

  loadedConfig  = new ConfigModel;
  configChanged: Subscription;
  deviceOn:boolean=false;
  intervalBlinking;

  constructor(private dataService:DataService, private modalCtrl:ModalController, private alertCtrl:AlertController) { }

  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(data=>{
      this.loadedConfig=data;
    })

    this.dataService.getConfig();
  }

  onClickSwitch(id : number)
  {
    this.dataService.changeControllerState(id);
  }


  onRemovingController(id:number)
  {
    this.presentAlertConfirmDelete(id);
  }

  async presentModal(){

    const modal = await this.modalCtrl.create({
      component: AddPage,
      componentProps: {data: this.loadedConfig.leds}
    });

    modal.onWillDismiss()
    .then(data=>{
      let newController:ControllerModel=data['data'];
      newController=newController['data'];
      if (newController)
      {
        this.dataService.addController(newController);
      }
    }
    )
    return await modal.present();
  }

  async presentAlertConfirmDelete(id: number) {
    const alert = await this.alertCtrl.create({
      header: 'Conferma',
      message: 'Desideri rimuovere il controller?',
      buttons: [
        {
          text: 'Annulla',
          handler: () => {

          }
        }, {
          text: 'Conferma',
          handler: () => {
            this.dataService.removeController(id);
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

  ionViewDidEnter()
  {
    this.intervalBlinking=setInterval(()=>{
      this.deviceOn=!this.deviceOn;
    },2000)
  }

  ionViewDidLeave()
  {
    clearInterval(this.intervalBlinking);
  }
}
