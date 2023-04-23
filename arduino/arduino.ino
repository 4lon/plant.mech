// IMPORTS
#include <arduino-timer.h>

// GLOBAL VARIABLES
int flLightPin = A0;
int frLightPin = A1;
int blLightPin = A2;
int brLightPin = A3;
int moisturePin = A4;

int flLight;
int frLight;
int blLight;
int brLight;
int moisture;

int pump = 2;
int waterThreshold = 360;

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
  digitalWrite(motorAEnablePin, LOW);
  digitalWrite(motorBEnablePin, LOW);
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
  while (true) {
    takeReading();
    Serial.println(flLight);
    Serial.println(frLight);
    Serial.println(blLight);
    Serial.println(brLight);
    Serial.println(moisture);
    delay(1000);
  }
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
    count++;
  }
  digitalWrite(pump, LOW);
}


// SETUP FUNCTION
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initMotors();
  initPump();
}


// MAIN FUNCTION
void loop() {
  // put your main code here, to run repeatedly: 
}
