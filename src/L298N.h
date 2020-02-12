/************************************************************************************************************************
 * This program is design for RACE curicullum                                                                  *
 * 1) Encoder wheel, 1 rotation = 20 ticks = 21cm = 210mm                                                                  *
 * 2)                                                 *
 * **********************************************************************************************************************/
/*L298N(Motor Driver) Library for arduino, Created by Amizzuddin, Nov 08 2019*/

#ifndef L298N_H
#define L298N_H

#include "Arduino.h"

class L298N{
 public:
    /********************************************************
     *         en1              Motor A input pin 1         *
     *         en2              Motor A input pin 2         *
     *         enA              Motor A enable pin          *
     *         en3              Motor B input pin 1         *
     *         en4              Motor B input pin 2         *
     *         enB              Motor B enable pin          * 
     ********************************************************/
    L298N(byte en1, byte en2, byte en3, byte en4, byte enA, byte enB);

    /********************************************************
     * Initialize the pinMode of the L298N inputs           *
     ********************************************************/
    void initialize();

    /********************************************************
     * Commands to send to L298N H-bridge                   *
     ********************************************************/
    void drive_motor(byte direction, byte motor1_pwm, byte motor2_pwm);

 private:
    byte _en[6] ;
};

#endif