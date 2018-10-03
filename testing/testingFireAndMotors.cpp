#include "include.h"
#include "Motors.h"
#include "FireSensors.h"

int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};
int motorPins[] = {2, 3, 4, 5};

Motors motors(motorPins, 255);
FireSensors fireSensors(fireSensorsPins);

const int baseSpeed = 180;

bool isFire(int *fireSensor);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int fireSensor;

  Serial.println(fireSensor);

  if (isFire(&fireSensor)) {
    if (fireSensor == 4) {
      Serial.println("forward");
      motors.forward(baseSpeed, baseSpeed);
    } else if (fireSensor < 4) {
      Serial.println("right");
      motors.moveTank(baseSpeed, -baseSpeed);
      delay(20);
    } else if (fireSensor > 4) {
      Serial.println("left");
      motors.moveTank(-baseSpeed, baseSpeed);
      delay(20);
    }
  } else {
    motors.moveTank(0, 0);
  }
}

bool isFire(int *fireSensor) {
  for (unsigned int i = 0; i < arrLen(fireSensorsPins); i++) {
    if (fireSensors.getFire(i) == 0) {
      *fireSensor = i;
      return true;
    }
  }
  *fireSensor = -1;

  return false;
}
