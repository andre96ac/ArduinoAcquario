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
import { LedModel } from 'src/app/models/led.model';
import { ModalController, AlertController } from '@ionic/angular';
import { AddPage } from './add/add.page';
import { TermometroModel } from 'src/app/models/termometro.model';

@Component({
  selector: 'app-temperature',
  templateUrl: './temperature.page.html',
  styleUrls: ['./temperature.page.scss'],
})
export class TemperaturePage implements OnInit {

  loadedConfig: ConfigModel=new ConfigModel;
  configChanged: Subscription;
  interval;

  constructor(private dataService:DataService, private modalCtrl: ModalController, private alertCtrl:AlertController) {
   }

  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(newConfig=>{
    this.loadedConfig=newConfig;  
  })
    this.dataService.getConfig();
  }

  findLed(id:number):LedModel
  {
    return this.loadedConfig.leds.find(elem=>{
      return elem.id===id;
    })
  }

  onRemoving(id: number)
  {
    this.alertCtrl.create({
      header: 'Conferma',
      message:'Desideri rimuovere il controller?',
      buttons:[
        {
          text:'Annulla',
          handler: ()=>{}
        },
        {
          text: 'Conferma',
          handler: ()=>{
            this.dataService.removeTermometro(id);
          }
        }
      ]
    }).then(controller=>{
      controller.present();
    })
  }

  onSwitching(id: number)
  {
    this.dataService.changeTermometroState(id);
  }

  async onAdding()
  {
    const modal= await this.modalCtrl.create({
      component: AddPage,
      componentProps: {data:this.loadedConfig}
    })

    modal.onWillDismiss().then(data=>{
      let newTermometro :TermometroModel =data['data'];
      if (newTermometro)
      {
        console.log(newTermometro);
        this.dataService.addTermometro(newTermometro);
      }
    })

    modal.present();
  }

  ionViewDidEnter()
  {
    this.interval=setInterval(()=>{
      if (this.loadedConfig.termometri.length!=0)
      {
        this.dataService.getConfig();
      }
    },2000)
  }

 
  ionViewDidLeave()
  {
    clearInterval(this.interval);
  }
}
