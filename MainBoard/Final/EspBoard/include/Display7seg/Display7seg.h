/*
 * Display7seg.h
 *
 *  Created on: 19/06/2017
 *      Author: rober
 */

#ifndef INCLUDE_DISPLAY7SEG_H_
#define INCLUDE_DISPLAY7SEG_H_



class Display7seg {
public:
	Display7seg(char D, char SH, char ST);
	void writeDisplay(char n);
private:
	 unsigned char DATAPIN, SHPIN, STPIN;
	 char display[10];
	 void shift74ch595(char data);
};

#endif /* INCLUDE_DISPLAY7SEG_H_ */
