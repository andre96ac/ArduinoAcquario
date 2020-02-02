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
    
  isSwitchable(controller : ControllerModel)
  {
    let led1: LedModel;
    let led2: LedModel;
    led1=this.loadedConfig.leds.find(element=>{
     return  element.id===controller.idled1? true: false;
      
    });
    led2=this.loadedConfig.leds.find(element=>{
      return element.id===controller.idled2? true: false
    });

    if ((led1.busy||led2.busy)&&(controller.state===false))
    {
      return false;
    }
    else
    {
      return true;
    }
  }
}
