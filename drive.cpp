#include "Arduino.h" 
#include "drive.h"
#include "log.h"


// MOTOR PINS

#define FL 0
#define FR 1
#define RL 2
#define RR 3
#define EN 0
#define IN1 1
#define IN2 2

const unsigned int motor_pins[4][3] = {

/**
 * EN pins must be PWM capable;
 * on UNO 3, 5, 6, 9, 10 or 11.
 */

  // FL
  {
    3,  // EN
    A4, // IN1
    A5  // IN2
  },

  // FR
  {
    5,  // EN
    6,  // IN1
    7   // IN2
  },

  // RL
  {
    9,  // EN
    8,  // IN1
    10  // IN2
  },

  // RR
  {
    11, // EN
    12, // IN1
    13  // IN2
  },
};


// HELPER DEFINITIONS

void stopAll();
void onClockwise(int motor);
void onCounterClockwise(int motor);


// INTERFACE IMPLEMENTATION

void Drive::setup() {
  for(int motor = 0; motor < 4; motor++) {
    for (int pin = 0; pin < 3; pin++) {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }
  }
}

void Drive::forward(int durationMs){
  onCounterClockwise(FL);
  onClockwise(FR);
  onCounterClockwise(RL);
  onClockwise(RR);
  delay(durationMs);
  stopAll();
}

void Drive::reverse(int durationMs){
  onClockwise(FL);
  onCounterClockwise(FR);
  onClockwise(RL);
  onCounterClockwise(RR);
  delay(durationMs);
  stopAll();
}

void Drive::right(){
  onCounterClockwise(FL);
  onCounterClockwise(RL);
  onCounterClockwise(FR);
  onCounterClockwise(RR);
  delay(TURN_TIME);
  stopAll();
}

void Drive::left(){
  onClockwise(FL);
  onClockwise(RL);
  onClockwise(FR);
  onClockwise(RR);
  delay(TURN_TIME);
  stopAll();
}


// HELPERS

void stopAll() {
  for(int motor = 0; motor < 4; motor++) {
    for (int pin = 0; pin < 3; pin++) {
      digitalWrite(motor_pins[motor][pin], LOW);
    }
  }
}

void onCounterClockwise(int motor) {
  digitalWrite(motor_pins[motor][EN], HIGH);
  digitalWrite(motor_pins[motor][IN1], HIGH);
  digitalWrite(motor_pins[motor][IN2], LOW);
}

void onClockwise(int motor) {
  digitalWrite(motor_pins[motor][EN], HIGH);
  digitalWrite(motor_pins[motor][IN1], LOW);
  digitalWrite(motor_pins[motor][IN2], HIGH);
}
