// IMPORTS
#include <arduino-timer.h>

// GLOBAL VARIABLES
int flLightPin = A0;
int frLightPin = A3;
int blLightPin = A2;
int brLightPin = A1;
int moisturePin = A4;

int flLight;
int frLight;
int blLight;
int brLight;
int moisture;

int pump = 2;
int waterThreshold = 360;

int lightThreshold = 300;

// Define Motor Driver pins
int motorAEnablePin = 5;
int motorBEnablePin = 6;
int motorAInput1 = 4;
// int motorAInput2 = 3;
int motorBInput1 = 7;
// int motorBInput2 = 5;

void initMotors() {
  // Set Motor Driver pins as output
  pinMode(motorAEnablePin, OUTPUT);
  pinMode(motorBEnablePin, OUTPUT);
  pinMode(motorAInput1, OUTPUT);
  // pinMode(motorAInput2, OUTPUT);
  pinMode(motorBInput1, OUTPUT);
  // pinMode(motorBInput2, OUTPUT);

  // Enable both motors
//  digitalWrite(motorAEnablePin, LOW);
//  digitalWrite(motorBEnablePin, LOW);
  digitalWrite(motorAEnablePin, LOW);
  digitalWrite(motorBEnablePin, LOW);
}

void rightMotorForward() {
  digitalWrite(motorBEnablePin, HIGH);
  digitalWrite(motorBInput1, LOW);
}

void rightMotorBackward() {
  digitalWrite(motorBEnablePin, HIGH);
  digitalWrite(motorBInput1, HIGH);
}

void rightMotorOff() {
  digitalWrite(motorBEnablePin, LOW);
}

void leftMotorForward() {
  digitalWrite(motorAEnablePin, HIGH);
  digitalWrite(motorAInput1, HIGH);
}

void leftMotorBackward() {
  digitalWrite(motorAEnablePin, HIGH);
  digitalWrite(motorAInput1, LOW);
}

void leftMotorOff() {
  digitalWrite(motorAEnablePin, LOW);
}

void turnLeft() {
  rightMotorForward();
  leftMotorBackward();
}

void turnRight() {
  rightMotorBackward();
  leftMotorForward();
}

void driveForward() {
  rightMotorForward();
  leftMotorForward();
}

void driveBackward() {
  rightMotorBackward();
  leftMotorBackward();
}

void stop() {
  rightMotorOff();
  leftMotorOff();
}

/**
 *@brief Tests the motors in an infinite loop
 *
 */
void motorTest() {
  while (true) {
    rightMotorForward();
    delay(1000);
    rightMotorBackward();
    delay(1000);
    rightMotorOff();
    delay(500);
    leftMotorForward();
    delay(1000);
    leftMotorBackward();
    delay(1000);
    leftMotorOff();
    delay(500);
    rightMotorForward();
    leftMotorForward();
    delay(1000);
    rightMotorBackward();
    leftMotorBackward();
    delay(1000);
    rightMotorOff();
    leftMotorOff();
    delay(5000);
    
//    // Make Motor A spin forward
//    digitalWrite(motorAInput1, HIGH);
//    // digitalWrite(motorAInput2, LOW);
//
//    // Make Motor B spin backward
//    digitalWrite(motorBInput1, HIGH);
//    // digitalWrite(motorBInput2, HIGH);
//
//    // Wait for 2 seconds
//    delay(2000);
//
//    // Stop both motors
//    digitalWrite(motorAInput1, LOW);
//    // digitalWrite(motorAInput2, LOW);
//    digitalWrite(motorBInput1, LOW);
//    // digitalWrite(motorBInput2, LOW);
//
//    // Wait for 1 second
//    delay(1000);
  }
}

void initPump() {
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
}

/**
  @brief Tests the pump in an infinite loop

*/
void pumpTest() {
  while (true) {
    // Make Motor A spin forward
    digitalWrite(pump, HIGH);

    // Wait for 2 seconds
    delay(1000);

    // Stop both motors
    digitalWrite(pump, LOW);

    // Wait for 1 second
    delay(1000);
  }
}

void sensorTest() {
  takeReading();
  Serial.println(flLight);
  Serial.println(frLight);
  Serial.println(blLight);
  Serial.println(brLight);
  Serial.println(moisture);
}



// LIBRARY FUNCTIONS
void takeReading() {
  flLight = analogRead(flLightPin);
  frLight = analogRead(frLightPin);
  blLight = analogRead(blLightPin);
  brLight = analogRead(brLightPin);
  moisture = analogRead(moisturePin);
}

void waterPlant() {
  long time = millis();
  digitalWrite(pump, HIGH);
  while ((analogRead(moisturePin) > waterThreshold) && (millis() < time + 1000)) {
  }
  digitalWrite(pump, LOW);
}

void turnToSun() {
  takeReading();
  while ((max(flLight, blLight) != flLight) && (max(frLight, brLight) != frLight) && (max(flLight, frLight) - min(flLight, frLight) > 30)) {
//    Not facing max light
  if (max(flLight, blLight) > (max(frLight, brLight))) {
//    turn left
    turnLeft();
  } else {
//    turn right
    turnRight();
  }
  delay(100);
  stop();
  takeReading();
  }
}

void drive() {
  takeReading();

  while (((flLight + frLight)/2) < lightThreshold) {
    // drive forward
    delay(100);
    takeReading();
  }
}

void moveToSun() {
  takeReading();

//  Face right direction
  turnToSun();
//  Drive towards
  drive();
}


// SETUP FUNCTION
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initMotors();
  initPump();
//  sensorTest();
}


// MAIN FUNCTION
void loop() {
  // put your main code here, to run repeatedly: 
  turnToSun();
  sensorTest();
}
