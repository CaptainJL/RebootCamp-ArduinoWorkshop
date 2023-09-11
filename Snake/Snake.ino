#include <DigitShield.h>
#include <Adafruit_NeoMatrix.h>

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 11,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_TILE_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

// Colours
int WHITE = matrix.Color(255,255,255);
int BLACK = matrix.Color(0,0,0);
int RED = matrix.Color(255,0,0);
int BLUE = matrix.Color(0,0,255);
int GREEN = matrix.Color(0,255,0);
int YELLOW = matrix.Color(255,255,0);
int AQUA = matrix.Color(0,255,255);
int PURPLE = matrix.Color(255,0,255);

const byte PIN_ANALOG_X = 3;
const byte PIN_ANALOG_Y = 2;

int mscount = 0;
int gamespeed = 120;

int dotx;
int doty;
int snakevx = 1;
int snakevy = 1;

void setup() {
  // put your setup code here, to run once:
  DigitShield.begin();
  matrix.begin();
  matrix.setBrightness(40);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  dotx = random(0, 7);
  doty = random(0, 7);
}

void loop() {
  // put your main code here, to run repeatedly:
  DigitShield.setValue(score);
  analogX = analogRead(PIN_ANALOG_X);
  analogY = analogRead(PIN_ANALOG_X);
  dotx = map(analogX, 0, 850, 1, -1);
  doty = map(analogY, 0, 850, 1, -1);

  mscount++;
  if (mscount > gamespeed) {  // Create new frame
    mscount = 0;

    
  }

}

void loop() {
  // put your main code here, to run repeatedly:



matrix.fillScreen(0);
  matrix.drawPixel(myx,myy, BLUE);
  matrix.drawPixel(myxright,myy, BLUE);
  matrix.drawPixel(myxleft,myy, BLUE);
  matrix.drawPixel(ballx,bally, RED);
}
