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

<<<<<<< HEAD
// LED pins
int const LED_S1 = 14;
int const LED_S2 = 15;
int const LED_S3 = 16;
int const LED_S4 = 17;
=======
int const LED_S_1 = 14;
int const LED_S_2 = 15;
int const LED_S_3 = 16;
int const LED_S_4 = 17;
>>>>>>> master

SoftwareSerial firstSlave(FIRST_SLAVE_RX, FIRST_SLAVE_TX);
SoftwareSerial secondSlave(SECOND_SLAVE_RX, SECOND_SLAVE_TX);
SoftwareSerial thirdSlave(THIRD_SLAVE_RX, THIRD_SLAVE_TX);
SoftwareSerial fourthSlave(FOURTH_SLAVE_RX, FOURTH_SLAVE_TX);

SoftwareSerial slaves[4] = {firstSlave, secondSlave, thirdSlave, fourthSlave};

// Slaves states
enum {
	OCIOSO,
	SEM_RESPOSTA,
	SEM_EMERGENCIA,
	ALERTA,
	EMERGENCIA,
} STATE = OCIOSO;

int SLAVES_STATES[4] = {
	SEM_EMERGENCIA,
	SEM_EMERGENCIA,
	SEM_EMERGENCIA,
	SEM_EMERGENCIA,

};

// No response counter
int counters[4] = {0, 0, 0, 0};

// Data receive/transmit
char charSlave1;
char charSlave2;
char charSlave3;
char charSlave4;

String recDataSlave1;
String recDataSlave2;
String recDataSlave3;
String recDataSlave4;

// Slave state counter
int ch = 1;

int lastChar;

void turnOn(int id) {
	digitalWrite(id, HIGH);
}

void turnOff(int id) {
	digitalWrite(id, LOW);
}

void initializeLEDs() {
	pinMode(LED_S_1, OUTPUT);
	pinMode(LED_S_2, OUTPUT);
	pinMode(LED_S_3, OUTPUT);
	pinMode(LED_S_4, OUTPUT);
}

void listenSlave1() {
	firstSlave.listen();
	if(firstSlave.isListening()) {
		Serial.println("Listening slave 1");
		delay(1000);
		if(firstSlave.available() > 0) {
			recDataSlave1 = "";
			Serial.println("Reading slave 1");
			while(firstSlave.available()) {
				charSlave1 = firstSlave.read();
				recDataSlave1 += charSlave1;
			}
		}
	}

	// Check if the data arrived/exists
	if(recDataSlave1 != "") {
		lastChar = recDataSlave1.length() - 1;
		if(recDataSlave1[lastChar] == '1') {
			Serial.println(recDataSlave1);
			setAlert(1);
			STATE = ALERTA;
		} else {
			Serial.println(recDataSlave1);
		}
		ch = 2;
	} else {
		Serial.println("No data received at slave 1");
	}
	delay(1000);
}

void listenSlave2() {
	secondSlave.listen();
	if(secondSlave.isListening()) {
		Serial.println("Listening slave 2");
		delay(1000);
		if(secondSlave.available() > 0) {
			Serial.println("Reading slave 2");
			recDataSlave2 = "";
			while(secondSlave.available()) {
				charSlave2 = secondSlave.read();
				recDataSlave2 += charSlave2;
			}
		}
	}

	// Check if the data arrived/exists
	if(recDataSlave2 != "") {
		lastChar = recDataSlave2.length() - 1;
		if(recDataSlave2[lastChar] == '1') {
			Serial.println(recDataSlave2);
			setAlert(2);
			STATE = ALERTA;
		} else {
			Serial.println(recDataSlave2);
		}
		ch = 3;
	} else {
		Serial.println("No data received at slave 2");
	}
	delay(1000);
}


void listenSlave3() {
	thirdSlave.listen();
	if(thirdSlave.isListening()) {
		Serial.println("Listening slave 3");
		delay(1000);
		if(thirdSlave.available() > 0) {
			Serial.println("Reading slave 3");
			recDataSlave3 = "";
			while(thirdSlave.available()) {
				charSlave3 = thirdSlave.read();
				recDataSlave3 += charSlave3;
			}
		}
	}

	// Check if the data arrived/exists
	if(recDataSlave3 != "") {
		lastChar = recDataSlave3.length() - 1;
		if(recDataSlave3[lastChar] == '1') {
			Serial.println(recDataSlave3);
			setAlert(3);
			STATE = ALERTA;
		} else {
			Serial.println(recDataSlave3);
		}
		ch = 4;
	} else {
		Serial.println("No data received at slave 3");
	}
	delay(1000);
}

void listenSlave4() {
	fourthSlave.listen();
	if(fourthSlave.isListening()) {
		Serial.println("Listening slave 4");
		delay(1000);
			if(fourthSlave.available() > 0) {
			Serial.println("Reading slave 4");
			recDataSlave4 = "";
			while(fourthSlave.available()) {
				charSlave4 = fourthSlave.read();
				recDataSlave4 += charSlave4;
			}
		}
	}

	// Check if the data arrived/exists
	if(recDataSlave4 != "") {
		lastChar = recDataSlave4.length() - 1;
		if(recDataSlave4[lastChar] == '1') {
			Serial.println(recDataSlave4);
			setAlert(4);
			STATE = ALERTA;
		} else {
			Serial.println(recDataSlave4);
		}
		ch = 1;
	} else {
		Serial.println("No data received at slave 4");
	}
	delay(1000);
}

void listenSlaves() {
	switch(ch) {
		case 1: listenSlave1();
			break;
		case 2: listenSlave2();
			break;
		case 3: listenSlave3();
			break;
		case 4: listenSlave4();
			break;
	}
}

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

void sendAlert(int id){
	/* TODO: uma função que ativa algum dispositivo que emite um alerta para os bombeiros


	Requisitos: deve-se informar qual é o slave que está em alerta
	*/
	Serial.println("O slave " + String(id) + " esta pegando fogo");
}

void setAlert(int id) {
	switch (id) {
		case 1:
			turnOn(LED_S_1);
			delay(3000);
			turnOff(LED_S_1);
			break;
		case 2:
			turnOn(LED_S_2);
			delay(3000);
			turnOff(LED_S_2);
			break;
		case 3:
			turnOn(LED_S_3);
			delay(3000);
			turnOff(LED_S_3);
			break;
		case 4:
			turnOn(LED_S_4);
			delay(3000);
			turnOff(LED_S_4);
			break;
	}
	sendAlert(id);
}

void slaveEmergencia() {
	STATE = OCIOSO;
}

/* 
	Função para quando não teve nenhuma resposta do slave

	paramêtro:

		int id: específica o id do slave

	pseudo código:

		adiciona um no contador se o número de chamadas for menor que 3;

		caso seja igual ou maior a tres, o estado para o slave em específico irá para "SEM_RESPOSTA".
*/
void semResposta(int id){
	if(counters[id] < 3) {
		counters[id]++;
	} else {
		SLAVES_STATES[id] = SEM_RESPOSTA;
	}
}


void slaveRotina(){
	switch (STATE) {
		case OCIOSO: listenSlaves(); break;
		case ALERTA: slaveEmergencia(); break;
	}
}

void setup() {
	Serial.begin(9600);

  	initializeSlaves();
	initializeLEDs();
}

void loop() {
	slaveRotina();
}