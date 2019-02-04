int ledPin = 3;
int buttonPin = 6;

int butt;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, INPUT);
}

void loop() {
 butt = digitalRead(buttonPin1);

 digitalWrite(ledPin, butt);
 
}
