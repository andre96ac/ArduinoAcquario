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
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { ControllerModel } from 'src/app/models/controller.model';
import { ModalController, NavParams } from '@ionic/angular';
import { LedModel } from 'src/app/models/led.model';

@Component({
  selector: 'app-add',
  templateUrl: './add.page.html',
  styleUrls: ['./add.page.scss'],
})
export class AddPage implements OnInit {

  form: FormGroup;
  newController:ControllerModel;
  leds : LedModel[];

  constructor(private modalCtrl: ModalController, private navParams: NavParams) {
    this.leds=navParams.get('data');
   }

  ngOnInit() {

    this.newController=new ControllerModel;

    this.form=new FormGroup({
      id: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      idL1: new FormControl(this.newController.idled1,{
        updateOn:'blur',
        validators: [Validators.required]
      }),
      idL2: new FormControl(this.newController.idled2, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      deltaTime: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      })
  });
  }


  close()
  {
    this.modalCtrl.dismiss(
      {
        data:null
      }
    )
  }


  submit()
  {
    if (!this.form.valid)
    {
      return
    }
    else
    {
      this.newController.id=this.form.value.id;
      this.newController.idled1=this.form.value.idL1;
      this.newController.idled2=this.form.value.idL2;
      this.newController.deltatime=this.form.value.deltaTime;
      this.modalCtrl.dismiss(
          {
            data: this.newController
          })
    }
  }
}
