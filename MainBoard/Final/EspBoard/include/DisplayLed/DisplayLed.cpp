/*
 * DisplayLed.cpp
 *
 *  Created on: 19/06/2017
 *      Author: rober
 */

#include "DisplayLed.h"

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;




static const int led1 = D0;
static const int led2 = D1;
static const int led3 = D2;
static const int led4 = D3;
static const int led5 = D4;
static const int led6 = D5;

static const int inLed = D8;


DisplayLed::DisplayLed() {
	pinMode(led1,0x1);
	pinMode(led2,0x1);
	pinMode(led3,0x1);
	pinMode(led4,0x1);
	pinMode(led5,0x1);
	pinMode(led6,0x1);
	pinMode(inLed,0x1);

	digitalWrite(led1,0);
	digitalWrite(led2,0);
	digitalWrite(led3,0);
	digitalWrite(led4,0);
	digitalWrite(led5,0);
	digitalWrite(led6,0);
	digitalWrite(inLed,0);

	verification = 0;

}

void DisplayLed::write(unsigned int data){

	data = (data % 64); //Para evitar data > 64
	verification = data;

	digitalWrite(led1,0);
	digitalWrite(led2,0);
	digitalWrite(led3,0);
	digitalWrite(led4,0);
	digitalWrite(led5,0);
	digitalWrite(led6,0);


	if( (data&0x0001) != 0){
		digitalWrite(led1,1);
	}
	if( (data>>1)&0x1 != 0){
		digitalWrite(led2,1);
	}
	if( (data>>2)&0x1 != 0){
		digitalWrite(led3,1);
	}
	if( (data>>3)&0x1 != 0){
		digitalWrite(led4,1);
	}
	if( (data>>4)&0x1 != 0){
		digitalWrite(led5,1);
	}
	if( (data>>5)&0x1 != 0){
		digitalWrite(led6,1);
	}


	Serial.print("%%%%%%%%%%%%%%%% Turned leds on with n: ");
	Serial.println(data);



}
