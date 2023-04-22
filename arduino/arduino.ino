#include <arduino-timer.h>

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

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

void takeReading() {
  light0 = analogRead(light0Pin);
  light1 = analogRead(light1Pin);
  light2 = analogRead(light2Pin);
  light3 = analogRead(light3Pin);
  moisture = analogRead(moisturePin);
}
