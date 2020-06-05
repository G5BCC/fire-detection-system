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

int const LED_S_1 = 14;
int const LED_S_2 = 15;
int const LED_S_3 = 16;
int const LED_S_4 = 17;

SoftwareSerial firstSlave(FIRST_SLAVE_RX, FIRST_SLAVE_TX);
SoftwareSerial secondSlave(SECOND_SLAVE_RX, SECOND_SLAVE_TX);
SoftwareSerial thirdSlave(THIRD_SLAVE_RX, THIRD_SLAVE_TX);
SoftwareSerial fourthSlave(FOURTH_SLAVE_RX, FOURTH_SLAVE_TX);

SoftwareSerial slaves[4] = {firstSlave, secondSlave, thirdSlave, fourthSlave};
// Slaves states
enum {
	SEM_RESPOSTA,
	SEM_EMERGENCIA,
	ALERTA,
	ALERTA_A,
	EMERGENCIA,
	EMERGENCIA_A
	
};

int SLAVES_STATES[4] = {
	SEM_EMERGENCIA,
	SEM_EMERGENCIA,
	SEM_EMERGENCIA,
	SEM_EMERGENCIA,

};
// Not response counter

int counters[4] = {0,0,0,0};

// Data receive/transmit
char charSlave1;
char charSlave2;
char charSlave3;
char charSlave4;

String recDataSlave1;
String recDataSlave2;
String recDataSlave3;
String recDataSlave4;

// Sensor Variables
String temp;
String gas;

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

	if(recDataSlave1 != "") {
		Serial.println(recDataSlave1);
	} else {
		Serial.println("No data received at slave 1");
	}

	slaveRotina(0);
	delay(1000);
}

void listenSlave2() {
	secondSlave.listen();
	if(secondSlave.isListening()) {
		Serial.println("Listening slave 2");
		delay(1000);
		if(secondSlave.available() > 0) {
			recDataSlave2 = "";
			while(secondSlave.available()) {
				charSlave2 = secondSlave.read();
				recDataSlave2 += charSlave2;
			}
		}
	}

	if(recDataSlave2 != "") {
		Serial.println(recDataSlave2);
	} else {
		Serial.println("No data received at slave 2");
	}
	slaveRotina(1);
	delay(1000);
}


void listenSlave3() {
	thirdSlave.listen();
	if(thirdSlave.isListening()) {
		Serial.println("Listening slave 3");
		delay(1000);
		if(thirdSlave.available() > 0) {
			recDataSlave3 = "";
			while(thirdSlave.available()) {
				charSlave3 = thirdSlave.read();
				recDataSlave3 += charSlave3;
			}
		}
	}

	if(recDataSlave3 != "") {
		Serial.println(recDataSlave3);
	} else {
		Serial.println("No data received at slave 3");
	}
	slaveRotina(2);
	delay(1000);
}

void listenSlave4() {
	fourthSlave.listen();
	if(fourthSlave.isListening()) {
		Serial.println("Listening slave 4");
		delay(1000);
			if(fourthSlave.available() > 0) {
			recDataSlave4 = "";
			while(fourthSlave.available()) {
				charSlave4 = thirdSlave.read();
				recDataSlave4 += charSlave4;
			}
		}
	}

	if(recDataSlave4 != "") {
		Serial.println(recDataSlave4);
	} else {
		Serial.println("No data received at slave 4");
	}

	slaveRotina(3);
	delay(1000);
}

