#include "include.h"
#include "Motors.h"
#include "LightSensors.h"

int motorPins[4] = {2, 3, 4, 5};
int lightSensorsPins[8] = {13, 12, 11, 10, 9, 8, 7, 6};

Motors motors(motorPins, 255);
LightSensors lightSensors(lightSensorsPins);

bool isLine(short *sensor);

int baseSpeed = 150;

void setup() {
  Serial.begin(9600);
}

void loop() {
  short lightSensor;
  if (isLine(&lightSensor)) {
    if (lightSensor == 0 || lightSensor == 1) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (lightSensor == 2 || lightSensor == 3) {
      motors.moveTank(-baseSpeed, baseSpeed);
    }
  }

  else {
    motors.forward(baseSpeed, baseSpeed);
  }
}

bool isLine(short *sensor) {
  for (unsigned int i = 0; i < arrLen(lightSensorsPins); i++) {
    if (lightSensors.getLight(i) == 0) {
      *sensor = i;
      return true;
    }
  }

  *sensor = -1;
  return false;
}
