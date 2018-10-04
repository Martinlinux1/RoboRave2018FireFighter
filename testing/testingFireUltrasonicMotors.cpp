#include "include.h"
#include "Motors.h"
#include "FireSensors.h"

#define SLOW_DOWN 1
#define TURN 2

int motorPins[4] = {2, 3, 4, 5};
int trigPins[5] = {29, 48, 31, 32, 51};
int echoPins[5] = {47, 30, 49, 50, 33};
int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};

FireSensors fireSensors(fireSensorsPins);
Motors motors(motorPins, 255);

int baseSpeed = 150;
int currSpeed = baseSpeed;

float distanceCm(int sensor);
int isWall(short *sensor);
bool isFire(short *fireSensor);

void setup() {
  for (unsigned int i = 0; i < arrLen(trigPins); i++) {
    pinMode(trigPins[i], OUTPUT);
  }

  for (unsigned int i = 0; i < arrLen(echoPins); i++) {
    pinMode(echoPins[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  short USSensor = -1, fireSensor = -1;

  isFire(&fireSensor);

  if (isWall(&USSensor) == SLOW_DOWN) {
    currSpeed = baseSpeed - 30;
    Serial.println("Slowing down");
    motors.forward(currSpeed, currSpeed);
  }

  else if (isWall(&USSensor) == TURN && fireSensor != 0) {
    if (USSensor == 0) {
      motors.moveTank(baseSpeed, -baseSpeed);
      Serial.println("Turning");
    }

    else if (USSensor == 1) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (USSensor == 3) {
      motors.moveTank(-baseSpeed, baseSpeed);
    }
  }

  else if (isFire(&fireSensor)) {
    if (fireSensor == 4) {
      Serial.println("forward");
      motors.forward(baseSpeed, baseSpeed);
    }

    else if (fireSensor < 4) {
      Serial.println("right");
      motors.moveTank(baseSpeed, -baseSpeed);
      delay(20);
    }

    else if (fireSensor > 4) {
      Serial.println("left");
      motors.moveTank(-baseSpeed, baseSpeed);
      delay(20);
    }
  }

  else {
    motors.forward(baseSpeed, baseSpeed);
  }
}

float distanceCm(int sensor) {
  digitalWrite(trigPins[sensor], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPins[sensor], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[sensor], LOW);

  unsigned long duration = pulseIn(echoPins[sensor], HIGH);

  return duration * 0.034 / 2;
}

int isWall(short *sensor) {
  if (distanceCm(0) < 10) {
    *sensor = 0;
    return TURN;
  }

  else if (distanceCm(1) < 10) {
    *sensor = 1;
    return TURN;
  }

  else if (distanceCm(3) < 10) {
    *sensor = 3;
    return TURN;
  }

  if (distanceCm(0) < 15) {
    *sensor = 0;
    return SLOW_DOWN;
  }

  else if (distanceCm(1) < 15) {
    *sensor = 1;
    return SLOW_DOWN;
  }

  else if (distanceCm(3) < 15) {
    *sensor = 3;
    return SLOW_DOWN;
  }

  *sensor = -1;

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
