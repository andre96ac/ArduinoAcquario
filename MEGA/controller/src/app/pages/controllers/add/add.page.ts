import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { ControllerModel } from 'src/app/models/controller.model';
import { ModalController } from '@ionic/angular';

@Component({
  selector: 'app-add',
  templateUrl: './add.page.html',
  styleUrls: ['./add.page.scss'],
})
export class AddPage implements OnInit {

  form: FormGroup;
  newController:ControllerModel;

  constructor(private modalCtrl: ModalController) { }

  ngOnInit() {

    this.newController=new ControllerModel;

    this.form=new FormGroup({
      id: new FormControl(null, {
        updateOn: 'blur',
        validators: [Validators.required]
      }),
      idL1: new FormControl(null,{
        updateOn:'blur',
        validators: [Validators.required]
      }),
      idL2: new FormControl(null, {
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
