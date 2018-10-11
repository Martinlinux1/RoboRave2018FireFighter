#include "include.h"
#include "Motors.h"
#include "LightSensors.h"
#include "UltrasonicSensors.h"
#include "FireSensors.h"
#include "fan.h"

#define SLOW_DOWN 1
#define TURN 2

int motorPins[] = {2, 3, 4, 5};
int lightSensorsPins[] = {13, 12, 11, 10, 9, 8, 7, 6};
int trigPins[] = {29, 48, 49, 50, 33};
int echoPins[] = {47, 30, 31, 32, 51};
int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};
short fanPins[] = {A8, A9};

Motors motors(motorPins, 255);
LightSensors lightSensors(lightSensorsPins);
UltrasonicSensors prox(trigPins, echoPins);
FireSensors fireSensors(fireSensorsPins);
Fan fan(fanPins);


int baseSpeed = 150;


bool isLine(short *lightSensor);
int isWall(short *ultrasonicSensor);
bool isFire(short *fireSensor);


void setup() {
  Serial.begin(9600);
}


void loop() {
  short ultrasonicSensor, fireSensor;

  if (isWall(&ultrasonicSensor) && ultrasonicSensor == 0 && isFire(&fireSensor) && fireSensor == 4) {
    motors.forward(0, 0);

    fan.turnFan(true, 0);
    delay(2000);
    fan.turnFan(false, 0);
  }

  // else if (isLine(&lightSensor)) {
  //   if (lightSensor == 0 || lightSensor == 1) {
  //     motors.moveTank(-baseSpeed, baseSpeed);
  //   }
  //
  //   else if (lightSensor == 7) {
  //     motors.moveTank(baseSpeed, -baseSpeed);
  //   }
  // }
  //
  // else if (isFire(&fireSensor)) {
  //   if (fireSensor == 3) {
  //     Serial.println("forward");
  //     motors.forward(baseSpeed, baseSpeed);
  //   }
  //
  //   else if (fireSensor < 3) {
  //     Serial.println("right");
  //     motors.moveTank(baseSpeed, -baseSpeed);
  //     delay(20);
  //   }
  //
  //   else if (fireSensor > 3) {
  //     Serial.println("left");
  //     motors.moveTank(-baseSpeed, baseSpeed);
  //     delay(20);
  //   }
  // }

  else if (isWall(&ultrasonicSensor) == SLOW_DOWN) {
    int currSpeed = baseSpeed - 30;
    Serial.println("Slowing down");
    motors.forward(currSpeed, currSpeed);
  }

  else if (isWall(&ultrasonicSensor) == TURN) {
    Serial.println("Turning");

    if (ultrasonicSensor == 0) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (ultrasonicSensor == 1) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (ultrasonicSensor == 3) {
      motors.moveTank(-baseSpeed, baseSpeed);
    }
  }

  else if (isFire(&fireSensor)) {
    if (fireSensor == 4) {
      Serial.println("forward");
      motors.forward(baseSpeed, baseSpeed);
    } else if (fireSensor < 4) {
      Serial.println("right");

      while (fireSensor != 4) {
        motors.moveTank(baseSpeed, -baseSpeed);
        isFire(&fireSensor);
      }

      motors.forward(0, 0);

    } else if (fireSensor > 4) {
      Serial.println("left");

      while (fireSensor != 4) {
        motors.moveTank(-baseSpeed, baseSpeed);
        isFire(&fireSensor);
      }

      motors.forward(0, 0);
    }
  }

  else {
    motors.forward(baseSpeed, baseSpeed);
  }
}


// bool isLine(short *lightSensor) {
//   for (unsigned int i = 0; i < 8; i++) {
//     if (lightSensors.getLight(i) == 1) {
//       *lightSensor = i;
//       return true;
//     }
//   }
//
//   *lightSensor = -1;
//   return false;
// }


int isWall(short *ultrasonicSensor) {
  if (prox.distanceCm(0) < 10) {
    *ultrasonicSensor = 0;
    return TURN;
  }

  else if (prox.distanceCm(1) < 10) {
    *ultrasonicSensor = 1;
    return TURN;
  }

  else if (prox.distanceCm(3) < 10) {
    *ultrasonicSensor = 3;
    return TURN;
  }

  if (prox.distanceCm(0) < 15) {
    *ultrasonicSensor = 0;
    return SLOW_DOWN;
  }

  else if (prox.distanceCm(1) < 15) {
    *ultrasonicSensor = 1;
    return SLOW_DOWN;
  }

  else if (prox.distanceCm(3) < 15) {
    *ultrasonicSensor = 3;
    return SLOW_DOWN;
  }

  *ultrasonicSensor = -1;

  return 0;
}


bool isFire(short *fireSensor) {
  if (fireSensors.getFire(4) == 0) {
    *fireSensor = 4;
    return true;
  }

  for (unsigned int i = 0; i < 9; i++) {
    if (fireSensors.getFire(i) == 0) {
      *fireSensor = i;
      return true;
    }
  }

  *fireSensor = -1;

  return false;
}
