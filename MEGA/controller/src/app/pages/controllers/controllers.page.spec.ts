import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { ControllersPage } from './controllers.page';

describe('ControllersPage', () => {
  let component: ControllersPage;
  let fixture: ComponentFixture<ControllersPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ControllersPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(ControllersPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
