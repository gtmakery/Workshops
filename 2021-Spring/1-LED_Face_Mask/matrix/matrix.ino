#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define LOOP_DELAY 5

#define WIDTH 8
#define HEIGHT 8
#define PIN_NEOMATRIX 2

#define PIN_MIC A4
#define HISTORY_LENGTH 2
#define MIN_VOLUME 80
#define MAX_VOLUME 750
#define NUM_MIC_STATES 4
#define SMILE_DELAY 500

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, PIN_NEOMATRIX,
  NEO_MATRIX_BOTTOM  + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

long volumeHistory[HISTORY_LENGTH];
int nextVolumeIndex = 0;
long lastSpeak = 0;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  for (int i = 0; i < HISTORY_LENGTH; i++) {
    volumeHistory[i] = 0;
  }
}

long readMic() {
  long sum = 0;
  for(int i=0; i<100; i++) {
    sum += analogRead(PIN_MIC);
  }
  return sum / 100;
}

long movingMicAverage() {
  volumeHistory[nextVolumeIndex] = readMic();
  nextVolumeIndex = (nextVolumeIndex + 1) % HISTORY_LENGTH;
  long avg = 0;
  for (int i = 0; i < HISTORY_LENGTH; i++) {
    avg += volumeHistory[i];
  }
  return avg / HISTORY_LENGTH;
}

int getVolumeInterval(long micLevel) {
  return min((int) ((micLevel - MIN_VOLUME) * (NUM_MIC_STATES - 1) / (MAX_VOLUME - MIN_VOLUME) ), NUM_MIC_STATES - 1);
}

void drawMouth(int openness) {
  matrix.fillScreen(0);
  for (int i = 0; i < WIDTH/2; i++) {
    int y = min(i, openness);
    matrix.drawPixel(i,HEIGHT/2-1-y,matrix.Color(0,0,255));
    matrix.drawPixel(WIDTH - 1 - i,HEIGHT/2-1-y,matrix.Color(0,0,255));
    matrix.drawPixel(i,HEIGHT/2+y,matrix.Color(0,0,255));
    matrix.drawPixel(WIDTH -1 - i,HEIGHT/2+y,matrix.Color(0,0,255));
  }
  matrix.show();
}

void drawSmile() {
  matrix.fillScreen(0);
  for (int i = 0; i < WIDTH/2; i++) {
    int y = min(i, 2);
    matrix.drawPixel(i,HEIGHT/2-1-y+2,matrix.Color(0,0,255));
    matrix.drawPixel(WIDTH -1 - i,HEIGHT/2-1-y+2,matrix.Color(0,0,255));
    matrix.drawPixel(i,HEIGHT/2-1-y+1,matrix.Color(0,0,255));
    matrix.drawPixel(WIDTH -1 - i,HEIGHT/2-1-y+1,matrix.Color(0,0,255));
  }
  matrix.show();
}

void loop() {
  long micLevel = movingMicAverage();
//  Serial.print(micLevel);
  int micState = getVolumeInterval(micLevel);
//  Serial.print("\t");
//  Serial.println(micState);
  

  long currTime = millis();
  if (micState > 0) {
    lastSpeak = currTime;
    drawMouth(micState);
  } else if (currTime - lastSpeak > SMILE_DELAY) {
    drawSmile();
  } else {
    drawMouth(micState);
  }
  
  delay(LOOP_DELAY);
}
