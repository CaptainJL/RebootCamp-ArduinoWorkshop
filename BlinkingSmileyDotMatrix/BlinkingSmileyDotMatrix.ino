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
  matrix.begin();
  matrix.setBrightness(40);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Normal happy face
  matrix.fillScreen(0);          // Turn off all the LEDs
  matrix.fillRect(1,5,2,2,RED);  // Left Eye
  matrix.fillRect(5,5,2,2,RED);  // Right Eye
  // Mouth
  matrix.drawLine(2,1,5,1,RED);  // Bottom of mouth
  matrix.drawPixel(0,3,RED);    
  matrix.drawPixel(1,2,RED);
  matrix.drawPixel(6,2,RED);
  matrix.drawPixel(7,3,RED);  
  matrix.show();
  delay(800);  

  // Winking happy face
  matrix.fillScreen(0);          // Turn off all the LEDs
  matrix.fillRect(1,5,2,2,RED);  // Left Eye
  matrix.drawLine(5,5,6,5,RED);  // Right Winking Eye
  // Mouth
  matrix.drawLine(2,1,5,1,RED);  // Bottom of mouth
  matrix.drawPixel(0,3,RED);
  matrix.drawPixel(1,2,RED);
  matrix.drawPixel(6,2,RED);
  matrix.drawPixel(7,3,RED);  
  matrix.show();
  delay(400); 
  
}
