//This example shows how to make HTTP request
//HTTP methods you can use are (GET, HEAD, POST, PUT, DELETE, TRACE, OPTIONS, CONNECT, PATCH)
//In this example we will use GET metod
#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
const char apn[] PROGMEM = {"internet.ht.hr"}; //APN name
const char server[] PROGMEM = {"thingspeak.com"};//Server address you are connecting
const char api[] PROGMEM = {"https://api.thingspeak.com/apps/thinghttp/send_request?api_key=LZQ1MEOQP6XDDW59"};//API link, data you want to GET
const char host[] PROGMEM = {"www.ferit.unios.hr"};// Host address
String message = ""; //Returns String with HTTP info so we can save it here and use it later
String data; //Data you want to read from HTTP message

ETA_AT SIM; //Create an ETA_AT object

void setup() {
  Serial.begin(bauds); //Setting baud rate
  while (!Serial)
  {
    ; //Waiting until the baud rate is set
  }
  SIM.begin(bauds); //Setting baud rate
  delay(100);

  SIM.powerOn();  //MUST HAVE!!Turning on the A6 module
  SIM.Test();     //MUST HAVE!! Starts commuication with A6_module(OK: +CIEV: READY)
  message = SIM.requestHTTP(apn, server, api, host);//Returns String with HTTP information
  Serial.println(message);//Print HTTP request
 
  //Example how you can get data from HTTP request
  delay(4000);
  data = message.substring(0, message.indexOf(13));//Saving data from beginig of message until first <CR>
  Serial.println(data);//Print data you saved

}

void loop() {
  // put your main code here, to run repeatedly:

}
