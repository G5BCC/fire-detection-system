// Link Circuits: https://www.tinkercad.com/things/37ZMHeRq6PL-mestre-escravo/editel?sharecode=uk_3F3u3vzGGc00bNpZa_nuqQCyqDc-KUgMwVkn1uI8

#include <SoftwareSerial.h>

/*
First Slave:
TX = digital pin 10, RX = digital pin 11

Secons slave:
TX = digital pin 8, RX = digital pin 9

Third slave:
TX = digital pin 6, RX = digital pin 7

Fourth slave:
TX = digital pin 4, RX = digital pin 5
*/
int const FIRST_SLAVE_RX = 11;
int const FIRST_SLAVE_TX = 10;
int const SECOND_SLAVE_RX = 9;
int const SECOND_SLAVE_TX = 8;
int const THIRD_SLAVE_RX = 7;
int const THIRD_SLAVE_TX = 6;
int const FOURTH_SLAVE_RX = 5;
int const FOURTH_SLAVE_TX = 4;

SoftwareSerial firstSlave(FIRST_SLAVE_RX, FIRST_SLAVE_TX);
SoftwareSerial secondSlave(SECOND_SLAVE_RX, SECOND_SLAVE_TX);
SoftwareSerial thirdSlave(THIRD_SLAVE_RX, THIRD_SLAVE_TX);
SoftwareSerial fourthSlave(FOURTH_SLAVE_RX, FOURTH_SLAVE_TX);

// Data receive/transmit
char c;
String recData, recDataOld;
int ch = 0;

// Sensor Variables
String temp;
String gas;

void initializeSlaves() {
	firstSlave.begin(9600);
	secondSlave.begin(9600);
	thirdSlave.begin(9600);
	fourthSlave.begin(9600);

	pinMode(FIRST_SLAVE_RX, INPUT);
	pinMode(FIRST_SLAVE_TX, OUTPUT);

	pinMode(SECOND_SLAVE_RX, INPUT);
	pinMode(SECOND_SLAVE_TX, OUTPUT);

	pinMode(THIRD_SLAVE_RX, INPUT);
	pinMode(THIRD_SLAVE_TX, OUTPUT);

	pinMode(FOURTH_SLAVE_RX, INPUT);
	pinMode(FOURTH_SLAVE_TX, OUTPUT);
}

void setInterval() {
	delay(200);
}

void gasSensor() {
	firstSlave.listen();

	if (firstSlave.isListening()) {
		if (firstSlave.available() > 0){
			recData = "";

			while (firstSlave.available()) {
				c = firstSlave.read();
				recData += c;
			}

			int SgasValue = recData.toInt();

			if (SgasValue != 0) {
				Serial.println(recData);
				gas = recData;
				ch = 1;
			}
		}
	}

	setInterval();
}

void temperatureSensor(){
	firstSlave.listen();

	if (firstSlave.isListening()) {
		if (firstSlave.available() > 0) {
			recData = "";

			while (firstSlave.available()) {
				c = firstSlave.read();
				recData += c;
			}

			float StempValue = recData.toFloat();

			if (StempValue != 0) {
				Serial.println(recData);
				temp = recData;
				ch = 0;
			}
		}
	}

	setInterval();
}

void setup() {
	Serial.begin(9600);

	initializeSlaves();
}

void loop() {
	switch (ch) {
		case 0: gasSensor();         break;
		case 1: temperatureSensor(); break;
		default:                     break;
	}

	setInterval();
}