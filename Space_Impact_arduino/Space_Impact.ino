
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


static const unsigned char PROGMEM Hero[] =
{
  B11110000, B00000000,
  B00011101, B11000000,
  B00011101, B11100000,
  B00111111, B11111100,
  B00011101, B11100000,
  B00011101, B11000000,
  B11110000, B00000000,
};

static const unsigned char PROGMEM Bullet[] =
{
  B11111111,
};

static const unsigned char PROGMEM Alien[] =
{
  B01100000, B00111110,
  B10010010, B11110000,
  B00001111, B11111100,
  B00001111, B11111111,
  B00001111, B11111100,
  B10010010, B11110000,
  B01100000, B00111110,
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
}

void drawHero(int x, int y)    // draws the player at position x and position y
{
  display.drawBitmap(x, y, Hero, 14, 7, WHITE);
  display.display();
}

void drawBullet(int x, int y)  // draws the bullet at position x and position y
{
  display.drawBitmap(x, y, Bullet, 8, 1, WHITE);
  display.display();
}

void drawAlien(int x, int y)  // draws the alien at position x and position y
{
  display.drawBitmap(x, y, Alien, 15, 7, WHITE);
  display.display();
}


void loop()
{

  //display.drawBitmap(0, 20, Hero, 14, 7, WHITE);
  //display.drawBitmap(40,23, Bullet, 8, 1, WHITE);
  //display.drawBitmap(100, 20, Alien, 15, 7, WHITE);
  //display.display();
  int bytes [3] = {0, 0, 0};
  while (1)
  {
    bytes[0] = Serial.read();

    // Clears the display

    if (bytes[0] == 0)
    {
      display.clearDisplay();
    }

    // Creates the player

    else if (bytes[0] == 1)
    {
      bytes[1] = Serial.read();
      bytes[2] = Serial.read();

      drawHero(bytes[1], bytes[2]);
    }

    // Creates the Bullet

    else if (bytes[0] == 2)
    {
      bytes[1] = Serial.read();
      bytes[2] = Serial.read();

      drawBullet(bytes[1], bytes[2]);
    }

    // Creates the alien

    else if (bytes[0] == 3)
    {
      bytes[1] = Serial.read();
      bytes[2] = Serial.read();

      drawAlien(bytes[1], bytes[2]);
    }
  }
}
