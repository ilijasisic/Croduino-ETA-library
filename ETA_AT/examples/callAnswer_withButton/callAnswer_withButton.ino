/*
Answers the incoming call, when pressing a pushbutton attached to pin 7.

  The circuit:
  - pushbutton attached to pin 7 from +5V
  - 10K resistor attached to pin 7 from ground
  
*/

#include <ETA_AT.h>

const int buttonPin = 7;     // the number of the pushbutton pin, note that pins 2 and 3 are used by software serial
unsigned long bauds = 19200; //baud rate

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
ETA_AT SIM;   //create an object


void setup() {
   Serial.begin(bauds);
  while (!Serial) {
    ;
  }
  SIM.begin(bauds);
  delay(100);
  SIM.powerOn();  //power on the a6 module on the board
  SIM.Test();     //performe communication test - without this you can't talk to the module
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT); //set button pin to INPUT
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin); //Read button pin and put the value into buttonState

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // answer the call:
    SIM.callAnswer();
    //SIM.callHangUp(); //If you'd like to hang up 
  } 
}
