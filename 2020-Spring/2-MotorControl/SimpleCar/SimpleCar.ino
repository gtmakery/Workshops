#define PIN_POT A0

#define PIN_GO_BTN 2


#define PIN_L_MTR_FWD 10
#define PIN_L_MTR_REV 11
#define PIN_R_MTR_FWD 5
#define PIN_R_MTR_REV 6



void setupButtons() {
  pinMode(PIN_GO_BTN, INPUT_PULLUP);
}

bool btnGo() {
  return digitalRead(PIN_GO_BTN) != HIGH;
}


void setupPotentiometer() {
  pinMode(PIN_POT, INPUT);
}


//range: 0-1023
bool potentiometerDebug = true;
int readPot() {
  int pot_angle = analogRead(PIN_POT);
  if (potentiometerDebug) {
    printPotentiometerData(pot_angle);
  }
  return pot_angle;
}
void printPotentiometerData(int pot_angle) {
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
    Serial.println("GO!");
    int choice = readPot() * 3 / 1023;
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
  delay(50);
}

//drive in a line
void line() {
  Serial.println("line");
  setDrive(255, 255);
  delay(1000);
  setDrive(0, 0);
}

//drive in a square
void square() {
  Serial.println("square");
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
  Serial.println("circle");
  setDrive(255, 220);
  delay(2000);
  setDrive(0, 0);
}

//input: -255, 255
void setDrive(int left, int right) {
  if (left < 0) {
    analogWrite(PIN_L_MTR_FWD, 0);
    analogWrite(PIN_L_MTR_REV, -left);
  } else {
    analogWrite(PIN_L_MTR_FWD, left);
    analogWrite(PIN_L_MTR_REV, 0);
  }
  if (right < 0) {
    analogWrite(PIN_R_MTR_FWD, 0);
    analogWrite(PIN_R_MTR_REV, -right);
  } else {
    analogWrite(PIN_R_MTR_FWD, right);
    analogWrite(PIN_R_MTR_REV, 0);
  }
}
