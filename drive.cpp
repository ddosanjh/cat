#include "Arduino.h" 
#include <L298N.h>
#include "drive.h"

/**
 * On UNO PWM output is possible on digital I/O pins 
 * 3, 5, 6, 9, 10 and 11.
 */

const unsigned int FRONT_LEFT_EN = 3;
const unsigned int FRONT_LEFT_IN1 = 2;
const unsigned int FRONT_LEFT_IN2 = 4;

const unsigned int FRONT_RIGHT_IN3 = 7; /* switched to match direction */
const unsigned int FRONT_RIGHT_IN4 = 6; /* switched to match direction */
const unsigned int FRONT_RIGHT_EN = 5;

const unsigned int REAR_LEFT_EN = 9;
const unsigned int REAR_LEFT_IN1 = 8;
const unsigned int REAR_LEFT_IN2 = 10;

const unsigned int REAR_RIGHT_IN3 = 13; /* switched to match direction */
const unsigned int REAR_RIGHT_IN4 = 12; /* switched to match direction */
const unsigned int REAR_RIGHT_EN = 11;

L298N motors[] = {
  L298N(FRONT_LEFT_EN, FRONT_LEFT_IN1, FRONT_LEFT_IN2),
  L298N(FRONT_RIGHT_EN, FRONT_RIGHT_IN3, FRONT_RIGHT_IN4),
  L298N(REAR_LEFT_EN, REAR_LEFT_IN1, REAR_LEFT_IN2),
  L298N(REAR_RIGHT_EN, REAR_RIGHT_IN3, REAR_RIGHT_IN4)
};


void Drive::setup() {
    for (int motor = FRONT_LEFT; motor <= REAR_RIGHT; motor++) {
      motors[motor].setSpeed(SPEED_MAX);
    }
}

void Drive::forward(int durationMs){

  for (int motor = FRONT_LEFT; motor <= REAR_RIGHT; motor++) {
    motors[motor].forward();
  }

  delay(durationMs);

  for (int motor = FRONT_LEFT; motor <= REAR_RIGHT; motor++) {
    motors[motor].stop();
  }

}

void Drive::reverse(int durationMs){

  for (int motor = FRONT_LEFT; motor <= REAR_RIGHT; motor++) {
    motors[motor].backward();
  }

  delay(durationMs);

  for (int motor = FRONT_LEFT; motor <= REAR_RIGHT; motor++) {
    motors[motor].stop();
  }

}

void Drive::right() {
  motors[FRONT_LEFT].forward();
  motors[REAR_LEFT].forward();
  delay(3000);
}
