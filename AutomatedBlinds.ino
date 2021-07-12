//Include the Arduino Stepper Library
#include <Stepper.h>
#include <IRremote.h>

//CONSTANTS
//Steps per internal motor revolution
const float STEPS_PER_REV = 32;

const int irReceiverPin = 7;
IRrecv irrecv(irReceiverPin);
decode_results results;

//Amount of Gear Reduction
const float GEAR_RED = 64;

//Steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

//VARIABLES
int StepsRequired;
int LED = 6;

//Create Instance of Stepper Class
//Pins used are 8,9,10,11 connceted to ULN2003 Motor Driver In1, In2, In3, In4
//Pins entered in sequence 1-3-2-4 for proper step sequencing

Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  pinMode(LED, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    long int decCode = results.value;
    switch (results.value) {
      case 16753245:
      digitalWrite(LED, HIGH);
      StepsRequired = STEPS_PER_OUT_REV / 2;
      steppermotor.setSpeed(400);
      steppermotor.step(StepsRequired);
      break;

      case 16736925:
      digitalWrite(LED, LOW);
      StepsRequired = - STEPS_PER_OUT_REV / 2;
      steppermotor.setSpeed(400);
      steppermotor.step(StepsRequired);
      break;
    }
    irrecv.resume();
  }
  delay(1);
}
