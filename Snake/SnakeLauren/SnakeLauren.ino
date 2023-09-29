//written by Lauren Szmandiuk 2023 on Reboot

#include <DigitShield.h>
#include <Adafruit_NeoMatrix.h>
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 11,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_TILE_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);

// Colours
int WHITE = matrix.Color(255, 255, 255);
int BLACK = matrix.Color(0, 0, 0);
int RED = matrix.Color(255, 0, 0);
int BLUE = matrix.Color(0, 0, 255);
int GREEN = matrix.Color(0, 255, 0);
int YELLOW = matrix.Color(255, 255, 0);
int AQUA = matrix.Color(0, 255, 255);
int PURPLE = matrix.Color(255, 0, 255);


int score = 0;

int length = 1;

const byte PIN_ANALOG_X = 3;
const byte PIN_ANALOG_Y = 2;
int analogX;
int analogY;
//int myx;
//int myy;
int dt = 0;
// Edit these
int scaleX = 900;
int scaleY = 900;

int snakex = 0;
int snakey = 0;
int snakexv = 0;
int snakeyv = 0;

int spawnx;
int spawny;

String direction;


int matrixGrid[8][8]; 
/* 
0 = empty
-1 = dots 
anything above 0 = body parts 
*/

void setup() {
  // put your setup code here, to run once:
  DigitShield.begin();

  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(20);
  Serial.begin(9600);
  dt = 0;
  spawnDot();
}

void spawnDot() {
  spawnx = random(0, 8);
  spawny = random(0, 8);
  if (matrixGrid[spawnx][spawny] > 0){
    spawnDot();
  }
  else{
    matrixGrid[spawnx][spawny] = -1;
  }
  
}


void SnakeDotCollissionCheck() {
  if ((snakex == spawnx) && (snakey == spawny)) {
    score++;
    length++;
    spawnDot();
  }
}

void printAnalogInfo() {
  // Print X and Y values to Serial Monitor
  // But only once every second
  dt = dt + 1;
  if (dt > 20) {

    if (analogX > 800) {
      Serial.println("left");
    } else if (analogX < 300) {
      Serial.println("right");
    }

    if (analogY > 800) {
      Serial.println("up");
    } else if (analogY < 300) {
      Serial.println("down");
    }
    dt = 0;
  }
}

void mapJoystickInformation() {
  // Get Joystick X and Y values
  analogX = analogRead(PIN_ANALOG_X);
  analogY = analogRead(PIN_ANALOG_Y);

  if (analogX > 700) {
   

    if (direction != "right"){
      snakexv = -1;
      snakeyv = 0;
      direction = "left";
    }
  } 
  else if (analogX < 300) {
    if (direction != "left"){
      snakexv = 1;
      snakeyv = 0;
      direction = "right";
    }
  }

  if (analogY > 700) {
    if (direction != "down"){
      snakeyv = 1;
      snakexv = 0;
      direction = "up";
    }
  } else if (analogY < 300) {
    if (direction != "up"){
      snakeyv = -1;
      snakexv = 0;
      direction = "down";
    }
  }
}

void updateSnakePosition() {
  snakex += snakexv;
  snakey += snakeyv;

  if (snakex > 7) {
    snakex = 0;
  } else if (snakex < 0) {
    snakex = 7;
  }

  if (snakey > 7) {
    snakey = 0;
  } else if (snakey < 0) {
    snakey = 7;
  }

  if (matrixGrid[snakex][snakey] > 0){
    //game over
    gameOver();
  }
  else {
    matrixGrid[snakex][snakey] = length;
  }
}


void printGrid(){
  Serial.println("{");
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      Serial.print(matrixGrid[x][y]);
    }
    Serial.println("");
  }
  Serial.println("}");
}

void drawGrid(){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){

      if (matrixGrid[x][y] == 0){ //draws blank
        matrix.drawPixel(x, y, BLACK);
      }
      else if (matrixGrid[x][y] == -1){ //draws dots
        matrix.drawPixel(x, y, WHITE);
      }
      else if ((matrixGrid[x][y] == 1) || (matrixGrid[x][y] == 2)){ //draws dots
        matrix.drawPixel(x, y, YELLOW);
      }
      else { //draws snake body segments
        matrix.drawPixel(x, y, PURPLE);
      }
    }
  }
}

void gameOver(){
  eraseGrid();
  snakex = 0;
  snakey = 0;
  snakexv = 0;
  snakeyv = 0;
  length = 1;
  spawnDot();
  score = 0;

  matrix.fillRect(0,0,8,8,RED);
  matrix.show();
  delay(1000);
}

void eraseGrid(){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      matrixGrid[x][y] = 0;
    }
  }
}

void updateGrid(){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      if (matrixGrid[x][y] > 0){
        matrixGrid[x][y] --;
      }
    }
  }
}

void loop() {
  DigitShield.setValue(score);
  // put your main code here, to run repeatedly:
  mapJoystickInformation();   
  printAnalogInfo();

  // // Display the dot of where the joystick is pointing.
  matrix.fillScreen(0);
  // matrix.drawPixel(myx,myy, WHITE);
  // matrix.show();
  updateGrid();
  updateSnakePosition();
  //drawSnake();
  //drawDot();
  drawGrid();
  matrix.show();
  SnakeDotCollissionCheck();
  // Wait a short time before doing it again
  //printGrid();
  delay(100);
}
