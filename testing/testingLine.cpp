#include "include.h"
#include "LightSensors.h"

int lightSensorsPins[8] = {13, 12, 11, 10, 9, 8, 7, 6};
LightSensors lightSensors(lightSensorsPins);

void setup() {

}

void loop() {
  Serial.print("Light sensors:");
  for (unsigned int i = 0; i < arrLen(lightSensorsPins); i++) {
    Serial.print("\t");
    Serial.print(lightSensors.getLight(i));
  }
}
