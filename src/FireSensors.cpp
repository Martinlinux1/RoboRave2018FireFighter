#include "FireSensors.h"

FireSensors::FireSensors(int *sensorsPins) {
  FireSensors::fireSensorsPins = sensorsPins;
}


bool FireSensors::getFire(int pin) {
  return digitalRead(FireSensors::fireSensorsPins[pin]);
}
