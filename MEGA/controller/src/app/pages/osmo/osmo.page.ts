import { Component, OnInit } from '@angular/core';
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';
import { OsmoModel } from 'src/app/models/osmo.model';
import { RunningType } from 'src/app/models/osmo.model'
import { LedModel } from 'src/app/models/led.model';
import { AlertController, ModalController } from '@ionic/angular';
import { AddPage } from './add/add.page';


@Component({
  selector: 'app-osmo',
  templateUrl: './osmo.page.html',
  styleUrls: ['./osmo.page.scss'],
})
export class OsmoPage implements OnInit {

  //questo mi serve per poter utileizzare l'enum RunningType nell'html
  runningType : typeof RunningType=RunningType;
  loadedConfig: ConfigModel = new ConfigModel;
  configChanged: Subscription;

  constructor(
    private dataService: DataService,
    private alertCtrl:AlertController,
    private modalCtrl:ModalController
     ) { }

  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(newConfig =>{
      this.loadedConfig=newConfig;
    })
    this.dataService.getConfig();
  }

  runningState(osmo:OsmoModel):RunningType
  {
    if(osmo.state)
    {
      if (osmo.stateSwitch1&&osmo.stateSwitch2)
      {
        return RunningType.REFLOW;
      }
      else if (!osmo.stateSwitch1&&osmo.stateSwitch2)
      {
        return RunningType.LEVEL_OK;
      }
      else if (!osmo.stateSwitch2)
      {
        return RunningType.EMERGENCY;
      }
    }
    else if (osmo.emptyError)
    {
      return RunningType.EMPTY;
    }
    else
    {
      return;
    }
  }

  onClickSwitch(osmo : OsmoModel)
  {
    this.dataService.changeOsmoState(osmo.id);
  }


  refresh(event)
  {
    this.dataService.getConfig();
    setTimeout(()=>{
      event.target.complete()
    }, 1000);
  }

  async onDeleteElement(osmo: OsmoModel)
  {
      const alert= await this.alertCtrl.create({
      header:'Conferma',
      message: 'Desideri rimuovere il controller?',
      buttons: [
        {
          text: 'Conferma',
          handler: ()=>{
            this.dataService.removeOsmo(osmo.id);
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

  presentModalAdd()
  {
    this.modalCtrl.create({
      component:AddPage,
      componentProps:{data:this.loadedConfig},
    }).then(modal=>{
      modal.onDidDismiss().then(data=>{
        let newOsmo:OsmoModel=data['data']
        if (newOsmo!=null)
          {this.dataService.addOsmo(newOsmo)}
      });
      modal.present();
      })
  }

}
