import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { TemperaturePageRoutingModule } from './temperature-routing.module';

import { TemperaturePage } from './temperature.page';
import { AddPage } from './add/add.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    ReactiveFormsModule,
    IonicModule,
    TemperaturePageRoutingModule
  ],
  declarations: [TemperaturePage, AddPage],
  entryComponents: [AddPage]
})
export class TemperaturePageModule {}
