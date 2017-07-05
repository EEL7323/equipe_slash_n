/*
 * CatracaEntrada.cpp
 *
 *  Created on: 09/06/2017
 *      Author: rober
 */

#include "Catraca.h"


Catraca::Catraca() {
	//Valores iniciais
	RU_PRICE = 1.5;
	ocupacaoRU = 15;
	lastEntradaTime = millis();
	lastSaidaTime = millis();

	//Timer para ligar os leds que representam a liberação da catraca
	inTimer.initializeMs(750, timerEntrada);


	//Para testa da listra de entrada
	listaEntrada.addEntry(14101350,0);
	listaEntrada.addEntry(14101336,1);
	listaEntrada.addEntry(14101345,1);
	listaEntrada.addEntry(14101300,1);
	listaEntrada.addEntry(14101331,1);
	listaEntrada.addEntry(14101377,1);
	listaEntrada.addEntry(14101366,1);
	listaEntrada.addEntry(14101310,1);
	listaEntrada.addEntry(14101311,1);

	matr = 1000;  //Cada vez que o botao é pressinado, entra um estudante com uma matricula "aleatoria"



}

Catraca::~Catraca(){

	//TODO
}

int Catraca::getOcupacao(){
	return ocupacaoRU;
}


//Quando há entrada pelo cartão
void Catraca::interruptEntrada(){
	int currentTime = millis();
	float cred;

	AlunoNode* node;
	if(currentTime-lastEntradaTime > 1000){
		//Como nao conseguimos ler a matricula no cartao RFID, vamos 'inventar' uma matricula qualquer
		matr += 1;
		node = arvore.findNodo(matr);
		if(node != 0){
			cred = node->getCreditoCard();
			if(cred >= RU_PRICE){
				ocupacaoRU += 1;
				node->setCreditoCard(cred-RU_PRICE);
				listaEntrada.addEntry(matr,0);
				openCatracaEntrada();
				Serial.printf("%%%%%%%%%%%% Entrada: %d \n",matr);
			}
			else{
				Serial.printf("%%%%%%%%%%%% Matricula %d não tem creditos suficientes (%d) \n",matr,cred);
			}
		}
		else{
			Serial.print("%%%%%%%%%%%%%%%% Aluno não encontrado no banco de dados local: ");
			Serial.println(matr);
		}
		lastEntradaTime = currentTime;
	}



}

void Catraca::interruptSaida(){
	int currentTime = millis();
	if(currentTime-lastSaidaTime > 1000){
		ocupacaoRU -= 1;
		if(ocupacaoRU <0 ){
			ocupacaoRU = 0;
		}
		lastSaidaTime = currentTime;
		Serial.printf("%%%%%%%%%%%% Saída!\n");
	}
}


//Entrada pelo smartphone
bool Catraca::entradaMobile(int matr, int LEDs){

	if( (LEDs%64) == display.verification){
		ocupacaoRU += 1;
		openCatracaEntrada();
		display.write(millis()); //Valor 'aleatório' do display = tempo atual em milisegundos
		return true;
	}
	else{
		Serial.printf("Valor enviado de LEDs: %d, diferente de: %d \n", LEDs, display.verification);
		return false;
	}


}

void Catraca::setVerification(int verif){
	display.write(verif);
}


void Catraca::openCatracaEntrada(){
	//Abre a catraca, depois de um segundo, fecha
	digitalWrite(inLed,1);
	inTimer.start(false); //repeating = false
}


void Catraca::setPrecoRU(int newPrice){
	RU_PRICE = newPrice;
}


