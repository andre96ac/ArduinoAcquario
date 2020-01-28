import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { ControllersPageRoutingModule } from './controllers-routing.module';

import { ControllersPage } from './controllers.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    ControllersPageRoutingModule
  ],
  declarations: [ControllersPage]
})
export class ControllersPageModule {}
