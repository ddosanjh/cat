#include "Arduino.h"
#include <stdarg.h>

#define SERIAL_BAUD 115200

namespace Log {
  void setup();
  void out(const char* input...);
}