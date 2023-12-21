/*

NOTES:

  - USE IRemote (by shiriff) ISR example
  - signal into pin 2
  - seems to want gnd pin on digital pins side of board
    - todo: confirm there is any difference
  - ISR should filter messages and push them to queue
    - keep timestamps so we can discard messages if don't get to them in time 

*/

#define 

namespace Controller {

  enum Command { 
    LEFT = 0x44,
    RIGHT = 0x43,
    UP = 0x46,
    DOWN = 0x15,
    OK = ,
    ONE = ,
    TWO = ,
    THREE = ,
    FOUR = ,
    FIVE = ,
    SIX = ,
    SEVEN = ,
    EIGHT = ,
    NINE = ,
    ZERO = ,
    POUND = ,
    ASTERISK = 
  };

  Command getQueuedCommand();
  
}