import { Component, OnInit } from '@angular/core';
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';

@Component({
  selector: 'app-controllers',
  templateUrl: './controllers.page.html',
  styleUrls: ['./controllers.page.scss'],
})
export class ControllersPage implements OnInit {

  loadedConfig : ConfigModel;
  configChanged: Subscription;

  constructor(private dataService:DataService) { }

  ngOnInit() {
    this.configChanged=this.dataService.configChanged.subscribe(data=>{
      this.loadedConfig=data;
    })

    this.dataService.getConfig();
  }

  

}
