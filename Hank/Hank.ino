/*
 * Hank
 * Contributors: Leonardo Munoz
 * Version 0.0
 */

#include "SimpleRSLK.h"
#include "QTRSensors.h"
#include <stdio.h>

#define LED RED_LED
#define LED2 GREEN_LED

const int leftCollLED = 4;
const int rightCollLED = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  pinMode(leftCollLED, OUTPUT);
  pinMode(rightCollLED, OUTPUT);
  setupRSLK();

  delay(4000);
  enableMotor(BOTH_MOTORS);
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
  setMotorSpeed(BOTH_MOTORS,30);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED2, HIGH); 
  for(int x = 0;x<6;x++)
    {
          if(isBumpSwitchPressed(x) == true){
            if (x >= 3){leftCollision(x);}
            else if (x <= 2){rightCollision(x);}
          }
      }
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);
  setMotorSpeed(BOTH_MOTORS,30);
}

void leftCollision(int bumperSwitch){
  digitalWrite(LED2, LOW);
  digitalWrite(leftCollLED, HIGH);
  digitalWrite(LED, HIGH);
  setMotorSpeed(BOTH_MOTORS, 0);
  delay(1000);
  switch (bumperSwitch){
    case 3:
      handleCollisionResolve(15, 0);
      break;
    case 4:
      handleCollisionResolve(10, 0);
      break;
    case 5:
      handleCollisionResolve(6, 0);
      break;
  }
  
}

void handleCollisionResolve(int movementSpeed, int collisionSide){
   if (collisionSide == 0){ //leftCollision
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_BACKWARD);
    setMotorSpeed(RIGHT_MOTOR, movementSpeed); //changes direction.
    setMotorSpeed(LEFT_MOTOR, movementSpeed);
    delay(2400);
    setMotorSpeed(BOTH_MOTORS,0);
    delay(1000);
    digitalWrite(LED, LOW);
    digitalWrite(leftCollLED, LOW);
    digitalWrite(LED2, HIGH);
   }
  else if (collisionSide == 1){
    setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_FORWARD);
    setMotorDirection(LEFT_MOTOR,MOTOR_DIR_BACKWARD);
    setMotorSpeed(LEFT_MOTOR, movementSpeed); //changes direction.
    setMotorSpeed(RIGHT_MOTOR, movementSpeed);
    delay(2400);
    setMotorSpeed(BOTH_MOTORS,0);
    delay(1000);
    digitalWrite(LED, LOW);
    digitalWrite(rightCollLED, LOW);
    digitalWrite(LED2, HIGH);
  }
}

void rightCollision(int bumperSwitch){
  digitalWrite(LED2, LOW);
  digitalWrite(rightCollLED, HIGH); 
  digitalWrite(LED, HIGH);
  setMotorSpeed(BOTH_MOTORS, 0);
  delay(1000);
  switch (bumperSwitch){
    case 2:
      handleCollisionResolve(15, 1);
      break;
    case 1:
      handleCollisionResolve(10, 1);
      break;
    case 0:
      handleCollisionResolve(6, 1);
      break;
  }
  
}
