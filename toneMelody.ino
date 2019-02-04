int melody[] = {
  261, 293, 329, 349, 392, 440, 493, 523
};

int noteDuration = 500 
void setup() {
  
}

void loop() {
  
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      tone(8, melody[thisNote], noteDuration);
      delay(pauseBetweenNotes);
      noTone(8);
  }
  
}
