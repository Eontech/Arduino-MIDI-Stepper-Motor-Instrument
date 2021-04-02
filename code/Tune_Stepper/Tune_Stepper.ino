/*
 * TuneStepper
 * 
 * By Jonathan Kayne
 * April 2018
 * 
 * This program allows the user to input a speed value through the serial monitor 
 * and runs that motor at that speed.
 * You should compare the sound with the value on the pitches.h file
 * and check for the resonant frequency of your stepper. 
 * The resonant frequency will cause the motor to produce a garbled tone.
 * It will appear as if the motor has stalled. If this happens, raise/lower the pitch value
 * by an octave.
 */

//ARDUINO PINS
#define stepPin 3
#define dirPin 6
#define enPin 8

unsigned long motorSpeed = 0;
unsigned long prevStepMicros = 0;
bool stepState = false;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  Serial.begin(9600);
  while(!Serial) {/*do nothing*/;}

  Serial.println("\n\nPlease Enter a Stepper Motor Speed Value.");
}

void loop() {
  if (motorSpeed == 0)
  {
    digitalWrite(enPin, HIGH);
  }
  else
  {
    digitalWrite(enPin, LOW);
  }
  // Srg: Serial monitor must be set to 'No line ending' for this to work
  while(Serial.available() > 0) //taking in the speed value
  {
    motorSpeed = Serial.parseInt();
    Serial.print("Stepper Motor Speed set to: ");
    Serial.println(motorSpeed);
    Serial.println("\nPlease Enter a Stepper Motor Speed Value.");
  }
  if ((micros() - prevStepMicros >= motorSpeed) && motorSpeed != 0)//stepper motor speed control
  {
    prevStepMicros += motorSpeed;
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
  }
}
