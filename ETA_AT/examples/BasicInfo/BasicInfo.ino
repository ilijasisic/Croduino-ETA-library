#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
ETA_AT SIM; //Create an ETA_AT object
void setup() {

  Serial.begin(bauds); //Setting baud rate 
  while (!Serial) {;} //Waiting until the baud rate is set
  SIM.begin(bauds); //Setting baud rate 
  delay(100);
  
  SIM.powerOn(); //Turning on the A6 module
  SIM.Test(); //Establishing communication with the module

//Serial.println(SIM.getSignalQuality());  //gets signal value from 0-100 (int)

//Serial.println(SIM.SIMgetID()); //gets SIM ID as a String value

//Serial.println(SIM.availableOperators()); //Gets a list of available operators in range as a String value

Serial.println(SIM.currentOp()); //gets current operator as a String value

}

void loop() {
  // put your main code here, to run repeatedly:

}
