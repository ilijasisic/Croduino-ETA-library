#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
ETA_AT SIM; //Create an ETA_AT object

void setup() {

  Serial.begin(bauds); //Setting baud rate 
  while (!Serial) {;} //Waiting until the baud rate is set
  SIM.begin(bauds); //Setting baud rate 
  delay(100);
  
  SIM.powerOn(); //Turning on the A6 module
  SIM.Test(); //Establishing communication with module

  
}

void loop() {

  
SIM.autoAnswerSettings(2,1); //First number means how many rings you want until it answers, the seccond is 1-answer or 2-hang up


}
