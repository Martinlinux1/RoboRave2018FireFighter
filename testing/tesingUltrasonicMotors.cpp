#include "include.h"
#include "Motors.h"

int motorPins[4] = {2, 3, 4, 5};
int trigPins[5] = {29, 48, 31, 32, 51};
int echoPins[5] = {47, 30, 49, 50, 33};

Motors motors(motorPins, 255);

int baseSpeed = 150;
int currSpeed = baseSpeed;

float distanceCm(int sensor);

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
  if (distanceCm(0) < 10) {
    motors.moveTank(baseSpeed, -baseSpeed);
    Serial.println("Turning");
  }

  else if (distanceCm(1) < 10) {
    motors.moveTank(baseSpeed, -baseSpeed);
  }

  else if (distanceCm(3) < 10) {
    motors.moveTank(-baseSpeed, baseSpeed);
  }

  else if (distanceCm(0) < 15) {
    currSpeed = baseSpeed - 30;
    Serial.println("Slowing down");
    motors.forward(currSpeed, currSpeed);
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
