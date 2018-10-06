#include "include.h"
#include "Motors.h"
#include "LightSensors.h"
#include "UltrasonicSensors.h"
#include "FireSensors.h"

#define SLOW_DOWN 1
#define TURN 2

int motorPins[4] = {2, 3, 4, 5};
int lightSensorsPins[8] = {13, 12, 11, 10, 9, 8, 7, 6};
int echoPins[5] = {47, 30, 31, 32, 51};
int trigPins[5] = {29, 46, 49, 50, 33};
int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};

Motors motors(motorPins, 255);
LightSensors lightSensors(lightSensorsPins);
UltrasonicSensors prox(trigPins, echoPins);
FireSensors fireSensors(fireSensorsPins);


int baseSpeed = 150;


bool isLine(short *lightSensor);
int isWall(short *ultrasonicSensor);
bool isFire(short *fireSensor);


void setup() {
  Serial.begin(9600);
}


void loop() {
  short lightSensor, ultrasonicSensor, fireSensor;

  if (isLine(&lightSensor)) {
    if (lightSensor == 0 || lightSensor == 1) {
      motors.moveTank(-baseSpeed, baseSpeed);
    }

    else if (lightSensor == 7) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }
  }

  else if (isFire(&fireSensor)) {
    if (fireSensor == 3) {
      Serial.println("forward");
      motors.forward(baseSpeed, baseSpeed);
    }

    else if (fireSensor < 3) {
      Serial.println("right");
      motors.moveTank(baseSpeed, -baseSpeed);
      delay(20);
    }

    else if (fireSensor > 3) {
      Serial.println("left");
      motors.moveTank(-baseSpeed, baseSpeed);
      delay(20);
    }
  }

  else if (isWall(&ultrasonicSensor) == SLOW_DOWN) {
    int currSpeed = baseSpeed - 30;
    Serial.println("Slowing down");
    motors.forward(currSpeed, currSpeed);
  }

  else if (isWall(&ultrasonicSensor) == TURN) {
    Serial.println("Turning");

    if (ultrasonicSensor == 0) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (ultrasonicSensor == 1) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (ultrasonicSensor == 3) {
      motors.moveTank(-baseSpeed, baseSpeed);
    }
  }
}


bool isLine(short *lightSensor) {
  for (unsigned int i = 0; i < arrLen(lightSensorsPins); i++) {
    if (lightSensors.getLight(i) == 0) {
      *lightSensor = i;
      return true;
    }
  }

  *lightSensor = -1;
  return false;
}


int isWall(short ultrasonicSensor) {
  if (prox.distanceCm(0) < 10) {
    ultrasonicSensor = 0;
    return TURN;
  }

  else if (prox.distanceCm(1) < 10) {
    ultrasonicSensor = 1;
    return TURN;
  }

  else if (prox.distanceCm(3) < 10) {
    ultrasonicSensor = 3;
    return TURN;
  }

  if (prox.distanceCm(0) < 15) {
    ultrasonicSensor = 0;
    return SLOW_DOWN;
  }

  else if (prox.distanceCm(1) < 15) {
    ultrasonicSensor = 1;
    return SLOW_DOWN;
  }

  else if (prox.distanceCm(3) < 15) {
    ultrasonicSensor = 3;
    return SLOW_DOWN;
  }

  ultrasonicSensor = -1;

  return 0;
}


bool isFire(short *fireSensor) {
  for (unsigned int i = 0; i < arrLen(fireSensorsPins); i++) {
    if (fireSensors.getFire(i) == 0) {
      *fireSensor = i;
      return true;
    }
  }

  *fireSensor = -1;

  return false;
}
