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
int analogX = 0;
int myx = 0;
int myxleft = 0;
int myxright = 0;
int myy = 0;
int score = 0;
int mscount = 0;
int gamespeed = 160;
int gamespeedchange = 10;
int ballx = 0;
int bally = 1;
int ballvx = 1;
int ballvy = 1;

// Change bat size to 1, 2, or 3 for difficulty setting.
int mysize = 3;

void setup() {
  // put your setup code here, to run once:
  DigitShield.begin();
  matrix.begin();
  matrix.setBrightness(40);
  randomSeed(analogRead(0));
  ballx = random(0, 7);
  ballvx = random(-1, 1);
  bally = 1;    
  ballvy = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  DigitShield.setValue(score);
  analogX = analogRead(PIN_ANALOG_X);
  myx = map(analogX, 0, 850, 6, 0);
  if (mysize == 3) {  // Bat size 3
    myxleft = myx - 1;
    myxright = myx + 1;
  }
  else if (mysize == 2) {  // Bat size 2
    myxleft = myx;
    myxright = myx + 1;
  }
  else if (mysize == 1) {  // Bat size 1
    myxleft = myx;
    myxright = myx;
  }
  else {  // Only allow bat sizes between 1 and 3
    mysize = 3;
    return;
  }
  

  // mscount states how many 'loops' will it take to create a new frame
  mscount++;

  if (mscount > gamespeed) {  // Create new frame
    mscount = 0;

    // Bounce ball off the walls
    if (ballvx > 0 && (ballx + 1) > 7) {
      ballvx = -ballvx;
    }
    else if (ballvx < 0 && (ballx - 1) < 0) {
      ballvx = -ballvx;
    }
    ballx = ballx + ballvx;

    // Bounce the ball off the roof
    if (ballvy > 0 && (bally + 1) > 7) {
      ballvy = -ballvy;
    }
    bally = bally + ballvy;

    if (ballvy < 0 && bally == 1) {
      // Check if ball is on top of the bat
      if (ballx <= myxright && ballx >= myxleft) {  
        // If the bat is only 1 pixel size, bounce the ball normally
        if (mysize == 1) {  
          
        }
        // If on the right of the bat, bounce the ball right
        if (ballx == myxright) {  
          ballvx = 1;
        }
        // If on the left of the bat, bounce the ball left
        else if (ballx == myxleft) {  
          ballvx = -1;
        }
        else {  // If in the middle of the bat, bounce normally
          
        }        
        ballvy = -ballvy;   
        score++;      
        gamespeed = gamespeed - gamespeedchange;       
      }      
    }
    else if (bally < 1) {   // Ball missed the bat. Game over!
      score = 0;
      gamespeed = 160; 
      ballx = random(0, 7);
      ballvx = random(-1, 1);
      bally = 1;    
      ballvy = 1;
    }
  }
  
  if (score == 15) {    // WIN!
    matrix.fillScreen(0);
    gamespeed = 160;
    score = 0;
    ballx = random(0, 7);
    ballvx = random(-1, 1);
    bally = 1;    
    ballvy = 1;
  }

  matrix.fillScreen(0);
  matrix.drawPixel(myx,myy, BLUE);
  matrix.drawPixel(myxright,myy, BLUE);
  matrix.drawPixel(myxleft,myy, BLUE);
  matrix.drawPixel(ballx,bally, RED);
  matrix.show();
}
