/*
 * CatracaEntrada.h
 *
 *  Created on: 09/06/2017
 *      Author: rober
 */

#ifndef INCLUDE_CATRACA_CATRACA_H_
#define INCLUDE_CATRACA_CATRACA_H_




#include "ListaEntrada/entryList.cpp"
//#include "Display7seg/Display7seg.cpp"
#include "DisplayLed/DisplayLed.cpp"
#include "LocalDatabase/ABB.cpp"




class Catraca {
public:
	Catraca();
	virtual ~Catraca();
	int getOcupacao();
	void setVerification(int verif);
	void interruptEntrada();
	bool entradaMobile(int matr,int LEDs);
	void interruptSaida();
	void openCatracaEntrada();
	void setPrecoRU(int newPrice);
	entryList listaEntrada;
	ABB arvore;
private:
	float RU_PRICE;
	Timer inTimer;
	DisplayLed display;
	int ocupacaoRU;
	int matr;
	int lastEntradaTime;
	int lastSaidaTime;
};



void timerEntrada(){
	digitalWrite(inLed,0);
}



#endif /* INCLUDE_CATRACA_CATRACA_H_ */
