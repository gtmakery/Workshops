int k = 1;
float i;

void setup() {
  Serial.begin(9600); // Should be done in setup
}

void loop() {
  Serial.println("This is serial communication");
  
  k = 6 + k*3;
  i = k/3;
  Serial.print("Value of i is: ");
  Serial.println(i);
  
}
