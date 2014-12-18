/*
  AUTEUR: Oliver Nyssen
  BESCHRIJVING: header file de correcte vertaling van de commando's om de motoraansturing correct te bedienen
*/
 
#ifndef Aansturing_h
#define Aansturing_h

#include <Arduino.h>
#include <Motordriver.h>
#include <code_positiecontrollers_JanHuijghebaert.h>

byte byte1 = B1000;		// eerste variabele die je moet gebruiken.
int int1;
int int2;
int int3;
	
void translateCommand();				// gaat nakijken de code vertalen, waarbij SOF, LEN en CMD-ID worden ingelezen.
boolean StartOfMessage(byte sof); 		// gaat na of de SOF token correct is. indien 0xAA, return true
void InputCommand(int LEN, int CMD);	// gaat de juiste informatie uit de datavelden inlezen en die doorgeven naar de juiste methode voor verdere uitwerking.
void MoveCommand (int snelheid, int richting); 		// gaat motoren juist instellen om vooruit te bewegen
void TurnOnSpotCommand (int snelheid, int richting);	// ter plaatse draaien.
void TurnCommand (int hoek, int snelheid, int richting); 		// draaien over een bepaalde hoek
void SpeedChange (int targetspeed, int inc);		//verander de snelheid waarmee de robot vooruit rijdt
void MoveDistance (int snelheid, int richting, int afstand)			// laat de robot vooruitrijden over een bepaalde afstand

#endif
     