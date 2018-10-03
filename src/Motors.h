/**
  Class for controlling motors on fire fighter robot.
  Creator: Martinlinux
  Version: 0.2
  Log:
    v0.1 - Made function forward, back and moveTank.
    v0.2 - Tested with motors - found bug, when motor stopped spinning, when
           function moveTank(x, 0) was called.
           Fixed.
           Tested with motors - successful
*/

/*========Precprocessor part begin.========*/

#include "include.h"

/*========Precprocessor part end.========*/

/*========Class definition begin.========*/

class Motors {

/*========Public members definition begin========*/

public:
  //Constructor.
  Motors(int pins[4], int maxSpeed);

  // Move forward.
  void forward(int speedA, int speedB);

  // Move backward.
  void back(int speedA, int speedB);

  // Move forward / backward.
  void moveTank(int speedA, int speedB);

/*========Public members definition end.========*/

/*========Private members definition begin.========*/
private:
  // Array of motor pins.
  int *motorPins;

  // Maximal speed of motors.
  int maxSpeed = 0;

/*========Private members definition end.========*/

};

/*========Class definition end.========*/
