import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { TimersPage } from './timers.page';

const routes: Routes = [
  {
    path: '',
    component: TimersPage
  },
  {
    path: 'add',
    loadChildren: () => import('./add/add.module').then( m => m.AddPageModule)
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class TimersPageRoutingModule {}
