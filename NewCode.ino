#include <L298NX2.h>

 L298N LeftMotor(3,2,4);
 L298N RightMotor (9,8,7);

 
int ManualMode;
 int ManualModeButtonPin = 10;

int LeftIRSensorPin = 5;
 int RightIRSensorPin = 6;

 int TrigPin = 11;
 int EchoPin = 12;
 int Time;
 int Distance;
 int RealDistance;
 int Stop;

  void MoveFront(){
 
  
  RightMotor.forward();
  LeftMotor.forward();
  }  
  

void MoveBack(){


  RightMotor.backward();
  LeftMotor.backward();
}

void MoveLeft(){
 

  LeftMotor.backward();
  RightMotor.forward();
 }

void MoveRight(){

 
  RightMotor.backward();
  LeftMotor.forward();
}

void StopMotors(){
  RightMotor.stop();
  LeftMotor.stop();
}
void setup() {
  Serial.begin(9600);

  TCCR0B = TCCR0B & B11111000 | B00000010 ;

  pinMode(5, INPUT);
  pinMode(6,INPUT);

   pinMode(TrigPin, OUTPUT);
 pinMode(EchoPin, INPUT);

 pinMode(10, INPUT);
 pinMode(13, OUTPUT);

}

void loop() {
  digitalWrite(13, HIGH);

  if(digitalRead(ManualModeButtonPin) == HIGH){
    ManualMode = 1;
  }
  else{
    ManualMode = 0;
  }

  if(ManualMode == 0){
  LeftMotor.setSpeed(70);
  RightMotor.setSpeed(70);

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

  if(Stop == 1){
    StopMotors();
  }
  else if(Stop == 0 ){
  if(digitalRead(LeftIRSensorPin) == LOW && digitalRead(RightIRSensorPin) == LOW){
  MoveFront();
 }
 if(digitalRead(LeftIRSensorPin) == HIGH && digitalRead(RightIRSensorPin) == LOW){
  
  MoveLeft();
 }
 if(digitalRead(LeftIRSensorPin) == LOW && digitalRead(RightIRSensorPin) == HIGH){
  
  MoveRight();
 }
 if(digitalRead(LeftIRSensorPin) == HIGH && digitalRead(RightIRSensorPin) == HIGH){
  StopMotors();
  }
  }
  }
  else if(ManualMode == 1){
  LeftMotor.setSpeed(100);
  RightMotor.setSpeed(100);
  if(Serial.available() > 0){
    int data = Serial.read();
    
    switch(data){
      case 119:
     MoveFront();
      break;

      case 100:
      MoveRight();
      break;

      case 115:
      MoveBack();
      break;

      case 97:
      MoveLeft();
      break;

     case 120:
      StopMotors();
      break;


    }
  }
  }




}
