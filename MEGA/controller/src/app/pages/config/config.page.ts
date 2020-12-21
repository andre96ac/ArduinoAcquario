import { Component, OnInit } from '@angular/core';
import { LocalService } from 'src/app/services/local.service';
import { Storage } from '@ionic/storage';
import { AlertController } from '@ionic/angular';
import { DataService } from 'src/app/services/data.service';
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-config',
  templateUrl: './config.page.html',
  styleUrls: ['./config.page.scss'],
})
export class ConfigPage implements OnInit {

  loadedConfig:ConfigModel;
  configListener:Subscription;

  loadedIp: string;
  loadedPort: string;
  myHour:Date= new Date;
  interval;




  constructor(private localService: LocalService,
              private dataService: DataService,
              private alertCtrl: AlertController) 
      { 
        
      }

  ngOnInit() {
    this.loadedIp=this.localService.myIp;
    this.loadedPort=this.localService.myPort;

    this.configListener = this.dataService.configChanged.subscribe(data => {
      this.loadedConfig = data;
      this.myHour=new Date( this.loadedConfig.systemtime.year,
                            this.loadedConfig.systemtime.month-1,
                            this.loadedConfig.systemtime.day,
                            this.loadedConfig.systemtime.hour,
                            this.loadedConfig.systemtime.minute,
                            this.loadedConfig.systemtime.second)
      
    });
    this.dataService.getConfig();


  }

  ionViewDidEnter() {
    this.interval = setInterval(() => {
      this.myHour= new Date(this.myHour.getTime()+1000);
    }, 1000);

  }

  onSubmit()
  {
    this.alertCtrl.create({
      header: 'Sei Sicuro?',
      message: 'Settaggi di rete errati non permetteranno la comunicazione con il controller',
      buttons: [
        {
          text: 'Conferma',
          handler: ()=>{
            this.localService.myIp=this.loadedIp;
            this.localService.myPort=this.loadedPort;
            this.dataService.getConfig;
            
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

  ionViewDidLeave()
  {
    clearInterval(this.interval);
  }

  syncHour()
  {
    let newHour:Date=new Date;
    console.log(newHour)
    this.dataService.setClock(newHour);
  }

}
