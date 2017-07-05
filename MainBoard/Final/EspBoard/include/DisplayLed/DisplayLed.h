/*
 * DisplayLed.h
 *
 *  Created on: 19/06/2017
 *      Author: rober
 */

#ifndef INCLUDE_DISPLAYLED_DISPLAYLED_H_
#define INCLUDE_DISPLAYLED_DISPLAYLED_H_

class DisplayLed {
public:
	DisplayLed();
	void write(unsigned int data);
	int verification;
};

#endif /* INCLUDE_DISPLAYLED_DISPLAYLED_H_ */
