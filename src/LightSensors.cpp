#include "LightSensors.h"

LightSensors::LightSensors(int *pins) {
  LightSensors::sensorPins = pins;

  for (unsigned int i = 0; i < 8; i++) {
    pinMode(LightSensors::sensorPins[i], INPUT);
  }
}

int LightSensors::getLight(int sensor) {
  return analogRead(LightSensors::sensorPins[sensor]);
}
