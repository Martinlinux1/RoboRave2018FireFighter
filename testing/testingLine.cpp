#include "include.h"
#include "LightSensors.h"

// #TODO Sensor 6 is maybe disconnected, sensor 1 & 4 isn't connected.
int lightSensorsPins[8] = {13, 12, 11, 10, 9, 8, 7, 6};
LightSensors lightSensors(lightSensorsPins);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("\nLight sensors obj:");
  for (unsigned int i = 0; i < 8; i++) {
    Serial.print("\t");
    Serial.print(lightSensors.getLight(i));
  }

  delay(100);
}
