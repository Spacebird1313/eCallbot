/*
  PingSensor.cpp - Library for the ping sensors of the E-callbot,
  developed for the Arduino Mega with Parallax Ping Sensor.
  Note: this library uses timer1 Compare Register C and the pins 48, 50, 52 (ping sensors) of the Arduino Mega.
  Created by Jan Huijghebaert & Thomas Huybrechts - 07/12/2014
 */
 
#include "Arduino.h"
#include "PingSensor.h"

volatile int _pingPulsSection;
volatile float pingDistanceL;
volatile float pingDistanceM;
volatile float pingDistanceR;

void PingSensorInit(void)
{
	//Start ping sensor calculation
	_pingPulsSection = 0;
	
	//Set pins to output
	setPinmodePingSensors(1);
	
	//Timer 1 CompC: pingsensor timer
	TIMSK1 |= (1 << OCIE1C);  //Output compare portA interrupt - OCIE1C: enabled
	OCR1C = 500;              //Compare value (start delay)
	
	//Set prescaler (256) - timer 4 on
	//TCCR4B |= (1 << CS41);                //Counter on - CS41: prescaler (256)
}

//Interrupt vector timer 4: pingsensor timer
ISR(TIMER1_COMPC_vect)
{
	pingsensorPulsGeneration();
}

//Change pinmode of pingsensor pins
//Pinmode (0: Input, 1: Output)
void setPinmodePingSensors(int PinMode)
{
	DDRL = (DDRL & 0XFD) | (PinMode << 1);     //Set pin 48 (pingsensor: Left) (L1)
	DDRB = (DDRB & 0XF7) | (PinMode << 3);     //Set pin 50 (pingsensor: Middle) (B3)
	DDRB = (DDRB & 0XFD) | (PinMode << 1);     //Set pin 52 (pingsensor: Right) (B1)
}

//Set pinvalue of pingsensor pins
//Value (0: Low, 1: High)
void setValuePingSensors(int value)
{
	PORTL = (PORTL & 0XFD) | (value << 1);     //Set value pin 48 (pingsensor: Left) (PL1)
	PORTB = (PORTB & 0XF7) | (value << 3);     //Set value pin 50 (pingsensor: Middle) (PB3)
	PORTB = (PORTB & 0XFD) | (value << 1);     //Set value pin 52 (pingsensor: Right) (PB1)
}

/* Output compare register values
//   Time       Ticks
//   2micros  -  4    (Wait 1)
//   5micros  -  10   (Wait 2)
*/
void pingsensorPulsGeneration()
{
	  //Get current counter value
	int CurrentCount = TCNT1;
	int stepTime = 0;
	int NewCounter = 0;
	
	  if(_pingPulsSection == 0)
	  {
		setPinmodePingSensors(1);      //Set pinmode to output
		setValuePingSensors(0);        //Set pins low to ensure stable activation
		stepTime = 16;                 //Compare value - Wait (2 micros)
	  }
	  else if(_pingPulsSection == 1)
	  {
		setValuePingSensors(1);        //Set pins high to active the measurement
		stepTime = 40;                 //Compare value - Wait (5 micros)
	  }
	  else if(_pingPulsSection == 2)
	  {
		setValuePingSensors(0);        //Set pins low to end measurement
		setPinmodePingSensors(0);      //Set pinmode to input
		stepTime = 99999999;                 //Compare value - Wait (5 micros)
	  }
	  
	  //Check for overflow timer
	  if(0xFFFF - CurrentCount < stepTime)
	  {
		NewCounter = stepTime - (0XFFFF - CurrentCount) - 1;	//New interrupt value when overflow occures
	  }
	  else
	  {
		NewCounter = CurrentCount + stepTime;					//New interrupt value when no overflow occures
	  }
	  
	  _pingPulsSection = _pingPulsSection + 1;
	  
	  if(_pingPulsSection == 3)
	  {
		_pingPulsSection = 0;
	  }
	  
	  OCR1C = NewCounter;		   	   	//Set new counter value for next interrupt
}

//Conversion from time (microseconds) to distance (centimeter)
float microSecToCentimeter(float microseconds)
{
	//Speed of sound is 340.29 m/s or 29 microseconds per centimeter
	//Signal travels back and forth and needs an integer division by 2
	return microseconds / 29 / 2;
}