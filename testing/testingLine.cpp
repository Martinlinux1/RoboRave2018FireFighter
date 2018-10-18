#include "include.h"
#include "LightSensors.h"

// #TODO Sensor 6 is maybe disconnected, sensor 1 & 4 isn't connected.
int lightSensorsPins[8] = {13, 10, 12, 9, 6, 7, 8};
LightSensors lightSensors(lightSensorsPins);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("\nLight sensors obj:");
  for (unsigned int i = 0; i < 7; i++) {
    Serial.print("\t");
    Serial.print(lightSensors.getLight(i));
  }

  delay(100);
}
