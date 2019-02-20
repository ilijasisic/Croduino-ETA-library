#include <ETA_AT.h>

unsigned long bauds = 19200; //You should use baud rate of 19200
int x=1;  //Index of the message you want to read
String message; //SMSread returns String so we can save it here and use it later
ETA_AT SIM; //Create an ETA_AT object
void setup() {
  Serial.begin(bauds); //Setting baud rate 
  while (!Serial) {;} //Waiting until the baud rate is set
  SIM.begin(bauds); //Setting baud rate 
  delay(100);
  
  SIM.powerOn(); //Turning on the A6 module
  SIM.Test(); //Establishing communication with the module

  SIM.enableTextMode(); //enable text mode so you can read the SMS
  
  message=SIM.SMSread(x); //Read SMS
  
  message=SIM.SMStext(message);            //If you'd like to get the message text into String message
 //message=SIM.SMSnumberOfSender(message); //If you'd like to get the number of sender into String message
  
  Serial.println(message); //Prints the message to serial monitor
  //SIM.enablePDUMode(); //returns to default PDU mode
}

void loop() {
  // put your main code here, to run repeatedly:

}
