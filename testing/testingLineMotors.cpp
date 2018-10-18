#include "include.h"
#include "Motors.h"
#include "LightSensors.h"

int motorPins[4] = {2, 3, 4, 5};
int lightSensorsPins[8] = {13, 10, 12, 11, 9, 6, 7, 8};

Motors motors(motorPins, 255);
LightSensors lightSensors(lightSensorsPins);

bool isLine(int *sensor);

int baseSpeed = 150;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lightSensor;

  if (isLine(&lightSensor)) {
    Serial.print("Line detected");

    if (lightSensor == 0 || lightSensor == 1) {
      Serial.println(", going right.");

      motors.back(baseSpeed, baseSpeed);
      delay(500);
      motors.moveTank(-baseSpeed, baseSpeed);
      delay(500);
      motors.stop();
    }

    else if (lightSensor == 7) {
      Serial.println(", going left.");

      motors.back(baseSpeed, baseSpeed);
      delay(500);
      motors.moveTank(-baseSpeed, baseSpeed);
      delay(500);
      motors.stop();
    }
  }

  else {
    motors.forward(baseSpeed, baseSpeed);
  }
}

bool isLine(int *sensor) {
  for (unsigned int i = 0; i < 8; i++) {
    if (lightSensors.getLight(i) == 1) {
      *sensor = i;
      return true;
    }
  }

  *sensor = -1;
  return false;
}
