/*
  Motordriver.h - Library for the motordriver of the E-callbot,
  developed for the Arduino Mega with Parallax HB-25.
  Note: this library uses timer1 and pin 22 (motor signal) of the Arduino Mega.
  Created by Thomas Huybrechts - 10/11/2014
 */
 
#ifndef Motordriver_h
#define Motordriver_h

#include "Arduino.h"

extern volatile int _speedLeft;
extern volatile int _speedRight;
extern volatile int _commandPulsSection;
	
void MotordriverInit(void);
void setMotorL(int speed);		//Set left motor speed and direction (range: -25 - 25)
void setMotorR(int speed);		//Set left motor speed and direction (range: -25 - 25)
void setMotor(int speed);		//Set both motor speed and direction (range: -25 - 25)
int getMotorL(void);			//Get the current speed of the left motor
int getMotorR(void);			//Get the current speed of the right motor
void motorPulsGeneration(void);

#endif
     