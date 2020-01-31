import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { TimersPageRoutingModule } from './timers-routing.module';

import { TimersPage } from './timers.page';
import { AddPage } from './add/add.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    ReactiveFormsModule,
    IonicModule,
    TimersPageRoutingModule    
  ],
  declarations: [TimersPage, AddPage],
  entryComponents: [AddPage]
})
export class TimersPageModule {}
