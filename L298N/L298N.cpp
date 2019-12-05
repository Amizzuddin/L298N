/*L298N(Motor Driver) Library for arduino, Created by Amizzuddin, Nov 08 2019*/

#include "Arduino.h"
#include "L298N.h"

L298N::L298N(int en1, int en2, int en3, int en4, int enA, int enB){
    //make it clear that the variables is private
	_en[0]= en1;
	_en[1]= en2;
	_en[2]= en3;
	_en[3]= en4;
	_en[4]= enA;
	_en[5]= enB;
    
	//Set the following pin as OUTPUT
	for(register int i=0; i < 6; i++){
		pinMode(_en[i], OUTPUT);
	}
}

void L298N::drive_motor(int direction, int speed[]){
	for(int i=0; i < 6; i++){
		if( i < 4){
			digitalWrite(_en[i], direction & B0001);
			direction = direction >> 1;
		}
		else{
			analogWrite(_en[i], speed[i-4]);
		}
	}
}