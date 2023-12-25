#include "log.h"
#include "drive.h"
#include "command.h"
#include "sound.h"

void setup() {
  Log::setup();
  Log::out("cat has awoken");
  Drive::setup();
  Command::setup();
  Sound::setup();
}

void loop() {
  
  int cmd = Command::dequeue();

  if (cmd != -1) {

    Log::out("recieved command: %d", cmd);

    if (cmd >= 111 && cmd <= 999) {
      Sound::play(cmd);
    } else {

      switch(cmd) {

      
      case -1: 
        break;

      case DRIVE_FORWARD:
        Log::out("forward");
        Drive::forward(3000);
        break;

      case DRIVE_REVERSE:
        Log::out("reverse");
        Drive::reverse(3000);
        break;

      case DRIVE_RIGHT:
        Log::out("right");
        Drive::right();
        break;

      case DRIVE_LEFT:
        Log::out("left");
        Drive::left();
        break;

      default:
        Log::out("undefined command: %x(%d)", cmd, cmd);
        break;
      }
      
    }

    Command::ready();
  }
  
  Sound::loop();

}