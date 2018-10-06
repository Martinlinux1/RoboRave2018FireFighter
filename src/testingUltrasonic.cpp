#include "include.h"
#include "UltrasonicSensors.h"

int echoPins[5] = {47, 30, 31, 32, 51};
int trigPins[5] = {29, 46, 49, 50, 33};

UltrasonicSensors prox(trigPins, echoPins);

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
  Serial.print("Ultrasonic sensors obj: ");
  for (int i = 0; i < 5; i++) {
    Serial.println(prox.distanceCm(i));
  }

  delay(500);
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
