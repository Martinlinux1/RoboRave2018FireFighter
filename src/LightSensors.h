#include "include.h"

class LightSensors {
public:
  LightSensors(int *pins);
  int getLight(int sensor);
private:
  int *sensorPins;
};
