#include <LCD5110_Graph.h>

#define RST 12    // RESET
#define CE  13    // CS
#define DC  11    // Data/Command
#define DIN  10   // MOSI
#define CLK  9    // SCK

#define BUTTON_A  2 
#define BUTTON_B  3
#define BUTTON_C  4
#define BUTTON_D  5

LCD5110 myGLCD(CLK, DIN, DC, RST, CE); // LCD5110(SCK, MOSI, DC, RST, CS);

extern uint8_t SmallFont[];

int body[][2] = {
   {16, 10},
   {12, 10},
   {8, 10},
   {4, 10},
   {0, 10}
};

int x = 20;
int y = 10;

int lastX = 0;
int lastY = 0;


String direction = "Right";
const char title[] = "Snake";
const int width = 3;
const int height = 3;
const char over[] = "game over!";


void setup()
{
  /* Init LCD5110_Graph library */
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  randomSeed(analogRead(0));

  // Setup button inputs with internal pull up high resistor
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  /* Init Serial port */
  Serial.begin(115200);
}

void loop()
{

  //User input
  if (!digitalRead(BUTTON_B)) {
      direction = "Right";
  }
  
  if (!digitalRead(BUTTON_D)) {
      direction = "Left";
  }
  
  if (!digitalRead(BUTTON_A)) {
      direction = "Up";
  }

  if (!digitalRead(BUTTON_C)) {
      direction = "Down";
  }

  draw();
}


void draw()
{

  lastX = x;
  lastY = y;
  
  myGLCD.clrScr();

  myGLCD.print(String(lastX), CENTER, 10);
  //myGLCD.print(String(lastY), 10, 20);

  myGLCD.print(String(x), CENTER, 20);
  //myGLCD.print(String(y), CENTER, 20);

  if (x < 0) {
    x = 84 - width;
    myGLCD.print(over, CENTER, 50);
  }

  if (x > 84 - width) {
    x = 0;
  }

  if (y < 0) {
    y = 48 - height;
  }

  if (y > 48 - height) {
    y = 0;
  }

  //drawing body
  for (int i = 0; i < 6; i++) {
      myGLCD.drawRect(body[i][0], body[i][1], body[i][0] + width, body[i][1] + height); 
  }

  if (direction == "Right") {
      myGLCD.drawRect(x, y, x + width, y + height);
      x += 4;
  }

  if (direction == "Left") {
      myGLCD.drawRect(x, y, x + width, y + height);
      x -= 4;
  }

  if (direction == "Up") {
      myGLCD.drawRect(x, y, x + width, y + height);
      y -= 4;
  }

  if (direction == "Down") {
      myGLCD.drawRect(x, y, x + width, y + height);
      y += 4;
  }

  //updating body
  for (int j = 1; j < 6; j++) {
     body[j][0] = body[j - 1][0];
     body[j][1] = body[j - 1][1];
  }

  body[0][0] = lastX;
  body[0][1] = lastY;

  myGLCD.update();

  delay(150);
}
