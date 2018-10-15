#include "FireSensors.h"

FireSensors::FireSensors(int *sensorsPins) {
  FireSensors::fireSensorsPins = sensorsPins;

  for (int i = 0; i < 8; i++) {
    pinMode(FireSensors::fireSensorsPins[i], INPUT);
  }
}


bool FireSensors::getFire(int pin) {
  return digitalRead(FireSensors::fireSensorsPins[pin]);
}