void listenSlaves() {
	listenSlave1();

	listenSlave2();
			
	listenSlave3();

	listenSlave4();
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

void setEmergency(int id) {
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
	SLAVES_STATES[id] = EMERGENCIA;
}

/* 
	Função para quando não há nenhuma emergencia do slave

	paramêtro:

		int id: específica o id do slave

	pseudo código:
		sobrescreve o estado do slave específicado para "SEM_EMERGENCIA"
		
*/
void semEmergencia(int id){
	SLAVES_STATES[id] = SEM_EMERGENCIA;
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
	if(counters[id] < 3){
		counters[id]++;
	} else {
		SLAVES_STATES[id] = SEM_RESPOSTA;
		Serial.println("******SMTP SERVER******")
		Serial.println("sendmail: support@G5BCC")
		Serial.println("content: slave %d not response more than 3 time", id);
		Serial.println("******SMTP SERVER******")
	}
}

void emitirAlerta(int id){
	/* TODO: uma função que ativa algum dispositivo que emite um alerta para os bombeiros


	Requisitos: deve-se informar qual é o slave que está em alerta
	*/
	setEmergency(id);
	Serial.println("O slave " + String(id) + " está pegando fogo");
}

void readIncomingData(int id) {
	int lastChar;
	switch(id) {
		case 1:
			lastChar = recDataSlave1.length() - 1;
			if(recDataSlave1.charAt(lastChar) == '1') {
				turnOn(LED_S_1);
			} else {
				turnOff(LED_S_1);
			}
			Serial.println(recDataSlave1);
			break;
		case 2:
			lastChar = recDataSlave2.length() - 1;
			if(recDataSlave2.charAt(lastChar) == '1') {
				turnOn(LED_S_2);
			} else {
				turnOff(LED_S_2);
			}
			Serial.println(recDataSlave2);
			break;
		case 3:
			lastChar = recDataSlave3.length() - 1;
			if(recDataSlave3.charAt(lastChar) == '1') {
				turnOn(LED_S_3);
			} else {
				turnOff(LED_S_3);
			}
			Serial.println(recDataSlave3);
			break;
		case 4:
			lastChar = recDataSlave4.length() - 1;
			if(recDataSlave4.charAt(lastChar) == '1') {
				turnOn(LED_S_4);
			} else {
				turnOff(LED_S_4);
			}
			Serial.println(recDataSlave4);
			break;
	}
}

/* 
	Função para quando há uma mensagem de alerta

	paramêtro:

		int id: específica o id do slave

	pseudo código:

		se o estado do slave especifico for alerta, 
			toca o sinal.
		se o estado do slave especifico for um alerta atendido, 
			aguarda.
		se nenhuma das ocorrencias for atendido, 
			estado do slave é sobrescrito para ALERTA e o sinal é tocado.
*/
void slaveAlerta(int id){
	
	// Para a primeira ocorrencia do alerta
	switch (SLAVES_STATES[id])
	{
	case ALERTA:
		emitirAlerta(id);
		break;
	case ALERTA_A:
		break;
	default:
		SLAVES_STATES[id] = ALERTA;
		emitirAlerta(id);
		break;
	}
}


/* 
	Função para quando há uma mensagem de emergência

	paramêtro:

		int id: específica o id do slave

	pseudo código:

	se o estado do slave especifico for emergencia, 
			toca o sinal.
		se o estado do slave especifico for um emergencia atendido, 
			aguarda.
		se nenhuma das ocorrencias for atendido, 
			estado do slave é sobrescrito para EMERGENCIA e o sinal é tocado.

*/
void slaveEmergencia(int id){
	// Para a primeira ocorrencia da emergência
	switch (SLAVES_STATES[id])
	{
	case EMERGENCIA:
		emitirAlerta(id);
		break;
	case EMERGENCIA_A: // TODO: Precisa ter um botão para alterar o estado de emergencia
		break;
	default:
		SLAVES_STATES[id] = EMERGENCIA;
		emitirAlerta(id);
		break;
	}

}

void slaveRotina(int id){
	int indexChar = recDataSlave1.charAt(lastChar);
	readIncomingData(id);
	switch ('1') // entrada dos dados
	{
	case '0':
		// Ler dados
		semEmergencia(id);
		break;
	case '1':
		// Verificar se existe alguma emergência
		slaveAlerta(id);
		break;
	case '2':
		// Acionar emergência
		slaveEmergencia(id);
		break;
	default:
		semResposta(id);
		break;
	}

}

void setup() {
	Serial.begin(9600);

  	initializeSlaves();
	initializeLEDs();
}

void loop() {
	
	listenSlaves();
	
}