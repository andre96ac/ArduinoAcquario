import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { OsmoPage } from './osmo.page';

describe('OsmoPage', () => {
  let component: OsmoPage;
  let fixture: ComponentFixture<OsmoPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ OsmoPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(OsmoPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
