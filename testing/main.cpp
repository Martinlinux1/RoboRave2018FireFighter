#include "include.h"
#include "Motors.h"
#include "UltrasonicSensors.h"
#include "LightSensors.h"
#include "FireSensors.h"

int motorPins[4] = {2, 3, 4, 5};
int trigPins[5] = {29, 48, 31, 32, 51};
int echoPins[5] = {47, 30, 49, 50, 33};
int lightSensorsPins[8] = {13, 12, 11, 10, 9, 8, 7, 6};
int fireSensorsPins[16] = {39., 38., 40., 41., 42., 43., 44., 45., 46., 47, 48, 49, 50, 51, 52. , 53};

Motors motors(motorPins, 255);
UltrasonicSensors prox(trigPins, echoPins);
LightSensors lineSensors(lightSensorsPins);
FireSensors fireSensors(fireSensorsPins);

double wallProx = 10.0;
int baseSpeed = 180;


bool isOnEdge(int *lineSensor);
bool isFire(int *fireSensor);
bool isWall(int *usSensor);

void setup() {
  Serial.begin(115200);
}

void loop() {
  int lineSensor, fireSensor, usSensor;

  if (isOnEdge(&lineSensor)) {
    if (lineSensor < 4) {
      motors.moveTank(-baseSpeed, baseSpeed);
      delay(500);
      motors.forward(baseSpeed, baseSpeed);
      delay(500);
    }
    else {
      motors.moveTank(baseSpeed, -baseSpeed);
      delay(500);
      motors.forward(baseSpeed, baseSpeed);
      delay(500);
    }
  }

  else if (isWall(&usSensor)) {
    if (usSensor < 3) {
      while (isWall(&usSensor)) {
        motors.moveTank(-baseSpeed, baseSpeed);
      }
      motors.moveTank(0, 0);
    }

    else {
      while (isWall(&usSensor)) {
        motors.moveTank(baseSpeed, -baseSpeed);
      }
      motors.moveTank(0, 0);
    }
  }

  else if (isFire(&fireSensor)) {
    if (fireSensor == 0 && lineSensors.getLight(0) == 0) {
      while (fireSensors.getFire(0) == 1) {
      }
    }
    else {
      while (fireSensors.getFire(0) == 1) {
        motors.moveTank(-baseSpeed, baseSpeed);
      }

      motors.moveTank(0, 0);
    }
  }
}

bool isOnEdge(int *lineSensor) {
  int x;
  for (unsigned int i = 0; i < arrLen(lightSensorsPins); i++) {
    if (lineSensors.getLight(i) == 0 && !isFire(&x)) {
      *lineSensor = i;
      return true;
    }
  }
  return false;
}

bool isFire(int *fireSensor) {
  return false;
  for (unsigned int i = 0; i < arrLen(fireSensorsPins); i++) {
    if (fireSensors.getFire(i) == 1) {
      *fireSensor = i;
      return true;
    }
  }

  return false;
}

bool isWall(int *usSensor) {
  for (unsigned int i = 0; i < arrLen(echoPins); i++) {
    if (prox.distanceCm(i) < wallProx) {
      *usSensor = i;
      return true;
    }
  }

  return false;
}
