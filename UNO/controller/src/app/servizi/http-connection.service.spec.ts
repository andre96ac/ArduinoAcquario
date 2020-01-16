import { TestBed } from '@angular/core/testing';

import { HttpConnectionService } from './http-connection.service';

describe('HttpConnectionService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: HttpConnectionService = TestBed.get(HttpConnectionService);
    expect(service).toBeTruthy();
  });
});
