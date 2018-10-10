#include "include.h"

void setup() {
  pinMode(A8, OUTPUT);
}

void loop() {
  digitalWrite(A8, HIGH);
  delay(1000);
  digitalWrite(A8, LOW);
  delay(1000);
}
