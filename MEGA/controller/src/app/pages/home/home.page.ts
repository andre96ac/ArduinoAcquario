import { Component, OnInit } from '@angular/core';
import { DataService } from '../../services/data.service'

@Component({
  selector: 'app-home',
  templateUrl: './home.page.html',
  styleUrls: ['./home.page.scss'],
})
export class HomePage implements OnInit {

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
    response=this.dataService.addLed(5);
    console.log(response);
  }

}
