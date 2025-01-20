#include <L298NX2.h>


int ManualMode;
 int ManualModeButtonPin = 10;
 int BluetoothCommand;

 //IR Sensor stuff
 int LeftIRSensorPin = 5;
 int RightIRSensorPin = 6;

 //Motors
 L298N LeftMotor(3,2,4);
 L298N RightMotor (9,8,7);

//Ultrasonic sensor stuff
 int TrigPin = 11;
 int EchoPin = 12;
 int Time;
 int Distance;
 int RealDistance;
 int Stop;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  pinMode(5, INPUT);
  pinMode(6,INPUT);

  pinMode(TrigPin, OUTPUT);
 pinMode(EchoPin, INPUT);

  pinMode(ManualModeButtonPin, INPUT);
 
}

 
  void MoveFront(){
  RightMotor.forward();
  LeftMotor.forward();
  }  
  

void MoveBack(){
  RightMotor.backward();
  LeftMotor.backward();
}

void MoveLeft(){
  RightMotor.forward();
 }

void MoveRight(){
  LeftMotor.forward();
}

void StopMotors(){
  RightMotor.stop();
  LeftMotor.stop();
}

void loop() {

   LeftMotor.setSpeed(255);
  RightMotor.setSpeed(255);

  digitalWrite(13, HIGH);

 ManualMode = digitalRead(ManualModeButtonPin);
 
 if(ManualMode != HIGH){
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

  if(Stop == 0){
     if(digitalRead(LeftIRSensorPin) == LOW && digitalRead(RightIRSensorPin) == LOW){
  MoveFront();
 }
 if(digitalRead(LeftIRSensorPin) == HIGH && digitalRead(RightIRSensorPin) == LOW){
  LeftMotor.stop();
  MoveLeft();
 }
 if(digitalRead(LeftIRSensorPin) == LOW && digitalRead(RightIRSensorPin) == HIGH){
  RightMotor.stop();
  MoveRight();
 }
 if(digitalRead(LeftIRSensorPin) == HIGH && digitalRead(RightIRSensorPin) == HIGH){
  StopMotors();
  }

 
 }
 }
 else{
  if(Serial.available()>0){
    int data = Serial.read();
    if(data != 13 && data != 10){
      BluetoothCommand = data;
      Serial.println(BluetoothCommand);
    }
      else{
        BluetoothCommand = 0;
      }
      if(BluetoothCommand = 49){
        MoveFront();
      }
      if(BluetoothCommand= 50){
        MoveBack();
      }
      if(BluetoothCommand = 51){
        MoveLeft();
      }
      if(BluetoothCommand = 52){
        MoveRight();
      }
      if(BluetoothCommand= 0){
        StopMotors();
      }
    }
  }
 }
 
 
 

  

 

    
 
  

  


