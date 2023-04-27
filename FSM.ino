#include "FSM.h"

void initFSM() {
  // TODO Initialize pins used in state machine
  motionDetectedFlag = 0;
}

FSMState nextStateFunction(FSMState currentState) {
  // Log the current state
  Serial.print("Current state: ");
  Serial.println(currentState);

  FSMState nextState = error;

  if (currentState == sleepState) {
    nextState = poll;
  } else if (currentState == poll) {
    if (motionDetectedFlag) {
      nextState = detected;
    } else {
      nextState = sleepState;
    }
  } else if (currentState == detected) {
    nextState = sleepState;
  } else if (currentState == snooze) {
    nextState = transition;
  } else if (currentState == transition) {
    nextState = sleepState;
    motionDetectedFlag = 0;
  }

  // Log the current state
  Serial.print("Next state: ");
  Serial.println(nextState);
  return nextState;
}

void outputStateFunction(FSMState currentState) {
  if (currentState == sleepState) {
    // TODO Implement
    delay(10000);
  } else if (currentState == poll) {
    // TODO setup timer interupt to exit polling state after 45 seconds (subject to change)
    pollDistanceSensor();
  } else if (currentState == detected) {
    // TODO implement
  } else if (currentState == snooze) {
    // Enter low power mode than can be interrupted from button interrupts or timer

    // If timer interrupt, wake cpu

    // If snooze button interrupt, wake cpu, add more time to the timer, sleep again

    // If cancel button interrupt, wake cpu 
  } else if (currentState == transition) {
    // Slow blink 5 times over 5 seconds
  } else {
    // Illuminate error light
    // Todo, research if its possible to make the arduino reset itself with the reset pin
  }
}

void pollDistanceSensor() {
  // TODO update to use timer interupt to break infinite polling loop, not for loop
  long duration, inches, cm;
  for (int i = 0; i < 45; i++) {
    // Get sensor data
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    pinMode(echoPin, INPUT);

    duration = pulseIn(echoPin, HIGH);
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    if (inches < 7) {
      motionDetectedFlag = 1;
      return;
    }
  }
}