int pin_colorChannelButton = 6;
int pin_colorAddButton = 7;

int pin_potentiometer = A0;

int pin_LEDred = 2;
int pin_LEDgreen = 3;
int pin_LEDblue = 4;


void setupButtons() {
  pinMode(pin_colorChannelButton, INPUT_PULLUP);
  pinMode(pin_colorAddButton, INPUT_PULLUP);
}

void setupPotentiometer() {
  pinMode(pin_potentiometer, INPUT);
}

void setupLED() {
  pinMode(pin_LEDred, OUTPUT);
  pinMode(pin_LEDgreen, OUTPUT);
  pinMode(pin_LEDblue, OUTPUT);
}

bool btn_colorChannel() {
  return digitalRead(pin_colorChannelButton) != HIGH;
}
bool btn_colorAdd() {
  return digitalRead(pin_colorAddButton) != HIGH;
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



int colors[5][3];
int displayIndex;
int colorIndex;
bool editingColor;

int rgbIndex;
int currColor[3];
void setup() {
  Serial.begin(9600);
  //setup inputs
  setupButtons();
  setupPotentiometer();
  //setup outputs
  setupLED();

  //other setup code
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      colors[i][j] = 0;
    }
  }
}


void loop() {
  if (btn_colorChannel()) {
    while(btn_colorChannel()) {}
    if (!editingColor) {
      rgbIndex = 0;
      currColor[0] = 0;
      currColor[1] = 0;
      currColor[2] = 0;
      editingColor = true;
    } else {
      rgbIndex = (rgbIndex+1)%3;
    }
  }
  
  if (btn_colorAdd()) {
    while(btn_colorAdd()) {}
    if (editingColor) {
      for (int i = 0; i<3; i++) {
        colors[colorIndex][i] = currColor[i];
      }
      editingColor = false;
      colorIndex = (colorIndex + 1) % 5;
    }
  }

  if (editingColor) {
    potentiometer();
    currColor[rgbIndex] = map(pot_angle, 0, 1023, 0, 255);
    setLED(currColor);
  } else {
    setLED(colors[displayIndex++]);
    displayIndex %= colorIndex;
    delay(500);
  }

  
}

void setLED(int color[]) {
  int red = color[0], green = color[1], blue = color[2];
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(pin_LEDred, red);
  analogWrite(pin_LEDgreen, green);
  analogWrite(pin_LEDblue, blue);  
}
