#include <Motordriver.h>
#include <PositionController.h>
//#include <PingSensor.h>

volatile float _translocationL;
volatile float _translocationR;
volatile float _positionL;
volatile float _positionR;
volatile int _correctionMode;
int _direction;
int _speed;
char state;
int speed = 10;
byte byte1 = B1000;
int byte2 = 0;
byte byte3 = B1000;

void moveStraightCommand(int speedStraight, int directionStraight)
{
  _correctionMode = 0x00;
  
  //Reset position controllers
  resetPosition(Wheel_Both);
  
  if(directionStraight == 0)
  {
    _direction = 1;
  }
  else
  {
    _direction = -1;
  }
  
  _speed = speedStraight/10.2;
  
  setMotor(_direction * _speed);
  
  //Activate position controller interrupt
  TIMSK1 |= (1 << OCIE1B); //Output compare portB interrupt - OCIE1B: enabled
}

void stopCommand()
{
  //Deactive position controller interrupt
  TIMSK1 &= ~(1 << OCIE1B);
  setMotor(0);
}

void moveDistanceCommand(float translocation, float rotation, int distanceSpeed)
{
  _correctionMode = 0x01;
  _speed = speedStraight/10.2;
  
  //Reset position controllers
  resetPosition(Wheel_Both);
  
  _translocationL = translocation*0.1;
  _translocationR = translocation*0.1;
  
  noInterrupts();
  
  //Get current counter value
  int CurrentCount = TCNT1;
  int PulsValue = 500;      //20 ms (prescaler: 64)
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
  
  if(translocation >= 0)
  {
    _direction = 1;
    setMotor(_speed);
  }
  else
  {
    _direction = -1;
    setMotor(-_speed);
  }
  
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
  
  if(_correctionMode == 0x01)
  {
    if(_translocationL > 0)
    {
      if(_positionL >= _translocationL)
      {
        positionLReached = true;
        setMotorL(0);
      }
    }
    else
    {
      if(_positionL <= _translocationL)
      {
        positionLReached = true;
        setMotorL(0);
      }
    }
    
    if(_translocationR > 0)
    {
      if(_positionR >= _translocationR)
      {
        positionRReached = true;
        setMotorR(0);
      }
    }
    else
    {
      if(_positionR <= _translocationR)
      {
        positionRReached = true;
        setMotorR(0); 
      }
    }
    
    if(positionLReached && positionRReached)
    {
      //Translation completed
      setMotor(0);
    }
  }
  
  //if(_correctionMode == 0x00)
  {
    difference = _positionL - _positionR;
    
    if(difference < 0)
    {
      difference = -difference;
    }
    
    if(difference > 0.10)
    {
      if(_direction * _positionL < _direction * _positionR)
      {
        if(positionRReached == false)
        {
          setMotorR((_direction * _speed)/2);
        }  
      }
      else
      {
        if(positionLReached == false)
        {
          setMotorL((_direction * _speed)/2);
        }
      }
    }
    else
    {
      if(positionLReached == false)
      {
        setMotorL((_direction * _speed));
      }
      if(positionRReached == false)
      {
        setMotorR((_direction * _speed));
      } 
    }
  }
  
  /*
  if(_correctionMode == 0x01)
  {
    if(_translocationL > 0)
    {
      if(_positionL >= _translocationL)
      {
        positionLReached = true;
        setMotorL(0);
      }
    }
    else
    {
      if(_positionL <= _translocationL)
      {
        positionLReached = true;
        setMotorL(0);
      }
    }
    
    if(_translocationR > 0)
    {
      if(_positionR >= _translocationR)
      {
        positionRReached = true;
        setMotorR(0);
      }
    }
    else
    {
      if(_positionR <= _translocationR)
      {
        positionRReached = true;
        setMotorR(0); 
      }
    }
    
    if(positionLReached && positionRReached)
    {
      //Translation completed
      setMotor(0);
    }
  }
  */
  
  //if(positionLReached && positionRReached)
  //{
    //Deactive position controller interrupt
    //TIMSK1 &= ~(1 << OCIE1B);
    
    //Translation completed
    //setMotor(0);
  //}
  //else
  //{
    //Get current counter value
    int CurrentCount = TCNT1;
    int PulsValue = 750;      //30 ms (prescaler: 64)
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
  //}
}

void setup()
{
  noInterrupts();
  
  //Correction mode
  //0x00: Both wheels equal distance
  //0x01: Predefined distance stop
  _correctionMode = 0x00;
  
  _direction = 1;       //Move forward
  
  _speed = 10;          //Initial speed
  
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

int teller = 0;

void loop()
{
  state = ' ';
  if(Serial1.available() > 0)
  {
    state = Serial1.read();
  }
  
  if(state == 'z')
  {
    Serial.println("Command Z read");
    moveDistanceCommand(10.0, 0.0); 
  }
  
  if(state == 's')
  {
    Serial.println("Command S read");
    moveDistanceCommand(-10.0, 0.0);
  }
  
  if(state == 'q')
  {
    Serial.println("Command Q read");
    moveStraightCommand(140, 0);
  }
  
  if(state == 'd')
  {
    Serial.println("Command D read");
    moveStraightCommand(80, 1);
  }
  
  if(state == 'a')
  {
    stopCommand();
    Serial.println("STOP");
  }
  
  if(teller >= 9999)
  {
    teller = 0;
    Serial.println(_direction);
    Serial.println(_speed);
    Serial.println(_positionL);
    Serial.println(_positionR);
    //Serial.println(Conv_Position(getPosition(Wheel_Left)));
  }
  else
  {
    teller = teller + 1;
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
