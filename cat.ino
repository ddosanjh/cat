#include "log.h"
#include "drive.h"
#include "command.h"

void setup() {
  Log::setup();
  Drive::setup();
  Command::setup();
}

void loop() {
    // Drive::reverse(2000);
    // Drive::forward(255, 2000);
  
  switch(Command::dequeue()) {
    
    case -1: 
      break;

    case DRIVE_FORWARD:
      Log::out("forward");
      Drive::forward(3000);
      break;
  }
  
  // if (newCommand != -1) {
  //   Log::out("command: 0x%x (%d)", newCommand, newCommand);
  //   Command::ready();
  // }
}