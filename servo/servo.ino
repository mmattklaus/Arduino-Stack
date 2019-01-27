#include <Servo.h>

int servoPin = 6;
int servoAngle = 0;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
}

void loop() {
  servo.write(45);      // Turn SG90 servo Left to 45 degrees
   delay(1000);          // Wait 1 second
   servo.write(90);      // Turn SG90 servo back to 90 degrees (center position)
   delay(1000);          // Wait 1 second
   servo.write(135);     // Turn SG90 servo Right to 135 degrees
   delay(1000);          // Wait 1 second
   servo.write(90);      // Turn SG90 servo back to 90 degrees (center position)
   delay(1000);
}
