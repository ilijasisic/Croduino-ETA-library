#ifndef ETA_A6_h
#define ETA_A6_h

#define DEF_RX_PIN 2
#define DEF_TX_PIN 3


#include "Arduino.h"
//#include <ETA_A6.h>
#include <SoftwareSerial.h>

class ETA_A6
{
  public:
    ETA_A6();
    void powerOn();
    void powerOff();
    void connectCheck();
    void networkRegister();
    void infoGeneral();
    void infoSIM();
    void sendSMS(char *num, char *msg);
    void listSMS();
    void readSMS(char *numb);
    void readAllSMS(int numb);
    void deleteSMS(char *n);
    void formatSMS();
    void makeCall(char *nm);
    void endCall();
    void updateSerial();
    void begin(unsigned long speed);
	String requestHTTP(const char *a, const char *b, const char *c, const char *d);
    void closeHttp();
	
	
  private:
    void clearBuffer();
	char buff[250];
	unsigned long vrijeme;
	void clearSerial();
	

};
#endif
