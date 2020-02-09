import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { OsmoPageRoutingModule } from './osmo-routing.module';

import { OsmoPage } from './osmo.page';
import { RunningType } from 'src/app/models/osmo.model';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    OsmoPageRoutingModule
  ],
  declarations: [OsmoPage]
})
export class OsmoPageModule {}
