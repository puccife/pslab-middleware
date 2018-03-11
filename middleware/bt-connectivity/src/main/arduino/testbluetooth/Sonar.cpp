/* Models the sonar sensor and provide methods to read the detected values.*/

#include "Sonar.h"

#include "Arduino.h"

/*
 * Sound speed in cm/us
 */
#define SOUND_SPEED 29.0f

static float microsecondsToCentimeters(unsigned long microseconds);

Sonar::Sonar(int echoPin, int trigPin) : echoPin(echoPin), trigPin(trigPin) {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

float Sonar::getDistance() {
  unsigned long duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return microsecondsToCentimeters(duration);
}

float microsecondsToCentimeters(unsigned long microseconds) {
  return ((float)microseconds) / (SOUND_SPEED * 2.0f);
}
