#include "include.h"
#include "Motors.h"
#include "LightSensors.h"
#include "UltrasonicSensors.h"
#include "FireSensors.h"
#include "fan.h"

#define SLOW_DOWN 1
#define TURN 2

int motorPins[] = {2, 3, 4, 5};
int lightSensorsPins[] = {13, 10, 12, 9, 6, 7, 8};
int trigPins[] = {29, 48, 49, 50, 33};
int echoPins[] = {47, 30, 31, 32, 51};
int fireSensorsPins[] = {39, 40, 22, 41, 23, 42, 24, 25, 28};
int multiplexPins[] = {43, 44};
int fanPin = 45;
int servoPin = 11;

const int baseSpeed = 130;

bool wall, line, fire;

bool wallBefore, lineBefore;

Motors motors(motorPins, 255);
LightSensors lightSensors(lightSensorsPins);
UltrasonicSensors prox(trigPins, echoPins);
FireSensors fireSensors(fireSensorsPins, multiplexPins);

Servo servo;


bool isLine(int *lightSensor);
int isWall(int *ultrasonicSensor);
bool isFire(int *fireSensor);

bool checkExtinguish();

void readUltrasonic();
void readFireSensors();
void readLineSensors();
void checkEverything();

TimedAction readLine(10, readLineSensors);
TimedAction readWall(10, 10, readUltrasonic);
TimedAction readFire(20, 10, readFireSensors);
TimedAction forward(20, 10, checkEverything);


void setup() {
  servo.attach(servoPin);
  servo.write(179);
  Serial.begin(9600);
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 18; j++) {
      fireSensors.getFire(j);
    }
  }
}


void loop() {
  readWall.check();
  readLine.check();
  readFire.check();
  forward.check();
}


void readUltrasonic() {
  wall = true;
  int ultrasonicSensor;

  if (checkExtinguish()) {
    return;
  }

  else if (isWall(&ultrasonicSensor) == SLOW_DOWN) {
    int currSpeed = baseSpeed - 40;
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

  if (checkExtinguish()) {
    return;
  }

  if (isLine(&lightSensor)) {
    Serial.print("Line detected");

    if (lightSensor == 0 || lightSensor == 1) {
      Serial.println(", going right.");

      motors.back(baseSpeed, baseSpeed);
      delay(500);
      motors.moveTank(-baseSpeed, baseSpeed);
      delay(500);
      motors.stop();

      return;
    }

    else if (lightSensor == 6) {
      Serial.println(", going left.");

      motors.back(baseSpeed, baseSpeed);
      delay(500);
      motors.moveTank(baseSpeed, -baseSpeed);
      delay(500);
      motors.stop();

      return;
    }
  }

  line = false;
}


void readFireSensors() {
  fire = true;

  int fireSensor;

  if (checkExtinguish()) {
    return;
  }

  if (wall) {
    return;
  }

  if (isFire(&fireSensor)) {
    Serial.println("Fire detected!");

    motors.stop();

    if (fireSensor == 4) {
      fire = false;
      return;
    }

    else if (fireSensor < 4) {
      Serial.println("Going right.");

      while (fireSensor != 4) {
        motors.moveTank(baseSpeed, -baseSpeed);
        isFire(&fireSensor);
      }
    }
    else if (fireSensor > 4) {
      Serial.println("Going left.");

      while (fireSensor != 4) {
        motors.moveTank(-baseSpeed, baseSpeed);
        isFire(&fireSensor);
      }
    }

    return;
  }

  fire = false;
}


void checkEverything() {
  if (!wall && !fire && !line) {
    motors.stop();
    Serial.println("Going forward.");
    motors.forward(baseSpeed, baseSpeed);
  }

  if (wall && wallBefore && line && lineBefore) {
    motors.back(baseSpeed, baseSpeed);
    delay(500);
  }

  wallBefore = wall;
  lineBefore = line;
}


bool checkExtinguish() {
  int lightSensor, fireSensor;

  if (prox.distanceCm(0) < 22 && isLine(&lightSensor) && lightSensor == 0 && isFire(&fireSensor) && fireSensor == 4) {
    Serial.println("Blowing candle.");
    motors.stop();
    digitalWrite(fanPin, HIGH);
    servo.write(180);
    delay(1700);
    servo.write(150);
    delay(1700);
    servo.write(120);
    delay(1700);
    digitalWrite(fanPin, LOW);

    motors.back(baseSpeed, baseSpeed);
    delay(1000);
    motors.moveTank(baseSpeed, -baseSpeed);
    delay(1000);
    motors.stop();

    return true;
  }

  return false;
}


bool isLine(int *lightSensor) {
  for (unsigned int i = 0; i < 7; i++) {
    if (lightSensors.getLight(i) == 1) {
      *lightSensor = i;
      return true;
    }
  }

  *lightSensor = -1;
  return false;
}


int isWall(int *ultrasonicSensor) {
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


bool isFire(int *fireSensor) {
  if (fireSensors.getFire(4) == 0) {
    *fireSensor = 4;
    return true;
  }

  for (unsigned int i = 0; i < 18; i++) {
    if (fireSensors.getFire(i) == 0) {
      *fireSensor = i;
      return true;
    }
  }

  *fireSensor = -1;

  return false;
}
