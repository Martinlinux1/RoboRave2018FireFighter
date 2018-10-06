#include "UltrasonicSensors.h"

UltrasonicSensors::UltrasonicSensors(int *trigPins, int *echoPins) {
  UltrasonicSensors::trigPins = trigPins;
  UltrasonicSensors::echoPins = echoPins;
  
  for (unsigned int i = 0; i < arrLen(trigPins); i++) {
    pinMode(UltrasonicSensors::trigPins[i], OUTPUT);
  }

  for (unsigned int i = 0; i < arrLen(echoPins); i++) {
    pinMode(UltrasonicSensors::echoPins[i], INPUT);
  }
}

float UltrasonicSensors::distanceCm(int sensor) {
  digitalWrite(UltrasonicSensors::trigPins[sensor], LOW);
  delayMicroseconds(2);
  digitalWrite(UltrasonicSensors::trigPins[sensor], HIGH);
  delayMicroseconds(10);
  digitalWrite(UltrasonicSensors::trigPins[sensor], LOW);

  unsigned long duration = pulseIn(UltrasonicSensors::echoPins[sensor], HIGH);

  return duration * 0.034 / 2;
}

float UltrasonicSensors::distanceInch(int sensor) {
  return UltrasonicSensors::distanceCm(sensor) / 2.54;
}
