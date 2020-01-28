import { Component, OnInit } from '@angular/core';
import { NavParams, ModalController } from '@ionic/angular';

@Component({
  selector: 'app-add',
  templateUrl: './add.component.html',
  styleUrls: ['./add.component.scss'],
})
export class AddComponent implements OnInit {

  dpinBusy:boolean[];

  constructor(private navParams: NavParams, private modalCtrl: ModalController) { }

  ngOnInit() {
    this.dpinBusy=this.navParams.get('data');
  }

  confirm(selection)
  {
    this.modalCtrl.dismiss(
      {
        data:selection
      }
    )

  }

  close()
  {
    this.modalCtrl.dismiss(
      {
        data:this.dpinBusy.length+1
      }
    )
  }



}
