import { Component, OnInit } from '@angular/core';
import { ConfigModel } from 'src/app/models/config.model';
import { Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';
import { OsmoModel } from 'src/app/models/osmo.model';
import { RunningType } from 'src/app/models/osmo.model'
import { LedModel } from 'src/app/models/led.model';


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

  constructor(private dataService: DataService ) { }

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
      className : String
      if (osmo.stateSwitch1&&osmo.stateSwitch2)
      {
        return RunningType.REFLOW;
      }
      else if (!osmo.stateSwitch1&&osmo.stateSwitch2)
      {
        return RunningType.LEVEL_OK;
      }
      else if (!osmo.stateSwitch1&&!osmo.stateSwitch2)
      {
        console.log ('bp');
        return RunningType.EMERGENCY;
      }
    }
    else
    {
      return;
    }
  }

  onClickRemove(osmo: OsmoModel)
  {
    this.dataService.removeOsmo(osmo.id);
  }

  onClickSwitch(osmo : OsmoModel)
  {
    this.dataService.changeOsmoState(osmo.id);
  }

}
