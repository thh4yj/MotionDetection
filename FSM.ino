#include "FSM.h"

void initFSM() {
  // TODO Initialize pins used in state machine
  motionDetectedFlag = false;
  runPolling = false;
  pollCounter = 0;

  TCCR1A = 0;           // set entire TCCR1A register to 0
  TCCR1B = 0;           // same for TCCR1B
  TCNT1 = 0;            //initialize counter value to 0
  TCCR1B |= B00000101;  //Prescaler 1024
  TIMSK1 |= B00000010;
  OCR1A = 65535;  // ~ 4 seconds
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
    motionDetectedFlag = false;
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
  long duration, inches, cm;
  cli();  // Enable interrupts

  while (runPolling) {
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
      motionDetectedFlag = true;
      return;
    }
  }

  sei();  // Disable interrupts 
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;  // Reset timer for next interrupt
  pollCounter += 1;
  if (pollCounter == 3) {
    pollCounter = 0;
    runPolling = false;
  }
}