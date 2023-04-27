#include <avr/sleep.h>
#include "FSM.h"

// PINS
#define motionReader 2
#define pingPin 7 // Trigger Pin of Ultrasonic Sensor
#define echoPin 6 // Echo Pin of Ultrasonic Sensor
#define whiteLed 9
#define greenLed 10

#define LED 13

// SYSTEM VARIABLES
int readVal = -1;

// Ultrasonic code from https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm



void setup() {
  // pinMode(motionReader, INPUT);
  pinMode(motionReader, INPUT);
  pinMode(whiteLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  Serial.begin(115200);
}

void loop() {
  // Check Motion
  // readVal = digitalRead(motionReader);
  // Serial.println(readVal);

  //  long duration, inches, cm;
  //  pinMode(pingPin, OUTPUT);
  //  digitalWrite(pingPin, LOW);
  //  delayMicroseconds(2);
  //  digitalWrite(pingPin, HIGH);
  //  delayMicroseconds(10);
  //  digitalWrite(pingPin, LOW);
  //  pinMode(echoPin, INPUT);
  //  duration = pulseIn(echoPin, HIGH);
  //  inches = microsecondsToInches(duration);
  //  cm = microsecondsToCentimeters(duration);
  //  Serial.print(inches);
  //  Serial.print("in, ");
  //  Serial.print(cm);
  //  Serial.print("cm");
  //  Serial.println();

  //  if(readVal){
  //   digitalWrite(whiteLed, HIGH);
  //   delay(200);
  //   digitalWrite(whiteLed, LOW);
  //  }

  //  if(inches < 7) {
  //   digitalWrite(greenLed, HIGH);
  //   delay(200);
  //   digitalWrite(greenLed, LOW);
  //  }

  // readVal = digitalRead(motionReader);
  // digitalWrite(whiteLed, readVal);
  delay(5000);
  sleep();

}

void sleep(){
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(motionReader), wakeUp, RISING );
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  Serial.println("Going to sleep");
  digitalWrite(LED, LOW);
  delay(1000);
  sleep_mode();
  Serial.println("Just woke up!");
  digitalWrite(LED, HIGH);
}

void wakeUp(){
  Serial.println("Running ISR");
  sleep_disable();
  detachInterrupt(0);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
