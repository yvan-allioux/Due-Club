
// Led stick
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

// Led Bar
#include <Grove_LED_Bar.h>

// Led stick
#define PIN 5
#define NUMPIXELS 10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Led Bar
Grove_LED_Bar bar(7, 6, 0); // Clock pin, Data pin, Orientation

// Led
#define LED_RED 2
#define LED_GREEN 3
#define LED_BLUE 4
#define LED_WHITE 8

int leds[] = {LED_RED, LED_GREEN, LED_BLUE, LED_WHITE};
int numLeds = sizeof(leds) / sizeof(leds[0]);
int barValue = 1;
void setup()
{

// Led Stick
#if defined(__AVR_ATtiny85__)
    if (F_CPU == 16000000)
        clock_prescale_set(clock_div_1);
#endif
    pixels.begin();

    // Led Bar
    Serial.begin(9600);
    Serial2.begin(9600); // Utiliser Serial2 pour la communication avec le téléphone (RX2, TX2)
    bar.begin();

    // Led
    for (int i = 0; i < numLeds; i++)
    {
        pinMode(leds[i], OUTPUT);
    }
}

void loop()
{
    // Check for commands received on RX2
    if (Serial2.available())
    {
        char command = Serial2.read();
        handleCommand(command);
    }

    // Set the LED bar based on the loudness
    bar.setBits((1 << barValue) - 1);

    // Led Stick
    // Set the color based on the current iteration
    int red = random(256);
    int green = random(256);
    int blue = random(256);

    pixels.setBrightness(random(5, 5 + (25 * barValue)));

    // Set the color based on random values
    pixels.setPixelColor(random(NUMPIXELS), pixels.Color(red, green, blue));
    pixels.show();
}

// Function to handle commands received on RX2
void handleCommand(char command)
{
    switch (command)
    {
    case 'B':
        // Éteindre tout
        for (int i = 0; i < numLeds; i++)
        {
            digitalWrite(leds[i], LOW);
        }
        bar.setBits(0);

        break;
    case 'A':
        // Allumer tout
        for (int i = 0; i < numLeds; i++)
        {
            digitalWrite(leds[i], HIGH);
        }
        break;
    case 'C':
        // Allumer tout
        if (barValue < 10)
        {
            barValue = barValue + 1;

            if (barValue < 3)
            {
                Serial.println("Silencieux");
                Serial2.write("1");
            }
            else if (barValue < 6)
            {
                Serial.println("Modéré");
                Serial2.write("2");
            }
            else
            {
                Serial.println("Bruyant");
                Serial2.write("3");
            }
        }
        else
        {
            Serial.println("Maximum");
            Serial2.write("4");
        }
        break;
    case 'D':
        // Allumer tout
        if (barValue > 1)
        {
            barValue = barValue - 1;

            if (barValue < 3)
            {
                Serial.println("Silencieux");
                Serial2.write("1");
            }
            else if (barValue < 6)
            {
                Serial.println("Modéré");
                Serial2.write("2");
            }
            else
            {
                Serial.println("Bruyant");
                Serial2.write("3");
            }
        }
        else
        {
            Serial.println("Minimum");
            Serial2.write("0");
        }
        break;
        // Ajoutez d'autres cas pour d'autres commandes au besoin
    }
}