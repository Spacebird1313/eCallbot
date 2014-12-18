/*
  AUTEUR: Oliver Nyssen
  BESCHRIJVING: Code voor de correcte vertaling van de commando's om de motoraansturing correct te bedienen
*/

#include <Arduino.h>
#include <Motordriver.h>
#include <code_positiecontrollers_JanHuijghebaert.h>
#include <Aansturing.h>


// NIEUWE LIBRARY
// globale Variabelen

byte byte1 = B1000;		// eerste variabele die je moet gebruiken.
int int1;
int int2;
int int3;

/*
void setup()																							
{
  MotordriverInit();        //Initialise the motordriver on Pin 22

}*/

void translateCommand()
{   
  if(Serial.available() > 7)
  {
    byte1 = Serial.read();
    if(StartOfMessage(byte1) == true )
    {
      //Read LEN and CMD
      int i = 0;
      while (i < 1)
      {
        if(Serial.available()>7)
        {
			int1 = Serial.read()-'0';
			i = i++;
		}
		else
        {
		//Wait for buffer to fill LEN message
		}
      }
      while(i < 2)
      {
         if(Serial.available() > 7)
         {
           int2 = Serial.read()-'0';
           i = i++;
         }
         else
         {
           //Wait for buffer to fill CMD-ID message
         }
      }
      InputCommand(int1, int2);
    }
    else
    {
      // Wait for start of frame
    }
  }
}

boolean StartOfMessage(byte sof)
{
  if(sof == 0xAA)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void InputCommand(int LEN, int CMD)
{
  //counter for input
  int i = 0;
  //len variable for amount of input bytes to come
  int j = LEN - 1;
	
  if(j == 0)
  {
    //Generate BCC
  }
  else if(j == i)
  {
    //if(CMD == 0x01)
	if(CMD == 1)
    {
      //MoveCommand(byte1, byte2);
	  MoveCommand(int1, int2);
      i++;
    }
    //else if(CMD == 0x02)
	else if(CMD == 2)
    {
      //TurnOnSpotCommand(byte1, byte2);
	  TurnOnSpotCommand(int1, int2);
      i++;
    }
    //else if(CMD == 0x03)
	else if(CMD == 3)
    {
      //TurnCommand(byte1, byte2, byte3);
	  TurnCommand(int1, int2, int3);
      i++;
    }
    //else if(CMD == 0x04)
	else if(CMD == 4)
    {
      //Stop command
      stopCommand();
      i++;
    }
    //else if(CMD == 0x06)
	else if(CMD == 6)
    {
      //SpeedChange(byte1, byte2);
	  SpeedChange(int1, int2);
      i++;
    }
		else if(CMD == 7)
    {
	  MoveDistance(int1, int2, int3);
      i++;
    }
    else
    {
			
    }
    j = -1;
  }
  else if(j = 1)
  {
    //Read first variable
    if(Serial.read() > 7)
    {
      int1 = Serial.read()-'0';
      i++;
    }
  }
  else if(j == 2)
  {
    //Read second variable
    if(Serial.read() > 7)
    {
      int2 = Serial.read()-'0';
      i++;
    }
  }
  else if(j == 3 )
  {
    //Read thirth variable
    if(Serial.read() > 7)
    {
		int3 = Serial.read()-'0';
		i++;
    }
  }
  else
  {
    //End command
  }

// MoveStraightForward(Speed, Direction) 
void MoveCommand (int snelheid, int richting) {
	if (richting == 0){
		setMotor(snelheid);
	}
	else {
		setMotor(-snelheid);
	}
}

// intersection turn (Speed, Direction)             het ter plaatste draaien
void TurnOnSpotCommand (int snelheid, int richting) {
    // links draaien
    if (richting == 0) {
		setMotorL(-snelheid);
		setMotorR(snelheid);
    }
    // rechts draaien
    else if (richting == 1){
		setMotorL(snelheid);
		setMotorR(-snelheid);
    }
    else {
		// do nothing
    }
}

void TurnCommand (int hoek, int snelheid, int richting) {

	// resetten van de positiecontrollers
	resetPosition(0x00);
	
	// wensen te draaien over een bepaalde hoek. 1 wiel omwenteling komt overeen met 90 graden en 1 omwenteling is 1080 posities 
	// 1 graad = 12 posities
	boolean turned = false;
	
	//links draaien
	if (richting == 0) {
		setMotorL(0);
		setMotorR(snelheid);
		while (turned == false){ 
			if (getPosition(0x01) == 12*hoek) {
				turned = true;
			}
			else {
				// moet niets gedaan worden.
			}
		}
		// draaien onder zoveel graden is uitgevoerd, dus motor volledig stilzetten.
		setMotor(0);
	}
	// rechts draaien
    else if (richting == 1){
		setMotorL(snelheid);
		setMotorR(0);
		while (turned == false){ 
			if (getPosition(0x01) == 12*hoek) {
				turned = true;
			}
			else {
				// moet niets gedaan worden.
			}
		}
		// draaien onder zoveel graden is uitgevoerd, dus motor volledig stilzetten.
		setMotor(0);
    }
    else {
		// do nothing
    }
}

void SpeedChange (int targetspeed, int inc) {
		
		// TODO, met timer werken
		

}

void MoveDistance (int snelheid, int richting, int afstand) {


	// TODO, doorverwijzen naar commando van Thomas

}