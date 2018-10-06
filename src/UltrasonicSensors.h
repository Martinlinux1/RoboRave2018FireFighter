/**
  Class for reading data from ultrasonic sensors for fire fighter robot.

  Creator: Martinlinux.
  Version: 0.1.
  Log:
    -Add functions distanceCm and distanceInch.
    -Tested with HC-SR04 ultrasonic sensors - successful.
*/

#include "include.h"

class UltrasonicSensors {
public:
  UltrasonicSensors(int *trigPins, int *echoPins);
  float distanceCm(int sensor);
  float distanceInch(int sensor);
  int *trigPins;
  int *echoPins;
private:

};
