/**
  Class for reading value from fire sensors. Used for fire fighter robot for
  robotic competition RoboRave.

  version: 0.2
  log:
    v0.1 - made constructor and getFire function for returning current fire state
           from chosen sensor.
    v0.2 - overloaded constructor for setup multiplexed fire sensors and created
           function getAnalogFire, which reads multiplexed sensors.
           Sensors multiplexed by: CD74HC4067,
           datasheet: http://www.ti.com/lit/ds/symlink/cd74hc4067.pdf
*/

/*========Preprocessor part begin.========*/

#include "include.h"

/*========Preprocessor part end.========*/

/*========Class definition begin.========*/

class FireSensors {
public:
  // Constructor.
  FireSensors(int *sensorsPins);

  // Constructor for multiplexed sensors.
  FireSensors(int *analogPins, int *signalPins);

  // Get fire status on sensor in digital form.
  bool getFire(int pin);

  // Get fire status on multiplexed sensor in analog form.
  int getAnalogFire(int pin);
private:
  // Pins of sensors.
  int *fireSensorsPins;

  // Read pins of multiplexed sensors.
  int *analogPins;

  // Channel choosing pins of multiplexed sensors.
  int *signalPins;

  // If sensors are multiplexed.
  bool multiplex;
};

/*========Class definition end.========*/
