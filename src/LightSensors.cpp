#include "LightSensors.h"

LightSensors::LightSensors(int *pins) {
  LightSensors::sensorPins = pins;

  for (unsigned int i = 0; i < arrLen(LightSensors::sensorPins); i++) {
    pinMode(LightSensors::sensorPins[i], INPUT);
  }
}

int LightSensors::getLight(int sensor) {
  return analogRead(LightSensors::sensorPins[sensor]);
}
