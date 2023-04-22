// IMPORTS
#include <arduino-timer.h>

// GLOBAL VARIABLES
int light0Pin = A0;
int light1Pin = A1;
int light2Pin = A2;
int light3Pin = A3;
int moisturePin = A4;

int light0;
int light1;
int light2;
int light3;
int moisture;

int pump = 2;

int pump = 2;

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
  digitalWrite(motorAEnablePin, HIGH);
  digitalWrite(motorBEnablePin, HIGH);
}

/**
 *@brief Tests the motors in an infinite loop
 *
 */
void motorTest() {
  while (true) {
    // Make Motor A spin forward
    digitalWrite(motorAInput1, HIGH);
    // digitalWrite(motorAInput2, LOW);

    // Make Motor B spin backward
    digitalWrite(motorBInput1, HIGH);
    // digitalWrite(motorBInput2, HIGH);

    // Wait for 2 seconds
    delay(2000);

    // Stop both motors
    digitalWrite(motorAInput1, LOW);
    // digitalWrite(motorAInput2, LOW);
    digitalWrite(motorBInput1, LOW);
    // digitalWrite(motorBInput2, LOW);

    // Wait for 1 second
    delay(1000);
  }
}



// LIBRARY FUNCTIONS
void takeReading() {
  light0 = analogRead(light0Pin);
  light1 = analogRead(light1Pin);
  light2 = analogRead(light2Pin);
  light3 = analogRead(light3Pin);
  moisture = analogRead(moisturePin);
}


// SETUP FUNCTION
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
}

// MAIN FUNCTION
void loop() {
  // put your main code here, to run repeatedly: 
  takeReading();
  Serial.println(light0);
  Serial.println(light1);
  Serial.println(light2);
  Serial.println(light3);
  Serial.println(moisture);
  delay(1000);
}
