import { Component, OnInit } from '@angular/core';
import { DataService } from '../../services/data.service'
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { LedModel } from 'src/app/models/led.model';

@Component({
  selector: 'app-home',
  templateUrl: './home.page.html',
  styleUrls: ['./home.page.scss'],
})
export class HomePage implements OnInit {

  loadedConfig:ConfigModel=new ConfigModel;

  configChanged:Subscription;

  constructor(private dataService:DataService) { }

  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(data=>{
      this.loadedConfig=data;
       //console.log(this.loadedConfig);
    })

    this.dataService.getConfig();

  }
 

  onClickSwitch(id:number)
  {
    let response=this.dataService.switch(id);
    console.log(response)
  }

}
