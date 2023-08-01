#include <DigitShield.h>
#include <Adafruit_NeoMatrix.h>

#define PIN 11

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(204, 0, 204), matrix.Color(204, 204, 0), matrix.Color(0, 255, 255),
  matrix.Color(255, 10, 127), matrix.Color(127, 0, 255), matrix.Color(0, 255, 0),
  matrix.Color(255, 99, 255)};

int x = matrix.width();
int pass = 0;
int testDigitVal = 0;

void setup() {
  // put your setup code here, to run once:
  DigitShield.begin();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}

void loop() {
  // put your main code here, to run repeatedly:
  DigitShield.setValue(testDigitVal);
  matrix.fillScreen(0);    //Turn off all the LEDs
  matrix.setCursor(x, 0);
  matrix.print(F("GOD is KING!"));

  if( --x < -110 ) {
    x = matrix.width();

    if(++pass >= 8) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  testDigitVal = testDigitVal + 1;
  if (testDigitVal > 9999)
  {
    testDigitVal = 0;    
  }
  delay(250);  
}
