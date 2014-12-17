#include <Motordriver.h>
#include <PositionController.h>
//#include <PingSensor.h>

volatile float _translocationL;
volatile float _translocationR;
volatile float _positionL;
volatile float _positionR;
volatile int _correctionMode;
volatile int _speedL;
volatile int _speedR;
char state;
int speed = 10;

//speedStraight: range 0-255
//directionStraight: 0x00 - forwards
//                   0x01 - backwards
void moveStraightCommand(int speedStraight, int directionStraight)
{
  int directionMove = 0;
  _correctionMode = 0x00;
  
  //Reset position controllers
  resetPosition(Wheel_Both);
  
  if(directionStraight == 0)
  {
    directionMove = 1;
  }
  else
  {
    directionMove = -1;
  }
  
  _speedL = directionMove * (speedStraight/10.2);
  _speedR = _speedL;
  
  setMotor(_speedL);
  
  //Activate position controller interrupt
  TIMSK1 |= (1 << OCIE1B); //Output compare portB interrupt - OCIE1B: enabled
}

//turnSpeed: range 0-255
//turnDirection: 0x00 - counter-clockwise
//               0x01 - clockwise
void turnCommand(int turnSpeed, int turnDirection)
{
  _correctionMode = 0x02;
  
  if(turnDirection == 0x00)
  {
    turnDirection = 1;
  }
  else
  {
    turnDirection = -1;
  }
  
  _speedL = (turnSpeed/10.2) * (-turnDirection);
  _speedR = (turnSpeed/10.2) * turnDirection;
 
  setMotorL(_speedL);
  setMotorR(_speedR);
}

void stopCommand()
{
  //Deactive position controller interrupt
  TIMSK1 &= ~(1 << OCIE1B);
  setMotor(0);
}

//translocation: X * 10.0cm
//rotation: x degrees
//distanceSpeed: range 0-255
void moveDistanceCommand(float translocation, int rotation, int distanceSpeed)
{
  float rotationL = 0;
  float rotationR = 0;
  int directionMove = 0;
  int travelSpeed = 0;
  
  //Reset position controllers
  resetPosition(Wheel_Both);
  
  if(translocation >= 0)
  {
    directionMove = 1;
  }
  else
  {
    directionMove = -1;
  }
  
  travelSpeed = directionMove * (distanceSpeed/10.2);
  
  if(rotation > 0)
  {
    _correctionMode = 0x02;
    rotationL = rotation * (Outline_Wheel/90);
    _speedL = travelSpeed;
    _speedR = travelSpeed/2; 
  }
  else if(rotation < 0)
  {
    _correctionMode = 0x02;
    rotationR = rotation * (Outline_Wheel/90);
    _speedR = travelSpeed;
    _speedL = travelSpeed/2;
  }
  else
  {
    _correctionMode = 0x01;
    _speedL = travelSpeed;
    _speedR = travelSpeed;
  }
  
  _translocationL = translocation*0.1 + rotationL;
  _translocationR = translocation*0.1 + rotationR;
  
  noInterrupts();
  
  //Get current counter value
  int CurrentCount = TCNT1;
  int PulsValue = 6250;      //25 ms (prescaler: 64)
  int NewCounter = 0;
 
  //Check for overflow timer
  if(0xFFFF - CurrentCount < PulsValue)
  {
    NewCounter = PulsValue - (0XFFFF - CurrentCount) - 1;	//New interrupt value when overflow occures
  }
  else
  {
    NewCounter = CurrentCount + PulsValue;		        //New interrupt value when no overflow occures
  }
  
  OCR1B = NewCounter;      //Compare value
  
  //Activate position controller interrupt
  TIMSK1 |= (1 << OCIE1B); //Output compare portB interrupt - OCIE1B: enabled
  
  setMotorL(_speedL);
  setMotorR(_speedR);
  
  interrupts();
}

//Interrupt vector timer 1: position controller communication
ISR(TIMER1_COMPB_vect)
{  
  _positionL = Conv_Position(getPosition(Wheel_Left));
  _positionR = Conv_Position(getPosition(Wheel_Right));
  boolean positionLReached = false;
  boolean positionRReached = false;
  float difference = 0;
  float correctionDifference = 0.06;     //Difference between wheels before correction
  float errorDifference = 0.3;           //Difference between wheels before error stop
  int speedL = _speedL;
  int speedR = _speedR;
  
  if(_correctionMode < 0x02)
  {
    difference = _positionL - _positionR;
    
    if(difference < 0)
    {
      difference = -difference;
    }
    
    if(difference > errorDifference)      //Difference between to large - shutdown procedure
    {
      errorPositionControl();
      return;
    }
    else if(difference > correctionDifference)
    {
      if(abs(_positionL) < abs(_positionR))
      {
        speedR = _speedR/2;
        speedL = _speedL; 
      }
      else
      {
        speedL = _speedL/2;
        speedR = _speedR;
      }
    }
    else
    {
      speedL = _speedL;
      speedR = _speedR;
    }
  }
  
  if(_correctionMode > 0x00)
  {
    if(_translocationL > 0)
    {
      if(_positionL >= _translocationL)
      {
        speedL = 0;
      }
    }
    else
    {
      if(_positionL <= _translocationL)
      {
        speedL = 0;
      }
    }
    
    if(_translocationR > 0)
    {
      if(_positionR >= _translocationR)
      {
        speedR = 0;
      }
    }
    else
    {
      if(_positionR <= _translocationR)
      {
        speedR = 0;
      }
    }
    
    if(speedR == 0 && speedL == 0)
    {
      //Translation completed
      stopCommand();
    }
  }
  
  setMotorL(speedL);
  setMotorR(speedR);
  
  noInterrupts();
  
  //Get current counter value
  int CurrentCount = TCNT1;
  int PulsValue = 6250;      //25 ms (prescaler: 64)
  int NewCounter = 0;
 
  //Check for overflow timer
  if(0xFFFF - CurrentCount < PulsValue)
  {
    NewCounter = PulsValue - (0XFFFF - CurrentCount) - 1;	//New interrupt value when overflow occures
  }
  else
  {
    NewCounter = CurrentCount + PulsValue;		        //New interrupt value when no overflow occures
  }
  
  OCR1B = NewCounter;      //Compare value
  
  interrupts();
}

