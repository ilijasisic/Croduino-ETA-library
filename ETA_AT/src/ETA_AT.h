#ifndef ETA_AT_h
#define ETA_AT_h

#define DEF_RX_PIN 2
#define DEF_TX_PIN 3

//#define DEBUG  //comment this line if you don't want anything on serial monitor

#include "Arduino.h"
#include <SoftwareSerial.h>



class ETA_AT
{
  public:
	ETA_AT();
    void powerOn();
    void powerOff();
    void Test();
    void callMake(char *addr);
    void callAnswer();
    void callHangUp();
    void autoAnswerSettings(int x, int y);
    void SMSsend(char *addr, char *msg);
    String SMSread(int x);
    String SMSnumberOfSender(String x);
    String SMStext(String x);
    void SMSlistAll();
    void SMSlistRead();
    void SMSlistUnread();
    int SMSnumber();
    String SMSdelete(int x);
    void SMSformat();
    void switchToHeadphones();
    void switchToSpeakers();
    int getSignalQuality();
    String SIMgetID();
    String availableOperators();
    String currentOp();
	void enableTextMode();
	void enablePDUMode();
    void updateSerial();
	void begin(unsigned long speed);
	String requestHTTP(const char *a, const char *b, const char *c, const char *d);
  private:
    void clearBuffer();
    int checkRing(int i);
    int numOfMsg(int i);
    int errorCheck(String x);
	char ioBuffer[150];
	unsigned long vrijeme;
	void clearSerial();
	
}; 
#endif
