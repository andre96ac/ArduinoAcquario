// Copyright 2020 Andrea Cuppini

// This file is part of ArduinoAcquario.
// ArduinoAcquario is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Nome-Programma is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.

import { Injectable } from '@angular/core';
import { Storage } from '@ionic/storage';

@Injectable({
  providedIn: 'root'
})
export class LocalService {

  private _myIp : string;
  private _myPort: string;
  private _myUrl: string=''

  constructor(private storage: Storage) {  }

  loadFromMemory()
  {
    this.storage.get('ip').then(ip=>
      {this._myIp=ip}
      )
    this.storage.get('port').then(port=>
      {this._myPort=port}
      )
  }

  get myUrl ()
  {
    this._myUrl=('http://'+this._myIp+':'+this._myPort+'/?');
    return this._myUrl;
  }

  set myIp(ip)
  {
    this._myIp=ip;
    this.storage.set('ip', this._myIp);
    
  }

  set myPort(port)
  {
    this._myPort=port;
    this.storage.set('port', this._myPort);
  }

  get myIp()
  {
    return this._myIp;
  }

  get myPort()
  {
    return this._myPort;
  }
}
