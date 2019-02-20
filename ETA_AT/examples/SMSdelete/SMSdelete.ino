#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
int x=16; //Index of the message we want to delete
ETA_AT SIM; //Create an ETA_AT object
void setup() {

  Serial.begin(bauds); //Setting baud rate 
  while (!Serial) { //Waiting until the baud rate is set
    ;
  }
  SIM.begin(bauds); //Setting baud rate 
  delay(100);
  SIM.powerOn(); //Turning on the A6 module
  SIM.Test(); //Establishing communication with the module
  
  Serial.println(SIM.SMSdelete(x)); //Returns -1 if it succesfully deleted the msg, or it returns an error number
  //SIM.SMSformat(); //CAUTION - THIS WILL DELETE ALL YOUR SMS MESSAGES
}

void loop() {
  // put your main code here, to run repeatedly:
//SIM.updateSerial();
}
