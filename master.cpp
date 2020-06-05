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

// LED pins
int const LED_S1 = 14;
int const LED_S2 = 15;
int const LED_S3 = 16;
int const LED_S4 = 17;

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
char c;
String recData;
int ch = 1;

void turnOn(int id) {
	digitalWrite(id, HIGH);
}

void turnOff(int id) {
	digitalWrite(id, LOW); 
}

void initializeLEDs() {
	pinMode(LED_S1, OUTPUT);
	pinMode(LED_S2, OUTPUT);
	pinMode(LED_S3, OUTPUT);
	pinMode(LED_S4, OUTPUT);
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

void fire() {
	int lastChar = recData.length() - 1;
    if(recData.charAt(lastChar) == '1') {
		switch (ch)	{
			case 1: turnOn(LED_S1);
				break;
			case 2: turnOn(LED_S2);
				break;
			case 3: turnOn(LED_S3);
				break;
			case 4: turnOn(LED_S4);
				break;
		}
    } else {
      switch (ch) {
			case 1: turnOff(LED_S1);
				break;
			case 2: turnOff(LED_S2);
				break;
			case 3: turnOff(LED_S3);
				break;
			case 4: turnOff(LED_S4);
				break;
		}
    }
    Serial.println(recData);
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
	if(counters[id] < 3) {
		counters[id]++;
	} else {
		SLAVES_STATES[id] = SEM_RESPOSTA;
	}
}

void emitirAlerta(int id){
	/* TODO: uma função que ativa algum dispositivo que emite um alerta para os bombeiros


	Requisitos: deve-se informar qual é o slave que está em alerta
	*/
     // turnOn(EMERGENCY_LED);
}

void listenSlave1() {
	firstSlave.listen();
	if(firstSlave.isListening()) {
		Serial.println("Listening to slave 1");
		if(firstSlave.available() > 0) {
			recData = "";
			while(firstSlave.available()) {
				c = firstSlave.read();
				recData += c;
			}
		}
	}
	ch = 2;
	delay(500);
}

void listenSlave2() {
	secondSlave.listen();
	if(secondSlave.isListening()) {
		Serial.println("Listening to slave 2");
		if(secondSlave.available() > 0) {
			recData = "";
			while(secondSlave.available()) {
				c = secondSlave.read();
				recData += c;
			}
		}
	}
	ch = 3;
	delay(500);
}

void listenSlave3() {
	thirdSlave.listen();
	if(thirdSlave.isListening()) {
		Serial.println("Listening to slave 3");
		if(thirdSlave.available() > 0) {
			recData = "";
			while(thirdSlave.available()) {
				c = thirdSlave.read();
				recData += c;
			}
		}
	}
	ch = 4;
	delay(500);
}

void listenSlave4() {
	fourthSlave.listen();
	if(fourthSlave.isListening()) {
		Serial.println("Listening to slave 4");
		if(fourthSlave.available() > 0) {
			recData = "";
			while(fourthSlave.available()) {
				c = fourthSlave.read();
				recData += c;
			}
		}
	}
	ch = 1;
	delay(500);
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
	switch (SLAVES_STATES[id]) {
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

void slaveRotina(){
	int lastChar = recData.length() - 1;
	switch (recData.charAt(lastChar)) { // entrada dos dados 
		case '0':
			semEmergencia(id);
			break;
		case '1':
			slaveAlerta(id);
			break;
		case '2':
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