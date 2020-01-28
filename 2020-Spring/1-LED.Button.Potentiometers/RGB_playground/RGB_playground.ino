#define PIN_COLOR_CHANNEL_BUTTON 6
#define PIN_COLOR_ADD_BUTTON 7

#define pin_potentiometer A0

#define COMMON_ANODE 1
#define PIN_LED_RED 10
#define PIN_LED_GREEN 3
#define PIN_LED_BLUE 11


void setupButtons() {
  pinMode(PIN_COLOR_CHANNEL_BUTTON, INPUT_PULLUP);
  pinMode(PIN_COLOR_ADD_BUTTON, INPUT_PULLUP);
}

void setupPotentiometer() {
  pinMode(pin_potentiometer, INPUT);
}

void setupLED() {
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
}

bool btn_colorChannel() {
  return digitalRead(PIN_COLOR_CHANNEL_BUTTON) != HIGH;
}
bool btn_colorAdd() {
  return digitalRead(PIN_COLOR_ADD_BUTTON) != HIGH;
}

//range: 0-1023
bool potentiometerDebug = true;
int readPot() {
  int pot_angle = analogRead(pin_potentiometer);
  if (potentiometerDebug) {
    printPotentiometerData(pot_angle);
  }
  return pot_angle;
}
void printPotentiometerData(int pot_angle) {
  Serial.println(pot_angle);
}



unsigned char colors[5][3];
int displayIndex = 0;
int colorIndex = 0;
bool editingColor = false;

int rgbIndex = 0;
unsigned char currColor[3] = {0, 0, 0};
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

int t = 0;
void loop() {
  if (btn_colorChannel()) {
    Serial.print("EDIT PRESSED");
    while(btn_colorChannel()) {}
    if (!editingColor) {
      rgbIndex = 0;
      currColor[0] = 0;
      currColor[1] = 0;
      currColor[2] = 0;
      editingColor = true;
      Serial.println(" begin");
    } else {
      rgbIndex = (rgbIndex+1)%3;
      Serial.println(rgbIndex);
    }
  }
  
  if (btn_colorAdd()) {
    Serial.print("ADD PRESSED");
    while(btn_colorAdd()) {}
    if (editingColor) {
      for (int i = 0; i<3; i++) {
        colors[colorIndex][i] = currColor[i];
      }
      editingColor = false;
      t = 0;
      colorIndex = (colorIndex + 1) % 5;
      Serial.println(colorIndex);
    } else {
      Serial.println("NONE");
    }
  }

  if (editingColor) {
    currColor[rgbIndex] = readPot() / 4;
    setLED(currColor);
  } else {
    setLED(colors[displayIndex]);
    if (t == 50) {
      displayIndex++;
      t = 0;
    }
    displayIndex %= colorIndex;
    if (colorIndex == 0) {
      displayIndex = 0;
    }
  }
  t++;
}

void setLED(unsigned char color[]) {
  unsigned char red = color[0], green = color[1], blue = color[2];
  Serial.print("SET LED: ");
  Serial.print(red);Serial.print(" ");
  Serial.print(green);Serial.print(" ");
  Serial.println(blue);
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(PIN_LED_RED, red);
  analogWrite(PIN_LED_GREEN, green);
  analogWrite(PIN_LED_BLUE, blue);  
}
