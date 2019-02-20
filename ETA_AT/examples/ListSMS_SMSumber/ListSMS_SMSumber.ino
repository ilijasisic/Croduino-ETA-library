#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
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

  SIM.SMSlistAll(); //Lists all messages to serial monitor

 // SIM.SMSlistRead(); //Lists all read messages to serial monitor

 // SIM.SMSlistUnread(); //Lists all unread messages to serial monitor
 
 Serial.println(SIM.SMSnumber()); // SMSnumber() returns an int so we can just print it out to serial
}

void loop() {


}
