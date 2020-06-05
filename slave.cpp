// Link Circuits: https://www.tinkercad.com/things/37ZMHeRq6PL-mestre-escravo/editel?sharecode=uk_3F3u3vzGGc00bNpZa_nuqQCyqDc-KUgMwVkn1uI8

#include <SoftwareSerial.h>

/*
Firt Slave: TX = digital pin 10, RX = digital pin 11
Second Slave: TX = digital pin 8, RX = digital pin 9
Third Slave: TX = digital pin 6, RX = digital pin 7
Fourth Slave: TX = digital pin 4, RX = digital pin 5
*/
int const PIN_RX = 11;
int const PIN_TX = 10;
int const EMERGENCY_LED = 2;

SoftwareSerial firstSlave(PIN_RX, PIN_TX);

char c;
String recData;

int const PIN_SGAS = A1;
int const PIN_STEMP = A0;

void setInterval() {
	delay(2000);
}

void turnOn(int id) {
	digitalWrite(id, HIGH);
}

void turnOff(int id) {
	digitalWrite(id, LOW);
}

int gas() {
	int value = analogRead(PIN_SGAS);
	recData = String(value);

	delay(250);

	Serial.println("Gas value: " + recData);

	setInterval();

	return value;
}

float temperature() {
	int SensorTempTensao = analogRead(PIN_STEMP);
	float Tensao = SensorTempTensao * 5;
	Tensao /= 1024;

	float TemperatureC = (Tensao - 0.5) * 100;
	recData = String(TemperatureC);

	delay(250);

	Serial.println("Temperature: " + recData);

	setInterval();

	return TemperatureC;
}

bool inFireEmergency(float temp) {
	if (temp > 45.0f)) {
		turnOn(EMERGENCY_LED);
		return true;
    } else {
      	turnOff(EMERGENCY_LED);
    	return false;
    }
}


bool inGasEmergency(int gas) {
	if (gas > 130)) {
		turnOn(EMERGENCY_LED);
		return true;
    } else {
      	turnOff(EMERGENCY_LED);
    	return false;
    }
}

void setup() {
	Serial.begin(9600);

	pinMode(PIN_RX, INPUT);
	pinMode(PIN_TX, OUTPUT);
	pinMode(EMERGENCY_LED, OUTPUT);

	firstSlave.begin(9600);
}

void loop() {
	int gasVal = gas();
	int tempVal = temperature();

	if(inFireEmergency(tempVal)) {
		firstSlave.print("lixo S1: 1");
	} else if(inFireEmergency(gasVal)){
		firstSlave.print("lixo S2: 2")
	}else{
		firstSlave.print("lixo S1: 0");
	}
}