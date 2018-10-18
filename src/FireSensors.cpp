#include "FireSensors.h"


FireSensors::FireSensors(int *sensorsPins, int *multiplexPins) {
  FireSensors::fireSensorsPins = sensorsPins;
  FireSensors::multiplexPins = multiplexPins;
}

bool FireSensors::getFire(int pin) {
  digitalWrite(multiplexPins[0], HIGH);
  digitalWrite(multiplexPins[1], HIGH);

  if (pin < 9) {
    return digitalRead(fireSensorsPins[pin]);
  }

  else {
    return digitalRead(fireSensorsPins[pin % 9]);
  }
}

void FireSensors::resetSensors(int row) {
  digitalWrite(FireSensors::multiplexPins[row], LOW);
}
