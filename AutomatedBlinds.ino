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
      
      //Twist blinds fully open
      case 16753245:
      digitalWrite(LED, HIGH);
      
      // Sets motor direction clockwise
      digitalWrite(dirPin, HIGH); 
  
      // Spin motor 18 rotation
      for(int x = 0; x < (STEPS_PER_REV * 18); x++) {
        digitalWrite(stepPin, HIGH); 
        delayMicroseconds(1000); 
        digitalWrite(stepPin, LOW); 
        delayMicroseconds(1000); 
      }
      break;

      //Twist blinds fully closed
      case 16736925:
      digitalWrite(LED, LOW);
      
      // Sets motor direction counterclockwise
      digitalWrite(dirPin, LOW);
  
      // Spin motor 18 rotations
      for(int x = 0; x < (STEPS_PER_REV * 18); x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(1000);
      }
      break;

      //Twist blinds half closed
      case 16769565:
      digitalWrite(LED, LOW);

      //Sets motor direction counterclockwise
      digitalWrite(dirPin, LOW); 

      // Spin motor 9 rotations
      for(int x = 0; x < (STEPS_PER_REV * 9); x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
      break;

      //Twist blinds half open
      case 16720605:
      digitalWrite(LED, HIGH);

      //Sets motor direction clockwise
      digitalWrite(dirPin, HIGH); 

      // Spin motor 9 rotations
      for(int x = 0; x < (STEPS_PER_REV * 9); x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
      break;
    }
    irrecv.resume();
  }
  delay(1);
}
