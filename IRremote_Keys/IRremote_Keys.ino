#include <IRremote.h>

const int REC_PIN = 7;
IRrecv irrecv(REC_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  if (irrecv.decode(&results)) {
     Serial.println(results.value, HEX);
     irrecv.resume();
   }
}
