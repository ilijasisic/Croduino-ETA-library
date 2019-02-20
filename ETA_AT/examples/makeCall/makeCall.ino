#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
char addr[] = "+xxxxxxxxxxx"; //Your number here
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

  SIM.callMake(addr); //Calls selected number

}

void loop() {
}
