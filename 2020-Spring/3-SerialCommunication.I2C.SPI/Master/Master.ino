#include <Wire.h>

int pin_potentiometer = A0;

int pin_sendButton = 7;

void setupButtons() {
  pinMode(pin_sendButton, INPUT_PULLUP);
}

bool btnSend() {
  return digitalRead(pin_sendButton) != HIGH;
}


void setupPotentiometer() {
  pinMode(pin_potentiometer, INPUT);
}

//range: 0-1023
int pot_angle;
bool potentiometerDebug = true;
void potentiometer() {
  pot_angle = analogRead(pin_potentiometer);
  if (potentiometerDebug) {
    printPotentiometerData();
  }
}
void printPotentiometerData() {
  Serial.println(pot_angle);
}


void setupI2C() {
  Wire.begin();
}


void setup() {
  Serial.begin(9600);
  //setup input
  setupButtons();
  setupPotentiometer();
  //other setup
  setupI2C();
}


void loop()
{
  if (btnSend()) {
    while (btnSend()) {}
    potentiometer();
    int br = pot_angle / 4;
    byte brightness = br;
    Serial.println(brightness);
    Wire.beginTransmission(4);       // transmit to device #4
    Wire.write("x is ");             // sends five bytes
    Wire.write(brightness);  // sends one byte  
    Wire.endTransmission();          // stop transmitting
  }
}
