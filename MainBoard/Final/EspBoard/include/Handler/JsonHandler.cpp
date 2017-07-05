/*
 * JsonHandler.cpp
 *
 *  Created on: 05/06/2017
 *      Author: rober
 */

#include "JsonHandler.h"

//GPIO descrito em DisplayLed.cpp
#define ENTRADA D6 //GPIO D6
#define SAIDA D7   //GPIP D7

void DispatchInterruptEntrada(){
	catraca.interruptEntrada();
}

void DispatchInterruptSaida(){
	catraca.interruptSaida();
}


JsonHandler::JsonHandler(){
	Serial.println("%%%%%%%%%%%% Created Handler");
	lastUpdateTime = 0;
	//Setup catraca
	attachInterrupt(ENTRADA, DispatchInterruptEntrada,FALLING);
	attachInterrupt(SAIDA, DispatchInterruptSaida,FALLING);
}

void JsonHandler::handleData(char* data, TcpClient& client){
	DynamicJsonBuffer jsonBuffer;
	JsonArray& rootArray = jsonBuffer.parseArray(data);
	JsonObject& root = rootArray[0];


	if (!root.success()) {
		Serial.println("parseObject() failed");
		return;
	}


	String responseType = root["ThereIs"];


	if(responseType == "Aluno"){
		JsonArray& alunos = rootArray[1];
		int howMuch = root["HowMuch"];
		for(int n=0;n<howMuch;n++){
			int matr = alunos[n]["Matricula"];
			float credCard = alunos[n]["creditsCard"];
			float credMobile = alunos[n]["creditsMobile"];
			Serial.printf("%%%%%%Aluno recebido. Matricula: %d, CreditoCard: %f, CreditoMobile: %f \n", matr, credCard, credMobile);
			catraca.arvore.inserirNodo(matr,credCard,credMobile);
		}

	}


	else if(responseType == "WhatDoYouWant"){
			DynamicJsonBuffer ResJsonBuffer;
			JsonObject& root = ResJsonBuffer.createObject();

			unsigned int currentTime = millis();
			if(currentTime - lastUpdateTime > 3000){
				root["IWant"] = "rAluno";
				root["Matricula"] = 0;
				lastUpdateTime = currentTime;
			}
			else{
				root["ThereIs"] = "IWant";
				root["IWant"] = "nothing";
			}

			String jsonString;
			root.printTo(jsonString);
			jsonString = "["+jsonString+"]";

			client.sendString(jsonString,false);
			Serial.print("%%%%%%%%%%%%%%%% Sending: ");
			Serial.println(jsonString);

		}



	 else if(responseType == "getUpdates"){

				Serial.println("%%%%%%%%%%%% Getting update");

				StaticJsonBuffer<2048> jsonBuffer;
				JsonArray& res = jsonBuffer.createArray();
				JsonObject& cab = res.createNestedObject();
				JsonArray& lista = res.createNestedArray();

				int size = catraca.listaEntrada.size;
				cab["IWant"] = "updateAlunos";

				if(size <= 4){
					cab["HowMuch"] = size;
					cab["allAlunos"] = "true";
					for(int i=0;i<size;i++){
						int matr, credType;
						//matr e credType passados por referência
						catraca.listaEntrada.getHead(matr,credType);
						JsonObject& obj = lista.createNestedObject();
						obj["matricula"] = matr;
						if(credType == 0){
							obj["credit"] = "card";
						}
						else{
							obj["credit"] = "mobile";
						}
						lista[i] = obj;
					}
				}
				else{
					cab["HowMuch"] = 4;
					cab["allAlunos"] = "false";
					for(int i=0;i<4;i++){
					int matr, credType;
					//matr e credType passados por referência
					catraca.listaEntrada.getHead(matr,credType);
					JsonObject& obj = lista.createNestedObject();
					obj["matricula"] = matr;
					if(credType == 0){
						obj["credit"] = "card";
					}
					else{
						obj["credit"] = "mobile";
					}
					lista[i] = obj;
					}

				}

					String jsonString;
					res.printTo(jsonString);

					Serial.print("%%%%%%%%%%%% Lista de entrada: ");
					Serial.println(jsonString);
					delayMilliseconds(100);
					client.sendString(jsonString,true);
					delayMilliseconds(100);
	 }




	else if(responseType == "LEDs"){
		int matr = root["Matricula"];
		int leds = root["LEDs"];
		bool success = false;;

		DynamicJsonBuffer ResJsonBuffer;
		JsonObject& resp = ResJsonBuffer.createObject();
		resp["ThereIs"] = "Feedback";
		resp["youTry"] = "enterRU";

		AlunoNode* aluno = catraca.arvore.findNodo(matr);
		if(aluno != 0){
			float cred = aluno->getCreditoMobile();
			if(cred>1.5){
				success = catraca.entradaMobile(matr, leds);
				if(success == true){
					aluno->setCreditoMobile(cred-1.5);
					catraca.listaEntrada.addEntry(matr,1);
					Serial.printf("Entrada do aluno %d via mobile \n",matr);
					resp["Acknowledge"] = "noError";
					resp["ErrorText"] = "";
				}
				else{
					Serial.println("Autentificacao errada");
					resp["Acknowledge"] = "error";
					resp["ErrorText"] = "verificationError";
				}
			}
			else{
				Serial.printf("Não ( há creditos suficientes / verification errada ) no aluno %d \n", matr);
				resp["Acknowledge"] = "error";
				resp["ErrorText"] = "noCredit";
			}
		}
		else{
			Serial.println("Aluno nao encontrado no banco de dados local");
			resp["Acknowledge"] = "error";
			resp["ErrorText"] = "notOnDatabase";
		}


		String jsonString;
		resp.printTo(jsonString);
		//TODO FIX THIS GAMBIARRA
		jsonString = "["+jsonString+"]";

		client.sendString(jsonString,false);
		Serial.print("%%%%%%%%%%%%%%%% Sending: ");
		Serial.println(jsonString);



	}



	else if(responseType == "getOcupacao"){
		int ocupacao = catraca.getOcupacao();
		Serial.printf("%%%%%%%%%%%%%%%% GetOcupacao: %d \n",ocupacao);
		DynamicJsonBuffer ResJsonBuffer;
		JsonObject& root = ResJsonBuffer.createObject();

		root["ThereIs"] = "ocupacaoRU";
		root["ocupacao"] = ocupacao;

		String jsonString;
		root.printTo(jsonString);
		jsonString = "["+jsonString+"]";
		client.sendString(jsonString,false);
		Serial.print("%%%%%%%%%%%%%%%% Sending: ");
		Serial.println(jsonString);
	}


	 else if(responseType == "updateSingle"){
		int matr = root["info"][0];
		int cred = root["info"][1];
		Serial.printf("%%%%%%%%%%%% Tipo update single. Matricula: %d, Credito: %d \n",matr,cred);
		catraca.arvore.inserirNodo(matr,cred, 0); // Mobile = 0
		}

	else if(responseType == "updateMult"){
		int size = root["size"];
		Serial.printf("%%%%%%%%%%%% Tipo: update multiplos, size: %d \n ",size);
		for(int i=0;i<size;i++){
			int matr = root["students"][i]["matr"];
			int cred = root["students"][i]["cred"];
			catraca.arvore.inserirNodo(matr,cred,0); //Credito mobile = 0

		}
	}

		else if(responseType == "setVerification"){
			int verification = root["verification"];
			Serial.printf("%%%%%%%%%%%%%%%% Setting verification: %d \n ",verification);
			catraca.setVerification(verification);
		}

	else if (responseType == "printABB"){
		catraca.arvore.imprimirABB();
	}






	else if(responseType == "openCatraca"){
		Serial.println("%%%%%%%%%%%%%% Open catraca da entrada");
		catraca.openCatracaEntrada();
	}






	else if(responseType == "changePrice"){
		int price = root["price"];
		catraca.setPrecoRU(price);
		Serial.printf("%%%%%%%%%%%%%%%% Novo preço RU: %d \n",price);
	}





	else if(responseType == "printHeapSize"){
	    Serial.printf("%%%%%%%%%%% Free Heap: %d \n",system_get_free_heap_size());
	}




	else {
		Serial.println("%%%%%%%%%%%%%%%% ResponseType não encontrado");
	}
	Serial.println("\n\n\n");
}


void JsonHandler::addTestDatabase(){
	for(int i=1000;i<=1050;i++){
			catraca.arvore.inserirNodo(i,i%5, i%15);
			Serial.printf("%%%%%% Free Heap: %d \n",system_get_free_heap_size());
			delayMilliseconds(10);
		}
	catraca.arvore.inserirNodo(14101350,123, 14);
	catraca.arvore.inserirNodo(14101336,10, 3);
	catraca.arvore.inserirNodo(14101345,100, 34);

}




