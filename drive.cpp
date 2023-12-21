#include "Arduino.h" 
#include <L298NX2.h>
#include "drive.h"

/*

NOTES

 -- ground pin on arduino must tie to motor power source negative terminal

*/

/**
 * EN (enable) pins, which enable speed control via PWM,
 * must utilize PWM capable pins.
 *
 * On UNO PWM output is possible on digital I/O pins 
 * 3, 5, 6, 9, 10 and 11 (via analogWrite call to set duty cycle).
 *
 * IN (input) pins, control motor activation and direction,
 * can use any digital pins.
 *
 */

 // FRONT MOTORS
const int FRONT_EN_A = 3;
const int FRONT_IN1_A = 2;
const int FRONT_IN2_A = 4;
const int FRONT_IN3_B = 6;
const int FRONT_IN4_B = 7;
const int FRONT_EN_B = 5;

// REAR MOTORS
const int REAR_EN_A = 9;
const int REAR_IN1_A = 8;
const int REAR_IN2_A = 10;
const int REAR_IN3_B = 12;
const int REAR_IN4_B = 13;
const int REAR_EN_B = 11;

L298NX2 frontMotors(
  FRONT_EN_A, 
  FRONT_IN1_A, 
  FRONT_IN2_A, 
  FRONT_EN_B, 
  FRONT_IN3_B, 
  FRONT_IN4_B
);

L298NX2 rearMotors(
  FRONT_EN_A, 
  FRONT_IN1_A, 
  FRONT_IN2_A, 
  FRONT_EN_B, 
  FRONT_IN3_B, 
  FRONT_IN4_B
);

void Drive::setup()
{
  Serial.begin(9600);
  frontMotors.setSpeed(80);
}

void Drive::forward() {
  frontMotors.forward();
  Serial.println("forward we go");
}

