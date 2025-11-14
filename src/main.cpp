#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include <Wire.h>
#include <ZE7_CO.h>

#define LED_Pin D2
#define read_flag_Pin D1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NEOPIXEL_PIN 2
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int testConcentration = 0;         // Simulated CO concentration for testing
int graphData[SCREEN_WIDTH] = {0}; // Graph data array

HardwareSerial COSerial(0);

ZE7_CO ZE7_CO(&COSerial);

unsigned long previousMillis = 0;
unsigned long currentMillis;

float concentration = 0; // CO concentration in ppm.
bool read_flag = false;  // Toggles when UART data is received
bool last_read_flag;

void updateNeopixels(int concentration);
void updateDisplay(int concentration);
void Print_Concentration();

void setup()
{
  // Initialize Serial for debugging
  Serial.begin(9600);
  COSerial.begin(9600);
  ZE7_CO.beginMode1();
  Serial.println("Carbon Monoxide Detector/Decorative Night Light\nZurain Nazir | E: nazirzurain@gmail.com\nDec. 2024");

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.display();

  // Initialize Neopixels
  pixels.begin();
  pixels.clear();
}

void loop()
{
  // Simulate test concentration (replace this with actual sensor data)
  testConcentration = random(0, 150);
  ZE7_CO.updateMode1_data(concentration, read_flag);

  // Update the OLED display
  // updateDisplay(testConcentration);
  updateDisplay(concentration);

  // Update the Neopixel LEDs
  // updateNeopixels(testConcentration);
  updateNeopixels(concentration);
  Print_Concentration();

  delay(1000); // Wait for 1 second
}

void updateDisplay(int concentration)
{
  // Shift graph data to the left
  for (int i = 0; i < SCREEN_WIDTH - 1; i++)
  {
    graphData[i] = graphData[i + 1];
  }
  // Add new data to the graph
  graphData[SCREEN_WIDTH - 1] = map(concentration, 0, 150, 0, SCREEN_HEIGHT);

  // Clear the display
  display.clearDisplay();

  // Display text
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("CO Concentration: "));
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(concentration);
  display.print(F(" ppm"));

  // Draw the graph
  for (int x = 0; x < SCREEN_WIDTH; x++)
  {
    int y = SCREEN_HEIGHT - graphData[x];
    display.drawPixel(x, y, SSD1306_WHITE);
  }

  display.display();
}

void updateNeopixels(int concentration)
{
  uint32_t color;

  if (concentration <= 50)
  {
    color = pixels.Color(0, 255, 0); // Green
  }
  else if (concentration <= 100)
  {
    color = pixels.Color(255, 255, 0); // Yellow
  }
  else
  {
    color = pixels.Color(255, 0, 0); // Red
  }

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void Print_Concentration()
{
  if (read_flag != last_read_flag)
  {
    last_read_flag = read_flag;

    // Print data
    Serial.println("UARTI/O Mode1 Concentration Level:");
    Serial.print(concentration, 1);
    Serial.println(" ppm CO");
    Serial.println("-------------------------------------");
    Serial.println("");
  }
}