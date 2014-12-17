/*
  Motordriver.cpp - Library for the motordriver of the E-callbot,
  developed for the Arduino Mega with Parallax HB-25.
  Note: this library uses timer1 Compare Register A and pin 22 (motor signal) of the Arduino Mega.
  Created by Thomas Huybrechts - 10/11/2014
 */
 
#include "Arduino.h"
#include "Motordriver.h"

volatile int _speedLeft;
volatile int _speedRight;
volatile int _commandPulsSection;

void MotordriverInit(void)
{
	//Initialise parameters
	_speedLeft = 375;
	_speedRight = 375;
	
	//Pinmode declarations
	DDRA |= (1<<(DDA0));     //Set pin 22 (motor driver communication) output
	
	//Turn motor communication pin low
	PORTA = (PORTA & 0XFE);
	
	//Timer 1 CompA: motor driver communication	
	TIMSK1 |= (1 << OCIE1A); //Output compare portA interrupt - OCIE1A: enabled
	OCR1A = 0;               //Compare value

	//Start motor driver communication
	_commandPulsSection = 0;
}

//Set left motor speed and direction (range: -25 - 25)
void setMotorL(int speed)
{
	_speedLeft = 375 - (5 * speed); 
}

//Set right motor speed and direction (range: -25 - 25)
void setMotorR(int speed)
{
	_speedRight = 375 - (5 * speed);
}

//Set both motor speed and direction (range: -25 - 25)
void setMotor(int speed)
{
	_speedLeft = 375 - (5 * speed);
	_speedRight = 375 - (5 * speed);
}

//Get the current speed of the left motor
int getMotorL(void)
{
	return _speedLeft;
}

//Get the current speed of the right motor
int getMotorR(void)
{
	return _speedRight;
}

//Interrupt vector timer 1: motor driver communication
ISR(TIMER1_COMPA_vect)
{
	motorPulsGeneration();
}

/* Output compare register values
// Time     Ticks
//   1ms  -  250    (Forwards)
// 1.5ms  -  375    (Stop)
//   2ms  -  500    (Backwards)
// 1.1ms  -  275    (Hold off 1)
// 5.25ms -  1315.5 (Hold off 2)
*/
void motorPulsGeneration(void)
{
	noInterrupts();
	
	//Get current counter value
	int CurrentCount = TCNT1;
	int PulsValue = 0;
	int NewCounter = 0;
	
	if(_commandPulsSection == 0)
	{
		PulsValue = _speedLeft; 		//Compare value - Puls 1 (left)
	}
	else if(_commandPulsSection == 1)
	{
		PulsValue = 275;           		//Compare value - Hold off 1 (1.1 ms)
	}
	else if(_commandPulsSection == 2)
	{
		PulsValue = _speedRight;   		//Compare value - Puls 2 (right)
	}
	else if(_commandPulsSection == 3)
	{
		PulsValue = 1313;      			//Compare value - Hold off 2 (5.25 ms - minimum)
		PulsValue = PulsValue + 1187;	//Extra hold off time (10 ms before new message)
	}
	
	//Check for overflow timer
	if(0xFFFF - CurrentCount < PulsValue)
	{
		NewCounter = PulsValue - (0XFFFF - CurrentCount) - 1;	//New interrupt value when overflow occures
	}
	else
	{
		NewCounter = CurrentCount + PulsValue;					//New interrupt value when no overflow occures
	}

	_commandPulsSection = _commandPulsSection + 1;

	if(_commandPulsSection == 4)
	{
		_commandPulsSection = 0;
	}
	
	OCR1A = NewCounter;		   	   	  //Set new counter value for next interrupt
	PORTA = (PORTA & 0XFE) | (~(PORTA & 0x01));  //Toggle motor communication pin
	
	interrupts();
}
 
 