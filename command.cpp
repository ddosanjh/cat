#include "command.h"
#include <stdio.h>

/*
  The remote crontol issue direction commands (arrows),
  and three digit numerical codes.

  The set of numerical codes are 111 to 999
  excluding all numbers containing zero. Represented internally as
  1110 to 9990 (so we can reserve 0-255 for other
  purposes).
*/

/**
 * While there is command waiting we will ignore other
 * remote control actions until the main loop
 * expresses its readiness to take a new command.
 */

int queuedCommand = 0;
int digitSequence = 0;
bool receivingInput = true;

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

void queue(int command) {
  queuedCommand = command;
  digitSequence = 0;
  receivingInput = false;
}

void handleButtonPress(int btn) {

  if (!receivingInput) {
    printf("ignored\n");
    return;
  }

  int digit = btnToDigit(btn);
  printf("button is digit %d\n", digit);

  if (digit != -1) { // is number button...
    
    if (digitSequence == 0) {
      // is first digit
      printf("first in sequence\n");
      digitSequence = digit;
    } else if (digitSequence < 10) {
      // second...
      printf("second in sequence\n");
      digitSequence = digitSequence * 10 + digit;
    } else {
      // third and final; queue command
      printf("third in sequence\n");
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

int Command::dequeue() {
  
  if (!queuedCommand) {
    return -1;
  }

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