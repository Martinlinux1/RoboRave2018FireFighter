#include "include.h"

class LightSensors {
public:
  LightSensors(int *pins);
  bool getLight(int sensor);
private:
  int *sensorPins;
};
