#include "LightSensors.h"

LightSensors::LightSensors(int *pins) {
  LightSensors::sensorPins = pins;

  for (unsigned int i = 0; i < arrLen(LightSensors::sensorPins); i++) {
    pinMode(LightSensors::sensorPins[i], INPUT);
  }
}

bool LightSensors::getLight(int sensor) {
  return digitalRead(sensor);
}
