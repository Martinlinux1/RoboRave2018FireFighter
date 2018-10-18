/**
  * Works.
*/

#include "include.h"
#include "FireSensors.h"

int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};
int multiplexPins[] = {44, 43};

FireSensors fireSensors(fireSensorsPins, multiplexPins);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Fire sensors: ");

  for (int i = 0; i < 9; i++) {
    Serial.print(fireSensors.getFire(i));
    Serial.print("\t");
  }

  for (int i = 9; i < 18; i++) {
    Serial.print(fireSensors.getFire(i));
    Serial.print("\t");
  }
  Serial.print("\n");
}
