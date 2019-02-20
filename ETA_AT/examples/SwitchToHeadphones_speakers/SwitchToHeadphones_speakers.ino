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

  SIM.switchToHeadphones(); //Sets headphones as a default communication device
 // SIM.switchToSpeakers(); //Sets sepakers as a default communication device - Speakers are a factory default
}

void loop() {
  // put your main code here, to run repeatedly:

}
