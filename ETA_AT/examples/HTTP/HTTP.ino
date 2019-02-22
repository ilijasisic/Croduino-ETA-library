#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
const char apn[] PROGMEM = {"internet.ht.hr"}; //APN name
const char server[] PROGMEM = {"thingspeak.com"};//Server address you are connecting
const char api[] PROGMEM = {"https://api.thingspeak.com/apps/thinghttp/send_request?api_key=LZQ1MEOQP6XDDW59"};//API link, data you want to GET
const char host[] PROGMEM = {"www.ferit.unios.hr"};// Host address
String message = ""; //SMSread returns String so we can save it here and use it later
ETA_AT SIM; //Create an ETA_AT object

void setup() {
  Serial.begin(bauds); //Setting baud rate
  while (!Serial) {
    ; //Waiting until the baud rate is set
  }
  SIM.begin(bauds); //Setting baud rate
  delay(100);

  SIM.powerOn(); //Turning on the A6 module
  SIM.Test(); //Establishing communication with the module
message=SIM.requestHTTP(apn, server, api, host);
Serial.println("pocetak");
Serial.println(message);
Serial.println("pocetak2");

}

void loop() {
  // put your main code here, to run repeatedly:

}
