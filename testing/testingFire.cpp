#include "include.h"
#include "FireSensors.h"

int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};

FireSensors fireSensors(fireSensorsPins);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Fire sensors: ");

  for (int i = 0; i < arrLen(fireSensorsPins); i++) {
    Serial.print(fireSensors.getFire(i));
    Serial.print("\t");
  }
  Serial.print("\n");
}
