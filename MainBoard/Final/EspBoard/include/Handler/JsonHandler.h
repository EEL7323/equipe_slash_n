/*
 * JsonHandler.h
 *
 *  Created on: 05/06/2017
 *      Author: rober
 */

#ifndef INCLUDE_JSONHANDLER_H_
#define INCLUDE_JSONHANDLER_H_

#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <string>
#include "Services/ArduinoJson/include/ArduinoJson.h"
#include "Catraca/Catraca.cpp"


//Interrupt não pode ser feito diretamente para um método de um objeto
//Solução encontrada é usar uma função secundária, que chama o método depois
void DispatchInterruptEntrada();
void DispatchInterruptSaida();
Catraca catraca;


class JsonHandler{
public:
	JsonHandler();
	void handleData(char* data, TcpClient& client);
	void addTestDatabase();
private:
	unsigned int lastUpdateTime;
};


#endif /* INCLUDE_JSONHANDLER_H_ */
