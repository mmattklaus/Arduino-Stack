#include <IRremote.h>
#include <Servo.h>

const int IR_OUT = 7;
const int SERVO_PIN = 14;
IRrecv irrecv(IR_OUT);
decode_results result;
Servo servo;

unsigned int key_value = 0;
unsigned int angle = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  // pinMode(SERVO_PIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&result)) {
    if (result.value == 0XFFFFFFFF)
      result.value = key_value;
    // Serial.println(result.value, HEX);
    switch(result.value) {
      case 0xFFE01F: // Vol -
        rotateLeft();
        break;
      case 0xFFA857: // Vol +
        rotateRight();
        break;  
    }
    // Serial.println(angle);
    // servo.write(angle);
    key_value = result.value;
    irrecv.resume();
    delay(1000);
  }
}

void rotateLeft () {
  angle -= 45;
  resolveAngle();
}

void rotateRight () {
  angle += 45;
  resolveAngle();
}

void resolveAngle () {
  if (angle < 0 or angle > 180)
    angle = 0;
  servo.write(45);
}
