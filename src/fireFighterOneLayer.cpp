#include "include.h"
#include "Motors.h"
#include "LightSensors.h"
#include "UltrasonicSensors.h"
#include "FireSensors.h"
#include "fan.h"

#define SLOW_DOWN 1
#define TURN 2

int motorPins[] = {2, 3, 4, 5};
int lightSensorsPins[] = {13, 10, 12, 11, 9, 6, 7, 8};
int trigPins[] = {29, 48, 49, 50, 33};
int echoPins[] = {47, 30, 31, 32, 51};
int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};
short fanPin = 45;

const int baseSpeed = 150;

bool wall, line, fire;

Motors motors(motorPins, 255);
LightSensors lightSensors(lightSensorsPins);
UltrasonicSensors prox(trigPins, echoPins);
FireSensors fireSensors(fireSensorsPins);


bool isLine(short *lightSensor);
int isWall(short *ultrasonicSensor);
bool isFire(short *fireSensor);

void readUltrasonic();
void readFireSensors();
void readLineSensors();
void checkEverything();

TimedAction readWall(10, readUltrasonic);
TimedAction readLine(10, 10, readLineSensors);
TimedAction readFire(20, 10, readFireSensors);
TimedAction forward(20, 10, checkEverything);


void setup() {
  Serial.begin(9600);
}


void loop() {
  readWall.check();
  readLine.check();
  readFire.check();
  forward.check();
}


void readUltrasonic() {
  wall = true;
  int ultrasonicSensor, lightSensor, fireSensor;

  if (prox.distanceCm(0) < 20 && isLine(&lightSensor) && (lightSensor == 0 || lightSensor == 1 || lightSensor == 7)
      && isFire(&fireSensor) && fireSensor == 4) {
    Serial.println("Blowing candle.");
    motors.stop();
    digitalWrite(fanPin, HIGH);
    delay(3000);
    digitalWrite(fanPin, LOW);

    motors.back(baseSpeed, baseSpeed);
    delay(1000);
    motors.moveTank(baseSpeed, -baseSpeed);
    delay(1000);
    motors.stop();

    return;
  }

  else if (isWall(&ultrasonicSensor) == SLOW_DOWN) {
    int currSpeed = baseSpeed - 30;
    Serial.println("Slowing down.");
    motors.forward(currSpeed, currSpeed);

    return;
  }

  else if (isWall(&ultrasonicSensor) == TURN) {
    Serial.println("Turning.");

    if (ultrasonicSensor == 0) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (ultrasonicSensor == 1) {
      motors.moveTank(baseSpeed, -baseSpeed);
    }

    else if (ultrasonicSensor == 3) {
      motors.moveTank(-baseSpeed, baseSpeed);
    }

    return;
  }

  wall = false;
}


void readLineSensors() {
  line = true;
  int lightSensor;

  if (isLine(&lightSensor)) {
    Serial.print("Line detected");

    if (lightSensor == 0 || lightSensor == 7) {
      motors.moveTank(baseSpeed, -baseSpeed);
      Serial.println(", going right.");
    }

    else if (lightSensor == 1) {
      motors.moveTank(-baseSpeed, baseSpeed);
      Serial.println(", going left.");
    }

    return;
  }

  line = false;
}


void readFireSensors() {
  fire = true;

  int fireSensor;

  if (isFire(&fireSensor)) {
    Serial.println("Fire detected!");

    if (fireSensor == 4) {
      fire = false;
    }

    else if (fireSensor < 4) {
      Serial.println("Going right.");

      while (fireSensor != 4) {
        motors.forward(baseSpeed, -baseSpeed);
        isFire(&fireSensor);
      }
    }
    else if (fireSensor > 4) {
      Serial.println("Going left.");

      while (fireSensor != 4) {
        motors.forward(-baseSpeed, baseSpeed);
        isFire(&fireSensor);
      }
    }

    return;
  }

  fire = false;
}


void checkEverything() {
  if (!wall && !fire) {
    Serial.println("Going forward.");
    motors.forward(baseSpeed, baseSpeed);
  }
}


bool isLine(short *lightSensor) {
  for (unsigned int i = 0; i < 8; i++) {
    if (lightSensors.getLight(i) == 1) {
      *lightSensor = i;
      return true;
    }
  }

  *lightSensor = -1;
  return false;
}


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
