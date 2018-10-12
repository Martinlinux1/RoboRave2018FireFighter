/*========Preprocessor part begin.========*/

// Include Motors.h.
#include "Motors.h"

/*========Preprocessor part end.========*/

/*========Function definition begin.========*/

// Constructor.
Motors::Motors(int pins[4], int maxSpeed) {
  Motors::motorPins = pins;
  Motors::maxSpeed = maxSpeed;

  for (unsigned int i = 0; i < 4; i++) {
    pinMode(Motors::motorPins[i], OUTPUT);
  }
}

// Move forward / backward.
void Motors::moveTank(int speedA, int speedB) {
  if (speedA <= 0 && speedB != 0) {
    if (speedB < 0) {
      analogWrite(Motors::motorPins[0], LOW);
      analogWrite(Motors::motorPins[1], abs(speedA));
      analogWrite(Motors::motorPins[2], LOW);
      analogWrite(Motors::motorPins[3], abs(speedB));
    }
    else {
      analogWrite(Motors::motorPins[0], LOW);
      analogWrite(Motors::motorPins[1], abs(speedA));
      analogWrite(Motors::motorPins[2], speedB);
      analogWrite(Motors::motorPins[3], LOW);
    }
  }

  else if (speedA >= 0 && speedB != 0) {
    if (speedB < 0) {
      analogWrite(Motors::motorPins[0], speedA);
      analogWrite(Motors::motorPins[1], LOW);
      analogWrite(Motors::motorPins[2], LOW);
      analogWrite(Motors::motorPins[3], abs(speedB));
    }
    else {
      analogWrite(Motors::motorPins[0], speedA);
      analogWrite(Motors::motorPins[1], LOW);
      analogWrite(Motors::motorPins[2], speedB);
      analogWrite(Motors::motorPins[3], LOW);
    }
  }
}

// Move forward.
void Motors::forward(int speedA, int speedB) {
  moveTank(speedA, speedB);
}

// Move backward.
void Motors::back(int speedA, int speedB) {
  moveTank(-speedA, -speedB);
}


void Motors::stop() {
  analogWrite(Motors::motorPins[0], HIGH);
  analogWrite(Motors::motorPins[1], HIGH);
  analogWrite(Motors::motorPins[2], HIGH);
  analogWrite(Motors::motorPins[3], HIGH);
  delay(10);
  analogWrite(Motors::motorPins[0], LOW);
  analogWrite(Motors::motorPins[1], LOW);
  analogWrite(Motors::motorPins[2], LOW);
  analogWrite(Motors::motorPins[3], LOW);
}

/*========Function definition end.========*/
