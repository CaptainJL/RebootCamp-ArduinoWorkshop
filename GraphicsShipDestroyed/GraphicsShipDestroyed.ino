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

void setup() {
  // put your setup code here, to run once:
  DigitShield.begin();
  matrix.begin();
  matrix.setBrightness(40);
  DigitShield.setValue(7777);
}

void loop() {

  // Explosion graphics
  for (int i = 0; i < 5; i++) {
    matrix.fillScreen(0);
    matrix.fillCircle(4, 4, i, RED);
    matrix.show();
    delay(500);
  }
  
  // Blink score counter
  for (int j = 0; j < 3; j++) {
    DigitShield.setBlank(true);     
    delay(250);    
    DigitShield.setBlank(false);     
    delay(250);     
  } 
  delay(1000); 
}
