#include "include.h"
#include "Motors.h"

int motorPins[4] = {2, 3, 4, 5};
Motors motors(motorPins, 255);


void setup() {

}

void loop() {
  for (int i = 0; i < 255; i++) {
    motors.moveTank(i, i);
    delay(10);
  }
  for (int i = 0; i < 255; i++) {
    motors.moveTank(-i, -i);
    delay(10);
  }
  for (int i = 0; i < 255; i++) {
    motors.moveTank(i, -i);
    delay(10);
  }
  for (int i = 0; i < 255; i++) {
    motors.moveTank(-i, i);
    delay(10);
  }
}
