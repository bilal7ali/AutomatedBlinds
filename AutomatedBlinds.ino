#include <IRremote.h>

//CONSTANTS
const int dirPin1 = 4; // Direction
const int stepPin1 = 5; // Step
const int dirPin2 = 2; // Direction
const int stepPin2 = 3; // Step
const int STEPS_PER_REV = 200; // Steps per rotation
const int irReceiverPin = 7;

IRrecv irrecv(irReceiverPin);
decode_results results;

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  //Receives IR signal from remote, decodes it and enters the correct case to turn CW or CCW
  if (irrecv.decode(&results)) { // If the IR receiver receives data
    long int decCode = results.value;
    switch (results.value) {

      // Twist blinds half closed
      case 16753245: // Button 1

        //Sets motor direction counterclockwise
        digitalWrite(dirPin1, LOW);

        // Spin motor 9 rotations
        for (int x = 0; x < (STEPS_PER_REV * 9); x++) {
          digitalWrite(stepPin1, HIGH);
          delayMicroseconds(1000);
          digitalWrite(stepPin1, LOW);
          delayMicroseconds(1000);
        }
        break;

      // Twist blinds half open
      case 16736925: // Button 2

        //Sets motor direction clockwise
        digitalWrite(dirPin1, HIGH);

        // Spin motor 9 rotations
        for (int x = 0; x < (STEPS_PER_REV * 9); x++) {
          digitalWrite(stepPin1, HIGH);
          delayMicroseconds(1000);
          digitalWrite(stepPin1, LOW);
          delayMicroseconds(1000);
        }
        break;

      // Opens blinds halfway
      case 16769565: // Button 3

        //Sets motor direction clockwise
        digitalWrite(dirPin2, HIGH);

        // Spin motor 13 rotations
        for (int x = 0; x < (STEPS_PER_REV * 13); x++) {
          digitalWrite(stepPin2, HIGH);
          delayMicroseconds(1000);
          digitalWrite(stepPin2, LOW);
          delayMicroseconds(1000);
        }
        break;

      //Closes blinds halfway
      case 16720605: // Button 4

        //Sets motor direction clockwise
        digitalWrite(dirPin2, LOW);

        // Spin motor 13 rotations
        for (int x = 0; x < (STEPS_PER_REV * 13); x++) {
          digitalWrite(stepPin2, HIGH);
          delayMicroseconds(1000);
          digitalWrite(stepPin2, LOW);
          delayMicroseconds(1000);
        }
        break;
    }
    irrecv.resume();
  }
  delay(1);
}
