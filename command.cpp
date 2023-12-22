#include "command.h"
#include <stdio.h>
#include "IR_pin_defs.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

/*
  The remote crontol issue direction commands (arrows),
  and three digit numerical codes.

  The set of numerical codes are 111 to 999
  excluding all numbers containing zero. Represented internally as
  1110 to 9990 (so we can reserve 0-255 for other
  purposes).
*/


// MODULE INTERNAL GLOBALS

// marked volatile because accessed from ISR
volatile int queuedCommand = 0;
volatile int digitSequence = 0;
volatile bool receivingInput = true;


// LOCAL HELPER DECLARATIONS

void isrHandler();
int btnToDigit(int btn);
void queue(int command);
void handleButtonPress(int btn);


// MODULE INTERFACE

void Command::setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrReceiver.registerReceiveCompleteCallback(isrHandler);
}

int Command::dequeue() {
  
  if (!queuedCommand) {
    return -1;
  }

  digitSequence = 0;
  receivingInput = false;
  const int newCommand = queuedCommand;
  queuedCommand = 0;

  return newCommand;
}

void Command::ready() {
  receivingInput = true;
}

void Command::provideTestInput(int * btns, int n) {
  printf("Testing cat modules\n");
  for(int i = 0; i < n; i++) {
    printf("handling button press: %X\n", btns[i]);
    handleButtonPress(btns[i]);
    printf(
      "[queuedCommand: 0x%X(%d), digitSequence: %d, receivingInput: %s]\n", 
      queuedCommand, queuedCommand, digitSequence, receivingInput ? "yes" : "no"
      );
  }
}


// LOCAL HELPER IMPLEMENTATIONS

void isrHandler() {
  IrReceiver.decode();
  if (! (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) ) {
     handleButtonPress(IrReceiver.decodedIRData.command);
  }
  IrReceiver.resume();
}

int btnToDigit(int btn) {
  switch (btn) {
    case BTN_ONE: return 1;
    case BTN_TWO: return 2;
    case BTN_THREE: return 3;
    case BTN_FOUR: return 4;
    case BTN_FIVE: return 5;
    case BTN_SIX: return 6;
    case BTN_SEVEN: return 7;
    case BTN_EIGHT: return 8;
    case BTN_NINE: return 9;
  }
  return -1;
}

void handleButtonPress(int btn) {

  if (!receivingInput) {
    return;
  }

  int digit = btnToDigit(btn);
  // printf("button is digit %d\n", digit);

  if (digit != -1) { // is number button...
    
    if (digitSequence == 0) {
      // is first digit
      // printf("first in sequence\n");
      digitSequence = digit;
    } else if (digitSequence < 10) {
      // second...
      // printf("second in sequence\n");
      digitSequence = digitSequence * 10 + digit;
    } else {
      // third and final; queue command
      // printf("third in sequence\n");
      queue(digitSequence * 10 + digit);
    }

  } else { // other button...

    // cancel any digital sequence that might have been in progress
    digitSequence = 0;
    
    // for non numerical commands, the internal 16 bit command is equal to the
    // 8 bit button value
    queuedCommand = btn;
  }
}

void queue(int command) {
  queuedCommand = command;
  digitSequence = 0;
  receivingInput = false;
}
