#include "Fan.h"

Fan::Fan(short *fanPins) {
  Fan::fanPins = fanPins;

  for (unsigned int i = 0; i < arrLen(fanPins); i++) {
    pinMode(Fan::fanPins[i], OUTPUT);
  }
}

void Fan::turnFan(bool on, short sensor) {
  digitalWrite(Fan::fanPins[sensor], on);
}
