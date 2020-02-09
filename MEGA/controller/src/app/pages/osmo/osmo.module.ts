import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { OsmoPageRoutingModule } from './osmo-routing.module';

import { OsmoPage } from './osmo.page';
import { RunningType } from 'src/app/models/osmo.model';
import { AddPage } from './add/add.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    ReactiveFormsModule,
    IonicModule,
    OsmoPageRoutingModule
  ],
  declarations: [OsmoPage, AddPage],
  entryComponents: [AddPage]

})
export class OsmoPageModule {}
