/*
 * Display7seg.cpp
 *
 *  Created on: 19/06/2017
 *      Author: rober
 */

#include "Display7seg.h"

//Segmentos e-d-g-f-a-b-c-p
#define n0 0b11011110
#define n1 0b00000110
#define n2 0b11101100
#define n3 0b01101110
#define n4 0b00110110
#define n5 0b01111010
#define n6 0b11111010
#define n7 0b00001110
#define n8 0b11111110
#define n9 0b00111110

#define TIME 2

Display7seg::Display7seg(char D, char SH, char ST) {
	char aux[10] = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9};
	for(int i=0;i<=9;i++){
		display[i] = aux[i];
	}
	DATAPIN = D;
	SHPIN = SH;
	STPIN = ST;
	pinMode(DATAPIN, 0x1); //0x1 == output
	pinMode(DATAPIN, 0x1);
	pinMode(DATAPIN, 0x1);

}



void Display7seg::writeDisplay(char n){
    int i=0,j=0;
	i = n/10;
	j= n%10;
	shift74ch595(display[j]);
	shift74ch595(display[i]);
}

void Display7seg::shift74ch595(char data){
	char i,ch;
		(STPIN,0);

		for(i=0;i<8;i++){
			ch = data >> i;
			ch = ch & 0x01;
			digitalWrite(DATAPIN,ch);
			delayMicroseconds(TIME);
			digitalWrite(SHPIN,1);
			delayMicroseconds(TIME);
			digitalWrite(SHPIN,0);
			delayMicroseconds(TIME);
		}

		digitalWrite(STPIN,1);
		delayMicroseconds(TIME);
		digitalWrite(STPIN,0);
}
