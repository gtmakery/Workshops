#define PIN_LED 3

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  analogWrite(PIN_LED, (sin(millis()/1000.0)+1) * 127);
  delay(10);
}
