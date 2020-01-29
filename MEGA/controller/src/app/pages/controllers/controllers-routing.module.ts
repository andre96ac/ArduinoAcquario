import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { ControllersPage } from './controllers.page';

const routes: Routes = [
    {
      path: '',
      component: ControllersPage
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
export class ControllersPageRoutingModule {}
