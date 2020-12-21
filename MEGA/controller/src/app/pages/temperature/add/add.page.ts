
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
import { ModalController, NavParams, PickerController } from '@ionic/angular';
import { TermometroModel, TermometroType } from 'src/app/models/termometro.model';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { ConfigModel } from 'src/app/models/config.model';
import { NgSwitchCase } from '@angular/common';



@Component({
  selector: 'app-add',
  templateUrl: './add.page.html',
  styleUrls: ['./add.page.scss'],
})
export class AddPage implements OnInit {

  newTermometro: TermometroModel=new TermometroModel;
  form: FormGroup;
  loadedConfig: ConfigModel;

  
  constructor(private modalCtrl : ModalController, private navParams : NavParams, private pickerCtrl: PickerController) { }

  ngOnInit() {

    this.newTermometro.type=TermometroType.TERMOMETRO;

    this.loadedConfig= this.navParams.get('data');
    this.form=new FormGroup({
      id: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      type: new FormControl(TermometroType.TERMOMETRO, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      idTerm: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      idRisc: new FormControl(null, {
        updateOn: 'blur',
        validators: []
      }),
      idRefrig: new FormControl(null, {
        updateOn: 'blur',
        validators: []
      }),
      setTemp: new FormControl(null, {
        updateOn: 'blur',
      }),
      deltaTemp: new FormControl(null, {
        updateOn: 'blur',
      })
    })

  }

  onChangingType()
  {
    this.newTermometro.type=this.form.value.type;
    if (this.newTermometro.type==TermometroType.TERMOMETRO)
    {

      this.form.get('idRisc').clearValidators();
      this.form.get('idRefrig').clearValidators();
      this.form.get('setTemp').clearValidators();
      this.form.get('deltaTemp').clearValidators();
    }
    else if(this.newTermometro.type==TermometroType.TERMOSTATO)
    {
      this.form.get('idRisc').setValidators([Validators.required]);
      this.form.get('setTemp').setValidators([Validators.required]);
      this.form.get('idRefrig').clearValidators();
      this.form.get('deltaTemp').clearValidators();
    }

    else 
    {
      this.form.get('idRisc').setValidators([Validators.required]);
      this.form.get('idRefrig').setValidators([Validators.required]);
      this.form.get('setTemp').setValidators([Validators.required]);
      this.form.get('deltaTemp').setValidators([Validators.required]);
    }
    this.form.get('idRisc').updateValueAndValidity();
    this.form.get('idRefrig').updateValueAndValidity();
    this.form.get('setTemp').updateValueAndValidity();
    this.form.get('deltaTemp').updateValueAndValidity();
  }
  close()
  {
    this.modalCtrl.dismiss(null);
  }

  submit()
  {
    if (this.form.valid)
    {  
      this.newTermometro.id=this.form.value.id;
      this.newTermometro.type=this.form.value.type;
      this.newTermometro.pinterm=this.form.value.idTerm;
      this.newTermometro.idrisc=this.form.value.idRisc;
      this.newTermometro.idrefrig=this.form.value.idRefrig;
      this.newTermometro.settemp=this.form.value.setTemp*10;
      this.newTermometro.deltatemp=this.form.value.deltaTemp*10;
      this.modalCtrl.dismiss(this.newTermometro);
    }
  }

  scrivi()
  {
    console.log(this.form.value.setTemp);
  }

  async showTempPicker()
  {
    let pickerIntOptions=[];
    let pickerDecOptions=[];

    for (let i= 5; i<=40; i++)
    {
      pickerIntOptions.push({text:i, value: i})
    }
    for (let i=0; i<10; i++)
    {
      pickerDecOptions.push({text: i, value: i})
    }
    
    
    const picker= await this.pickerCtrl.create({
      buttons:[
        {text: 'Annulla', role: 'cancel'},
        {text: 'Ok', handler: (value)=>{
          this.newTermometro.settemp=value['int']['value']+value['dec']['value']/10;
          this.form.get('setTemp').setValue(this.newTermometro.settemp);
        }}
      ],
      columns:[
        {
          name:'int',
          options:pickerIntOptions
        },
        {
          name:'dec',
          options:pickerDecOptions
        }
      ]

    })

    picker.present();
  }

  async showDeltaPicker()
  {
    let pickerIntOptions=[];
    let pickerDecOptions=[];

    for (let i= 0; i<=5; i++)
    {
      pickerIntOptions.push({text:i, value: i})
    }
    for (let i=0; i<10; i++)
    {
      pickerDecOptions.push({text: i, value: i})
    }
    
    
    const picker= await this.pickerCtrl.create({
      buttons:[
        {text: 'Annulla', role: 'cancel'},
        {text: 'Ok', handler: (value)=>{
          this.newTermometro.deltatemp=value['int']['value']+value['dec']['value']/10;
          this.form.get('deltaTemp').setValue(this.newTermometro.deltatemp);
        }}
      ],
      columns:[
        {
          name:'int',
          options:pickerIntOptions
        },
        {
          name:'dec',
          options:pickerDecOptions
        }
      ],
      animated:true,
      

    })

    picker.present();
  }
}
