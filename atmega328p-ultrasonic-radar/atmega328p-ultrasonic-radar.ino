#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "./servoMG90S.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int UNIT_PIN4 = 4;
int UNIT_STATUS = LOW;

int PING_12 = 12;
int ECHO_2 = 2;
int USPING_12status = LOW;
int TST_STATUS = HIGH;
int TST_STATUS2 = HIGH;
int duration = 0;
float distance = 0;
int angle = 180;
int pauseDur = 5000;
typedef void (*functiontype)();

int servoPin = 9;

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
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
  Serial.begin(9600);
  pinMode(UNIT_PIN4, INPUT);
  pinMode(PING_12, OUTPUT);
  pinMode(ECHO_2, INPUT);
  // Serial.println("in setup");
}

void loop()
{
  UNIT_STATUS = digitalRead(UNIT_PIN4);
  // Serial.println("in loop");
  // send :
  oscillate(angle, pauseDur, *getDistance);
  distance = getDistance();
  printOled(distance);    // Draw 'stylized' characters
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

float getDistance() {
    digitalWrite(PING_12, LOW);
  delay(2);
  digitalWrite(PING_12, HIGH);
  delay(10);
  digitalWrite(PING_12, LOW);

  // Read echo pulse
  digitalRead(ECHO_2);

  duration = pulseIn(ECHO_2, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
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
  display.print(distance, 2); //6-digit after decimal point
  display.print(F(" CM"));
  Serial.println(distance);

  display.println(F(""));
  display.println(F(""));
  display.print(distance/2.54, 2); //6-digit after decimal point
  display.print(F(" IN"));
  display.display();
  // delay(2000);
}