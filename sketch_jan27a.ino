#include <Adafruit_SSD1306.h>
#include <SimpleDHT.h>

#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 180

//Right motor
int enableRightMotor=9;
int rightMotorPin1=8;
int rightMotorPin2=7;

//Left motor
int enableLeftMotor=3;
int leftMotorPin1=2;
int leftMotorPin2=4;


 int TrigPin = 11;
 int EchoPin = 12;
 int Time;
 int Distance;
 int RealDistance;
 int Stop;




void setup()
{
  //This sets frequecny as 7812.5 hz.
  TCCR0B = TCCR0B & B11111000 | B00000010 ;

  Serial.begin(9600);
  
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   

  pinMode(13, OUTPUT);
  pinMode(10, INPUT);
}


void loop()
{

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  digitalWrite(13, HIGH);

  if(digitalRead(10) == LOW){

     digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  Time = pulseIn(EchoPin, HIGH);
  Distance = Time /29 /2;

  if(Distance > 0){
    RealDistance = Distance;
  }
  if(RealDistance < 12){
    Stop = 1;
  }
  else{
    Stop = 0;
  }

    //If none of the sensors detects black line, then go straight
  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW && Stop == 0)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW && Stop == 0)
  {
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED); 
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH && Stop == 0)
  {
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED); 
  } 
  //If both the sensors detect black line, then stop 
  else 
  {
    rotateMotor(0, 0);
  }

  }
  else if(digitalRead(10) == HIGH){
    if(Serial.available() > 0){
    int data = Serial.read();
    
    switch(data){
      case 119:
      rotateMotor(MOTOR_SPEED,MOTOR_SPEED);
      break;

      case 100:
      rotateMotor(MOTOR_SPEED,-MOTOR_SPEED);
      break;

      case 115:
     rotateMotor(-MOTOR_SPEED,-MOTOR_SPEED);
      break;

      case 97:
      rotateMotor(-MOTOR_SPEED,MOTOR_SPEED);
      break;

     case 120:
      rotateMotor(0,0);
      break;


    }
    }
  }
  

 

}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
