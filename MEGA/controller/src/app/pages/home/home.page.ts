import { Component, OnInit } from '@angular/core';
import { DataService } from '../../services/data.service'

@Component({
  selector: 'app-home',
  templateUrl: './home.page.html',
  styleUrls: ['./home.page.scss'],
})
export class HomePage implements OnInit {

  acceso=true;

  constructor(private dataService:DataService) { }

  ngOnInit() {
  }

  getconfig()
  {
    this.dataService.getConfig();
  }
  addLed()
  {
    let response: string;
    //this.dataService.addLed(5);
    this.dataService.addLed(5);
    console.log(this.dataService.error)
  }

  onChangestate()
  {
    this.acceso? this.acceso=false:this.acceso=true;
  }

}
