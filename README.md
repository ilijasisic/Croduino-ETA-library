# Croduino-ETA-library
This library provides wrapper methods for some AT commands defined in the official A6 manual, some helper methods to work with returned replies, and also methods to directly communicate with the chip. Full library documentation and numerous examples are also provided.

In order to be able to use this library without any complications you'll have to increse the buffer size in SoftwareSerial library.

On a Windows PC, go to C:\Program Files (x86) -> Arduino -> hardware -> Arduino -> avr -> libraries -> SoftwareSerial (-> src for newer version of Arduino IDE) Open SoftwareSerial.h and change the line:
```
// RX buffer size
#define _SS_MAX_RX_BUFF 64  
``` 
into ->
```
// RX buffer size
#define _SS_MAX_RX_BUFF 128 
```
