//This example shows general info about Croduino ETA A6 board

#include <ETA_AT.h>

unsigned long baudrate = 9600; // Set baudrate(9600 recommended)
ETA_AT INFO;

void setup() {

  Serial.begin(baudrate);
  while (!Serial) {
    ;
  }
  INFO.begin(baudrate);
  delay(100);
  INFO.powerOn();      //MUST HAVE!! Enables A6 on ETA board
  INFO.Test(); //MUST HAVE!! Starts commuication with A6_module

  INFO.infoGeneral(); 		//RETURNS MAIN IFO ABOUT A6 MODULe

void loop() {
  // put your main code here, to run repeatedly:

}
