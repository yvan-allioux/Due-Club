
// Led stick
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Led Bar
#include <Grove_LED_Bar.h>


// Led stick
#define PIN            5
#define NUMPIXELS      10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Led Bar
Grove_LED_Bar bar(7, 6, 0); // Clock pin, Data pin, Orientation
int loudness;

// Led
#define LED_RED 2
#define LED_GREEN 3
#define LED_BLUE 4
#define LED_WHITE 8

int leds[] = {LED_RED, LED_GREEN, LED_BLUE, LED_WHITE};
int numLeds = sizeof(leds) / sizeof(leds[0]);


void setup() {
  
  // Led Stick
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  pixels.begin();
    
  // Led Bar
  Serial.begin(9600);
  bar.begin();

  // Led
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  
  // Led Bar
  loudness = analogRead(0);

  // Map the loudness value to the LED bar range (0 to 10)
  int barValue = map(loudness, 0, 400, 0, 10);

  // Set the LED bar based on the loudness
  bar.setBits((1 << barValue) - 1);
  
  if(barValue < 3)
    Serial.println("Silencieux");
  else if(barValue < 6)
    Serial.println("Modéré");
  else
    Serial.println("Bruyant");


  // Led Stick
  // Set the color based on the current iteration
  int red = random(256);
  int green = random(256);
  int blue = random(256);

  pixels.setBrightness(random(5,5+(25*barValue)));

  // Set the color based on random values
  pixels.setPixelColor(random(NUMPIXELS), pixels.Color(red, green, blue));    pixels.show();

  //Led
  for (int i = 0; i < numLeds; i++) {
    // Allumer la LED actuelle
    digitalWrite(leds[i], HIGH);
    
    // Attendre un délai aléatoire entre 100 et 500 ms
    delay(50);

    // Éteindre la LED actuelle
    digitalWrite(leds[i], LOW);
  }
}
