#include "include.h"
#include "LightSensors.h"

int lightSensorsPins[8] = {13, 12, 11, 10, 9, 8, 7, 6};
LightSensors lightSensors(lightSensorsPins);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("\nLight sensors obj:");
  for (unsigned int i = 0; i < arrLen(lightSensorsPins); i++) {
    Serial.print("\t");
    Serial.print(lightSensors.getLight(i));
  }

  Serial.print("\nLight sensors dig:");
  for (unsigned int i = 0; i < arrLen(lightSensorsPins); i++) {
    Serial.print("\t");
    Serial.print(digitalRead(lightSensorsPins[i]));
  }
}
