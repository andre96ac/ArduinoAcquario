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
import { ModalController, NavParams } from '@ionic/angular';
import { OsmoModel } from 'src/app/models/osmo.model';
import { ConfigModel } from 'src/app/models/config.model';
import { FormGroup, FormControl, Validators } from '@angular/forms';

@Component({
  selector: 'app-add',
  templateUrl: './add.page.html',
  styleUrls: ['./add.page.scss'],
})
export class AddPage implements OnInit {

  form: FormGroup;
  loadedConfig:ConfigModel;
  newOsmo: OsmoModel=new OsmoModel;

  constructor(private modalCtrl:ModalController, private navParams:NavParams) { }

  ngOnInit() {
    this.loadedConfig=this.navParams.get('data');
    console.log(this.loadedConfig);
    this.form=new FormGroup(
      {
        id: new FormControl(null, {
          updateOn: 'blur',
          validators: [Validators.required]
        }),
        idSwitch1: new FormControl(null,{
          updateOn:'blur',
          validators: [Validators.required]
        }),
        idSwitch2: new FormControl(null, {
          updateOn: 'blur',
          validators: [Validators.required]
        }),
        idDevice: new FormControl(null, {
          updateOn: 'blur',
          validators: [Validators.required]
        })
    }
    )
    
  }

  close()
  {
    this.modalCtrl.dismiss(null)
  }

  submit()
  {
    if(this.form.valid)
    {
      this.newOsmo.id=this.form.value.id;
      this.newOsmo.idled=this.form.value.idDevice;
      this.newOsmo.idSwitch1=this.form.value.idSwitch1;
      this.newOsmo.idSwitch2=this.form.value.idSwitch2;
      this.modalCtrl.dismiss(this.newOsmo);
    }
  }



}
