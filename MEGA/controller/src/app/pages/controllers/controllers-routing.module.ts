import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { ControllersPage } from './controllers.page';

const routes: Routes = [
  {
    path: '',
    component: ControllersPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class ControllersPageRoutingModule {}
