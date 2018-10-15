#include "include.h"
#include "Fan.h"

int fanPin1 = 45;
int fanPin2 = 26;


void setup() {

}

void loop() {
  digitalWrite(fanPin1, HIGH);
  digitalWrite(fanPin2, LOW);
  delay(1000);
  digitalWrite(fanPin1, LOW);
  digitalWrite(fanPin2, LOW);
  delay(1000);
}
