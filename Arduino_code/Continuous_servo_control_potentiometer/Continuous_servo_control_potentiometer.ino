#include <Servo.h>

Servo servo;

const int servoPin = 9;
const int potPin   = A0;

// Servo pulse values
const int pulseMin  = 500;
const int pulseMax  = 2500;
const int pulseStop = 1500;

// Potentiometer calibration
const int potMin    = 0;
const int potMax    = 700;
const int potCenter = 350;

void setup() {
  servo.attach(servoPin);
  servo.writeMicroseconds(pulseStop);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);

  // Clamp pot value to avoid overflow
  potValue = constrain(potValue, potMin, potMax);

  int speed;
  int pulseWidth;

  if (potValue < potCenter) {
    // Reverse direction
    speed = map(potValue, potMin, potCenter, -100, 0);
    pulseWidth = map(speed, -100, 0, pulseMin, pulseStop);
  } else {
    // Forward direction
    speed = map(potValue, potCenter, potMax, 0, 100);
    pulseWidth = map(speed, 0, 100, pulseStop, pulseMax);
  }

  servo.writeMicroseconds(pulseWidth);

  // ----- SERIAL OUTPUT (PLOTTER FRIENDLY) -----
  Serial.print(potValue);
  Serial.print(" ");
  Serial.print(pulseWidth);
  Serial.print(" ");
  Serial.println(speed);

  delay(30);
}