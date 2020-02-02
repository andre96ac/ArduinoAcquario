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
