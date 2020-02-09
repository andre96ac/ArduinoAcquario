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
