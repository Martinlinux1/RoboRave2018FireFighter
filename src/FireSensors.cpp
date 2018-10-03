#include "FireSensors.h"

FireSensors::FireSensors(int *sensorsPins) {
  FireSensors::fireSensorsPins = sensorsPins;
  FireSensors::multiplex = false;
}

FireSensors::FireSensors(int *analogPins, int *signalPins) {
  FireSensors::analogPins = analogPins;
  FireSensors::signalPins = signalPins;

  FireSensors::multiplex = true;
}

bool FireSensors::getFire(int pin) {
  return digitalRead(FireSensors::fireSensorsPins[pin]);
}

int FireSensors::getAnalogFire(int pin) {
  int division;
  bool above16 = false;

  if (pin < 16) {
    division = pin;
  }
  else if (pin < 27) {
    division = pin % 16;
    above16 = true;
  }

  int writeChannel[4] = {};

  int j = 0;

  while (division > 0) {
    writeChannel[j] = division % 2;
    division = division / 2;
  }

  for (unsigned int i = 0; i < arrLen(writeChannel); i++) {
    if (!above16) {
      digitalWrite(FireSensors::signalPins[i], writeChannel[i]);
    }
    else {
      digitalWrite(FireSensors::signalPins[i + 4], writeChannel[i]);
    }
  }

  if (above16) {
    return analogRead(FireSensors::analogPins[1]);
  }
  else {
    return analogRead(FireSensors::analogPins[0]);
  }
}
