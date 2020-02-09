import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { OsmoPage } from './osmo.page';

const routes: Routes = [
  {
    path: '',
    component: OsmoPage
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
export class OsmoPageRoutingModule {}
