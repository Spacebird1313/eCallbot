/*
  PingSensor.h - Library for the ping sensors of the E-callbot,
  developed for the Arduino Mega with Parallax Ping Sensor.
  Note: this library uses timer4 and the pins 48, 50, 52 (ping sensors) of the Arduino Mega.
  Created by Jan Huijghebaert & Thomas Huybrechts - 07/12/2014
 */
 
 #ifndef PingSensor_h
 #define PingSensor_h
 
 #include "Arduino.h"
 
 extern volatile int _pingPulsSection;
 extern volatile float pingDistanceL;
 extern volatile float pingDistanceM;
 extern volatile float pingDistanceR;
 
 void PingSensorInit(void);
 void setPinmodePingSensors(int PinMode);	 		 //Change pinmode of pingsensor pins - Pinmode (0: Input, 1: Output)
 void setValuePingSensors(int value); 		 		 //Set pinvalue of pingsensor pins - Value (0: Low, 1: High)
 void pingsensorPulsGeneration();			 		 //Generate pulses to control ping sensors
 float microSecToCentimeter(float microseconds);	 //Conversion from time (microseconds) to distance (centimeter)
 
 #endif