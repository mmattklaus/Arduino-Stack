#include <IRremote.h>
#include <Servo.h>
#include <EEPROM.h>

const int IND_PIN = 8;
const int REC_PIN = 7;
const int SERVO_PIN = 9;

IRrecv irrecv(REC_PIN);
decode_results results;
Servo servo;

int pos = 0;
int address = 0;
const int MIN_ROT = 15;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  servo.attach(SERVO_PIN);

  pinMode(IND_PIN, OUTPUT);

  // pos = servo.read();
  pos = EEPROM.read(address);
  Serial.println(pos);
  if (pos > 180) {
    pos = 0;
  }
  servo.write(pos);
}

void blink_ind(int times = 3);
void rotate(bool);
void loop() {
  if (irrecv.decode(&results)) {
    // Serial.print("HEX Value: ");
    // Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xFF02FD: // + button
        Serial.println("+ button pressed");
        rotate(true);
        break;

      case 0xFF22DD: // - button
        Serial.println("- button pressed");
        rotate(false);
        break;
    }
    irrecv.resume();
  }

}

void rotate(bool add) {
  int current_pos = pos;

  Serial.print("Current angle: ");
  Serial.println(pos);
  if (add && pos == 180) {
    blink_ind();
  } else if (!add && pos == 0) {
    blink_ind();
  }  else {
    if (add) {
      pos += MIN_ROT;
      Serial.println("Added angle");
      if (pos > 180) {
        pos = 180;
      }
    } else {
      pos -= MIN_ROT;
      Serial.println("Added angle");
      if (pos < 0) {
        pos = 0;
      }
    }

    int diff, writeAngle;
    if (add) {
      diff = pos - current_pos;
      for (int ii = 0; ii < diff; ii++) {
        current_pos += 1;
        servo.write(current_pos);
        delay(15);  
      }
    } else {
      diff = current_pos - pos;
      for (int ii = diff; ii > 0; ii--) {
        current_pos -= 1;
        servo.write(current_pos);
        delay(15);  
      }
    }
    pos = current_pos;
    EEPROM.write(address, pos);
    Serial.print("EEPROM WRITE VALUE: ");
    Serial.println(EEPROM.read(address));

    if (pos == 0 || pos == 180) {
      blink_ind();
    }
  }

}

void blink_ind(int times) {
  for (int i = 0; i < times; i += 1) {
    digitalWrite(IND_PIN, HIGH);
    delay(250);
    digitalWrite(IND_PIN, LOW);
    delay(250);
  }
}
