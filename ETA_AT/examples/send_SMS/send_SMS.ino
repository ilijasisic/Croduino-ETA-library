#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
char addr[] = "+xxxxxxxxxxxxxx"; //Your number here
char msg[] = "Hello, this is ETA!"; //YOur message here
ETA_AT SIM; //Create an ETA_AT object
void setup() {

  Serial.begin(bauds); //Setting baud rate 
  while (!Serial) { //Waiting until the baud rate is set
    ;
  }
  SIM.begin(bauds); //Setting baud rate 
  delay(100);
  SIM.powerOn(); //Turning on the A6 module
  SIM.Test(); //Establishing communication with module

SIM.enableTextMode(); //Enable text mode so we can write normally, PDU mode is set by default on startup

SIM.SMSsend(addr, msg); //Sending the message

//SIM.enablePDUMode(); //If you'd like to return it to default PDU mode
}

void loop() {
}
