#include <SoftwareSerial.h>

SoftwareSerial mp3(5, 6);
static uint8_t cmdbuf[8] = {0};

const int buttonPin = 2;  // Le bouton est connecté à la pin 2
int buttonState = 0;      // Variable pour lire l'état du bouton

void command(int8_t cmd, int16_t dat)
{
  // ... (même code que précédemment pour la fonction command)
}

void setup()
{
  // ... (même code que précédemment pour la fonction setup)

  pinMode(buttonPin, INPUT_PULLUP); // Configure la pin du bouton comme entrée avec résistance de tirage interne activée
}

void loop() {
  buttonState = digitalRead(buttonPin); // Lit l'état du bouton

  // Vérifie si le bouton est pressé
  // Si l'état du bouton est LOW, le bouton est pressé (avec résistance de tirage interne activée)
  if (buttonState == LOW) {
    command(0x01, 0); // Commande pour passer à la piste suivante
    delay(500); // Délai pour éviter les rebonds du bouton
  }
}
