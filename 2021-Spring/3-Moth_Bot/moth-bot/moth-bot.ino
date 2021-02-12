#define PIN_MOTOR_LEFT_F 10
#define PIN_MOTOR_LEFT_R 11
#define PIN_MOTOR_RIGHT_F 5
#define PIN_MOTOR_RIGHT_R 6

#define PIN_PHORES_RIGHT A1
#define PIN_PHORES_LEFT A2

#define MIN_LIGHT_LEVEL 0
#define MAX_LIGHT_LEVEL 800
#define LIGHT_DIFF_THRESH 100

#define MIN_SPEED 20
#define MAX_TURN 255

void setup() {
  pinMode(PIN_PHORES_RIGHT, INPUT);
  pinMode(PIN_PHORES_LEFT, INPUT);

  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(2)) {
    setDrive(0,0);
    return;
  }
  
  int photoLeft = analogRead(PIN_PHORES_LEFT);
  int photoRight = analogRead(PIN_PHORES_RIGHT);

  Serial.print(photoLeft);
  Serial.print('\t');
  Serial.print(photoRight);
  Serial.print('\t');

  int forwardPow = constrain(map((photoLeft + photoRight) / 2, MIN_LIGHT_LEVEL, MAX_LIGHT_LEVEL, 0, 255-MIN_SPEED), 0, 255-MIN_SPEED) + MIN_SPEED;
  int turningPow = constrain(map(photoLeft - photoRight, -300, 300, -MAX_TURN, MAX_TURN), -MAX_TURN, MAX_TURN);
  int v = forwardPow - (abs(turningPow) * forwardPow / 255) + forwardPow;
  int w = turningPow - (abs(forwardPow) * turningPow / 255) + turningPow;

  int l = (v-w)/2;
  int r = (v+w)/2;

  Serial.print(l);
  Serial.print('\t');
  Serial.print(r);
  Serial.print('\t');

  setDrive(l,r);
  delay(100);
  Serial.println();
}

//input: -255, 255
void setDrive(int left, int right) {
  if (left < 0) {
    analogWrite(PIN_MOTOR_LEFT_F, 0);
    analogWrite(PIN_MOTOR_LEFT_R, -left);
  } else {
    analogWrite(PIN_MOTOR_LEFT_F, left);
    analogWrite(PIN_MOTOR_LEFT_R, 0);
  }
  if (right < 0) {
    analogWrite(PIN_MOTOR_RIGHT_F, 0);
    analogWrite(PIN_MOTOR_RIGHT_R, -right);
  } else {
    analogWrite(PIN_MOTOR_RIGHT_F, right);
    analogWrite(PIN_MOTOR_RIGHT_R, 0);
  }
}
