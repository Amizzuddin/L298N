/*This program test the output of L298N driver through Serial communication. The purpose of this example	*
 *is to eliminate too many wiring just to perform a test of motor driver and how vehicle behaves.			*/

#include <L298N.h>

L298N Hbridge(2,4,5,7,3,6);		//input pin	order(en1,en2,en3,en4,enA,enB)

unsigned long wait_time = 0;
int m_speed[2]={0};				//memory store the last change speed
int m_direction = 0;			//memory store the last change direction

void setup() {
  Serial.begin(9600);										//To initiate Serial communication
  while(!Serial);
  Serial.write("Ready to test L298N driver!\n");			// send message on serial coommunication device.
  Serial.flush();											//Ensure all data have been transmitted.
}

void loop() {
	int motor=0;											//pointere to access m_speed elements
	char c;													//A temp storage to read a single byte from rx buffer 
	
	do{
		if(!Serial.available()){
			Serial.write("Kindly enter motor direction (from 0 to 15): ");
		}
		while(!Serial.available());							//Do nothing until received data from serial
		c = Serial.read();
		if(Serial.peek() == -1){							//only hold first and last data received
			wait_time = millis();
		}
		while(millis() - wait_time <= 2); 				
		if( !isDigit(c) ){
			if( c != '\n' || c != '\r' ){
				Serial.write(c);
				Serial.write(", Invalid input! Try again\n");
			}
			while(Serial.available()){
				Serial.read(); 								//to flush out garbage input
			}
		}
		if( isDigit(c) ){
			m_direction = (m_direction * 10) + (c & B1111);
			if(!Serial.available()){						//Check input after read all serial data
				if(	m_direction < 0 || m_direction >15){
					Serial.print(m_direction);
					Serial.write(", Out of value range entered! Try again!\n");
					m_direction = 0;
				}
				else{
					break;
				}
			}
		}
	}while( true );
	Serial.println(m_direction);
	do{
		if(!Serial.available() && motor == 0 ){
			Serial.write("Kindly enter speed for motor 1 (from 0 to 255): ");
		}
		if(!Serial.available() && motor == 1 ){
			Serial.write("Kindly enter speed for motor 2 (from 0 to 255): ");
		}
		while(!Serial.available());							//Do nothing until received data from serial
		c = Serial.read();
		if(Serial.peek() == -1){							//only hold first and last data received
			wait_time = millis();
		}
		while(millis() - wait_time <= 2); 				
		if( !isDigit(c) ){
			if( c != '\n' || c != '\r' ){
				Serial.write(c);
				Serial.write(", Invalid input! Try again\n");
			}
			while(Serial.available()){
				Serial.read(); 								//to flush out garbage input
			}
		}
		if( isDigit(c) ){
			m_speed[motor] = (m_speed[motor] * 10) + (c & B1111);
			if(!Serial.available()){						//Check input after read all serial data
				if(	m_speed[motor] < 0 || m_speed[motor] >255){
					Serial.print(m_speed[motor]);
					Serial.write(", Out of value range entered! Try again!\n");
				}
				else{
					Serial.println(m_speed[motor]);
					motor++;
				}
			}
		}
	}while( motor <= 1 );
	Hbridge.drive_motor(m_direction, m_speed);				//Send the inputs to L298N motor driver
	Serial.write("motor 1 speed: ");
	Serial.print(m_speed[0]);
	Serial.write(",motor 2 speed: ");
	Serial.print(m_speed[1]);
	Serial.write("\n");
	Serial.write("Motor is going ");
	switch (m_direction){
		case 0: case 3: case 12: case 15: Serial.write("STOP position"); break;
		case 1: case 13: Serial.write("REV CLOCKWISE radial turn"); break;
		case 2: case 14: Serial.write("FWD ANTI-CLOCKWISE radial turn"); break;
		case 4: case 7: Serial.write("REV ANTI-CLOCKWISE radial turn"); break;
		case 5: Serial.write("REVERSE"); break;
		case 6: Serial.write("ANTI-CLOCKWISE spin"); break;
		case 8: case 11: Serial.write("FWD CLOCKWISE radial turn"); break;
		case 9: Serial.write("CLOCKWISE spin"); break;
		case 10: Serial.write("FORWARD"); break;
	}
	Serial.write("\t");
	if(m_speed[0] != m_speed[1]){
		Serial.write("NOTE: ");
		if( m_direction == 6 || m_direction == 9 ){
			Serial.write("vehicle will not spin at one spot");
		}
		if( m_direction == 5 || m_direction == 10 ){
			if( m_speed[0] > m_speed[1] ){
				Serial.write("vehicle will veer to the right");
			}
			if( m_speed[0] < m_speed[1] ){
				Serial.write("vehicle will veer to the left");
			}
		}
		Serial.write("\n");		
	}
	else{
		Serial.write("\n");
	}
}
