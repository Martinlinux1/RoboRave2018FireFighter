#include "include.h"

Servo servo;


void setup() {
  pinMode(45, OUTPUT);
  servo.attach(11);

}

void loop() {
  servo.write(180);
  digitalWrite(45, HIGH);
  delay(500);
  servo.write(135);
  delay(500);
}
