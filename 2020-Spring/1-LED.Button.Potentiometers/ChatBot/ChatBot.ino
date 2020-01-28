void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
}
char buffer[12];
void loop() {
  Serial.println("Enter up to 10 characters...");
  while (!Serial.available() > 0) {
    delay(100); 
  }
  for (int i = 0; i < 12; i++) {
    buffer[i] = '\0';
  }
  int idx = 0;
  while (Serial.available()&& idx < 12) {
    buffer[idx] = Serial.read();
    idx++;
  }
  buffer[11] = '\0';
  Serial.print("Your message was: ");
  Serial.println(buffer);
}
