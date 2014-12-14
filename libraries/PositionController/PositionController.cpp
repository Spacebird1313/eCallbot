/*
  PositionController.cpp - Library for the position controllers of the E-callbot,
  developed for the Arduino Mega with Parallax Position Controller Kit.
  Note: this library uses the serial 3 ports (pin 14 - 15) of the Arduino Mega.
  Created by Jan Huijghebaert & Thomas Huybrechts - 07/12/2014
 */
 
#include "Arduino.h"
#include "PositionController.h"

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

/*
  INFO FOR CONVERSION FUNCTIONS
  Diameter wheel = 0,1238 meter so
  Outline wheel = 0,3889 meter
*/
  int Num_Pos_Wheelrevolution = 1080;  	  //30*36 (gearbox and position wheels)
  double Outline_Wheel = 0.3889;          //Formula outline 
  double Outline_On_Position = 0.00036;   //0.3889/1080

void PositionControllerInit(void)
{
	//Initialise Serial3
	extern HardwareSerial Serial3;
	Serial3.begin(19200);			//Transceiver for the position controllers
}

//Get the position of a wheel
int getPosition(byte Wheel)
{
  int Result; 
  Result = sendToEncoder(QPOS, Wheel, 0);
  return Result;
}

//Get speed of a wheel
int getSpeed(byte Wheel) 
{
  int Result; 
  Result = sendToEncoder(QSPD, Wheel, 0);
  return Result;
}

//Check arrival
//Tolerance: 0 - 255 (0 = exact, 255 = inaccurate)
int checkArrival(byte Wheel, int Tolerance)
{
  int Result; 
  Result = sendToEncoder(CHFA, Wheel, Tolerance);
  return Result;
}

//Translate # positions of encoder wheel
int translateXEncoderPositions(byte Wheel, int encoderPositions)
{
  int Result; 
  Result = sendToEncoder(TRVL, Wheel, encoderPositions);
  return Result;
}

//Reset position
void resetPosition(byte Wheel)
{
  sendToEncoder(CLRP, Wheel, 0);
}

//Reverse turn direction
void reverseTurndirection(byte Wheel)
{
  sendToEncoder(SREV, Wheel, 0);
}

//Set transmit delay encoder
void setTransmitDelay(byte Delay)
{
  sendToEncoder(STXD, 0, Delay);
}

//Set maximum speed
//Speed range from 0 to 65535
void setMaxSpeed(byte Wheel, int Speed)
{
  sendToEncoder(SMAX, Wheel, Speed);
}

//Set speed (ramp rate)
//Ramp rate must be between 0 and 65535
void setRampRate(byte Wheel, byte RampRate)
{
  sendToEncoder(SSRR, Wheel, RampRate);
}

//Send data to the encoder and receive information back when needed
int sendToEncoder(byte Command, byte Address, int Parameter)
{
  //Variables
  int Num_Bytes_Write; 
  int Num_Bytes_Read;
  int Num_Bytes_Queue;
  byte Output_Buffer[4];
  byte Input_Buffer[4];
  int Received_Data;
  
  //Bytes to send
  Output_Buffer[0] = 0;
  Output_Buffer[1] = 0;
  Output_Buffer[2] = 0;
  Output_Buffer[3] = 0;
  
  Output_Buffer[0] = Command + Address;
  
  Serial3.flush();
  
  // Commands
  if(Command == QPOS) 
  {
    Num_Bytes_Write = 1;
    Num_Bytes_Read = 2;
  }
  else if(Command == QSPD)
  {
    Num_Bytes_Write = 1;
    Num_Bytes_Read = 2;
  }
  else if(Command == CHFA) 
  {
    Num_Bytes_Write = 2;
    Num_Bytes_Read = 1;
    Output_Buffer[1] = byte(Parameter);
  }
  else if(Command == TRVL) 
  {
    Num_Bytes_Write = 3;
    Num_Bytes_Read = 0;
    Output_Buffer[1] = byte(Parameter / 256);  //High byte
    Output_Buffer[2] = byte(Parameter);        //Low byte
  }
  else if(Command == CLRP) 
  {
    Num_Bytes_Write = 1;
    Num_Bytes_Read = 0;
  }
  else if(Command == SREV) 
  {
    Num_Bytes_Write = 1;
    Num_Bytes_Read = 0;
  }
  else if(Command == STXD)
  {
    Num_Bytes_Write = 2;
    Num_Bytes_Read = 0;
    Output_Buffer[1] = byte(Parameter);
  }
  else if(Command == SMAX)
  {
    Num_Bytes_Write = 3;
    Num_Bytes_Read = 0;
    Output_Buffer[1] = byte(Parameter / 256);  //High byte
    Output_Buffer[2] = byte(Parameter);        //Low byte
  }
  else if(Command == SSRR) 
  {
    Num_Bytes_Write = 2;
    Num_Bytes_Read = 0;
    Output_Buffer[1] = byte(Parameter);
  }
  
  noInterrupts();
  //Send data
  for (int i=0; i < Num_Bytes_Write; i++)
  {
     Serial3.write(Output_Buffer[i]);
  }
  interrupts();
  
  //To get a stable transaction, take a short break
  delay(100);
  
  //Some bytes in the queue
  //Warning! There will be a echo request from the Tx pin in the queue
  //Drop first received byte
  Num_Bytes_Queue = Serial3.available();  
  
  //Read received bytes
  for(int i = 0; i < Num_Bytes_Queue; i++)
  {
    Input_Buffer[i] = Serial3.read();
  }
  
  //Return results
  if(Num_Bytes_Read == 0) 
  {
    Received_Data = 0;
  }
  else if(Num_Bytes_Read == 1) 
  {
    Received_Data = Input_Buffer[Num_Bytes_Queue - 1];
  }
  else if(Num_Bytes_Read == 2) 
  {
    Received_Data = (256 * Input_Buffer[Num_Bytes_Queue - 2]) + Input_Buffer[Num_Bytes_Queue - 1];
  }
  
  return Received_Data;    
}

//Conversion of speed (to m/s)
//Received value = #positions/0.5sec
double Conv_Speed(int value) 
{
  double Result = value * 2;
  Result = Outline_On_Position * Result;
  return Result;
}

//Conversion of position (to m)
double Conv_Position(int value)
{
  double Result = Outline_On_Position * value;
  return Result;
}