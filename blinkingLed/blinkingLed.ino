const int led = 7;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(1000); // millisecond
  digitalWrite(led, LOW);
  delay(1000);
}
