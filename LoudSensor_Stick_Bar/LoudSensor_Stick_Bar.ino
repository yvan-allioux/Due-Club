// Led stick
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

// Led Bar
#include <Grove_LED_Bar.h>

// Led stick
#define PIN_LED_STICK 5
#define NUMPIXELS 10

Adafruit_NeoPixel led_stick = Adafruit_NeoPixel(NUMPIXELS, PIN_LED_STICK, NEO_GRB + NEO_KHZ800);

// Led Bar
Grove_LED_Bar led_bar(7, 6, 0); // Clock pin, Data pin, Orientation
int led_bar_value = 1;

// Led
#define LED_RED 2
#define LED_GREEN 3
#define LED_BLUE 4
#define LED_WHITE 8

int leds[] = {LED_RED, LED_GREEN, LED_BLUE, LED_WHITE};
int led_length = sizeof(leds) / sizeof(leds[0]);

void setup()
{

// Led Stick
#if defined(__AVR_ATtiny85__)
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
  Serial2.begin(9600); // Communication with Phone
  
  // Led Stick
  led_stick.begin();
  
  // Led Bar
  led_bar.begin();

  // Led
  for (int i = 0; i < led_length; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  // Get Phone commands
  if (Serial2.available())
  {
    char command = Serial2.read(); // Get Phone commands
    handleCommand(command);       // Handle Phone commands
  }

  // Set the LED bar based on the loudness
  led_bar.setBits((1 << led_bar_value) - 1);

  // Led Stick
  // Set the color based on the current iteration
  int red = random(256);
  int green = random(256);
  int blue = random(256);
  // Set the brightness based on the loudness
  led_stick.setBrightness(random(5, 5 + (25 * led_bar_value)));
  // Set the color based on random values
  led_stick.setPixelColor(random(NUMPIXELS), led_stick.Color(red, green, blue));
  led_stick.show();
}

// Function to handle commands received on Phone
void handleCommand(char command)
{
  switch (command)
  {
  case 'B':
    // Turn off all leds
    for (int i = 0; i < led_length; i++)
    {
      digitalWrite(leds[i], LOW);
    }
    break;
  case 'A':
    // Turn on all leds
    for (int i = 0; i < led_length; i++)
    {
      digitalWrite(leds[i], HIGH);
    }
    break;
  case 'C':
    // Increase light level
    if (led_bar_value < 10) // 10 is the maximum
    {
      led_bar_value = led_bar_value + 1;
      level();
    }
    else // Maximum reached
    {
      Serial2.write("4"); // Send 4 to master
    }
    break;
  case 'D':
    // Decrease light level
    if (led_bar_value > 0) // 0 is the minimum
    {
      led_bar_value = led_bar_value - 1;
      level();
    }
    else // Minimum reached
    {
      Serial2.write("0"); // Send 0 to master
    }
    break;
  }
}

void level()
{
  if (led_bar_value < 3)
  {
    Serial2.write("1"); // Send 1 to master
  }
  else if (led_bar_value < 6)
  {
    Serial2.write("2"); // Send 2 to master
  }
  else
  {
    Serial2.write("3"); // Send 3 to master
  }
}