import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { ControllersPageRoutingModule } from './controllers-routing.module';

import { ControllersPage } from './controllers.page';
import { AddPage } from './add/add.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    ControllersPageRoutingModule,
    ReactiveFormsModule
  ],
  declarations: [ControllersPage, AddPage],
  entryComponents: [AddPage]
})

export class ControllersPageModule {}
