import { Component, OnInit } from '@angular/core';
import { ModalController, NavParams } from '@ionic/angular';
import { TemporizzatoreModel } from 'src/app/models/temporizzatore.model';
import { LedModel } from 'src/app/models/led.model';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { Time } from '@angular/common';

@Component({
  selector: 'app-add',
  templateUrl: './add.page.html',
  styleUrls: ['./add.page.scss'],
})
export class AddPage implements OnInit {

  private newTemporizzatore : TemporizzatoreModel=new TemporizzatoreModel;
  leds: LedModel[];
  form: FormGroup;

  constructor(private modalCtrl: ModalController, private navParams: NavParams) {
    this.leds=navParams.get('data');
   }

  ngOnInit() {
    this.form=new FormGroup({
      id: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      idL: new FormControl(null,{
        updateOn:'blur',
        validators: [Validators.required]
      }),
      tAcc: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      tSpegn: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      })
  });
  }

  close()
  {
    this.modalCtrl.dismiss(null);
  }

  submit()
  {
    if (this.form.valid)
    {
      let timeAcc= new Date (this.form.value.tAcc);
      let timeSpegn= new Date(this.form.value.tSpegn);
      this.newTemporizzatore.id=this.form.value.id;
      this.newTemporizzatore.idled=this.form.value.idL;
      this.newTemporizzatore.hacc=timeAcc.getHours();
      this.newTemporizzatore.minacc=timeAcc.getMinutes();
      this.newTemporizzatore.hspegn=timeSpegn.getHours();
      this.newTemporizzatore.minspegn=timeSpegn.getMinutes();
      this.modalCtrl.dismiss(this.newTemporizzatore);

    }
    else
    {
      return;
    }
  }

}
