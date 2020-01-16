import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http'

@Injectable({
  providedIn: 'root'
})
export class HttpConnectionService 
{
  private url : string = "http://192.168.1.137"
  constructor(private httpClient : HttpClient) { };

  sendCommand(command:string)
  {
    return this.httpClient.get(this.url+'/'+command);
    console.log(this.url+'/'+command);
  }


}
