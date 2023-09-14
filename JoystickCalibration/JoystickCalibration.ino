#include <Adafruit_NeoMatrix.h>

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 11,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_TILE_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

// Colours
int WHITE = matrix.Color(255,255,255);

const byte PIN_ANALOG_X = 3;
const byte PIN_ANALOG_Y = 2;
int analogX;
int analogY;
int myx;
int myy;
int dt = 0;

// Edit these
int scaleX = 900;
int scaleY = 900;

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(40);
  Serial.begin(9600);
  dt = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  // Get Joystick X and Y values
  analogX = analogRead(PIN_ANALOG_X);
  analogY = analogRead(PIN_ANALOG_Y);

  // Print X and Y values to Serial Monitor
  // But only once every second
  dt = dt + 1;
  if (dt > 20)
  {
    Serial.print("Joystick X = ");
    Serial.println(analogX);
    Serial.print("Joystick Y = ");
    Serial.println(analogY);
    dt = 0;
  }  

  // Change X and Y values to match scale 0 to 7
  myx = map(analogX, 0, scaleX, 7, 0);  
  myy = map(analogY, 0, scaleY, 0, 7);

  // Display the dot of where the joystick is pointing.
  matrix.fillScreen(0);
  matrix.drawPixel(myx,myy, WHITE);
  matrix.show();

  // Wait a short time before doing it again
  delay(50);  
}
