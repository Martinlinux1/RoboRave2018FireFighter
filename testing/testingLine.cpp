#include "include.h"
#include "LightSensors.h"

int lightSensorsPins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
LightSensors lightSensors(lightSensorsPins);

void setup() {
  Serial.begin(4800);
}

void loop() {
  Serial.print("\nLight sensors obj:");
  for (unsigned int i = 0; i < arrLen(lightSensorsPins); i++) {
    Serial.print("\t");
    Serial.print(lightSensors.getLight(i));
  }
}
