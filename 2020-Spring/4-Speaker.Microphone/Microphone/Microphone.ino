#include <Tone.h>

int trigger = 7;
int echo = 5;

Tone player;

void setup() {
  Serial.begin(9600);
  player.begin(3);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

int beat = 0;
void loop() {

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  int duration = pulseIn(echo, HIGH);

  if (duration >= 0) {
    int note = duration/4;
    Serial.println(note);
    player.play(note);
  }
  delay(10);
}