void errorPositionControl()
{
  Serial.println("Position controllers has reported an error: wheels are blocked.");
  stopCommand();
  Serial.println(Conv_Position(getPosition(Wheel_Left)));
  Serial.println(Conv_Position(getPosition(Wheel_Right)));
  errorBlinkLed();
}

void errorBlinkLed()
{
  //Pinmode declarations
  DDRB |= (1<<(DDB7));     //Set pin 13 (error-LED) output
  
  //Blink three times
  for(int i = 0; i < 3; i++)
  {
    //Turn LED pin high
    PORTB = (PORTB | 0X80);
    
    delay(500);
    
    //Turn LED pin low
    PORTB = (PORTB & 0X7F);
    
    delay(500);
  }
}

void setup()
{
  noInterrupts();
  
  //Correction mode
  //0x00: Both wheels equal distance
  //0x01: Predefined distance stop equal distance
  //0x02: Predefined distance stop not equal distance
  _correctionMode = 0x00;
  
  _speedL = 0;
  _speedR = 0;
  
  //Timer 1: interrupts timer (Normal - Prescaler (64))
  TCCR1A = 0;              //Waveform: Normal  
  TCCR1B = 0;              //Waveform - Normal + prescaler off (timer off)
  TCNT1 = 0;               //Reset timer
  
  MotordriverInit();                    //Initialise the motordriver on Pin 22
  PositionControllerInit();             //Initialise the position controllers on Pin 14, 15
  reverseTurndirection(Wheel_Right);    //Change turn direction right wheel (clock wise: positive)
  
  //PingSensorInit();             //Initialise the ping sensors on Pin 48, 50, 52
  
  //Initialise Serial1
  Serial1.begin(57600);          //Bluetooth transceiver port (pin 18 - 19)
  
  Serial.begin(9600);
  
  interrupts();
  
  //Timer 1 on
  TCCR1B |= (1 << CS11) | (1 << CS10);  //Counter on - CS11 + CS10: prescaler (64)
}

void loop()
{
  state = ' ';
  if(Serial1.available() > 0)
  {
    state = Serial1.read();
  }
  
  if(state == 'z')
  {
    Serial.println("Command forward");
    moveStraightCommand(80, 0);
  }
  
  if(state == 's')
  {
    Serial.println("Command backward");
    moveStraightCommand(80, 1);
  }
  
  if(state == 'q')
  {
    turnCommand(80, 1);
  }
  
  if(state == 'd')
  {
    turnCommand(80, 0);
  }
  
  if(state == '1')
  {
    Serial.println("Command 1m forward");
    moveDistanceCommand(10.0, 0, 120);
  }
  
  if(state == '2')
  {
    Serial.println("Command 1m backward");
    moveDistanceCommand(-10.0, 0, 120);
  }
  
  if(state == '3')
  {
    Serial.println("Command 1m turn 90° left forward");
    moveDistanceCommand(10.0, 90, 120);
  }
  
  if(state == '4')
  {
    Serial.println("Command 1m turn 90° right forward");
    moveDistanceCommand(10.0, -90, 120);
  }
  
  if(state == '5')
  {
    Serial.println("Command do a barrelrol, 2m turn 360° left forward");
    moveDistanceCommand(20.0, 360, 120);
  }
  
  if(state == '6')
  {
    Serial.println("Command 1m turn 180° left backwards");
    moveDistanceCommand(-10.0, 180, 120);
  }
  
  if(state == 'a')
  {
    stopCommand();
    Serial.println("STOP");
  }
  
  
  
  
  
  
  
  
  
  
  /*
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
	  byte2 = Serial.read()-'0';
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
           byte3 = Serial.read();
           i = i++;
         }
         else
         {
           //Wait for buffer to fill CMD-ID message
         }
      }
      InputCommand(byte2, byte3);
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

void InputCommand(int LEN, byte CMD)
{
  //counter for input
  int i = 0;
  //len variable for amount of input bytes to come
  int j = LEN;
  j = j-1;
	
  if(j == 0)
  {
    //Generate BCC
  }
  else if(j == i)
  {
    if(CMD == 0x01)
    {
      //MoveCommand(byte1, byte2);
      i++;
    }
    else if(CMD == 0x02)
    {
      //TurnOnSpotCommand(byte1, byte2);
      i++;
    }
    else if(CMD == 0x03)
    {
      //TurnCommand(byte1, byte2, byte3);
      i++;
    }
    else if(CMD == 0x04)
    {
      //Stop command
      stopCommand();
      i++;
    }
    else if(CMD == 0x05)
    {
      //SpeedChange(byte1, byte2);
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
      byte1 = Serial.read();
      i++;
    }
   }
   else if(j == 2)
   {
     //Read second variable
     if(Serial.read() > 7)
     {
       byte2 = Serial.read();
       i++;
     }
    }
    else if(j == 3 )
    {
      //Read thirth variable
      if(Serial.read() > 7)
      {
        byte3 = Serial.read();
	i++;
      }
    }
    else
    {
      //End command
    }
    */
}
