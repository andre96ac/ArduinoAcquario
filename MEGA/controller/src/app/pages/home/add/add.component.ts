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
