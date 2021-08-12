#include <IRremote.h>

//CONSTANTS
const int dirPin = 2;  // Direction
const int stepPin = 3; // Step
const int STEPS_PER_REV = 200; // Steps per rotation
const int irReceiverPin = 7;

IRrecv irrecv(irReceiverPin);
decode_results results;

//VARIABLES
int LED = 6;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  //Receives IR signal from remote, decodes it and enters the correct case to turn CW or CCW
  if (irrecv.decode(&results)) {
    long int decCode = results.value;
    switch (results.value) {
      //Twist Blinds Open
      case 16753245:
      digitalWrite(LED, HIGH);
      
      // Sets motor direction clockwise
      digitalWrite(dirPin,HIGH); 
  
      // Spin motor one rotation slowly
      for(int x = 0; x < STEPS_PER_REV; x++) {
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(1000); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(1000); 
      }
      break;

      //Twist Blinds Closed
      case 16736925:
      digitalWrite(LED, LOW);
      
      // Sets motor direction counterclockwise
      digitalWrite(dirPin,LOW);
  
      // Spin motor two rotations quickly
      for(int x = 0; x < (STEPS_PER_REV * 2); x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(100);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(1000);
      }
      break;    
    }
    irrecv.resume();
  }
  delay(1);
}
