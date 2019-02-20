
#include "Arduino.h"
#include <SoftwareSerial.h>
#include <ETA_AT.h>

SoftwareSerial GSM(DEF_RX_PIN, DEF_TX_PIN);
// ============================================================
//CONSTRUCTOR//////////////////////////////////////////////////
// ============================================================

ETA_AT::ETA_AT() {
	pinMode(4, OUTPUT);
}


// ============================================================
//SETUP FUNCTIONS//////////////////////////////////////////////
// ============================================================

void ETA_AT::powerOn() {
	digitalWrite(4, LOW);
	//  delay(5000);
	while (GSM.available() <= 0) {
	}
	clearSerial();
}
// ============================================================
void ETA_AT::powerOff() {
	digitalWrite(4, HIGH);
	delay(15000);
}
// ============================================================
void ETA_AT::Test()
{
	GSM.println("AT");
	GSM.println("AT");

	while (GSM.available() != '+') {
	}
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
	GSM.println("AT"); //Once the handshake test is successful, it will back to OK
	while (GSM.available() != '+') {
	}
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
	while (GSM.available() != 'E') {
	}
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
	GSM.println("AT+IPR=19200");
	delay(200);
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
//CALL FUNCTIONS///////////////////////////////////////////////
// ============================================================

void ETA_AT::callMake(char *addr)
{
	clearBuffer();
	strcat((ioBuffer), ("ATD"));
	strcat((ioBuffer), ("\""));
	strcat((ioBuffer), (addr));
	strcat((ioBuffer), ("\""));
	GSM.println(ioBuffer);
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
void ETA_AT::callAnswer() {
	GSM.println("ATA");
}
// ============================================================
void ETA_AT::callHangUp() {
	GSM.println("ATH");
}
// ============================================================
void ETA_AT::autoAnswerSettings(int x, int y)
{
	clearBuffer();
	int i = 0, k = 0, br = 0;
	while (GSM.available()) {
		//delay(0);  //delay to allow buffer to fill
		if (GSM.available() > 0) { //mislim da mi ne traba ovo???

			ioBuffer[i] = GSM.read();  //gets one byte from serial buffer
			i++;
			if (ioBuffer[i - 1] == 10) {
				if (i < 40) {
					k = checkRing(i);
					if (k == 1) {
						br++;
					}
					if (br > 166 * x) {
						switch (y) {
						case 1:    // your hand is on the sensor
							GSM.println("ATA");
							br = 0;
							clearBuffer();
							break;
						case 2:    // your hand is close to the sensor
							GSM.println("ATH");
							br = 0;
							clearBuffer();
							break;
						}
					}
					i = 0;
					clearBuffer();
				}
				else {
					i = 0;
					clearBuffer();
				}
			}
		}
	}
}
// ============================================================
//SMS FUNCTIONS////////////////////////////////////////////////
// ============================================================
void ETA_AT::SMSsend(char *addr, char *msg)
{
	clearBuffer();
	strcat((ioBuffer), ("AT+CMGS="));

	strcat((ioBuffer), ("\""));
	strcat((ioBuffer), (addr));
	strcat((ioBuffer), ("\""));
	GSM.println(ioBuffer);
	delay(100);
	//updateSerial();
	GSM.print(msg); //text content
					//updateSerial();
	GSM.write(26);
	delay(100);
	//updateSerial();
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
String ETA_AT::SMSread(int x) {
	String ioString = "";
	int a;
	GSM.print("AT+CMGR=");
	GSM.println(x);
	delay(100);
	while (GSM.available()) {
		ioString = GSM.readString();
	}
	a = errorCheck(ioString);
	if (a < 0)
		return ioString;
	else return ioString = String(a);
}
// ============================================================
String ETA_AT::SMSnumberOfSender(String x) {
	String ioString = "";
	char number[20] = { 0 };
	int k = 0;
	for (int i = 0; i < x.length(); i++) {
		delay(3);
		if (x[i] == 34 && x[i - 1] == 44 && x[i - 2] == 34 && x[i - 3] == 68 && x[i - 4] == 65) {

			for (int j = i + 1; j < i + 21; j++) {
				if (x[j] == 34) {
					ioString = number;
					return ioString;
				}
				number[k] = x[j];
				k++;
			}

		}
	}
	return "Error while checking";
}
// ============================================================
String ETA_AT::SMStext(String x) {
	String ioString = "";
	char number[140] = { 0 };
	int k = 0, br = 0;
	for (int i = 0; i < x.length(); i++) {
		delay(3);
		if (x[i] == 10) br++;
		if (br == 3) {
			for (int j = i + 1; j < i + 140; j++) {
				if (x[j] == 10) {
					ioString = number;
					return ioString;
				}
				number[k] = x[j];
				k++;
			}
		}
	}
	return "Error while reading";
}
// ============================================================
void ETA_AT::SMSlistAll() {
	GSM.println("AT+CMGF=1");
	delay(100);
	//  GSM.println("ATE0");
	//  delay(100);
	updateSerial();
	GSM.println("AT+CMGL=\"ALL\"");
	vrijeme = millis();
	while (GSM.available() || millis() < (vrijeme + 5000))
	{
		if (GSM.available() > 0) {
			Serial.write(GSM.read());//Forward what Software Serial received to Serial Port
		}
	}
	// ============================================================
}
void ETA_AT::SMSlistRead() {
	GSM.println("AT+CMGF=1");
	delay(100);
	GSM.println("ATE0");
	delay(100);
	updateSerial();
	GSM.println("AT+CMGL=\"REC READ\"");
	vrijeme = millis();
	while (GSM.available() || millis() < (vrijeme + 5000))
	{
		if (GSM.available() > 0) {
			Serial.write(GSM.read());//Forward what Software Serial received to Serial Port
		}
	}
}
// ============================================================
void ETA_AT::SMSlistUnread() {
	GSM.println("AT+CMGF=1");
	delay(100);
	GSM.println("ATE0");
	delay(100);
	updateSerial();
	GSM.println("AT+CMGL=\"REC UNREAD\"");
	vrijeme = millis();
	while (GSM.available() || millis() < (vrijeme + 5000))
	{
		if (GSM.available() > 0) {
			Serial.write(GSM.read());//Forward what Software Serial received to Serial Port
		}
	}
}
// ============================================================
int ETA_AT::SMSnumber() {
	clearBuffer();
	int i = 0, x = 0;
	GSM.println("AT+CPMS=\"SM\",\"SM\",\"SM\"");
	delay(200);
	while (GSM.available()) {
		//delay(10);  //delay to allow buffer to fill
		if (GSM.available() > 0) {
			ioBuffer[i] = GSM.read();  //gets one byte from serial buffer
			i++;
			if (ioBuffer[i - 1] == 10) {
				x = numOfMsg(i);
				i = 0;
				clearBuffer();
			}
		}
	}
	return x;
}
// ============================================================
String ETA_AT::SMSdelete(int x) {
	clearSerial();
	String ioString = "";
	// GSM.println("AT+CMGF=1");
	GSM.print("AT+CMGD=");
	GSM.println(x);
	delay(100);
	while (GSM.available()) {
		ioString = GSM.readString();
	}
	//Serial.println(ioString);
	return String(errorCheck(ioString));
}

// ============================================================
void ETA_AT::SMSformat() {
	GSM.println("AT+CMGD 1,4");
	delay(100);
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
//SOUND OUTPUT SETTINGS////////////////////////////////////////
// ============================================================
void ETA_AT::switchToHeadphones() {
	GSM.println("AT+SNFS=1");
	delay(100);
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
void ETA_AT::switchToSpeakers() {
	GSM.println("AT+SNFS=0");
	delay(100);
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
//OUTPUT SETTINGS//////////////////////////////////////////////
// ============================================================
void ETA_AT::enableTextMode() {
	GSM.println("AT+CMGF=1");
	delay(200);
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
void ETA_AT::enablePDUMode() {
	GSM.println("AT+CMGF=0");
	delay(200);
#ifdef DEBUG
	updateSerial();
#endif
	clearSerial();
}
// ============================================================
//GENERAL INFO/////////////////////////////////////////////////
// ============================================================
int ETA_AT::getSignalQuality() {
	int x = 0, y = 0;
	String ioString = "";
	int br = 0;
	GSM.println("AT+CSQ");
	delay(100);
	while (GSM.available()) {
		ioString = GSM.readString();
	}
	for (int i = 0; i < ioString.length(); i++) {
		delay(1);
		if (ioString[i] == '\n') {
			br++;
		}
		if (br == 2) {
			if (ioString[i] == ':') {
				x = ioString[i + 2] - 48;
				if (ioString[i + 3] <= '9' && ioString[i + 3] >= '0') {
					x = x * 10;
					y = ioString[i + 3] - 48;
					x = x + y + 1;
				}
			}
		}
	}
	x = x * 100;
	x = x / 32;
	if (x <= 100 && x >= 0)
		return x;
	else return -1;

}
// ============================================================
String ETA_AT::SIMgetID() {
	int k = 0, br = 0, z = 0;
	String ioString = "";
	char ID[25] = { 0 };
	GSM.println("AT+CCID");
	delay(100);
	while (GSM.available()) {
		ioString = GSM.readString();
	}
	for (int i = 0; i < ioString.length(); i++) {
		delay(1);
		if (ioString[i] == '\n') {
			br++;
		}
		if (br == 2) {
			if (ioString[i] == ':') {
				for (int j = i + 2; j < ioString.length(); j++) {
					delay(1);
					if (ioString[j] == '\r') {
						ioString = ID;
						return ioString;
					}
					ID[k] = ioString[j];
					k++;
				}
			}
		}
	}
	return "ERROR";
}
// ============================================================
String ETA_AT::availableOperators() {
	String ioString = "";
	int k = 0, br = 0;
	//char number[60]={0};

	GSM.println("AT+COPS=?");
	vrijeme = millis();
	while (GSM.available() || millis() < vrijeme + 12000)
	{
		delay(1);
		if (GSM.available() > 0) {

			ioString = GSM.readString(); //Forward what Software Serial received to Serial Port
		}
	}
	return ioString;
}
// ============================================================
String ETA_AT::currentOp() {
	String ioString = "";
	GSM.println("AT+COPS?");
	delay(100);
	while (GSM.available()) {
		delay(1);
		if (GSM.available() > 0) {

			ioString = GSM.readString();
		}
	}
	return ioString;

}
// ============================================================
//SERIAL UPDATE////////////////////////////////////////////////
// ============================================================
void ETA_AT::updateSerial()
{
	while (Serial.available())
	{
		GSM.write(Serial.read());//Forward what Serial received to Software Serial Port
	}
	while (GSM.available())
	{
		Serial.write(GSM.read());//Forward what Software Serial received to Serial Port
	}
}
// ============================================================
// ============================================================
void ETA_AT::clearBuffer()
{
	for (int i = 0; i < 150; i++) {
		ioBuffer[i] = 0;
	}
}
// ============================================================
int ETA_AT::checkRing(int i) {
	if ((ioBuffer[i - 3] == 71) && (ioBuffer[i - 4] == 78) && (ioBuffer[i - 5] == 73) && (ioBuffer[i - 6] == 82))
	{
		return 1;
	}
	else {
		return 0;
	}
}
// ============================================================
int ETA_AT::numOfMsg(int i) {
	int x, y;
	for (int j = 0; j < i; j++) {
		if (ioBuffer[j] == 58 && ioBuffer[j - 1] == 83 && ioBuffer[j - 2] == 77) {
			if ((ioBuffer[j + 2] >= 48) && (ioBuffer[j + 2] <= 57)) {
				x = ioBuffer[j + 2] - 48;
				if ((ioBuffer[j + 3] >= 48) && (ioBuffer[j + 3] <= 57)) {
					x = x * 10;
					y = ioBuffer[j + 3] - 48;
					x = x + y;
				}
				return x;
			}
		}
	}
}
// ============================================================
int ETA_AT::errorCheck(String x) {
	int i = x.length(), error_num = 0, temp = 0, temp1 = 0, temp2 = 0;
	if (x[i - 3] == 'K' && x[i - 4] == 'O')
	{
		return -1;
	}
	// if ([i - 2] != 'R' && ioBuffer[i - 3] == 'O' && ioBuffer[i - 4] != 'R' && ioBuffer[i - 5] != 'R' && ioBuffer[i - 4] != 'E')
	else {
		for (int j = i; j > i - 20; j--) {

			if (x[j] != 'R' && x[j - 1] == 'O' && x[j - 2] != 'R' && x[j - 3] != 'R' && x[j - 4] != 'E') {
				return 0;
			}
			if (x[j] == ':')
				return error_num;
			if (x[j] >= '0' && x[j] <= '9') {
				temp = x[j] - 48;
				error_num = temp;
				if (x[j - 1] >= '0' && x[j - 1] <= '9') {
					temp1 = x[j - 1] - 48;
					error_num = temp + (temp1 * 10);
					if (x[j - 2] >= '0' && x[j - 2] <= '9') {
						temp2 = x[j - 2] - 48;
						error_num = temp + (temp1 * 10) + (temp2 * 100);
					}
				}
				return error_num;
			}
		}
	}
}
// ============================================================
void ETA_AT::begin(unsigned long speed) {                       // Initializes SoftwareSerial object with the baudrate provided by the user.                                        // If this method is called without args, the simCom serial object will be initialized with the default baudrate as specified in the SIM800.h file.

	GSM.begin(speed);                                        // Calls SoftwareSerial method "begin" either with default baudrate or user provided baudrate.
}
void ETA_AT::clearSerial() {
	while (GSM.available() >0) {
		GSM.read();
	}
}