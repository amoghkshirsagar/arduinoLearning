#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  startUpOled();
  delay(2000);
}

void loop() 
{
  printOled(31.1416);    // Draw 'stylized' characters
}

void startUpOled() 
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Initializing Radar..."));
  display.display();
  delay(2000);
}
void printOled(float distance) 
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Distance:"));
  display.println(F(""));

  //(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.setTextSize(2);             // Draw 2X-scale text
  display.print(distance, 3); //6-digit after decimal point
  display.print(F(" CM"));

  display.display();
  delay(2000);
}