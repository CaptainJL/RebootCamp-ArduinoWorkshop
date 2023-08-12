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
int myx = 0;
int myy = 7;
int score = 0;
int enemyx = 0;
int enemyy = 0;
int mscount = 0;
int bulletx = 10;
int bullety = 10;
int firebutton = 0;
int gamespeed = 80;

void setup() {
//  pinMode(buzzerPin, OUTPUT);
  DigitShield.begin();
  matrix.begin();
  matrix.setBrightness(40);
}

void loop() {
  DigitShield.setValue(score);
  myx = analogRead(PIN_ANALOG_X);
  myx = map(myx, 0, 900, 7, 0);
  firebutton = digitalRead(A1);

  // When Shooting
  if (firebutton == 1) {
    bulletx = myx;
    bullety = myy-2;
  }

  // mscount states how many 'loops' will it take to create a new frame
  mscount++;

  if (mscount > gamespeed) {  // Create new frame
    mscount = 0;
    enemyx++;
    bullety--;
  }

  if (bulletx == enemyx && bullety == enemyy) {  // When hitting enemy
    score++;
    enemyy = 0;
    enemyx = 0;
    bullety = -1;               // Make bullet dissapear  
    gamespeed = gamespeed - 10; // Make it faster
  }

  // When enemy gets to the edge of the screen
  if (enemyx > 7){
    enemyx = 0;
    enemyy++;
  }

  if (enemyy >= 6){   // Lose a point
    enemyy = 0;
    score--;
    gamespeed = gamespeed + 10;
  }

  if (score < 0){     // Game over
    score = 0;
    gamespeed = 80;    
  }

  if (score == 5){    // WIN!
    matrix.fillScreen(0);
    gamespeed = 80;
    score = 0;
  }

  matrix.fillScreen(0);
  matrix.drawPixel(myx,myy, BLUE);
  matrix.drawPixel(myx+1,myy, BLUE);
  matrix.drawPixel(myx-1,myy, BLUE);
  matrix.drawPixel(myx,myy-1, BLUE);
  matrix.drawPixel(enemyx,enemyy, RED);
  matrix.drawPixel(bulletx,bullety, YELLOW);
  matrix.show();

}
