#include "sound.h"
#include "log.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

const byte RX_PIN = A1;
const byte TX_PIN = A0;

#define MSG_BUF_SIZE 32
char msg_buf[MSG_BUF_SIZE];
int msg_buf_ptr = 0;

SoftwareSerial mp3ModuleSerial(RX_PIN, TX_PIN);

void Sound::setup() {
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);
  mp3ModuleSerial.begin(9600);
  Log::out("setting sound volume to %d", SOUND_VOLUME);
  mp3ModuleSerial.print("AF:");
  mp3ModuleSerial.println(SOUND_VOLUME);
}

void Sound::loop() {

  // Buffer incoming message characters and output to log 
  // upon encountering newline char. 
  while (mp3ModuleSerial.available() > 0) {
    char c = mp3ModuleSerial.read();
    if (c == '\n' || msg_buf_ptr == MSG_BUF_SIZE - 1) {
      msg_buf[msg_buf_ptr] = 0; // NULL terminate to create c-string
      Log::out("msg from mp3 module: %s", msg_buf);
      msg_buf_ptr = 0;
    } else {
      msg_buf[msg_buf_ptr++] = c;
    }    
  }
}

void Sound::play(int code) {
  String playCmd = String("A7:00") + String(code);
  mp3ModuleSerial.println(playCmd);
}

