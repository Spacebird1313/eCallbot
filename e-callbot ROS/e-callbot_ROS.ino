#include <Motordriver.h>
#include <PositionController.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

volatile float _translocationL;
volatile float _translocationR;
volatile float _positionL;
volatile float _positionR;
volatile int _correctionMode;
volatile int _speedL;
volatile int _speedR;
char state;
int speed = 8;

//ROS node declarations
ros::NodeHandle nodeHandle;

void twistCommand(const geometry_msgs::Twist& msg)
{
  float translocation = (msg.linear.x);  //unit translation equals 0.1m
  float rotation = (msg.angular.z);
  float rotationL = 0;
  float rotationR = 0; 
  int travelSpeed = 0;
  _correctionMode = 0x00;
  
  //Reset position controllers
  resetPosition(Wheel_Both);
  
  if(translocation >= 0)
  {
    travelSpeed = speed;
  }
  else
  {
    travelSpeed = -speed;
  }
  
  _translocationL = translocation*0.1 + rotation/57 * (Outline_Wheel/90);
  _translocationR = translocation*0.1 + rotation/57 * (Outline_Wheel/90);
  
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

void stopCommand()
{
  //Deactive position controller interrupt
  TIMSK1 &= ~(1 << OCIE1B);
  setMotor(0);
}

//Interrupt vector timer 1: position controller communication
ISR(TIMER1_COMPB_vect)
{  
  _positionL = Conv_Position(getPosition(Wheel_Left));
  _positionR = Conv_Position(getPosition(Wheel_Right));
  float difference = 0;
  float correctionDifference = 0.03;     //Difference between wheels before correction
  float errorDifference = 0.5;           //Difference between wheels before error stop
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
        _speedL = 0;
      }
    }
    else
    {
      if(_positionL <= _translocationL)
      {
        speedL = 0;
        _speedL = 0;
      }
    }
    
    if(_translocationR > 0)
    {
      if(_positionR >= _translocationR)
      {
        speedR = 0;
        _speedR = 0;
      }
    }
    else
    {
      if(_positionR <= _translocationR)
      {
        speedR = 0;
        _speedR = 0;
      }
    }
    
    if(speedR == 0 && speedL == 0)
    {
      //Translation completed
      stopCommand();
      return;
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

void speedCommand(const std_msgs::Int16& msg)
{
  speed = msg.data;
}

void errorPositionControl()
{
  stopCommand();
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

//ROS subscriptions
ros::Subscriber<geometry_msgs::Twist> twistSub("/eCallBot/cmd_vel", &twistCommand);
ros::Subscriber<std_msgs::Int16> speedSub("/eCallBot/cmd_speed", &speedCommand);

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
  
  nodeHandle.initNode();      //Initialise ROS node
  
  nodeHandle.subscribe(twistSub);    //Initialise subscribe topics
  nodeHandle.subscribe(speedSub);
  
  interrupts();
  
  //Timer 1 on
  TCCR1B |= (1 << CS11) | (1 << CS10);  //Counter on - CS11 + CS10: prescaler (64)
}

void loop()
{
  nodeHandle.spinOnce();
  delay(100);  
}
