int pin_potentiometer = A0;

int pin_goButton = 2;


int pin_leftMotorForward = 10;
int pin_leftMotorReverse = 11;
int pin_rightMotorForward = 5;
int pin_rightMotorReverse = 6;



void setupButtons() {
  pinMode(pin_goButton, INPUT_PULLUP);
}

bool btnGo() {
  return digitalRead(pin_goButton) != HIGH;
}


void setupPotentiometer() {
  pinMode(pin_potentiometer, INPUT);
}

//range: 0-1023
int pot_angle;
bool potentiometerDebug = false;
void potentiometer() {
  pot_angle = analogRead(pin_potentiometer);
  if (potentiometerDebug) {
    printPotentiometerData();
  }
}
void printPotentiometerData() {
  Serial.println(pot_angle);
}



void setup() {
  Serial.begin(9600);
  //setup input
  setupButtons();
  setupPotentiometer();
}



void loop() {
  if (btnGo()) {
    while (btnGo()) {}
    potentiometer();
    int choice = pot_angle * 3 / 1023;
    switch(choice) {
      case 0:
        line();
        break;
      case 1:
        square();
        break;
      case 2:
      case 3:
        circle();
        break;
    }
  }
}

//drive in a line
void line() {
  setDrive(255, 255);
  delay(1000);
  setDrive(0, 0);
}

//drive in a square
void square() {
  line();
  setDrive(255, -255);
  delay(500);
  setDrive(0, 0);
  line();
  setDrive(255, -255);
  delay(500);
  setDrive(0, 0);
  line();
  setDrive(255, -255);
  delay(500);
  setDrive(0, 0);
  line();
  setDrive(255, -255);
  delay(500);
  setDrive(0, 0);
}

//drive in a circle
void circle() {
  setDrive(255, 100);
  delay(2000);
  setDrive(0, 0);
}

//input: -255, 255
void setDrive(int left, int right) {
  if (left < 0) {
    analogWrite(pin_leftMotorForward, 0);
    analogWrite(pin_leftMotorReverse, -left);
  } else {
    analogWrite(pin_leftMotorForward, left);
    analogWrite(pin_leftMotorReverse, 0);
  }
  if (right < 0) {
    analogWrite(pin_rightMotorForward, 0);
    analogWrite(pin_rightMotorReverse, -right);
  } else {
    analogWrite(pin_rightMotorForward, right);
    analogWrite(pin_rightMotorReverse, 0);
  }
}
