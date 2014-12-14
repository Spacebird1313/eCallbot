/*
  PositionController.cpp - Library for the position controllers of the E-callbot,
  developed for the Arduino Mega with Parallax Position Controller Kit.
  Note: this library uses the serial 3 ports (pin 14 - 15) of the Arduino Mega.
  Created by Jan Huijghebaert & Thomas Huybrechts - 07/12/2014
 */
 
#ifndef PositionController_h
#define PositionController_h

#include "Arduino.h"

//Define variables
#define QPOS         0x08            //Get position
#define QSPD         0x10            //Get speed
#define CHFA         0x18            //Check arrival
#define TRVL         0x20            //Translate X positions of encoder wheel
#define CLRP         0x28            //Reset position
#define SREV         0x30            //Reverse orientation turn direction
#define STXD         0x38            //Set delay Tx encoder
#define SMAX         0x40            //Set maximum speed
#define SSRR         0x48            //Set speed (ramp rate)
#define Wheel_Left   0x01            //Set address of left wheel
#define Wheel_Right  0x02            //Set address of right wheel
#define Wheel_Both   0x00            //Set address of both wheels

extern int Num_Pos_Wheelrevolution;
extern double Outline_Wheel;
extern double Outline_On_Position;

void PositionControllerInit(void);
int getPosition(byte Wheel);										//Get the position of a wheel
int getSpeed(byte Wheel);											//Get speed of a wheel
int checkArrival(byte Wheel, int Tolerance); 						//Check arrival - Tolerance: 0 - 255 (0 = exact, 255 = inaccurate)
int translateXEncoderPositions(byte Wheel, int encoderPositions);	//Translate # positions of encoder wheel
void resetPosition(byte Wheel);										//Reset position
void reverseTurndirection(byte Wheel);								//Reverse turn direction
void setTransmitDelay(byte Delay);									//Set transmit delay encoder
void setMaxSpeed(byte Wheel, int Speed);							//Set maximum speed - Speed range from 0 to 65535
void setRampRate(byte Wheel, byte RampRate);						//Set speed (ramp rate) - Ramp rate must be between 0 and 65535
int sendToEncoder(byte Command, byte Address, int Parameter);		//Send data to the encoder and receive information back when needed
double Conv_Speed(int value);										//Conversion of speed (to m/s) - Received value = #positions/0.5sec
double Conv_Position(int value);									//Conversion of position (to m)

#endif
     