int r = 9;
int g = 10;
int b = 11;

void setup() {
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {

  analogWrite(r, 0);
  analogWrite(b, 0);
  analogWrite(g, 0);

  for(int k = 0; k < 256; k++) {
    analogWrite(r, k);
    analogWrite(g, 255 - k);
    analogWrite(b, 0);
    delay(2);
  }

  analogWrite(r, 0);
  analogWrite(b, 0);
  analogWrite(g, 0);

  for(int k = 0; k < 256; k++) {
    analogWrite(r, k);
    delay(2);
  }

  for(int k = 0; k < 256; k++) {
    analogWrite(g, k);
    delay(2);
  }
  
  delay(1000);
}
