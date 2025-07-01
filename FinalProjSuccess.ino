#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#define BUTTON_FLAP 16
#define BUTTON_RESET 17


#include "bird01.c"

MCUFRIEND_kbv tft;

#define YP A1
#define XM A2
#define YM 7
#define XP 6

#define TS_MINX 100
#define TS_MAXX 920
#define TS_MINY 70
#define TS_MAXY 900

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

bool gameStarted = false;
int score = 0;
int highestScore = 0;

int birdY = 145;
float fallRate = 0;
int fallRateInt = 0;
bool flapRequested = false;

int pillarX = SCREEN_WIDTH;
int pillarGapY = 100;
int pillarSpeed = 2;

//const int BUTTON_FLAP = 16;
//const int BUTTON_RESET = 17;

int buttonPressed = 0; // variables for reading the pushbutton status
int restartPressed = 0;
bool touched = false;
void setup() {
  pinMode(BUTTON_FLAP, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  
  highestScore = EEPROM.read(0);
  drawStartScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
 
  buttonPressed = (digitalRead(BUTTON_FLAP) == LOW); // Reading the state of the push button values 
  restartPressed = (digitalRead(BUTTON_RESET) == LOW);
  
  if (p.z > 300) touched = true;

  if(restartPressed & !gameStarted) {
     gameStarted = true;
     startGame();
     delay(100);
  }
  else if((restartPressed || buttonPressed)&& gameStarted) {
     flapRequested = true;
     delay(20);
  }
  if (gameStarted) {
      updateBird();
      delay(30);
  }
}

void drawStartScreen() {
  gameStarted = false;
  score = 0;
  birdY = 145;
  fallRate = 0;
  pillarX = SCREEN_WIDTH;
  pillarGapY = random(40, 200);
  
  tft.fillScreen(tft.color565(114, 198, 206));
  tft.fillRect(0, 285, 240, 10, tft.color565(47, 175, 68));
  tft.fillRect(0, 295, 240, 25, tft.color565(221, 216, 148));
  
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("High: ");
  tft.print(highestScore);
  
  tft.setCursor(30, 190);
  tft.print("PRESS TO START");
  
  drawBird(birdY);
}

void startGame() {
  score = 0;
  fallRate = 0;
  birdY = 145;
  pillarX = SCREEN_WIDTH;
  pillarGapY = random(40, 200);
    
  tft.fillScreen(tft.color565(114, 198, 206));
  tft.fillRect(0, 285, 240, 10, tft.color565(47, 175, 68));
  tft.fillRect(0, 295, 240, 25, tft.color565(221, 216, 148));
    
  drawBird(birdY);
  drawPillars(pillarX, pillarGapY);
  drawScore();
}

void updateBird() {
  tft.fillRect(50, birdY, 35, 30, tft.color565(114, 198, 206));
  
  if (buttonPressed == HIGH) {
    fallRate = -2.6;
    flapRequested = false;
  }
  
  fallRate += 0.4;
  fallRateInt = int(fallRate);
  birdY += fallRateInt;
  
  if (birdY < 0) birdY = 0;
    if (birdY > 280) {
      birdY = 280;
      gameOver();
      return;
    }
  
    pillarX -= pillarSpeed;
    if (pillarX < -30) {
      pillarX = SCREEN_WIDTH;
      pillarGapY = random(40, 200);
      score++;
    }
  
  bool birdHitsPillar =
  (pillarX < 85 && pillarX + 30 > 50) &&
  (birdY < pillarGapY || birdY > pillarGapY + 60);
  
  if (birdHitsPillar) {
    gameOver();
    return;
  }
  
  drawPillars(pillarX, pillarGapY);
  drawBird(birdY);
  drawScore();
}

void drawBird(int y) {
  uint16_t lineBuffer[35]; // one line of bird (35 pixels)
  
  for (int row = 0; row < 30; row++) {
    for (int col = 0; col < 35; col++) {
      lineBuffer[col] = pgm_read_word(&bird01[row * 35 + col]);
    }
    tft.setAddrWindow(50, y + row, 50 + 34, y + row); // draw one row
    tft.pushColors(lineBuffer, 35, 1);
  }
}

void drawPillars(int x, int gapY) {
  tft.fillRect(x + 31, 0, 10, 285, tft.color565(114, 198, 206));
  
  tft.fillRect(x, 0, 30, gapY, tft.color565(0, 200, 20));
  tft.drawRect(x, 0, 30, gapY, 0x0000);
  
  tft.fillRect(x, gapY + 60, 30, 285 - (gapY + 60), tft.color565(0, 200, 20));
  tft.drawRect(x, gapY + 60, 30, 285 - (gapY + 60), 0x0000);
}

void drawScore() {
  tft.fillRect(120, 295, 110, 20, tft.color565(221, 216, 148));
  tft.setTextColor(0x0000);
  tft.setCursor(120, 300);
  tft.setTextSize(2);
  tft.print("Score: ");
  tft.print(score);
}

void gameOver() {
  gameStarted = false;

  if (score > highestScore) {
    highestScore = score;
    EEPROM.update(0, highestScore);
  }

  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.setCursor(20, 130);
  tft.print("GAME OVER");

  tft.setCursor(10, 10);
  tft.print("High Score: ");
  tft.print(highestScore);

  tft.setCursor(20, 160);
  tft.print("Play Again? Push button");

  // Wait for user to press BUTTON_RESET again
  while (digitalRead(BUTTON_RESET) == HIGH); // wait for release
  while (digitalRead(BUTTON_RESET) == LOW);  // wait for press

  drawStartScreen(); // Restart the game screen
}
