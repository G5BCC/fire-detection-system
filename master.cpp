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
String recData, recDataOld;
int ch = 0;

// Sensor Variables
String temp;
String gas;


void initializeSlavesSerials(){
	for(int i = 0; i<4; i++){
		slaves[i].begin(9600);
	}
}

void initializeSlaves() {
	initializeSlaves();

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
	} else{
		SLAVES_STATES[id] = SEM_RESPOSTA;
	}
}

void emitirAlerta(int id){
	/* TODO: uma função que ativa algum dispositivo que emite um alerta para os bombeiros


	Requisitos: deve-se informar qual é o slave que está em alerta
	*/
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

void setup() {
	Serial.begin(9600);

	initializeSlaves();
}

void loop() {
	switch (ch) {
		case 0:     
			slaveEmergencia(0);   
			break;
		case 1: 
			slaveAlerta(0);
			break;
		case 2: 
			semEmergencia(0);
			break;
		default: 
			semResposta(0);// Substituir "0" por id
			break;
	}

	setInterval();
}