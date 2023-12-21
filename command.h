/*

NOTES:

  - USE IRemote (by shiriff) ISR example
  - signal into pin 2
  - seems to want gnd pin on digital pins side of board
    - todo: confirm there is any difference
  - ISR should filter messages and push them to queue
    - keep timestamps so we can discard messages if don't get to them in time 

*/

#define DECODE_NEC 

#define BTN_LEFT 0x44
#define BTN_RIGHT 0x43
#define BTN_UP 0x46
#define BTN_DOWN 0x15
#define BTN_OK 0x40
#define BTN_ONE 0x16
#define BTN_TWO 0x19
#define BTN_THREE 0x0D
#define BTN_FOUR 0x0C
#define BTN_FIVE 0x18
#define BTN_SIX 0x5E
#define BTN_SEVEN 0x08
#define BTN_EIGHT 0x1C
#define BTN_NINE 0x5A
#define BTN_ZERO 0x52
#define BTN_POUND 0x42
#define BTN_ASTERISK 0x4A

namespace Command {

  const int
    CMD_SOUND_MEOW = 1110,
    CMD_DRIVE_CIRCLE = 2220,
    CMD_FORWARD = BTN_UP,
    CMD_BACK = BTN_DOWN,
    CMD_LEFT = BTN_LEFT,
    CMD_RIGHT = BTN_RIGHT;

  int dequeue();
  void ready();
  void provideTestInput(int * btns, int n);
}