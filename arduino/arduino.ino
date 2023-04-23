// IMPORTS
#include <arduino-timer.h>
#include "pitches.h"

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

int lightThreshold = 100;

// Define Motor Driver pins
int motorAEnablePin = 5;
int motorBEnablePin = 6;
int motorAInput1 = 4;
// int motorAInput2 = 3;
int motorBInput1 = 7;
// int motorBInput2 = 5;

// Speaker
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};



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
  }
  digitalWrite(pump, LOW);
}

void turnToSun() {
  takeReading();
  while ((max(flLight, blLight) != flLight) && (max(frLight, brLight) != frLight)) {
    //    Not facing max light
    if (max(flLight, blLight) > (max(frLight, brLight))) {
      //    turn left
    }
    else {
      //    turn right
    }
    takeReading();
  }
}

void drive() {
  takeReading();

  while (((flLight + frLight) / 2) < lightThreshold) {
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

/**
 * @brief Plays a song as defined by the global variables at the top
 *
 */
void playSong() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    noTone(8);
  }
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
  playSong();
  delay(500);

  // put your main code here, to run repeatedly: 
}
