#include <Tone.h>

Tone player;

int notes[] = {NOTE_C5, NOTE_B4, NOTE_G4,  NOTE_C5, NOTE_B4, NOTE_E4,       0, NOTE_C5, NOTE_C4, NOTE_G4, NOTE_A4, NOTE_C5};
int beats[] = {     16,      16,      16,       8,       8,       16,      32,      16,      16,      16,       8,       8};

int bps = 32;

int beatDuration;
int songLength;
void setup() {
  Serial.begin(9600);
  player.begin(3);
  beatDuration = 1000/bps;
  songLength = sizeof(beats)/sizeof(beats[0]);
}

int beat = 0;
void loop() {
  Serial.print(notes[beat]);
  Serial.print(" ");
  Serial.println(beats[beat]);
  player.play(notes[beat],beats[beat]*beatDuration);
  delay(beats[beat]*beatDuration);
  beat = (beat + 1) % songLength;
}
